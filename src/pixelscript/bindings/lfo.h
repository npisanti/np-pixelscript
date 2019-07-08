
#pragma once

#include <iostream>
#include "ofMain.h"

namespace lfo{
    
    struct Phasor {
        double phase;
        double playhead;
        double speed;
        bool freerun;
        
        void init();
        void update();
        void shift( double value );
    };
    
    void init();
    void resources( std::vector<Phasor> & phas );
    void resize( size_t size );

    void speed( double value, size_t lfoIndex=0 );
    void retrigger( size_t lfoIndex );
    void oneshot( bool value = true, size_t lfoIndex=0 );
    void shift( double value, size_t lfoIndex=0 );

    double triangle( size_t lfoIndex=0 );
    double ramp( size_t lfoIndex=0 );
    double saw( size_t lfoIndex=0 );
    double sine( size_t lfoIndex=0 );
    double pulse( double width, size_t lfoIndex=0 );
    double square( size_t lfoIndex=0 );
    
    double noise( size_t lfoIndex );
    double noise( double x, size_t lfoIndex );
    double noise( double x, double y, size_t lfoIndex );
    double noise( double x, double y, double z, size_t lfoIndex );

}
