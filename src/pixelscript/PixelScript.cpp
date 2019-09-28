
#include "PixelScript.h"

#include "bindings/px.h"
#include "bindings/font.h"
#include "bindings/lfo.h"


extern "C" {
	int luaopen_px(lua_State* L);
    int luaopen_lfo(lua_State* L);
    int luaopen_font(lua_State* L);
    int luaopen_png(lua_State* L);
}

np::PixelScript::PixelScript(){
    loaded = false;

	script.addListener(this);
    
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

void np::PixelScript::reload(){
    if(loaded){
        script.scriptExit();
    }
    script.init(true);
    luaopen_px(script); 
    luaopen_lfo(script); 
    luaopen_font(script); 
    luaopen_png(script); 
    font::resources( font );
    png::resources( images );
    script.doScript( filepath, true );
    script.scriptSetup();
    loaded = true;
}
    
void np::PixelScript::render( ofFbo & fbo ){

    float now = ofGetElapsedTimef();
    clock += (now-before) * (speed*speed*speed);
    before = now;
    lfo::setPlayHead( clock );

    font::resources( font );
    png::resources( images );
    
    fbo.begin();
        ofSetColor(255);
        px::beginFrame( fbo.getWidth(), fbo.getHeight() );
        script.scriptUpdate();
        script.scriptDraw();
        px::endFrame();
    fbo.end();
    
}

void np::PixelScript::draw( int x, int y, int w, int h ){

    lfo::setPlayHead( clock );

    font::resources( font );
    png::resources( images );
    
    ofPushMatrix();
    ofTranslate( x, y );
        ofSetColor(255);
        font::resources( font );
        px::beginFrame( w, h );
        script.scriptUpdate();
        script.scriptDraw();
        px::endFrame();
    ofPopMatrix();
    
    float now = ofGetElapsedTimef();
    clock += (now-before) * (speed*speed*speed);
    before = now;
}

void np::PixelScript::errorReceived(std::string& msg) {
	ofLogNotice() << "[ "<<filename<<" ] got a script error: " << msg;
}

void  np::PixelScript::setTime( float value ){
    clock = value;
}
