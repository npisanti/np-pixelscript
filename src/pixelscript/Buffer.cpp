
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
