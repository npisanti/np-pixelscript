/*====================================================================

	np-pixelscript - little 2d graphics scripting playground
  
	Copyright (c) 2019 Nicola Pisanti <nicola@npisanti.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    
====================================================================*/

#include "lfo.h"

namespace lfo{
    double playhead;
    
    void setPlayHead( double value ){
        playhead = value;
    }
    
    bool clock( int division ){
        if( ofGetFrameNum()%division == 0 ){
            return true;
        }
        return false;
    }
    
    double tick( double speed ){
        return floor( playhead*speed );
    }
    
    double phasor( double speed ){
        double ph = playhead*speed;
        ph = ph - (long) ph;
        return ph;
    }
     
    double triangle( double speed ){
        double ph = playhead*speed;
        ph = ph - (long) ph;
        return 1.0 - (abs( ph - 0.5 ) * 2.0 );
    }
    
    double ramp( double speed ){
        double ph = playhead*speed;
        ph = ph - (long) ph;
        return ph;
    }
    
    double saw( double speed ){
        double ph = playhead*speed;
        ph = ph - (long) ph;
        return 1.0f - ph;
    }
    
    double sine( double speed ){
        double ph = playhead*speed;
        ph = ph - (long) ph;
        return 1.0 - (cos(ph*TWO_PI)*0.5 + 0.5);
    }
    
    double pulse( double speed, double width ){
        double ph = playhead*speed;
        ph = ph - (long) ph;
        double value = ( ph>width ) ? 1.0 : 0.0;
        return value;
    }
    
    double square( double speed ){
        double ph = playhead*speed;
        ph = ph - (long) ph;
        double value = ( ph>0.5 ) ? 1.0 : 0.0;
        return value;
    }
    

    double triangle( double speed, double phase ){
        double ph = playhead*speed;
        ph += phase;
        ph = ph - (long) ph;
        return 1.0 - (abs( ph - 0.5 ) * 2.0 );
    }
    
    double ramp( double speed, double phase ){
        double ph = playhead*speed;
        ph += phase;
        ph = ph - (long) ph;
        return ph;
    }
    
    double saw( double speed, double phase ){
        double ph = playhead*speed;
        ph += phase;
        ph = ph - (long) ph;
        return 1.0f - ph;
    }
    
    double sine( double speed, double phase ){
        double ph = playhead*speed;
        ph += phase;
        ph = ph - (long) ph;
        return 1.0 - (cos(ph*TWO_PI)*0.5 + 0.5);
    }
    
    double pulse( double speed, double width, double phase ){
        double ph = playhead*speed;
        ph += phase;
        ph = ph - (long) ph;
        double value = ( ph>width ) ? 1.0 : 0.0;
        return value;
    }
    
    double square( double speed, double phase ){
        double ph = playhead*speed;
        ph += phase;
        ph = ph - (long) ph;
        double value = ( ph>0.5 ) ? 1.0 : 0.0;
        return value;
    }
    
    double noise( double speed ){ return ofNoise( playhead*speed, 0.0f ); }   
    
    double noise( double speed, double x ){ return ofNoise( playhead*speed, x ); }
    
    double noise( double speed, double x, double y ){ return ofNoise( playhead*speed, x, y ); }
    
    double noise( double speed, double x, double y, double z ){ return ofNoise( playhead*speed, x, y, z ); }    
    
}
