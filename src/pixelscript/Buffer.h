
#pragma once

#include "ofMain.h"

namespace np{ namespace pixelscript {
    
class Buffer{

public:
    Buffer();
    
    void allocate( int w, int h );
    void begin();
    void end();
    void swap();
    
    void draw( int x, int y );
    void draw( int x, int y, int w, int h );
    
    const ofTexture & getTexture() const;
    
    int getWidth() const { return w; }
    int getHeight() const { return h; }

private:

    std::vector<ofFbo> fbos;
    int now;
    int then;
    
    int w; 
    int h;

};
    
}}
