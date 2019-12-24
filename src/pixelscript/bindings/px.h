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
#include "../Buffer.h"

namespace px {

    void resources( np::pixelscript::Buffer & resource );
    void setRotated( bool rotate );
    
    void canvas( int w, int h, int layers = 1 );
    
    void framerate( int value );
    void blendmode( int value );
    
    void layer( int l );
    
    void begin();
    void finish();
    
    void clear();
    void clear( int r, int g, int b, int a );
    void clear( int r, int g, int b );
    void clear( int gray, int a );
    void clear( int gray );
    
    void background( int r, int g, int b, int a );
    void background( int r, int g, int b );
    void background( int gray, int a );
    void background( int gray );
    
    void fade( int speed );

    void color( int r, int g, int b, int a );
    void color( int r, int g, int b);
    void color( int grey, int a );
    void color( int grey );

    void fill( bool active = true );

    void stroke( double width );
    
    void point( int x, int y );
    void line( int x0, int y0, int x1, int y1 );
    void arcl( int cx, int cy, int radius, double angle_begin, double angle_end );

	void rect( int x, int y, int w, int h );
    void rect( int x, int y, int w, int h, int r );
    void circle( int x, int y, int radius );
	void ellipse( int cx, int cy, int width, int height );
    void poly( int cx, int cy, int radius, int N, double
     theta=-M_PI_2 );
    void triangle( int x0, int y0, int x1, int y1, int x2, int y2 );
     
    void begin_shape();
    void next( bool close = false );
    void end_shape( bool close = false );
	void vertex( int x, int y );
	void curve( int x, int y );
	void bezier( int c1x, int c1y, int c2x, int c2y, int x, int y );
    void arc( int cx, int cy, int radius, double angle_begin, double angle_end );
    void polypath( int cx, int cy, int radius, int N, double
     theta=-M_PI_2 );
    
    double map( double input, double inmin, double inmax, double outmin, double outmax );
    
    double random();
    double random( double max );
    double random( double min, double max );
    bool chance( double value );
        
    int width();
    int height();
        
    void push();
    void pop();
    void translate( int x, int y );
    void rotate( double rad );
    void scale( double x, double y );
    
}
