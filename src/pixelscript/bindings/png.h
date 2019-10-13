
#pragma once

#include <iostream>
#include "ofMain.h"

namespace png{

    struct Pair {
        Pair();
        std::string name;
        std::string path;
        std::vector<ofImage> folder;
        int index;
    };

    void init();
    void resources( std::vector<Pair> & reso );
    
    void load( const char * name, const char * path );
    
    // modes: 0/def = top left corner, 1 = center, 2 = bottom left corner  
    void mode( int value );
    
    void select( const char * name );
    
    void frame( int index );
    void pct( double value );
    
    int next();
    int prev();
    int step( int step );
    int random(); // don't repeat the same frame two time 
    int randjump( int stepmax ); // jumps a number of step between 1 and stepmax included
    
    
    
    void draw( int x, int y );
    
    int width();
    int height();
}
