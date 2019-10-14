
#include "Shader.h"

bool np::pixelscript::Shader::bDisableARB = true;

np::pixelscript::Shader::Shader(){

    name = "";
    
    vertexSrc.str(std::string());
#ifdef __ARM_ARCH
    vertexSrc  << "attribute vec4 position;\n";
    vertexSrc  << "attribute vec2 texcoord;\n";
    vertexSrc  << "uniform vec2 u_resolution;\n";
    vertexSrc  << "uniform mat4 modelViewProjectionMatrix;\n";
    vertexSrc  << "varying vec2 texcoord0;\n";
    vertexSrc  << "void main(void){\n";
    vertexSrc  << "\tgl_Position = modelViewProjectionMatrix * position;\n";
    vertexSrc  << "\ttexcoord0 = texcoord;\n";
    vertexSrc  << "}\n";
#else
    vertexSrc  << "varying vec2 texcoord0;\n";
    vertexSrc  << "uniform vec2 u_resolution;\n";
    vertexSrc  << "void main(void){\n";
    vertexSrc  << "\ttexcoord0 = gl_Vertex.xy;\n";
    vertexSrc  << "\tgl_Position = ftransform();\n";
    vertexSrc  << "}\n";
#endif
    if( bDisableARB ){
        ofDisableArbTex();
        ofLogNotice()<<"[pixelscript] disabling ARB textures for shaders";
        bDisableARB = false;
    } 
}

void np::pixelscript::Shader::reload() {
    if( filepath!="" ){
        shader.setupShaderFromSource( GL_VERTEX_SHADER, vertexSrc.str() );
        shader.setupShaderFromFile( GL_FRAGMENT_SHADER, filepath );
        shader.bindDefaults();
        shader.linkProgram();
    }    
}
