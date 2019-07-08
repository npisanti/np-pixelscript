
#pragma once

#include "ofMain.h"

#include "ofxLua/src/ofxLua.h"
#include "FileWatcher.h"
#include "bindings/lfo.h"
#include "bindings/sprite.h"

namespace np{ 
    
class PixelScript : public FileWatcher, public ofxLuaListener {
    
public:
    PixelScript();
    ~PixelScript();
    
    void render( ofFbo & fbo );
    void draw( int x, int y, int w, int h );
    
    void variable( std::string name, double value ){ script.setNumber( name, (lua_Number) value ); }
   
    void variable( std::string name, bool value ){ script.setBool( name, value ); }

    ofxLua script;    
        
private:
    
    ofTrueTypeFont font;
    std::vector<lfo::Phasor> phasors;
    
    std::vector<sprite::SpriteSheet> sprites;

    bool loaded;

    void errorReceived(std::string& msg);
    
    void reload() override;
    
};
    
}
