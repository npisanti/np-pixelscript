/*====================================================================

	np-pixelscript - little 2d graphics scripting playground
  
	Copyright (c) 2019 Nicola Pisanti <nicola@npisanti.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    
====================================================================*/

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
        ofLogVerbose()<<"[pixelscript] disabling ARB textures for shaders";
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
