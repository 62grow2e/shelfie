//
//  detector.cpp
//  shelfie
//
//  Created by YotaOdaka on 1/6/16.
//
//

#include "detector.h"

Detector::Detector(int crop_width, int crop_height)
  : running_(false), detecting_(false),
    match_id_(-1), num_found_(0), threshold_(34), black_white_level_(100) {
  // Setup
  color_image_.allocate(crop_width, crop_height);
  gray_image_.allocate(crop_width, crop_height);
  // Load match samples
  const boost::filesystem::path path("../../../data/img/sample_icons");
  const auto directory_iterator = boost::filesystem::directory_iterator(path);
  for (auto itr = boost::filesystem::begin(directory_iterator);
      itr != boost::filesystem::end(directory_iterator); itr++) {
    ofImage sample;
    auto filename = itr->path().filename().string();
    if (sample.load("img/sample_icons/" + filename)) {
      cout << "icon: " << filename << endl;
      samples_origin_.emplace_back(sample);
      samples_.emplace_back(MatchObject());
      samples_.back().allocate(sample.getWidth(), sample.getHeight());
      samples_.back().setFromPixels(sample.getPixels());
    }
  }
}

Detector::~Detector() {
  cout << "Detector destroyed." <<  endl;
}

void Detector::start(ofImage& input) {
  setInput(input);
  startThread();
//  cout << "Thread start." << endl;
}

void Detector::stop() {
  stopThread();
  cout << "Thread stop" << endl;
}

void Detector::threadedFunction() {
  while (isThreadRunning()) {
    if (lock()) {
      color_image_.setFromPixels(input_.getPixels());
      gray_image_ = color_image_;
//      gray_image_.threshold(black_white_level_);
      matches_.clear();
      match_id_ = -1;
      for (auto itr_samples = samples_.begin();
          itr_samples != samples_.end(); itr_samples++) {
        num_found_ = matcher_.findMatches(
          gray_image_, *itr_samples, threshold_);
        if (num_found_ != 0) {
          match_id_ = distance(samples_.begin(), itr_samples);
        }
      }
      unlock();
      stopThread();
    }
  }
}

void Detector::draw() {
  lock();
  if (match_id_ == 1) {
      samples_origin_.at(match_id_).draw(200, ofGetHeight()-200);
  }
  gray_image_.draw(0, 0);
  unlock();
}

#pragma mark Accessors
void Detector::setInput(ofImage& input) {
  if (isThreadRunning()) {
    return;
  }
  lock();
  input_ = input;
  unlock();
}

#pragma mark Status
bool Detector::detecting() {
  return detecting_;
}

void Detector::raiseThreshold(int diff) {
  threshold_ += diff;
  cout << threshold_ << endl;
}

void Detector::reduceThreshold(int diff) {
  threshold_ -= diff;
  cout << threshold_ << endl;
}

void Detector::raiseBlackWhiteLevel(int diff) {
  black_white_level_ += diff;
  cout << black_white_level_ << endl;
}

void Detector::reduceBlackWhiteLevel(int diff) {
  black_white_level_ -= diff;
  cout << black_white_level_ << endl;
}
