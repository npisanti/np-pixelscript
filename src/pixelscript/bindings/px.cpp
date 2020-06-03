/*====================================================================

	np-pixelscript - little 2d graphics scripting playground
  
	Copyright (c) 2019 Nicola Pisanti <nicola@npisanti.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    
====================================================================*/

#include "px.h"
#include "ofMain.h"

#define PIXELSCRIPT_ARC_RESO 30 

namespace px {
    
    np::pixelscript::Buffer * buffer;
    std::vector<std::string> * _args;
    bool _rotated = false;
    
    ofImage _saver;
    
    
    void _init( np::pixelscript::Buffer & resource ){
        resource.resetLayers();
    }
    
    void resources( np::pixelscript::Buffer & resource, std::vector<std::string> & arguments ){
        buffer = &resource;
        _args = &arguments;
    }
    
    int args(){
    	return _args->size();
   	}

    const char * arg( int index ){
		if( index>=0 && index < (int) _args->size() ){
			return _args->at(index).c_str();
		}else{
			return "undefined";
		}
    }
    
    void title( const char * name ){
        ofSetWindowTitle( name );
    }
    
    bool isRotated(){
        return _rotated;
    }
        
    void rotate( bool bRotate ){
        _rotated = bRotate;
    }
    
    void window( int w, int h ){            
        if( _rotated ){
            ofSetWindowShape( h, w );
        }else{
            ofSetWindowShape( w, h );
        }
    }
    
    void move_window( int x, int y ){
        ofSetWindowPosition( x, y );
    }
    
    void make_layer( const char * name, int w, int h, int pixelMult ){
        buffer->addLayer( name, w, h, pixelMult );
    }
    
    void move_layer( int x, int y ){
        buffer->moveLayer( x, y );
    }

    void canvas( int w, int h ){
        buffer->addLayer( "default", w, h, 0 );
        window( w, h );
    }
        
    void layer( int l ){
        buffer->setLayer( l );
    }
    
    void layer( const char * name ){
        buffer->setLayer( name );
    }
            
    void select( int l ){
        buffer->setLayer( l );
    }
    
    void select( const char * name ){
        buffer->setLayer( name );
    }
    
    void pipe( int l ){
        buffer->drawLayer( l );
    }
    
    void pipe( const char * name ){
        buffer->drawLayer( name );
    }
    
    void enable_layer( int l ){
        buffer->setActive( l, true );
    }
    
    void enable_layer( const char * name ){
        buffer->setActive( name, true );
    }
    
    void disable_layer( int l ){
        buffer->setActive( l, false );
    }
    
    void disable_layer( const char * name ){
        buffer->setActive( name, false );
    }
    
    void overlay( int l ){
        buffer->drawLayer( l );
    }
    
    void overlay( const char * name ){
        buffer->drawLayer( name );
    }

    void framerate( int value ){
        ofSetFrameRate( value );
    }
    
    void begin(){
        buffer->begin();
    }
    
    void finish(){
        buffer->end();
    }
        
    void open(){
        buffer->begin();
    }
    
    void close(){
        buffer->end();
    }
    
    void blendmode( int value ){
        switch( value ){
            case 1: ofEnableBlendMode( OF_BLENDMODE_ADD ); break;
            case 2: ofEnableBlendMode( OF_BLENDMODE_MULTIPLY ); break;
            case 3: ofEnableBlendMode( OF_BLENDMODE_SUBTRACT ); break;
            case 4: ofEnableBlendMode( OF_BLENDMODE_SCREEN ); break;
            default: ofEnableBlendMode( OF_BLENDMODE_ALPHA ); break;
        }
    }
    
    void blendmode_add(){
        ofEnableBlendMode( OF_BLENDMODE_ADD );
    }
    void blendmode_multiply(){
        ofEnableBlendMode( OF_BLENDMODE_MULTIPLY );
    }
    void blendmode_subtract(){
        ofEnableBlendMode( OF_BLENDMODE_SUBTRACT );
    }
    void blendmode_screen(){
        ofEnableBlendMode( OF_BLENDMODE_SCREEN );
    }
    void blendmode_alpha(){
        ofEnableBlendMode( OF_BLENDMODE_ALPHA );
    }
    
    void background( int r, int g, int b, int a ){
        ofBackground( r, g, b, a );
    }

    void background( int r, int g, int b ){
        ofBackground( r, g, b, 255 );
    }
    void background( int gray, int a ){
        ofBackground( gray, gray, gray, a );
    }
    
    void background( int gray ){
        ofBackground( gray, gray, gray, 255 );
    }
    
    void clear( int r, int g, int b, int a ){
        ofClear( r, g, b, a );
    }

    void clear( int r, int g, int b ){
        ofClear( r, g, b, 255 );
    }
    void clear( int gray, int a ){
        ofClear( gray, gray, gray, a );
    }
    
    void clear( int gray ){
        ofClear( gray, gray, gray, 255 );
    }

    void clear(){
        ofClear( 0, 0, 0, 0 );
    }
    
    void fade( int speed ){
        ofPushStyle();
            ofSetColor( 0, 0, 0, speed );
            ofFill();
            ofDrawRectangle( -1, -1, buffer->getWidth()+1, buffer->getHeight()+1 );
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
    
    void point( int x, int y ){
        ofDrawLine( x, y, x+1, y+1 );
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
        
        ofBeginShape();
        for(int i=0; i<N; ++i ){
            ofVertex( cx + cos(theta)*radius, cy + sin(theta)*radius );
            theta += step;
        }
        ofEndShape( true );
    }
     
    void polypath( int cx, int cy, int radius, int N, double
     theta ){
        float step = M_TWO_PI / float(N);

        for(int i=0; i<N; ++i ){
            ofVertex( cx + cos(theta)*radius, cy + sin(theta)*radius );
            theta += step;
        }
    }
     
    void begin_shape(){
        ofBeginShape();
    }
    
    void next( bool close ){
        ofNextContour( close );
    }
    
    void end_shape( bool close ){
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
        return buffer->getWidth();
    }

    int height(){
        return buffer->getHeight();
    }
    
    void save( const char * path ){
        _saver.grabScreen( 0, 0, ofGetWidth(), ofGetHeight() );
        std::string ap( path );
        if( ! ofFilePath::isAbsolute(ap)  ){
        ap = ofFilePath::getCurrentWorkingDirectory() + "/"+ ap;
        }
        _saver.save( ap );
    }
    
    void save( const char * path, int l ){
        buffer->getFbo( l ).readToPixels( _saver.getPixels() );
        _saver.update();
        std::string ap( path );
        if( ! ofFilePath::isAbsolute(ap)  ){
        ap = ofFilePath::getCurrentWorkingDirectory() + "/"+ ap;
        }
        _saver.save( ap );
    }
    
    void save( const char * path, const char * name ){
        buffer->getFbo( name ).readToPixels( _saver.getPixels() );
        _saver.update();
        std::string ap( path );
        if( ! ofFilePath::isAbsolute(ap)  ){
        ap = ofFilePath::getCurrentWorkingDirectory() + "/"+ ap;
        }
        _saver.save( ap );
    }
}
