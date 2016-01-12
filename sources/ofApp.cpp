#include "ofApp.h"

ofApp::ofApp() : detector_(250, 250) {
}

//--------------------------------------------------------------
void ofApp::setup() {
  crop_size_.set(500, 500);
//  ofSetVerticalSync(false);
  capture_layer_ = make_unique<
    CaptureLayer>(ofGetWidth(), ofGetHeight(), crop_size_.x, crop_size_.y);
  alert_layer_ = make_unique<AlertLayer>();
  detector_.startThread();
}

//--------------------------------------------------------------
void ofApp::update() {
  capture_layer_->update();
  if (!detector_.isThreadRunning()) {
    auto& cropped_frame = capture_layer_->getCroppedFrame();
    detector_.start(cropped_frame);
  }
  capture_layer_->setMatchID(detector_.getMatchID());
  alert_layer_->setMatchID(detector_.getMatchID());
  if (detector_.getMatchID() != -1) {
    alert_layer_->setShowText(true);
  }
  else {
    alert_layer_->setShowText(false);
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  capture_layer_->draw(0, 0);
  
  detector_.draw();
  alert_layer_->draw();
}

//--------------------------------------------------------------
void ofApp::exit() {
  detector_.stop();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  switch (key) {
    case 'c':
      break;
    case OF_KEY_UP:
      detector_.raiseThreshold();
      break;
    case OF_KEY_DOWN:
      detector_.reduceThreshold();
      break;
    case OF_KEY_RIGHT:
      detector_.raiseBlackWhiteLevel();
      break;
    case OF_KEY_LEFT:
      detector_.reduceBlackWhiteLevel();
      break;
    case ' ':
      break;
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
