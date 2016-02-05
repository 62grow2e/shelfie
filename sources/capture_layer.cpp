//
//  capture_layer.cpp
//  shelfie
//
//  Created by YotaOdaka on 1/6/16.
//
//

#include "capture_layer.h"

CaptureLayer::CaptureLayer(int frame_width, int frame_height,
  int crop_width, int crop_height)
  : match_id_(-1), frame_size_(frame_width, frame_height),
    cropped_frame_position_(390, 110),
    cropped_frame_size_(500, 500),
    original_inner_width_(crop_width), original_inner_height_(crop_height) {
  // Camera device
  auto capture_list = capture_.listDevices();
  for (auto itr = capture_list.begin(); itr != capture_list.end(); itr++) {
    cout << itr->id << ": " << itr->deviceName << endl;
  }
  cout << "Enter the number key to activate camera." << endl;
  int input_number = 0;
//  cin >> input_number;
  if (input_number >= capture_list.size()) {
    ofLogError("WARNING", "No such a camera exist.");
    exit(EXIT_FAILURE);
  }
  capture_.setDeviceID(input_number);
  capture_.setup(ofGetWidth(), ofGetHeight());

  // Load svg
  crop_assistant_.load("img/crop_assistant-01.svg");
  for (auto itr_paths = crop_assistant_.getPaths().begin();
      itr_paths != crop_assistant_.getPaths().end(); itr_paths++) {
    auto outline = itr_paths->getOutline();
    for (auto itr_outline = outline.begin();
        itr_outline != outline.end(); itr_outline++) {
      crop_assistant_lines_.emplace_back(
        itr_outline->getResampledBySpacing(1));
    }
  }
  crop_assistant_scale_.set(
    cropped_frame_size_.x/(float)original_inner_width_,
    cropped_frame_size_.y/(float)original_inner_height_);
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
  drawCropAssistant();
}

#pragma mark Image management
void CaptureLayer::drawCropAssistant() {
  ofPushMatrix();
  if (match_id_ != -1) {
    ofSetHexColor(0x00ff00);
  }
  else {
    ofSetHexColor(0xff0000);
  }
  ofFill();
  ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
  ofScale(crop_assistant_scale_.x, crop_assistant_scale_.y);
  ofTranslate(-crop_assistant_.getWidth()/2, -crop_assistant_.getHeight()/2);
  for (auto itr = crop_assistant_lines_.begin();
      itr != crop_assistant_lines_.end(); itr++) {
    ofBeginShape();
    for (auto itr_vertex = itr->begin(); itr_vertex != itr->end(); itr_vertex++) {
      ofVertex(*itr_vertex);
    }
    ofEndShape();
  }
  ofNoFill();
  ofSetHexColor(0xffffff);
  ofPopMatrix();
}

void CaptureLayer::cropFrame() {
  if (!capture_.isFrameNew()) {
    return;
  }
  cropped_frame_ = capture_.getPixels();
  cropped_frame_.crop(cropped_frame_position_.x, cropped_frame_position_.y,
    cropped_frame_size_.x, cropped_frame_size_.y);
  cropped_frame_.resize(250, 250);
}