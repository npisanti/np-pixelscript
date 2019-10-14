
#pragma once

#include "ofMain.h"

#include "ofxLua/src/ofxLua.h"
#include "FileWatcher.h"
#include "bindings/png.h"
#include "Buffer.h"
#include "Shader.h"
#include "ofxOsc.h"

namespace np{ 
    
class PixelScript : public FileWatcher, public ofxLuaListener {
    
public:
    PixelScript();
    ~PixelScript();
    
    void allocate( int w, int h );
    
    void update();
    
    void draw( int x, int y );
    void draw( int x, int y, int w, int h );
    
    void setTime( float value );
    
    void variable( std::string name, double value ){ lua.setNumber( name, (lua_Number) value ); }
   
    void variable( std::string name, bool value ){ lua.setBool( name, value ); }

    ofxLua lua;    

    ofParameter<float> speed;
    
    int getWidth() const { return buffer.getWidth(); };
    int getHeight() const { return buffer.getHeight(); };
    
    void oscReceived(const ofxOscMessage& message);

private:
    
    ofTrueTypeFont font;
    
    ofxOscSender sender;
    ofxOscReceiver receiver;

    std::vector<float> oscNumbers;

    std::vector<png::Pair> images;
    std::vector<np::pixelscript::Shader> shaders;
    
    np::pixelscript::Buffer buffer;

    bool loaded;

    void errorReceived(std::string& msg);
    
    float clock;
    float before; 
    
    void reload() override;
    
};
    
}
