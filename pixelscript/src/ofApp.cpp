
#include "ofMain.h"

#include "np-pixelscript.h"

// macro for chdir() as Windows uses a protected variant
#ifdef TARGET_WIN32
	#include <direct.h>
	#define CHDIR _chdir
#else
	#define CHDIR chdir
#endif
#include <errno.h>

class ofApp : public ofBaseApp{
public:
    
// ---------- variables ----------------------------------------
bool bShowFrameRate;
np::PixelScript script;
std::string path;

//--------------------------------------------------------------
void setup(){
    
    ofSetWindowTitle( ofFilePath::getFileName(path) );
    
    ofBackground( 0 );
    bShowFrameRate = false;
    
    script.load( path );
}

//--------------------------------------------------------------
void update(){
    script.update();
}

//--------------------------------------------------------------
void draw(){
    
    int x = (ofGetWidth() - script.getWidth())/2;
    int y = (ofGetHeight() - script.getHeight())/2;
    if( x<0 ) x=0;
    if( y<0) y=0;
    
    script.draw( x, y );
    
    if(bShowFrameRate){
        std::string info = "fps = ";
        info += ofGetFrameRate();
        ofSetColor(255);
        ofDrawBitmapString( info, 20, 20 );
        ofSetColor(0);
        ofDrawBitmapString( info, 20, 40 );
    }
}

//--------------------------------------------------------------
void exit(){

}

//--------------------------------------------------------------
void keyPressed(int key){
    switch( key ){    
        case 'f': bShowFrameRate = !bShowFrameRate; break;
        
        case '1':  
        
        break;
        
        case '2':  
        
        break;
    }
}

//--------------------------------------------------------------
void mousePressed(int x, int y, int button){}
void mouseDragged(int x, int y, int button){}
void mouseReleased(int x, int y, int button){}

//--------------------------------------------------------------
void keyReleased(int key){}
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
        std::string ext = ofFilePath::getFileExt( path );
        
        if( ext == "lua" ){

            if( ! ofFilePath::isAbsolute( path )){
                path = ofFilePath::getCurrentWorkingDirectory() + "/" + path;
            }
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
            settings.setSize( 480, 480 );     
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
