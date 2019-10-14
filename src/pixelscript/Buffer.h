
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
