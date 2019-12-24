/*====================================================================

	np-pixelscript - little 2d graphics scripting playground
  
	Copyright (c) 2019 Nicola Pisanti <nicola@npisanti.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    
====================================================================*/

#include "FileWatcher.h"

np::FileWatcher::FileWatcher(){
    
    parameters.setName("label me");
    interval = 0.05f;
    timePassed = 0.0f;
    
}

void np::FileWatcher::load( std::string path, bool watch ) {
    filepath = path;
    filename = ofFilePath::getFileName( filepath ); 

    if( ! ofFilePath::isAbsolute( filepath )){
        filepath = ofFilePath::getCurrentWorkingDirectory() + "/" + filepath;
    }

    ofFile file( filepath );
    if( file.exists() ){
        if( watch ){
            ofAddListener(ofEvents().update, this, &FileWatcher::checkFile);
            writeTimestamp = boost::filesystem::last_write_time( filepath );
        }
        reload();
        ofLogNotice() << "["<<filename<<"] file loaded";
    }else{
        ofLogError() << "[np::FileWatcher] file to load at "<<filepath <<" does not exists\n";
    }
    
    parameters.setName( filename );
}


void np::FileWatcher::checkFile(ofEventArgs &args){
    timePassed += ofGetLastFrameTime();
    if( timePassed > interval ){
        time_t checkTimestamp = boost::filesystem::last_write_time( filepath );
        if( checkTimestamp != writeTimestamp){
            writeTimestamp = checkTimestamp;
            reload();
            ofLogNotice() << "["<<filename<<"] file reloaded";
        }
    }
}
