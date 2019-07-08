
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
