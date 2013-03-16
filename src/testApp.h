#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxTween.h"

#define PORT 4444

#define LEFT_TWEEN_ID 0
#define RIGHT_TWEEN_ID 1

class testApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofImage rightImage;
    ofImage leftImage;
    
    bool bCompleteLoadingNewLeftImage, bCompleteLoadingNewRightImage;
    
    ofxOscReceiver receiver;
    
    string leftFile, rightFile;
    int leftCameraId, rightCameraId;
    
    int leftAlpha, rightAlpha;
    bool bLeftFadeIn, bRightFadeIn;
    bool bLeftFadeOut, bRightFadeOut;
    ofxTween leftAlphaTween, rightAlphaTween;
    ofxEasingCirc 	easingCirc;
    
    void tweenCompleted(int &id);
};
