#pragma once

#include "ofMain.h"
#include "Settings.h"
#include "ofxPiMapper.h"
#include "CustomSource.h"
#include "CrossSource.h"
#include "VideoSource.h"
#include "magSlideShowSource.h"

// ScreenCurtain
#include "ofxScreenCurtain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);

    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    
    void setNextPreset();

    ofxPiMapper piMapper;

    // By using a custom source that is derived from FboSource
    // you will be able to see the source listed in sources editor
    CustomSource *customSource;
    CrossSource *crossSource;
    magSlideShowSource *slideShowSource;
    
    // Curtain
    void raiseCurtain();
    void dropCurtain();
    
    ofxScreenCurtain curtain;
    bool goNextPreset;

};
