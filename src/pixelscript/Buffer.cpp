
#include "Buffer.h"

np::pixelscript::Buffer::Buffer(){
    now = 0;
    then = 1;
}
    
void np::pixelscript::Buffer::allocate( int w, int h ){
    this->w = w;
    this->h = h;

    ofFboSettings settings;
    settings.width = w; 
    settings.height = h;
    settings.minFilter = GL_NEAREST;
    settings.maxFilter = GL_NEAREST;
    
    fbos.resize(2);
    
    for( int i=0; i<2; ++i ){
        fbos[i].allocate( w, h );
        fbos[i].begin();
            ofClear( 0, 0, 0, 0 );
        fbos[i].end();
    }
}

void np::pixelscript::Buffer::begin(){
    fbos[now].begin();
}

void np::pixelscript::Buffer::end(){
    fbos[now].end();
}

void np::pixelscript::Buffer::swap(){
    then = now;
    now = (now==0) ? 1 : 0;
}

void np::pixelscript::Buffer::draw( int x, int y ){
    fbos[now].draw( x, y );
}
    
void np::pixelscript::Buffer::draw( int x, int y, int w, int h ){
    fbos[now].draw( x, y, w, h );
}
    
const ofTexture & np::pixelscript::Buffer::getTexture() const{
    return fbos[then].getTexture();
}
