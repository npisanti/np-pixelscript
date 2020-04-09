/*====================================================================

	np-pixelscript - little 2d graphics scripting playground
  
	Copyright (c) 2019 Nicola Pisanti <nicola@npisanti.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    
====================================================================*/

#pragma once

#include "ofMain.h"

#include "ofxLua/src/ofxLua.h"
#include "FileWatcher.h"
#include "bindings/png.h"
#include "Buffer.h"
#include "Shader.h"
#include "ofxOsc.h"
#include "osc.h"

namespace np{ 
    
class PixelScript : public FileWatcher, public ofxLuaListener {
    
public:
    PixelScript();
    ~PixelScript();

    void update();
    
    void draw( int x, int y );

    void setTime( float value );
    
    void variable( std::string name, double value ){ lua.setNumber( name, (lua_Number) value ); }
   
    void variable( std::string name, bool value ){ lua.setBool( name, value ); }

    ofxLua lua;    

    ofParameter<float> speed;
    
    int getWidth() const { return buffer.getWidth(); };
    int getHeight() const { return buffer.getHeight(); };
    
    void oscReceived(const ofxOscMessage& message);
    
    void headless( bool active, int usecs=100 );

	void pushArg( std::string option );

private:
    
    ofTrueTypeFont font;
    
    std::vector<osc::TaggedSender> senders;
    ofxOscReceiver receiver;

    std::vector<png::Pair> images;
    std::vector<np::pixelscript::Shader> shaders;
	std::vector<std::string> args;
    
    np::pixelscript::Buffer buffer;

    bool bHeadless;
    bool loaded;
    int usec;

    void errorReceived(std::string& msg);
    
    float clock;
    float before; 
    
    void reload() override;
    
};
    
}
