/*====================================================================

	np-pixelscript - little 2d graphics scripting playground
  
	Copyright (c) 2019 Nicola Pisanti <nicola@npisanti.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    
====================================================================*/

#pragma once

#include "ofMain.h"

namespace np{ namespace pixelscript {
    
class Buffer{

    struct Layer{
        Layer();
        
        void swap();
        void begin(){ fbos[now].begin(); }
        void end(){ fbos[now].end(); }
        void draw( int x, int y ){ fbos[now].draw( x, y ); }
        void draw( int x, int y, int w, int h ){ fbos[now].draw( x, y, w, h ); }
        
        std::vector<ofFbo> fbos;
        int now;
        int then;
    };

public:

    Buffer();
    
    void allocate( int w, int h, int numLayers );
    void begin();
    void end();
    void swap();
    
    void setLayer( int i );
    
    void draw( int x, int y );
    void draw( int x, int y, int w, int h );
    
    const ofTexture & getTexture() const;
    
    int getWidth() const { return w; }
    int getHeight() const { return h; }

private:
    int layer;
    int w; 
    int h;
    std::vector<Layer> layers;
    
};
    
}}
