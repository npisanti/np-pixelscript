
#include "png.h"

namespace png{
    
    Pair::Pair(){
        index = 0;
        name = "";
    }
    
    std::vector<Pair> * images;
    Pair * current;
    int alignMode;
      
    void init(){
        current = nullptr;
        images = nullptr;
        alignMode = 1;
    }
    
    void resources( std::vector<Pair> & reso ){
        images = &reso;
        auto pback = &images->back();
        current = pback;
    }
    
    void mode( int value ){
        alignMode = value;
    }
 
    void load( const char * path ){

        std::string name = ofFilePath::getBaseName( ofFilePath::getFileName( std::string( path ) ) );

        for(size_t i=0; i<images->size(); ++i ){
            if( images->at(i).name == name ){
                return; // already loaded for that name
            }
        }        
        
        images->back().name = name;

        if( ofFilePath::getFileExt( ofFilePath::getFileName( std::string( path ) )) == "png" ){
            images->back().folder[0].load( path );
        }else{
            // directory 
            ofDirectory dir;
            dir.listDir( path );
            dir.allowExt("png");

            if( dir.size() ){
                images->back().folder.resize( dir.size() );
            }

            for(int i = 0; i < (int)dir.size(); i++){
                images->back().folder[i].load(dir.getPath(i));
            }
        }
        
        images->emplace_back();
        images->back().folder.resize(1);
    }
 
    void select( const char * name ){
        for(size_t i=0; i<images->size(); ++i ){
            if( strcmp(images->at(i).name.c_str(), name) == 0 ){
                current = &(images->at(i));
                current->index = 0;
                return;
            }
        }
        current = &images->back();
        current->index = 0;
        std::cout<<"[pixelscript] "<<name<<" folder not loaded\n";
    }
    
    void frame( int index ){
        current->index = index % int( current->folder.size() );
    }
    
    void pct( double value ){
        if( value >= 1.0 ) value = 0.99999999;
        if( value < 0.0 ) value = 0.0;
        double max = current->folder.size();
        current->index = value * max;
    }
    
    void draw( int x, int y ){
        auto & img = current->folder[current->index];
        switch( alignMode ){
            case 0: 
                img.draw( x, y );                
            break;
            
            case 1:
                img.draw( x - img.getWidth()/2, y - img.getHeight()/2 );
            break;
            
            case 2: default:
                img.draw( x, y - img.getHeight() );
            break;
        }
    }

    int width(){
        return current->folder[current->index].getWidth();
    }
    
    int height(){
        return current->folder[current->index].getHeight();
    }

}
