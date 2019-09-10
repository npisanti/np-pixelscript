
#pragma once

#include <iostream>
#include "ofMain.h"

namespace png{

    struct Pair {
        Pair();
        std::string name;
        std::vector<ofImage> folder;
        int index;
    };

    void init();
    void resources( std::vector<Pair> & reso );
    
    void load( const char * path );
    
    // modes: 0/def = top left corner, 1 = center, 2 = bottom left corner  
    void mode( int value );
    
    void select( const char * name );
    
    int width();
    int height();

    void frame( int index );
    void pct( double value );
    void draw( int x, int y );

}
