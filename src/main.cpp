#include "testApp.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main(){
	ofAppGlutWindow window; // create a window
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
	 ofSetupOpenGL(&window, 1280, 760, OF_WINDOW);
    //ofSetupOpenGL(&window, 1000, 800, OF_WINDOW);
	ofRunApp(new testApp()); // start the app
}
