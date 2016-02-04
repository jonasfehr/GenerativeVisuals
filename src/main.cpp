#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"
#include "defines.h"

//========================================================================
int main( ){
    ofAppGlutWindow window;
    window.setGlutDisplayString("rgba double samples>=4");
    ofSetupOpenGL(&window, RENDERWIDTH/10+230, (RENDERHEIGHT/10+10)*5+10, OF_WINDOW);
    ofRunApp( new ofApp());
}

