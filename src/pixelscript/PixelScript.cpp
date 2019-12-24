/*====================================================================

	np-pixelscript - little 2d graphics scripting playground
  
	Copyright (c) 2019 Nicola Pisanti <nicola@npisanti.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    
====================================================================*/

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
    int luaopen_osc(lua_State* L);
}

np::PixelScript::PixelScript(){
    loaded = false;

	lua.addListener(this);
    shaders.reserve( 6 );
    
    bHeadless = false;
    usec = 100;
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
    osc::resources( receiver, senders );
    px::resources( buffer );
    lua.doScript( filepath, true );
    lua.scriptSetup();
    loaded = true;
}
    
void np::PixelScript::update(){

    osc::resources( receiver, senders );

    if( !bHeadless ){
        float now = ofGetElapsedTimef();
        clock += (now-before) * (speed*speed*speed);
        before = now;
        lfo::setPlayHead( clock );

        font::resources( font );
        png::resources( images );
        frag::resources( buffer, shaders, clock );
        px::resources( buffer );
    }
    
    lua.scriptUpdate();
    
    if( !bHeadless ){
        lua.scriptDraw();   
    }
    
    while(receiver.hasWaitingMessages()) {
        ofxOscMessage message;
        if( receiver.getNextMessage(message) ){
            oscReceived(message);
        }
    }
    
    if( bHeadless ){
        usleep( usec );
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
    
    osc::setMessage( message );
    
	lua_getglobal(lua, "osc_received");
	if(lua_pcall(lua, 0, 0, 0) != 0) {
		std::string line = "Error running osc_received(): " + (std::string) lua_tostring(lua, -1);
		lua.errorOccurred(line);
	}

}


void np::PixelScript::headless( bool active, int usecs ){
    bHeadless = true;
    usec = 100;
}
