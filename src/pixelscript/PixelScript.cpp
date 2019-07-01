
#include "PixelScript.h"

#include "bindings/px.h"
#include "bindings/lfo.h"
#include "bindings/font.h"

extern "C" {
	int luaopen_px(lua_State* L);
    int luaopen_lfo(lua_State* L);
    int luaopen_font(lua_State* L);
}

np::PixelScript::PixelScript(){
    loaded = false;

	script.addListener(this);
    before = 0.0f;
    speed = 1.0f;
    
    parameters.add( speed.set("speed", 1.0f, 0.0f, 2.0f) );
    
    clock = 0.0f;
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
    font::resources( font );
    script.doScript( filepath, true);
    script.scriptSetup();
    loaded = true;
    before = ofGetElapsedTimef();
}
    
void np::PixelScript::render( ofFbo & fbo ){
    
    float now = ofGetElapsedTimef();
    clock += (now-before) * (speed*speed*speed);
    before = now;
    lfo::setPlayHead( clock );

    fbo.begin();
        ofSetColor(255);
        font::resources( font );
        px::beginFrame( fbo.getWidth(), fbo.getHeight() );
        script.scriptUpdate();
        script.scriptDraw();
        px::endFrame();
    fbo.end();

}

void np::PixelScript::draw( int x, int y, int w, int h ){
    ofPushMatrix();
    ofTranslate( x, y );
        float now = ofGetElapsedTimef();
        clock += (now-before) * (speed*speed*speed);
        before = now;
        lfo::setPlayHead( clock );

        ofSetColor(255);
        font::resources( font );
        px::beginFrame( w, h );
        script.scriptUpdate();
        script.scriptDraw();
        px::endFrame();
    ofPopMatrix();
}

void np::PixelScript::errorReceived(std::string& msg) {
	ofLogNotice() << "[ "<<filename<<" ] got a script error: " << msg;
}
