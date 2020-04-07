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
    layers.reserve(12);
    w = 400;
    h = 400;
}

np::pixelscript::Buffer::Layer::Layer(){
    now = 0;
    then = 1;
    bRender = true;
    x = y = w = h = mw = mh = 0;
}
    

void np::pixelscript::Buffer::addLayer( std::string name, int w, int h, int mult ){
    
    int found = -1;
    for( size_t i=0; i<layers.size(); ++ i) {
        if( layers[i].name == name ){
            found = i;
        }
    }    
    
    Layer * lay = nullptr;
    
    if( found >= 0){
        lay = &layers[found];
    }else{
        layers.emplace_back();
        lay = &layers.back();
    }
    
    ofFboSettings settings;
    settings.width = w; 
    settings.height = h;

    if( mult>=1 ){
        lay->mult = mult;
        settings.minFilter = GL_NEAREST;
        settings.maxFilter = GL_NEAREST;
    }else{
        lay->mult = 1;
        settings.minFilter = GL_LINEAR;
        settings.maxFilter = GL_LINEAR;
    }

    lay->name = name;
    lay->w = w;
    lay->h = h;
    lay->mw = w * lay->mult;
    lay->mh = h * lay->mult;
    
    lay->fbos.resize(2);
    for( int i=0; i<2; ++i ){
        lay->fbos[i].allocate( settings );
        lay->fbos[i].begin();
            ofClear( 0, 0, 0, 0 );
        lay->fbos[i].end();
    }   
}

void np::pixelscript::Buffer::moveLayer( int x, int y ){
    layers[layer].x = x;
    layers[layer].y = y;
}

ofFbo & np::pixelscript::Buffer::getFbo( int i ){
    if( i<0 ){ 
        std::cout<<"[pixelscript] layer less than zero!\n";
        i=0;
    }
    if( i>=int(layers.size()) ){
        std::cout<<"[pixelscript] layer "<<i<<" outside allocated number!\n";
        i=0;
    }
    return layers[i].fbos[layers[i].now];
}

ofFbo & np::pixelscript::Buffer::getFbo( const char * name ){
    int found = -1;
    for( size_t i=0; i<layers.size(); ++ i) {
        if( strcmp( layers[i].name.c_str(), name ) == 0 ){
            found = i;
        }
    }
    if( found == -1 ){
        std::cout<<"[pixelscript] layer name not found, wrong name?\n";
        found = 0;
    }
    
    return layers[found].fbos[layers[found].now];
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

void np::pixelscript::Buffer::setLayer( const char * name ){
    for( size_t i=0; i<layers.size(); ++ i) {
        if( strcmp( layers[i].name.c_str(), name ) == 0 ){
            layer = i;
            return;
        }
    }
    std::cout<<"[pixelscript] layer name not found, wrong name?\n";
    return;
}

void np::pixelscript::Buffer::drawLayer( int i ){
    if( i<0 ){ 
        std::cout<<"[pixelscript] layer less than zero!\n";
        return;
    }
    if( i>=int(layers.size()) ){
        std::cout<<"[pixelscript] layer "<<i<<" outside allocated number!\n";
        return;
    }
    layers[i].draw( 0, 0 );
}

void np::pixelscript::Buffer::drawLayer( const char * name ){
    for( size_t i=0; i<layers.size(); ++ i) {
        if( strcmp( layers[i].name.c_str(), name ) == 0 ){
            layers[i].draw( 0, 0 );
            return;
        }
    }
    std::cout<<"[pixelscript] layer name not found, wrong name?\n";
    return;
}

void np::pixelscript::Buffer::pipeLayer( int i ){
    if( i<0 ){ 
        std::cout<<"[pixelscript] layer less than zero!\n";
        return;
    }
    if( i>=int(layers.size()) ){
        std::cout<<"[pixelscript] layer "<<i<<" outside allocated number!\n";
        return;
    }
    layers[i].bRender = false;
    layers[i].draw( 0, 0 );
}

void np::pixelscript::Buffer::pipeLayer( const char * name ){
    for( size_t i=0; i<layers.size(); ++ i) {
        if( strcmp( layers[i].name.c_str(), name ) == 0 ){
            layers[i].bRender = false;
            layers[i].draw( 0, 0 );
            return;
        }
    }
    std::cout<<"[pixelscript] layer name not found, wrong name?\n";
    return;
}

void np::pixelscript::Buffer::begin(){
    layers[layer].begin();
    w = layers[layer].w;
    h = layers[layer].h;
}

void np::pixelscript::Buffer::end(){
    layers[layer].end();
    w = ofGetWidth();
    h = ofGetHeight();
}

void np::pixelscript::Buffer::Layer::swap(){
    then = now;
    now = (now==0) ? 1 : 0;
}

void np::pixelscript::Buffer::swap(){
    layers[layer].swap();
}

void np::pixelscript::Buffer::draw( int x, int y ){
    ofPushMatrix();
    ofTranslate( x, y );        
        for( size_t i=0; i<layers.size(); ++i ){
            auto & le = layers[i];
            if( le.bRender ){
                le.draw();
            }
        }
    ofPopMatrix();
}

void np::pixelscript::Buffer::unpipe(){
    for( size_t i=0; i<layers.size(); ++i ){
        layers[i].bRender = true;
    }
}

    
const ofTexture & np::pixelscript::Buffer::getTexture() const{
    auto & la = layers[layer];
    return la.fbos[la.then].getTexture();
}
