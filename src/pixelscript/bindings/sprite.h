
#pragma once

#include <iostream>
#include "ofMain.h"

namespace sprite{
    class SpriteSheet;

    void init();
    void resources( std::vector<SpriteSheet> & reso );
    
    void load( const char * path, int w, int h );
    
    void bind( const char * name );
    void unbind();
    
    int width();
    int height();

    void frame( int index );
    void pct( double value );
    void draw( int x, int y );

    void clean();
    
    // ---------------------------------------------------------------
    class SpriteSheet {
    public:

        SpriteSheet();

        bool load( std::string path, int spriteWidth, int spriteHeight );
        
        void draw(float x=0, float y=0);

        void bind();
        void unbind();
        
        void setFrame( int index );
        void setFramePercent( double pct );
        
        std::string name;
        glm::vec2 spriteSize;
        
    private:
        bool bInitialized;
        
        ofImage png;
        
        int nFrames;
        int cursor;

        void setupSpriteVbo();
        ofVbo vbo;

        void initVbo();

    };

}
