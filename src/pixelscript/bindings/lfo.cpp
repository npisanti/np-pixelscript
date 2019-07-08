
#include "lfo.h"

namespace lfo{
    
    std::vector<Phasor> * phasors;
    
    void lfo::Phasor::init(){
        phase = 0.0;
        playhead = ofRandom( 420.0f );
        speed = 1.0 / 128.0;
        freerun = true;
    }
    
    void lfo::Phasor::update(){
        phase += speed;
        playhead += speed;
        if( freerun ){
            if( phase >= 1.0 ){
                phase = phase - floor( phase );
            }
        }else{
            if( phase >= 1.0 ){
                phase = 1.0;
            }
        }
    }
    
    void lfo::Phasor::shift( double value ){
        phase += value;
        playhead += value;
        if( phase >= 1.0 || phase < 0.0 ){
            phase = phase - floor( phase );
        }
    }
    
    void speed( double value, size_t lfoIndex ){
        if( lfoIndex < phasors->size() ){
            phasors->at(lfoIndex).speed = value;
        }
    }
    
    void retrigger( size_t lfoIndex ){
        if( lfoIndex < phasors->size() ){
            phasors->at(lfoIndex).phase = 0.0;
        }
    }
    
    void oneshot(  bool value, size_t lfoIndex ){
        if( lfoIndex < phasors->size() ){
            phasors->at(lfoIndex).freerun = !value;
        }
    }
    void shift( double value, size_t lfoIndex ){
        if( lfoIndex < phasors->size() ){
            phasors->at(lfoIndex).shift( value );
        }
    }

    void init(){
        phasors = nullptr;
    }
    
    void resources( std::vector<Phasor> & phas ){
        phasors = &phas;
    }
    
    void resize( size_t size ){
        phasors->resize( size );
        for( auto & phasor : *phasors ){
            phasor.init();
        }
    }
    
    double triangle( size_t lfoIndex ){
        return abs( (phasors->at(lfoIndex).phase * 2.0) - 1.0 );
    }
    
    double ramp( size_t lfoIndex ){
        return phasors->at(lfoIndex).phase;
    }
    
    double saw( size_t lfoIndex ){
        return 1.0f - phasors->at(lfoIndex).phase;
    }
    
    double sine( size_t lfoIndex ){
        return (sin(phasors->at(lfoIndex).phase*TWO_PI)*0.5 + 0.5);
    }
    
    double pulse( double width, size_t lfoIndex ){
        double value = ( phasors->at(lfoIndex).phase < width ) ? 1.0 : 0.0;
        return value;
    }
    
    double square( size_t lfoIndex ){
        double value = ( phasors->at(lfoIndex).phase < 0.5 ) ? 1.0 : 0.0;
        return value;
    }
    
    double noise( size_t lfoIndex ){ return ofNoise( phasors->at(lfoIndex).playhead, 0.0f ); }   
    
    double noise( double x, size_t lfoIndex ){ return ofNoise( phasors->at(lfoIndex).playhead, x ); }
    
    double noise( double x, double y, size_t lfoIndex ){ return ofNoise( phasors->at(lfoIndex).playhead, x, y ); }
    
    double noise( double x, double y, double z, size_t lfoIndex ){ return ofNoise( phasors->at(lfoIndex).playhead, x, y, z ); }    
    
}
