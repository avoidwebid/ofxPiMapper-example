#include "ofApp.h"

void ofApp::setup(){
    // Screen curtain
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    
	ofBackground(0);

	// Enable or disable audio for video sources globally
	// Set this to false to save resources on the Raspberry Pi
	ofx::piMapper::VideoSource::enableAudio = true;
	ofx::piMapper::VideoSource::useHDMIForAudio = false;

	// Add our CustomSource to list of fbo sources of the piMapper
	// FBO sources should be added before piMapper.setup() so the
	// piMapper is able to load the source if it is assigned to
	// a surface in XML settings.
	crossSource = new CrossSource();
	customSource = new CustomSource();

	// Create the slide show source.
	slideShowSource = new magSlideShowSource();

	// Register our sources:
	piMapper.registerFboSource(crossSource);
	piMapper.registerFboSource(customSource);
	piMapper.registerFboSource(slideShowSource);
	piMapper.setup();

	// The info layer is hidden by default, press <i> to toggle
	// piMapper.showInfo();

	ofSetFullscreen(Settings::instance()->getFullscreen());
	ofSetEscapeQuitsApp(false);
    ofSetLogLevel(OF_LOG_VERBOSE);

    slideShowSource->play();
    
    goNextPreset = false;
}

void ofApp::raiseCurtain(){
    if (curtain.isReady()){
        curtain.raiseCurtain(
                             0.30 /*go up duration*/,
                             true /*regardless curtain status*/
                             );
    }
}

void ofApp::dropCurtain(){
    if (curtain.isReady()){
        curtain.dropCurtain(
                            0.30 /*go down duration*/,
                            true /*regardless curtain status*/
                            );
    }
}

void ofApp::setNextPreset(){
    curtain.dropAndRaiseCurtain(
                                0.30 /*drop duration*/,
                                0.1 /*stay down duration*/,
                                0.25 /*rise duration*/,
                                true /*do it regardless, even if curtain is moving*/
                                );
}

void ofApp::update(){
    curtain.update( 0.016666f );
    if(curtain.hasReachedBottom()){
        piMapper.setNextPreset();
    }
	piMapper.update();
}

void ofApp::draw(){
	piMapper.draw();
    curtain.draw();
}

void ofApp::keyPressed(int key){
    switch (key) {
        case 'l':
            raiseCurtain();
            break;
        case 'b':
            dropCurtain();
            break;
        case 'n':
            setNextPreset();
            break;
        default:
            piMapper.keyPressed(key);
    }
}

void ofApp::keyReleased(int key){
	piMapper.keyReleased(key);
}

void ofApp::mousePressed(int x, int y, int button){
	piMapper.mousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button){
	piMapper.mouseReleased(x, y, button);
}

void ofApp::mouseDragged(int x, int y, int button){
	piMapper.mouseDragged(x, y, button);
}
