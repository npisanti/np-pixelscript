
#include "PixelScript.h"

#include "bindings/px.h"
#include "bindings/font.h"
#include "bindings/lfo.h"
#include "bindings/frag.h"

extern "C" {
	int luaopen_px(lua_State* L);
    int luaopen_lfo(lua_State* L);
    int luaopen_font(lua_State* L);
    int luaopen_png(lua_State* L);
    int luaopen_frag(lua_State* L);
}

np::PixelScript::PixelScript(){
    loaded = false;

	script.addListener(this);
    shaders.reserve( 6 );
    
    before = 0.0f;
    clock = 0.0f;
    parameters.add( speed.set("speed", 1.0f, 0.0f, 2.0f) );
    
    images.reserve(12);
    images.emplace_back();
    images.back().folder.resize(1);
    
    png::init();
}

np::PixelScript::~PixelScript(){
    if(loaded){
        script.scriptExit();
    }    
    script.clear();
}

void np::PixelScript::allocate( int w, int h ){
    buffer.allocate( w, h );
}

void np::PixelScript::reload(){
    if(loaded){
        script.scriptExit();
    }
    script.init(true);
    luaopen_px(script); 
    luaopen_lfo(script); 
    luaopen_font(script); 
    luaopen_png(script); 
    luaopen_frag(script); 
    px::resources( buffer );
    font::resources( font );
    png::resources( images );
    frag::resources( buffer, shaders, 0.0f );
    script.doScript( filepath, true );
    script.scriptSetup();
    loaded = true;
}
    
void np::PixelScript::update(){

    float now = ofGetElapsedTimef();
    clock += (now-before) * (speed*speed*speed);
    before = now;

    lfo::setPlayHead( clock );
    px::resources( buffer );
    font::resources( font );
    png::resources( images );
    frag::resources( buffer, shaders, clock );
    
    script.scriptUpdate();
    script.scriptDraw();
}

void np::PixelScript::draw( int x, int y, int w, int h ){
    buffer.draw( x, y, w, h ); 
}

void np::PixelScript::draw( int x, int y ){
    buffer.draw( x, y );
}

void np::PixelScript::errorReceived(std::string& msg) {
	ofLogNotice() << "[ "<<filename<<" ] got a script error: " << msg;
}

void  np::PixelScript::setTime( float value ){
    clock = value;
}
