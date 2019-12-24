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

namespace lfo{
    
    void setPlayHead( double value );

    double phasor( double speed );
    
    bool clock( int division );
    
    double tick( double speed );
     
    double triangle( double speed );
    double ramp( double speed );
    double saw( double speed );
    double sine( double speed );
    double pulse( double speed, double width );
    double square( double speed );
    
    double triangle( double speed, double phase );
    double ramp( double speed, double phase );
    double saw( double speed, double phase );
    double sine( double speed, double phase );
    double pulse( double speed, double width, double phase );  
    double square( double speed, double phase );  
    
    double noise( double speed );
    double noise( double speed, double x );
    double noise( double speed, double x, double y );
    double noise( double speed, double x, double y, double z );

}
