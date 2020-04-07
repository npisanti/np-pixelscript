/*====================================================================

	pixelscript - little 2d graphics scripting playground
  
	Copyright (c) 2019 Nicola Pisanti <nicola@npisanti.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

====================================================================*/

#include "ofMain.h"

#include "ofAppNoWindow.h"  

#include "ofxOsc.h"

// macro for chdir() as Windows uses a protected variant
#ifdef TARGET_WIN32
	#include <direct.h>
	#define CHDIR _chdir
#else
	#define CHDIR chdir
#endif
#include <errno.h>
#include "bindings/px.h"
#include "bindings/cam.h"

#include "PixelScript.h"

class ofApp : public ofBaseApp{
public:
struct KeyEvent {
    int key;
    bool pressed;
};
    
// ---------- variables ----------------------------------------
bool bShowFrameRate;
bool bMirror;
np::PixelScript script;
std::string path;
ofxOscReceiver receiver;
int usecs;
int mwidth;
int mheight;
std::vector<KeyEvent> keyEvents;


//--------------------------------------------------------------
void setup(){
    
    ofSetWindowTitle( ":x:" );
    
    ofHideCursor();
    ofSetBackgroundAuto( true );
    
    ofBackground( 0 );
    bShowFrameRate = false;
    
    if( usecs > 0 ){
        script.headless( true, usecs );
        ofSetVerticalSync( false );
    }
    
    script.load( path );    
    
    keyEvents.reserve(128);

}

//--------------------------------------------------------------
void update(){
    
    script.update();
    
    // key event are executed after update so you can draw with them
    for ( size_t i=0; i<keyEvents.size(); ++i ){
        script.lua.scriptKeyPressed( keyEvents[i].key, keyEvents[i].pressed );
    }
    keyEvents.clear();
}

//--------------------------------------------------------------
void draw(){
    
    if( px::isRotated() ){     
        ofTranslate( ofGetWidth(), 0 );
        ofRotateDeg( 90 );
    }

    script.draw( 0, 0 );
    
    if(bShowFrameRate){
        std::string info = "fps = ";
        info += ofToString(ofGetFrameRate());
        ofSetColor(255);
        ofDrawBitmapString( info, 20, 20 );
        ofSetColor(0);
        ofDrawBitmapString( info, 20, 40 );
    }
}

//--------------------------------------------------------------
void drawSecondWindow(ofEventArgs& args){
    script.draw( 0, 0 );
}
//--------------------------------------------------------------
void keyPressed(int key){
    switch( key ){    
        case 'f': bShowFrameRate = !bShowFrameRate; break;
    }
    
    keyEvents.emplace_back();
    keyEvents.back().key = key;
    keyEvents.back().pressed = true;
}

//--------------------------------------------------------------
void keyReleased(int key){
    keyEvents.emplace_back();
    keyEvents.back().key = key;
    keyEvents.back().pressed = false;
}

//--------------------------------------------------------------
void exit(){
    cam::_close();
}

//--------------------------------------------------------------
void mousePressed(int x, int y, int button){}
void mouseDragged(int x, int y, int button){}
void mouseReleased(int x, int y, int button){}
void mouseMoved(int x, int y){}
void mouseEntered(int x, int y){}
void mouseExited(int x, int y){}
void windowResized(int w, int h){}
void gotMessage(ofMessage msg){}
void dragEvent(ofDragInfo dragInfo){ }
//--------------------------------------------------------------

}; // class ofApp

int main( int argc, char *argv[] ){

    if( argc>1 ){		

        std::string path = std::string( argv[1] );
        
        if( ! ofFilePath::isAbsolute( path )){
            path = ofFilePath::getCurrentWorkingDirectory() + "/" + path;
        }
        
        std::string ext = ofFilePath::getFileExt( path );
        
        bool found_main = false;
        
        if( ext!="lua" ){
            path = ofFilePath::removeTrailingSlash( path );
            path += "/main.lua";
            ofFile file( path );
            if( file.exists() ){
                found_main = true;
                std::cout<<"[ pixelscript ] found main.lua in given folder\n";
            }
        }
        
        if( ext == "lua" || found_main ){

            std::string folder = ofFilePath::getEnclosingDirectory(path);
            
            // it's needed for relative shaders 
            if( CHDIR(folder.c_str()) < 0 ) {
                switch(errno) {
                    case ENOENT:
                        ofLogError("[ pixelscript ]") << "Script dir \"" << folder << "\" does not exist";
                        break;
                    case EACCES:
                        ofLogError("[ pixelscript ]") << "Could not access script dir \"" << folder << "\"";
                        break;
                    default:
                        ofLogError("[ pixelscript ]") << "Could not change to script dir \"" << folder << "\", error " << errno;
                        break;
                }
            }
            
            shared_ptr<ofApp> app(new ofApp);
            int width = 480;
            int height = 480;
            int px = -1;
            int py = -1;
            app->path = path;
            app->usecs = -1;
            app->bMirror = false;
            bool decorated = true;
            
            for( int i=1; i<argc; ++i ){
                std::string cmd = std::string( argv[i] );

                if( cmd == "--no-decoration" || cmd == "-nd" ){
                    decorated = false;   
                }

                if( cmd == "--size" || cmd == "-s" ){
                    if( i+1 < argc ){
                        // split by 'x'
                        auto splits = ofSplitString( std::string(argv[i+1]), "x");
                        if( splits.size()>1 ){
                            width = std::stoi( splits[0] );
                            height = std::stoi( splits[1] );
                        }else{
                            std::cout<<"[ pixelscript ] wrong argument for --size or -s, it should be a resolution delimited by x, for example 1280x720\n";
                            return 0;
                        }
                    }
                }
            
                if( cmd == "--position" || cmd == "-p" ){
                    if( i+1 < argc ){
                        // split by 'x'
                        auto splits = ofSplitString( std::string(argv[i+1]), ",");
                        if( splits.size()>1 ){
                            px = std::stoi( splits[0] );
                            py = std::stoi( splits[1] );
                        }else{
                            std::cout<<"[ pixelscript ] wrong argument for --position or -p, it should be two coordinates delimited by comma, for example 300,200 \n";
                            return 0;
                        }
                    }
                }
            
                if( cmd == "--mirror" || cmd == "-m" ){
                    if( i+1 < argc ){
                        // split by 'x'
                        auto splits = ofSplitString( std::string(argv[i+1]), "x");
                        if( splits.size()>1 ){
                            app->mwidth = std::stoi( splits[0] );
                            app->mheight = std::stoi( splits[1] );
                            app->bMirror = true;
                        }else{
                            std::cout<<"[ pixelscript ] wrong argument for --mirror or -m, it should be a resolution delimited by x, for example 1280x720\n";
                            return 0;
                        }
                    }
                }
                
                if( cmd == "--headless" || cmd == "-x" ){
                    if( i+1 < argc ){
                        app->usecs = std::stoi( argv[i+1] );
                    }
                }

            }
                            
            if( app->usecs > 0 ){
                ofAppNoWindow window; 
                ofSetupOpenGL( &window, 240, 240, OF_WINDOW);	
                ofRunApp( app );
            }else{
                #ifdef __ARM_ARCH
                ofGLESWindowSettings settings;
                settings.glesVersion = 2;
                #else
                ofGLFWWindowSettings settings;
                settings.resizable = true;
                settings.decorated = decorated;
                #endif
                    
                if( px>=0 ){
                    settings.setPosition( ofVec2f( px, py ) );    
                }
                    
                settings.setSize( width, height );     
                shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
                         
                if( app->bMirror ){
                    settings.setSize( app->mwidth, app->mheight );
                    settings.setPosition(ofVec2f(ofGetScreenWidth(), 0));
                    settings.resizable = false;
                    settings.decorated = false;
                    settings.shareContextWith = mainWindow;
                    shared_ptr<ofAppBaseWindow> secondWindow = ofCreateWindow(settings);
                    secondWindow->setVerticalSync(false);
                    ofAddListener(secondWindow->events().draw, app.get(), &ofApp::drawSecondWindow);
                }
                    
                ofRunApp(mainWindow, app);
                ofRunMainLoop();
            }

        }else{
            ofLogError() << "[ pixelscript ] not a .lua script file, quitting\n";
        }
 
	}else{
        ofLogError() << "[ pixelscript ] NO INPUT ARGUMENTS!\n";
    }
}
