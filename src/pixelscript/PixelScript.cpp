
#include "PixelScript.h"

#include "bindings/px.h"
#include "bindings/font.h"


extern "C" {
	int luaopen_px(lua_State* L);
    int luaopen_lfo(lua_State* L);
    int luaopen_font(lua_State* L);
    int luaopen_sprite(lua_State* L);
}

np::PixelScript::PixelScript(){
    loaded = false;

	script.addListener(this);
    
    phasors.resize( 32 );
    for( auto & phasor : phasors ){
        phasor.init();
    }
    
    sprites.reserve( 16 );
    sprites.emplace_back();
}

np::PixelScript::~PixelScript(){
    if(loaded){
        script.scriptExit();
    }    
    script.clear();

}

void np::PixelScript::reload(){
    if(loaded){
        script.scriptExit();
    }
    script.init(true);
    luaopen_px(script); 
    luaopen_lfo(script); 
    luaopen_font(script); 
    luaopen_sprite(script); 
    lfo::resources( phasors );
    font::resources( font );
    sprite::resources( sprites );
    script.doScript( filepath, true );
    script.scriptSetup();
    loaded = true;
}
    
void np::PixelScript::render( ofFbo & fbo ){
    
    for( auto & phasor : phasors ){
        phasor.update();
    }
    
    lfo::resources( phasors );
    font::resources( font );
    sprite::resources( sprites );
    
    fbo.begin();
        ofSetColor(255);
        px::beginFrame( fbo.getWidth(), fbo.getHeight() );
        script.scriptUpdate();
        script.scriptDraw();
        px::endFrame();
        
        //sprites.bind();
        //sprites.setFrame( int(ofGetElapsedTimef())%4 );
        //sprites.draw( 5, 5 );
        //sprites.unbind();
        sprite::clean();
    fbo.end();
    
}

void np::PixelScript::draw( int x, int y, int w, int h ){
    for( auto & phasor : phasors ){
        phasor.update();
    }
    lfo::resources( phasors );
    font::resources( font );
    sprite::resources( sprites );
    
    ofPushMatrix();
    ofTranslate( x, y );
        ofSetColor(255);
        font::resources( font );
        px::beginFrame( w, h );
        script.scriptUpdate();
        script.scriptDraw();
        px::endFrame();
        sprite::clean();
    ofPopMatrix();
}

void np::PixelScript::errorReceived(std::string& msg) {
	ofLogNotice() << "[ "<<filename<<" ] got a script error: " << msg;
}
