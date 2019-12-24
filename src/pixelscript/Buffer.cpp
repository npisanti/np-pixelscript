/*====================================================================

	np-pixelscript - little 2d graphics scripting playground
  
	Copyright (c) 2019 Nicola Pisanti <nicola@npisanti.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    
====================================================================*/

#include "Buffer.h"

np::pixelscript::Buffer::Buffer(){
    layer = 0;
}

np::pixelscript::Buffer::Layer::Layer(){
    now = 0;
    then = 1;
}
    
void np::pixelscript::Buffer::allocate( int w, int h, int numLayers ){
    this->w = w;
    this->h = h;

    ofFboSettings settings;
    settings.width = w; 
    settings.height = h;
    settings.minFilter = GL_NEAREST;
    settings.maxFilter = GL_NEAREST;

    layers.resize( numLayers );
    
    for ( auto & lay : layers ){
        lay.fbos.resize(2);
        
        for( int i=0; i<2; ++i ){
            lay.fbos[i].allocate( w, h );
            lay.fbos[i].begin();
                ofClear( 0, 0, 0, 0 );
            lay.fbos[i].end();
        }        
    }
}

void np::pixelscript::Buffer::setLayer( int  i ){
    if( i<0 ){ 
        std::cout<<"[pixelscript] layer less than zero!\n";
        return;
    }
    if( i>=int(layers.size()) ){
        std::cout<<"[pixelscript] layer "<<i<<" outside allocated number!\n";
        return;
    }
    layer = i;
}

void np::pixelscript::Buffer::begin(){
    layers[layer].begin();
}

void np::pixelscript::Buffer::end(){
    layers[layer].end();
}

void np::pixelscript::Buffer::Layer::swap(){
    then = now;
    now = (now==0) ? 1 : 0;
}

void np::pixelscript::Buffer::swap(){
    layers[layer].swap();
}

void np::pixelscript::Buffer::draw( int x, int y ){
    for( size_t i=0; i<layers.size(); ++i ){
        layers[i].draw( x, y );
    }
}
    
void np::pixelscript::Buffer::draw( int x, int y, int w, int h ){
    for( size_t i=0; i<layers.size(); ++i ){
        layers[i].draw( x, y, w, h );
    }
}
    
const ofTexture & np::pixelscript::Buffer::getTexture() const{
    auto & la = layers[layer];
    return la.fbos[la.then].getTexture();
}
