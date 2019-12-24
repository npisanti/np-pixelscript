/*====================================================================

	np-pixelscript - little 2d graphics scripting playground
  
	Copyright (c) 2019 Nicola Pisanti <nicola@npisanti.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    
====================================================================*/

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

namespace osc{
    
    struct TaggedSender{
        std::string name;
        std::string address;
        int port;
        ofxOscSender sender;
    };
    
    void setMessage( const ofxOscMessage & msg );
    
    void resources( ofxOscReceiver & rec, std::vector<TaggedSender> & send );
    
    void setup_receiver( int port );
    void setup_sender( const char * name, const char * addr, int port );

    const char * address();
    double number( int i );
    const char * string( int i );
    
    void begin( const char * name );
    void set_address( const char * str );
    void add_string( const char * str );
    void add_float( double value );
    void add_int( double num );
    void send();
    
    void route( const char * name );
    void route( const char * name, const char * address );

}
