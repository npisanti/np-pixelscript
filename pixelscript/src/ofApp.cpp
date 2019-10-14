
#include "ofMain.h"

#include "np-pixelscript.h"
#include "ofxOsc.h"

// macro for chdir() as Windows uses a protected variant
#ifdef TARGET_WIN32
	#include <direct.h>
	#define CHDIR _chdir
#else
	#define CHDIR chdir
#endif
#include <errno.h>
#include "pixelscript/bindings/px.h"

class ofApp : public ofBaseApp{
public:
    
// ---------- variables ----------------------------------------
bool bShowFrameRate;
bool bRotate;
np::PixelScript script;
std::string path;
ofxOscReceiver receiver;

//--------------------------------------------------------------
void setup(){
    
    ofSetWindowTitle( ":x:" );
    
    ofHideCursor();
    
    ofBackground( 0 );
    bShowFrameRate = false;
    
    px::setRotated( bRotate );
    
    script.load( path );    
    
}

//--------------------------------------------------------------
void update(){
    
    script.update();
}

//--------------------------------------------------------------
void draw(){
    
    int x=0;
    int y=0;

    if( !bRotate ){
        x = (ofGetWidth() - script.getWidth())/2;
        y = (ofGetHeight() - script.getHeight())/2;
        if( x<0 ) x=0;
        if( y<0) y=0;        
    }else{
        x = (ofGetHeight() - script.getWidth())/2;
        y = (ofGetWidth() - script.getHeight())/2;
        if( x<0 ) x=0;
        if( y<0) y=0;        
        ofTranslate( ofGetWidth(), 0 );
        ofRotateDeg( 90 );
    }

    script.draw( x, y );
    
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
void keyPressed(int key){
    switch( key ){    
        case 'f': bShowFrameRate = !bShowFrameRate; break;
    }
    script.lua.scriptKeyPressed( key );
}

//--------------------------------------------------------------
void keyReleased(int key){
    script.lua.scriptKeyReleased( key );
}

//--------------------------------------------------------------
void exit(){}

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
            
            shared_ptr<ofApp> mainApp(new ofApp);
            mainApp->path = path;
    
    #ifdef __ARM_ARCH
            ofGLESWindowSettings settings;
            settings.glesVersion = 2;
    #else
            ofGLFWWindowSettings settings;
            settings.resizable = true;
    #endif
            
            int width = 480;
            int height = 480;
            mainApp->bRotate = false;
            
            for( int i=1; i<argc; ++i ){
                std::string cmd = std::string( argv[i] );
    #ifndef __ARM_ARCH
                if( cmd == "--no-decoration" || cmd == "-nd" ){
                    settings.decorated = false;   
                }
    #endif
                if( cmd == "--width" || cmd == "-w" ){
                    if( argc < i+1 ){
                        width = std::stoi( argv[i+1] );
                    }
                }
                
                if( cmd == "--height" || cmd == "-h" ){
                    if( argc < i+1 ){
                        height = std::stoi( argv[i+1] );
                    }
                }
                
                if( cmd == "--height" || cmd == "-h" ){
                    if( argc < i+1 ){
                        height = std::stoi( argv[i+1] );
                    }
                }
                
                if( cmd == "--rotate" || cmd == "-r" ){
                    mainApp->bRotate = true;
                }
            }
                
            settings.setSize( width, height );     
            shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
                    
            ofRunApp(mainWindow, mainApp);
            ofRunMainLoop();
        }else{
            ofLogError() << "[ pixelscript ] not a .lua script file, quitting\n";
        }
 
	}else{
        ofLogError() << "[ pixelscript ] NO INPUT ARGUMENTS!\n";
    }
}
