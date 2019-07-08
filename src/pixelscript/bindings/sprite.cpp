
#include "sprite.h"

namespace sprite{
    
    std::vector<SpriteSheet> * sprites;
    SpriteSheet * current;
      
    void init(){
        current = nullptr;
        sprites = nullptr;
    }
    
    void resources( std::vector<SpriteSheet> & reso ){
        sprites = &reso;
        auto pback = &sprites->back();
        current = pback;
    }
 
    void load( const char * path, int w, int h, int mode ){
        std::string name = ofFilePath::removeExt( ofFilePath::getFileName( std::string( path ) ) );
        
        for(size_t i=0; i<sprites->size(); ++i ){
            if( sprites->at(i).name == name ){
                sprites->at(i).load( std::string( path ), w, h, mode );
                return;
            }
        }

        bool loaded = sprites->back().load( std::string( path ), w, h, mode );
        if( loaded ){
            sprites->emplace_back();
        }
    }
 
    void bind( const char * name ){
        auto pback = &sprites->back();
        if( current != pback ){
            current->unbind();
            current = pback;
        }
        for(size_t i=0; i<sprites->size(); ++i ){
            if( strcmp(sprites->at(i).name.c_str(), name) == 0 ){
                current = &(sprites->at(i));
                current->bind();
            }
        }
    }
    
    void unbind(){
        auto pback = &sprites->back();
        if( current != pback ){
            current->unbind();
            current = pback;
        }
    }

    void frame( int index ){
        current->setFrame( index );
    }
    
    void pct( double value ){
        current->setFramePercent( value );
    }
    
    void draw( int x, int y ){
        current->draw( x, y );
    }

    int width(){
        return current->spriteSize.x;
    }
    
    int height(){
        return current->spriteSize.y;
    }
    
    void clean(){
        unbind();
    }

}





// -------------------- SpriteSheet class ----------------------------

#define USE_TRIANGLE_STRIP

sprite::SpriteSheet::SpriteSheet()
{
	bInitialized = false;
    spriteSize = glm::vec2( 0, 0 );
    offset = glm::vec2( 0, 0 );
}

bool sprite::SpriteSheet::load( std::string path, int spriteWidth, int spriteHeight, int mode )
{
    bool loaded = png.load( path );

    if( loaded ){
        spriteSize = glm::vec2( spriteWidth, spriteHeight );

        nFrames = png.getWidth() / spriteWidth;
        
        switch( mode ){
            case 0:
                offset.x = 0;
                offset.y = -spriteHeight;
            break;
            
            case 1:
                offset.x = -spriteWidth/2;
                offset.y = -spriteHeight/2;
            break;
            
            default: 
                offset.x = 0;
                offset.y = 0;
            break;
        }
        
        cursor = 0;

        setupSpriteVbo();
        bInitialized = true;
        
        name = ofFilePath::removeExt( ofFilePath::getFileName( path ) );
        
        return true;
    }else{
        ofLogError()<<"[np-pixelscript] invalid spritesheet path\n";
        return false;
    }
}

void sprite::SpriteSheet::setFrame( int index )
{
    cursor = index;
    if(cursor>=nFrames){
        cursor = nFrames-1;
    }
    if( cursor < 0 ){ 
        cursor = 0; 
    }
}

void sprite::SpriteSheet::setFramePercent( double pct ){
    cursor = pct * nFrames;
    if(cursor>=nFrames){
        cursor = nFrames-1;
    }
    if( cursor < 0 ){ 
        cursor = 0; 
    }
}

void sprite::SpriteSheet::draw(float x, float y)
{
	if (!bInitialized) {
		return;
	}
    
	ofPushMatrix();
	ofTranslate( x + offset.x, y + offset.y );

#ifdef USE_TRIANGLE_STRIP
	vbo.draw(GL_TRIANGLE_STRIP, cursor*4, 4);
#else
	vbo.draw(GL_TRIANGLES, cursor*6, 6);
#endif

	ofPopMatrix();
}

void sprite::SpriteSheet::bind()
{
    png.getTexture().bind();
}

void sprite::SpriteSheet::unbind()
{
    png.getTexture().unbind();
}

void sprite::SpriteSheet::setupSpriteVbo()
{
	vector<glm::vec2> verts;
	vector<glm::vec2> texCoords;

	glm::vec2 tlVec(0, 0);
	glm::vec2 trVec(spriteSize.x, 0);
	glm::vec2 blVec(0, spriteSize.y);
	glm::vec2 brVec(spriteSize.x, spriteSize.y);

	glm::vec2 origin(0, 0);
	for (int i=0; i<nFrames; i++)
	{
#ifdef USE_TRIANGLE_STRIP
		// first triangle
		verts.push_back(glm::vec2(0, 0));
		texCoords.push_back(origin);

		verts.push_back(glm::vec2(spriteSize.x, 0));
		texCoords.push_back(origin + trVec);

		verts.push_back(glm::vec2(0, spriteSize.y));
		texCoords.push_back(origin + blVec);

		verts.push_back(glm::vec2(spriteSize.x, spriteSize.y));
		texCoords.push_back(origin + brVec);


#else								// GL_TRIANGLES
		// first triangle
		verts.push_back(glm::vec2(0, 0));
		texCoords.push_back(origin);

		verts.push_back(glm::vec2(spriteSize.x, 0));
		texCoords.push_back(origin + trVec);

		verts.push_back(glm::vec2(spriteSize.x, spriteSize.y));
		texCoords.push_back(origin + brVec);



		// second triangle
		verts.push_back(glm::vec2(spriteSize.x, spriteSize.y));
		texCoords.push_back(origin + brVec);

		verts.push_back(glm::vec2(0, spriteSize.y));
		texCoords.push_back(origin + blVec);

		verts.push_back(glm::vec2(0, 0));
		texCoords.push_back(origin);
#endif


		// advance origin
		origin.x += spriteSize.x;
#ifdef TARGET_OPENGLES
		if (origin.x + spriteSize.x > 1) { 		// normalized texture coords
#else
		if (origin.x + spriteSize.x > png.getTexture().getWidth()) {
#endif
			origin.y += spriteSize.y;
			origin.x = 0;
		}
	}

	vbo.setVertexData(&verts[0], verts.size(), GL_STATIC_DRAW);
	vbo.setTexCoordData(&texCoords[0], texCoords.size(), GL_STATIC_DRAW);
}

