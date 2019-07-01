
#pragma once

#include <iostream>
#include "ofMain.h"

namespace px {

    void beginFrame( int width, int height );
    void endFrame();
    
    void size( int w, int h );
    void framerate( int value );
    
    void clear();
    void background( int r, int g, int b, int a );
    void fade( int speed );

    void color( int r, int g, int b, int a );
    void color( int r, int g, int b);
    void color( int grey, int a );
    void color( int grey );

    void fill( bool active = true );

    void stroke( double width );
    
    void line( int x0, int y0, int x1, int y1 );
    void arcl( int cx, int cy, int radius, double angle_begin, double angle_end );

	void rect( int x, int y, int w, int h );
    void rect( int x, int y, int w, int h, int r );
    void circle( int x, int y, int radius );
	void ellipse( int cx, int cy, int width, int height );
    void poly( int cx, int cy, int radius, int N, double
     theta=-M_PI_2 );
    void triangle( int x0, int y0, int x1, int y1, int x2, int y2 );
     
    void begin();
    void next( bool close = false );
    void finish( bool close = false );
	void vertex( int x, int y );
	void curve( int x, int y );
	void bezier( int c1x, int c1y, int c2x, int c2y, int x, int y );
    void arc( int cx, int cy, int radius, double angle_begin, double angle_end );
    
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
