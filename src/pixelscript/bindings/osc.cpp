/*====================================================================

	np-pixelscript - little 2d graphics scripting playground
  
	Copyright (c) 2019 Nicola Pisanti <nicola@npisanti.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    
====================================================================*/

#include "osc.h"

#include <iostream>

namespace osc{
    
    ofxOscReceiver * receiver;
    std::vector<TaggedSender> * senders;
    const ofxOscMessage * message;
    ofxOscMessage toSend;
    int selected;
    std::string _address;
    
    void setMessage( const ofxOscMessage & msg ){
        message = &msg;
    }
    
    void resources( ofxOscReceiver & rec, std::vector<TaggedSender> & send){
        senders = &send;
        receiver = &rec;
        selected = 0;
    }
    
    void setup_receiver( int port ){
        receiver->setup( port );
        std::cout<<"[ osc ] receiving OSC on port "<<port<<"\n";
    }
    
    void setup_sender( const char * name, const char * addr, int port ){
        
        for(size_t i=0; i<senders->size(); ++i ){
            if( senders->at(i).name == name ){
                if( senders->at(i).address!=addr || senders->at(i).port!=port ){
                    std::cout<<"[ osc.setup_sender ] "<<name<<" name already taken by another sender!\n";
                }
                return;
            }
        }        

        senders->emplace_back();
        std::string a = addr;
        senders->back().sender.setup( a, port );
        std::cout<<"[ osc ] sending OSC to port "<<port<<", address "<<a<<"\n";
    }

    const char * address(){ 
        _address = message->getAddress();
        return _address.c_str(); 
    }
    
    double number( int i ){
        auto t = message->getArgType(i); 
        if( t == OFXOSC_TYPE_INT32 ){
            return double(  message->getArgAsInt32(i) );
        }else if( t == OFXOSC_TYPE_FLOAT ){
            return double(  message->getArgAsFloat(i) );
        }
        return 0.0;
    }
    
    const char * string( int i ){
        auto t = message->getArgType(i); 
        if( t == OFXOSC_TYPE_STRING ){
            return message->getArgAsString(i).c_str();
        }
        return "";
    }

    void begin( const char * name ){
        for(size_t i=0; i<senders->size(); ++i ){
            if( senders->at(i).name == name ){
                selected = i;
                toSend = ofxOscMessage();
                return;
            }
        }
        std::cout<<"[ osc.begin ] sender with given name not found!\n";
    }
    
    void set_address( const char * str ){
        toSend.setAddress( str );
    }
    
    void add_string( const char * str ){
        toSend.addStringArg( str );
    }
    
    void add_float( double value ){
        toSend.addFloatArg( value );
    }
    
    void add_int( double num ){
        toSend.addIntArg( int(num) );
    }
    
    void send(){
        senders->at(selected).sender.sendMessage( toSend, false );
    }
    
    void route( const char * name ){
        for(size_t i=0; i<senders->size(); ++i ){
            if( senders->at(i).name == name ){
                senders->at(i).sender.sendMessage( *message, false );
                return;
            }
        }
        std::cout<<"[ osc.route ] sender with given name not found!\n";
    }
    
    void route( const char * name, const char * address ){
        for(size_t i=0; i<senders->size(); ++i ){
            if( senders->at(i).name == name ){
                toSend = *message;
                toSend.setAddress( address );
                senders->at(i).sender.sendMessage( toSend, false );
                return;
            }
        }
        std::cout<<"[ osc.route ] sender with given name not found!\n";
    }
}
