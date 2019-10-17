
#include "PixelScript.h"

#include "bindings/px.h"
#include "bindings/font.h"
#include "bindings/lfo.h"
#include "bindings/frag.h"
#include "bindings/osc.h"

extern "C" {
	int luaopen_px(lua_State* L);
    int luaopen_lfo(lua_State* L);
    int luaopen_font(lua_State* L);
    int luaopen_png(lua_State* L);
    int luaopen_frag(lua_State* L);
    int luaopen_osc(lua_State* L);
}

np::PixelScript::PixelScript(){
    loaded = false;

	lua.addListener(this);
    shaders.reserve( 6 );
    
    before = 0.0f;
    clock = 0.0f;
    parameters.add( speed.set("speed", 1.0f, 0.0f, 2.0f) );
    
    images.reserve(12);
    images.emplace_back();
    images.back().folder.resize(1);
    
    
    oscNumbers.reserve( 16 );
    
    png::init();
}

np::PixelScript::~PixelScript(){
    if(loaded){
        lua.scriptExit();
    }    
    lua.clear();
}

void np::PixelScript::reload(){
    if(loaded){
        lua.scriptExit();
    }
    lua.init(true);
    luaopen_px(lua); 
    luaopen_lfo(lua); 
    luaopen_font(lua); 
    luaopen_png(lua); 
    luaopen_frag(lua); 
    luaopen_osc(lua); 
    font::resources( font );
    png::resources( images );
    frag::resources( buffer, shaders, 0.0f );
    osc::resources( receiver, sender );
    px::resources( buffer );
    lua.doScript( filepath, true );
    lua.scriptSetup();
    loaded = true;
}
    
void np::PixelScript::update(){

    float now = ofGetElapsedTimef();
    clock += (now-before) * (speed*speed*speed);
    before = now;

    lfo::setPlayHead( clock );

    font::resources( font );
    png::resources( images );
    frag::resources( buffer, shaders, clock );
    osc::resources( receiver, sender );
    px::resources( buffer );

    lua.scriptUpdate();
    lua.scriptDraw();
    
    while(receiver.hasWaitingMessages()) {
        ofxOscMessage message;
        if( receiver.getNextMessage(message) ){
            oscReceived(message);
        }
    }
}

void np::PixelScript::draw( int x, int y, int w, int h ){
    buffer.draw( x, y, w, h ); 
}

void np::PixelScript::draw( int x, int y ){
    ofSetColor(255);
    buffer.draw( x, y );
}

void np::PixelScript::errorReceived(std::string& msg) {
	ofLogNotice() << "[ "<<filename<<" ] got a script error: " << msg;
}

void  np::PixelScript::setTime( float value ){
    clock = value;
}

void np::PixelScript::oscReceived(const ofxOscMessage& message) {

	if(!lua.isValid() || !lua.isFunction("osc_received")) {
		return;
	}
    
    // parse message here
    oscNumbers.resize( message.getNumArgs() );
    
    for( size_t i=0; i<oscNumbers.size(); ++i ){
        double val = 0.0f;
        if(message.getArgType(i) == OFXOSC_TYPE_FLOAT){
            val = message.getArgAsFloat(i);
        }
        else if(message.getArgType(i) == OFXOSC_TYPE_INT32){
            val = message.getArgAsInt32(i);
        }
        oscNumbers[i] = val;
    }
    
    osc::setMessage( message.getAddress(), oscNumbers );
    
	lua_getglobal(lua, "osc_received");
	if(lua_pcall(lua, 0, 0, 0) != 0) {
		std::string line = "Error running osc_received(): " + (std::string) lua_tostring(lua, -1);
		lua.errorOccurred(line);
	}

}
