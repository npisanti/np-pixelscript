
#include "px.h"
#include "ofMain.h"

#define PIXELSCRIPT_ARC_RESO 30 

namespace px {
    
    int w; 
    int h;
    
    void beginFrame( int width, int height ){
        w = width;
        h = height;
        ofPushMatrix();
        ofSetCircleResolution( 60 );
        ofSetLineWidth( 1.0f );
        ofDisableAntiAliasing();
    }
    
    void endFrame(){
        ofPopMatrix();
    }
    
    void size( int w, int h ){
        ofSetWindowShape( w, h );
    }
    
    void framerate( int value ){
        ofSetFrameRate( value );
    }
    
    void background( int r, int g, int b, int a ){
        ofClear( r, g, b, a );
    }

    void clear(){
        ofClear( 0, 0, 0, 0 );
    }
    
    void fade( int speed ){
        ofPushStyle();
            ofSetColor( 0, 0, 0, speed );
            ofFill();
            ofDrawRectangle( -1, -1, w+1, h+1 );
        ofPopStyle();
    }

    void color( int r, int g, int b, int a ){
        ofSetColor( r, g, b, a );
    }
    
    void color( int r, int g, int b){
        ofSetColor( r, g, b );
    }
    
    void color( int grey, int a ){
        ofSetColor( grey, a );
    }
    
    void color( int grey ){
        ofSetColor( grey );
    }

    void fill( bool active ){
        if( active ){
            ofFill();
        }else{
            ofNoFill();
        }
    }

    void stroke( double width ){
        ofSetLineWidth( width );
    }
    
    void line( int x0, int y0, int x1, int y1 ){
        ofDrawLine( x0, y0, x1, y1 );
    }

	void arcl( int cx, int cy, int radius, double angle_begin, double angle_end ){
        ofBeginShape();
            arc( cx, cy, radius, angle_begin, angle_end );
        ofEndShape();
    }

	void rect( int x, int y, int w, int h ){
        ofDrawRectangle( x, y, w, h );
    }
    
    void rect( int x, int y, int w, int h, int r ){
        ofDrawRectRounded( x, y, w, h, r );
    }
    
    void circle( int x, int y, int radius ){
        ofDrawCircle( x, y, radius );
    }
    
	void ellipse( int cx, int cy, int width, int height ){
        ofDrawEllipse( cx, cy, width, height );
    }
    
    void triangle( int x0, int y0, int x1, int y1, int x2, int y2 ){
        ofDrawTriangle( x0, y0, x1, y1, x2, y2 );
    }
    
    void poly( int cx, int cy, int radius, int N, double
     theta ){
        float step = M_TWO_PI / float(N);

        for(int i=0; i<N; ++i ){
            ofVertex( cx + cos(theta)*radius, cy + sin(theta)*radius );
            theta += step;
        }
    }
     
    void begin(){
        ofBeginShape();
    }
    
    void next( bool close ){
        ofNextContour( close );
    }
    
    void finish( bool close ){
        ofEndShape( close );
    }
    
	void vertex( int x, int y ){
        ofVertex( x, y );
    }
    
	void curve( int x, int y ){
        ofCurveVertex( x, y );
        
    }
	void bezier( int c1x, int c1y, int c2x, int c2y, int x, int y ){
        ofBezierVertex( c1x, c1y, c2x, c2y, x, y );
    }
    
	void arc( int cx, int cy, int radius, double angle_begin, double angle_end ){
        double step = ( angle_end - angle_begin ) / PIXELSCRIPT_ARC_RESO;

        for(int i=0; i<=PIXELSCRIPT_ARC_RESO; ++i ){
            ofVertex( cx + cos(angle_begin)*radius, cy + sin(angle_begin)*radius );
            angle_begin += step;
        }
    }

    bool chance( double value ){ return (ofRandomuf()<value); }
    
    double map( double input, double inmin, double inmax, double outmin, double outmax ){
        return ofMap( input, inmin, inmax, outmin, outmax, true );
    }
    
    double random(){
        return ofRandomuf();
    }
    
    double random( double max ){
        return ofRandom( max );
    }
    
    double random( double min, double max ){
        return ofRandom( min, max );
    }
        
    void push(){
        ofPushMatrix();
    }
    void pop(){
        ofPopMatrix();
    }
    
    void translate( int x, int y ){
        ofTranslate( x, y );
    }
    
    void rotate( double rad ){
        ofRotateRad( rad );
    }
    void scale( double x, double y ){
        ofScale( x, y );
    }
    
    int width(){
        return w;
    }

    int height(){
        return h;
    }
}