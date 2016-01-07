//
//  capture_layer.cpp
//  shelfie
//
//  Created by YotaOdaka on 1/6/16.
//
//

#include "capture_layer.h"

CaptureLayer::CaptureLayer(int frame_width, int frame_height)
  : frame_size_(frame_width, frame_height),
    cropped_frame_position_(frame_size_.x/3, frame_size_.x/3),
    cropped_frame_size_(frame_size_.x/3, frame_size_.x/3) {
  // Camera device
  auto capture_list = capture_.listDevices();
  for (auto itr = capture_list.begin(); itr != capture_list.end(); itr++) {
    cout << itr->id << ": " << itr->deviceName << endl;
  }
  cout << "Enter the number key to activate camera" << endl;
  int input_number;
  cin >> input_number;
  if (input_number >= capture_list.size()) {
    exit(EXIT_FAILURE);
  }
  capture_.setDeviceID(input_number);
  capture_.setup(ofGetWidth(), ofGetHeight());
}

CaptureLayer::~CaptureLayer() {

}

#pragma mark Accessors
ofImage& CaptureLayer::getCroppedFrame(){
  return cropped_frame_;
}

#pragma mark Routine
void CaptureLayer::update() {
  capture_.update();
  cropFrame();
}

void CaptureLayer::draw(int x, int y) {
  capture_.draw(x, y);
}

#pragma Image management
void CaptureLayer::drawCropAssistant() {

}
void CaptureLayer::cropFrame() {
  if (!capture_.isFrameNew()) {
    return;
  }
  cropped_frame_ = capture_.getPixels();
  cropped_frame_.crop(cropped_frame_position_.x, cropped_frame_position_.y,
    cropped_frame_size_.x, cropped_frame_size_.y);
}