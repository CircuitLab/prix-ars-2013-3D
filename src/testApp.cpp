#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetFrameRate(60);
    ofEnableSmoothing();
    ofSetBackgroundAuto(false);
    ofSetCircleResolution(100);
    ofEnableAlphaBlending();
    
    rightImage.loadImage("fujitest1.jpg");
    leftImage.loadImage("fujitest2.jpg");
    
    bCompleteLoadingNewLeftImage = bCompleteLoadingNewRightImage = true;
    
    receiver.setup(PORT);
        
    leftAlpha = 255;
    leftAlphaTween.setParameters(LEFT_TWEEN_ID, easingCirc, ofxTween::easeOut, 0, 255, 500, 0);
    ofAddListener(leftAlphaTween.end_E, this, &testApp::tweenCompleted);
    
    rightAlpha = 255;
    rightAlphaTween.setParameters(RIGHT_TWEEN_ID, easingCirc, ofxTween::easeOut, 0, 255, 500, 0);
    ofAddListener(rightAlphaTween.end_E, this, &testApp::tweenCompleted);
}

//--------------------------------------------------------------
void testApp::update()
{
    while (receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        if (m.getAddress() == "/url/right"){
            rightFile = m.getArgAsString(0);
            cout << "rightFile: " << rightFile << endl;
            
            bCompleteLoadingNewRightImage = false;
            
            rightAlphaTween.setParameters(RIGHT_TWEEN_ID, easingCirc, ofxTween::easeOut, rightAlpha, 0, 500, 0);
        } else if (m.getAddress() == "/url/left" ){
            leftFile  = m.getArgAsString(0);
            cout << "leftFile: " << leftFile << endl;
            
            bCompleteLoadingNewLeftImage = false;
            
            leftAlphaTween.setParameters(LEFT_TWEEN_ID, easingCirc, ofxTween::easeOut, leftAlpha, 0, 500, 0);
        }
    }
    
    leftAlpha = leftAlphaTween.update();
    rightAlpha = rightAlphaTween.update();
        
    if (0 == leftAlpha && leftImage.isAllocated()) {
        // leftAlphaTween.setParameters(LEFT_TWEEN_ID, easingCirc, ofxTween::easeOut, leftAlpha, 255, 500, 0);
        //bLeftFadeIn = true;
    }
    
    if (0 == rightAlpha && rightImage.isAllocated()) {
        // rightAlphaTween.setParameters(RIGHT_TWEEN_ID, easingCirc, ofxTween::easeOut, rightAlpha, 255, 500, 0);
        //bRightFadeIn = true;
    }
}

//--------------------------------------------------------------
void testApp::draw()
{
    ofSetColor(255);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    if (leftImage.isAllocated()) {
        ofPushStyle();
        ofSetColor(255, 255, 255, leftAlpha);
        leftImage.draw(0, 0, ofGetWidth() / 2, ofGetHeight());
        ofPopStyle();
    }
    
    if (rightImage.isAllocated()) {
        ofPushStyle();
        ofSetColor(255, 255, 255, rightAlpha);
        rightImage.draw(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());
        ofPopStyle();
    }
    
    ofDrawBitmapString(leftFile + ofToString(leftCameraId) ,  100,ofGetHeight() -100);
    ofDrawBitmapString(rightFile + ofToString(rightCameraId) , ofGetWidth()/2 + 100,ofGetHeight() - 100);
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if(key == ' '){
        ofBackground(255, 255, 255);
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
    if (ofGetWidth() / 2 > x) {
        bCompleteLoadingNewLeftImage = false;
        
        leftAlphaTween.setParameters(LEFT_TWEEN_ID, easingCirc, ofxTween::easeOut, leftAlpha, 0, 500, 0);
        leftFile = "http://cache5.amanaimages.com/cen3tzG4fTr7Gtw1PoeRer/22973000320.jpg";
    } else {
        bCompleteLoadingNewRightImage = false;
        
        rightAlphaTween.setParameters(RIGHT_TWEEN_ID, easingCirc, ofxTween::easeOut, rightAlpha, 0, 500, 0);
        rightFile = "http://cache5.amanaimages.com/cen3tzG4fTr7Gtw1PoeRer/22973000320.jpg";
    }
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

//--------------------------------------------------------------
void testApp::tweenCompleted(int &id)
{
    cout << "tween completed. id: " << id << endl;
    
    if (LEFT_TWEEN_ID == id) {
        cout << "bLeftFadeOut: " << bLeftFadeOut << endl;
        cout << "bLeftFadeIn: " << bLeftFadeIn << endl;
        
        if (!bCompleteLoadingNewLeftImage) {
            cout << "load left: " << leftFile << endl;
            leftImage.clear();
            leftImage.loadImage(leftFile);
            
            leftAlphaTween.setParameters(LEFT_TWEEN_ID, easingCirc, ofxTween::easeOut, leftAlpha, 255, 500, 0);
            
            bCompleteLoadingNewLeftImage = true;
        }
    } else if (RIGHT_TWEEN_ID == id) {
        if (!bCompleteLoadingNewRightImage) {
            cout << "load right: " << rightFile << endl;
            rightImage.clear();
            rightImage.loadImage(rightFile);
            
            rightAlphaTween.setParameters(RIGHT_TWEEN_ID, easingCirc, ofxTween::easeOut, rightAlpha, 255, 500, 0);
            
            bCompleteLoadingNewRightImage = true;
        }
    }
}
