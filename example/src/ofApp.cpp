
#include "ofMain.h"
#include "np-pixelscript.h"

class ofApp : public ofBaseApp{
    
// ---------- variables ----------------------------------------
        
np::PixelScript script;
ofFbo fbo;
int downsample;

//--------------------------------------------------------------
void setup(){
    ofBackground( 0 );

    script.load( "/home/nicola/oF/addons/np-pixelscript/example/bin/data/sketch.lua" );

    downsample = 2;
    ofFboSettings settings;
    settings.width = ofGetWidth()/downsample;
    settings.height = ofGetHeight()/downsample;
    settings.minFilter = GL_NEAREST;
    settings.maxFilter = GL_NEAREST;
    fbo.allocate( settings );
    fbo.begin();
        ofClear( 0, 0, 0, 0 );
    fbo.end();
}

//--------------------------------------------------------------
void update(){
    script.render( fbo );
}

//--------------------------------------------------------------
void draw(){
    fbo.draw( 0, 0, fbo.getWidth()*downsample, fbo.getHeight()*downsample );
}

//--------------------------------------------------------------
void exit(){

}

//--------------------------------------------------------------
void keyPressed(int key){
    switch( key ){    
        case '1':  break;
        case '2':  break;
        case '3':  break;
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

int main(){

#ifdef __ARM_ARCH
    ofGLESWindowSettings settings;
    settings.glesVersion = 2;
#else
    ofGLFWWindowSettings settings;
    settings.resizable = true;
#endif

    settings.setSize( 800, 480 );    

    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    shared_ptr<ofApp> mainApp(new ofApp);
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
}
