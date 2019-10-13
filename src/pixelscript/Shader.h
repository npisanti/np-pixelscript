
#pragma once

#include "ofMain.h"
#include "FileWatcher.h"

namespace np{ namespace pixelscript {

class Shader : public FileWatcher {

public:
    Shader();
  
    std::string name;
    ofShader shader;
    
private: 
    
    std::stringstream vertexSrc;
    static bool bDisableARB;

    void reload() override;
    
};

}}
