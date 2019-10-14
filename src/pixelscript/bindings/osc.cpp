
#include "osc.h"

#define MAXARGUMENTS 16
#include <iostream>

namespace osc{
    
    float osc_numbers [MAXARGUMENTS];
    ofxOscReceiver * receiver;
    ofxOscSender * sender;
    std::string _address;
    int max;
    
    void setMessage( std::string addr, std::vector<float> args ){
        _address = addr;
        max = args.size();
        for( size_t i=0; i<args.size() && i<MAXARGUMENTS; ++i ){
            osc_numbers[i] = args[i];
        }
    }
    
    void resources( ofxOscReceiver & rec, ofxOscSender & sendr ){
        sender = &sendr;
        receiver = &rec;
    }
    
    void setup_receiver( int port ){
        receiver->setup( port );
        std::cout<<"[ pixelscript ] receiving OSC on port "<<port<<"\n";
    }
    
    void setup_sender( const char * addr, int port ){
        std::string a = addr;
        sender->setup( a, port );
        std::cout<<"[ pixelscript ] sending OSC to port "<<port<<", address "<<a<<"\n";
    }

    const char * address(){ 
        return _address.c_str(); 
    }
    
    double number( int i ){
        if( i >=0 && i<max && i < MAXARGUMENTS ){
            return osc_numbers[i];
        }else{
            return 0.0;
        }
    }
    
}
