/*====================================================================

	np-pixelscript - little 2d graphics scripting playground
  
	Copyright (c) 2019 Nicola Pisanti <nicola@npisanti.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    
====================================================================*/

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
