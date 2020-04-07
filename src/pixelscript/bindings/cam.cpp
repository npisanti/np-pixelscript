/*====================================================================

	np-pixelscript - little 2d graphics scripting playground
  
	Copyright (c) 2019 Nicola Pisanti <nicola@npisanti.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    
====================================================================*/

#include "px.h"
#include "ofMain.h"

namespace cam {

    ofVideoGrabber _webcam;
    int _w = 320;
    int _h = 240;
    int _id = -1;
    
    
    void resolution( int w, int h ){
        _w = w;
        _h = h;
    }
    
    void open( int id ){
        if( id != _id ){
            _id = id;
            _webcam.setDeviceID( _id );
            _webcam.setDesiredFrameRate(60);
            _webcam.initGrabber( _w, _h);            
        }
    }
    
    void _update(){
        _webcam.update();
    }
    void _close(){
        _webcam.close();
    }

    void draw(){
        _webcam.draw( 0, 0 );
    }
    
    void draw( int x, int y ){
        _webcam.draw( x, y );
    }
    
    void draw( int x, int y, int w, int h ){
        _webcam.draw( x, y, w, h );
    }
}
