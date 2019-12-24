/*====================================================================

	np-pixelscript - little 2d graphics scripting playground
  
	Copyright (c) 2019 Nicola Pisanti <nicola@npisanti.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    
====================================================================*/

#ifndef NP_FILEWATCHER_DEFINED
#define NP_FILEWATCHER_DEFINED

#include "ofMain.h"

namespace np{
    
class FileWatcher{

public:
    FileWatcher();
    
    void load( std::string path, bool watch=true );
    std::string getPath() const { return filepath; };

    float interval;

    ofParameterGroup parameters;

protected:
    std::string filepath;
    std::string filename;

    virtual void reload(){};

private:
    // --- variables for live check ---
    time_t writeTimestamp;
    float timePassed;
    void checkFile(ofEventArgs &args);
};
    
    
}

#endif // NP_FILEWATCHER_DEFINED
