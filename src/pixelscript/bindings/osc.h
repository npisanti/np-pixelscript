
#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

namespace osc{
    
    void setMessage( std::string addr, std::vector<float> args );
    
    void resources( ofxOscReceiver & rec, ofxOscSender & send );
    
    void setup_receiver( int port );
    void setup_sender( const char * addr, int port );

    const char * address();
    double number( int index );

}
