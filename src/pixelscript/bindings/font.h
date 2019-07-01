
#pragma once

#include <iostream>
#include "ofMain.h"

namespace font {

    void resources( ofTrueTypeFont & f );
    
    void load( const char * path, int size );

    void interline( double value );
    void spacing( double value );
    
    void draw( const char * text, int x, int y );
    
}
