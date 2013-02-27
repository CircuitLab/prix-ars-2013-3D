#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofEnableSmoothing();
    ofSetBackgroundAuto(false);
    ofSetCircleResolution(100);
    
    rightImage.loadImage("fujitest1.jpg");
    leftImage.loadImage("fujitest2.jpg");
    
    receiver.setup(PORT);

}

//--------------------------------------------------------------
void testApp::update(){
    while (receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        if (m.getAddress() == "/right/image"){
            rightFile = m.getArgAsString(0);
            rightCameraId = m.getArgAsInt32(1);
            cout << "get osc";
        } else if (m.getAddress() == "/left/image" ){
            leftFile  = m.getArgAsString(0);
            leftCameraId = m.getArgAsInt32(1);
        }
    }

}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableAlphaBlending();
    ofSetColor(100, 100, 100);
    ofRect(0,0,ofGetWidth()/2,ofGetHeight());
    
    ofSetColor(255, 255, 255);
    leftImage.draw(0,0,ofGetWidth()/2,ofGetHeight());
    rightImage.draw(ofGetWidth()/2,0,ofGetWidth()/2,ofGetHeight());
    
    ofDrawBitmapString(leftFile + ofToString(leftCameraId) ,  100,ofGetHeight() -100);
    ofDrawBitmapString(rightFile + ofToString(rightCameraId) , ofGetWidth()/2 + 100,ofGetHeight() -100);

}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if(key == ' '){
        ofBackground(255,255,255);
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}


