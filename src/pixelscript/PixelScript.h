
#pragma once

#include "ofMain.h"

#include "ofxLua/src/ofxLua.h"
#include "FileWatcher.h"
#include "bindings/png.h"

namespace np{ 
    
class PixelScript : public FileWatcher, public ofxLuaListener {
    
public:
    PixelScript();
    ~PixelScript();
    
    void render( ofFbo & fbo );
    void draw( int x, int y, int w, int h );
    void setTime( float value );
    
    void variable( std::string name, double value ){ script.setNumber( name, (lua_Number) value ); }
   
    void variable( std::string name, bool value ){ script.setBool( name, value ); }

    ofxLua script;    

    ofParameter<float> speed;
    
private:
    
    ofTrueTypeFont font;

    std::vector<png::Pair> images;

    bool loaded;

    void errorReceived(std::string& msg);
    
    float clock;
    float before; 
    
    void reload() override;
    
};
    
}
