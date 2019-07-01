
#include "px.h"
#include "ofMain.h"

namespace font {
    
    ofTrueTypeFont * font;
    
    void resources( ofTrueTypeFont & f ){
        font = &f;
    }
    
    void load( const char * path, int size ){
        font->load( path, size, false );
    }

    void interline( double value ){
        font->setLineHeight( value );
    }
    
    void spacing( double value ){
        font->setLetterSpacing( value );
    }
    
    void draw( const char * text, int x, int y ){
        font->drawString( text, x, y );
    }
}
