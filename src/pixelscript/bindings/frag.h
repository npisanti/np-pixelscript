
#pragma once

#include <iostream>
#include "ofMain.h"
#include "../Shader.h"
#include "../Buffer.h"

namespace frag{

    void resources( np::pixelscript::Buffer & buff, std::vector<np::pixelscript::Shader> & reso, float playhead );
    
    void load( const char * name, const char * path );
        
    void apply( const char * name );
    
    void begin( const char * name );
    void uniform( const char * name, float value );
    void uniform( const char * name, float x, float y );
    void uniform( const char * name, float x, float y, float z );
    void uniform( const char * name, float x, float y, float z, float w );
    void finish( const char * name );
}
