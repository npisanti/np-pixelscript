
#include "frag.h"

namespace frag{
    
np::pixelscript::Buffer * buffer;
std::vector<np::pixelscript::Shader> * shaders;
np::pixelscript::Shader * current;
float clock;

void resources( np::pixelscript::Buffer & buff, std::vector<np::pixelscript::Shader> & reso, float playhead ){
    shaders = &reso;       
    buffer = &buff;
    clock = playhead;
}
 
void load( const char * name, const char * path ){
    for(size_t i=0; i<shaders->size(); ++i ){            
        if( shaders->at(i).name.compare( name )==0 ){
            if( shaders->at(i).getPath().compare( path ) != 0 ){
                std::cout<<"[pixelscript] "<<name<<" name already taken by another shader!\n";
                std::cout<<"frag path is "<<shaders->at(i).getPath()<<"\n";
                std::cout<<"load path is "<<path<<"\n";
            }
            return; // already loaded for that name
        }
    }        
    if( ofFilePath::getFileExt( ofFilePath::getFileName( std::string( path ) )) == "frag" ){
        shaders->emplace_back();            
        shaders->back().name = name;
        shaders->back().load( path );
    }else{
        std::cout<<"[pixelscript] wrong extention loaded for name: "<<name<<"\n";
    }
}

void apply( const char * name ){
    
    for(size_t i=0; i<shaders->size(); ++i ){

        if( shaders->at(i).name.compare(name) == 0 ){
            current = &(shaders->at(i));

            buffer->swap();

            buffer->begin();
                //ofClear( 0, 0, 0, 0 );

                current->shader.begin();
    
                current->shader.setUniform1f( "u_time", clock );

                #ifdef __ARM_ARCH
                current->shader.setUniform2f( "u_resolution", buffer->getWidth()-1, buffer->getHeight()-1 );
                #else
                current->shader.setUniform2f( "u_resolution", buffer->getWidth(), buffer->getHeight() );
                #endif

                current->shader.setUniformTexture("u_tex0", buffer->getTexture(), buffer->getTexture().getTextureData().textureID );

                ofSetColor(255, 255, 255, 255);
                ofFill();
                ofDrawRectangle(0, 0, buffer->getWidth(), buffer->getHeight() );
                current->shader.end();
            buffer->end();
            
            return;
        }
    }
    std::cout<<"[pixelscript] "<<name<<" shader not loaded\n";
}


void begin( const char * name ){
        
    for(size_t i=0; i<shaders->size(); ++i ){

        if( shaders->at(i).name.compare(name) == 0 ){
            current = &(shaders->at(i));

            buffer->swap();

            buffer->begin();
                //ofClear( 0, 0, 0, 0 );

                current->shader.begin();
                
                #ifdef __ARM_ARCH
                current->shader.setUniform2f( "u_resolution", buffer->getWidth()-1, buffer->getHeight()-1 );
                #else
                current->shader.setUniform2f( "u_resolution", buffer->getWidth(), buffer->getHeight() );
                #endif

                current->shader.setUniformTexture("u_tex0", buffer->getTexture(), buffer->getTexture().getTextureData().textureID );
                
                current->shader.setUniform1f( "u_time", clock );

            return;
        }
    }
    std::cout<<"[pixelscript] "<<name<<" shader not loaded used in frag.begin(), brace yourself for frag.finish() errors\n";
}

void finish( const char * name ){
    ofSetColor(255, 255, 255, 255);
    ofFill();
    ofDrawRectangle(0, 0, buffer->getWidth(), buffer->getHeight() );
    current->shader.end();
    buffer->end();
}

void uniform( const char * name, float value ){
    current->shader.setUniform1f( name, value );
}

void uniform( const char * name, float x, float y ){
    current->shader.setUniform2f( name, x, y );
}

void uniform( const char * name, float x, float y, float z ){
    current->shader.setUniform3f( name, x, y, z );
}

void uniform( const char * name, float x, float y, float z, float w ){
    current->shader.setUniform4f( name, x, y, z, w );
}


}// end of namespace

