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
    num_found_(0), threshold_(50) {
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
      samples_origin_.emplace_back(sample);
      samples_.emplace_back(MatchObject());
      samples_.back().allocate(sample.getWidth(), sample.getHeight());
      samples_.back().setFromPixels(sample.getPixels());
    }
  }
}

Detector::~Detector() {
  cout << "Thread finished." <<  endl;
}

void Detector::start(ofImage& input) {
  setInput(input);
  startThread();
}

void Detector::threadedFunction() {
  while (isThreadRunning()) {
    if (lock()) {
      color_image_.setFromPixels(input_.getPixels());
      gray_image_ = color_image_;
      matches_.clear();
      for (auto itr_samples = samples_.begin();
          itr_samples != samples_.end(); itr_samples++) {
        num_found_ = matcher_.findMatches(
          gray_image_, *itr_samples, threshold_);
        auto& matches = matcher_.matches;
        for (auto itr_matches = matches.begin();
            itr_matches != matches.end(); itr_matches++) {
          matches_.emplace_back(*itr_matches);
          matches_.back().objectID = distance(matches.begin(), itr_matches);
        }
      }
      cout << "detected item: " << num_found_ << endl;
      unlock();
      stopThread();
    }
  }
}

void Detector::draw() {
  lock();
  for (auto itr = samples_origin_.begin(); itr != samples_origin_.end(); itr++) {
    itr->draw(distance(samples_origin_.begin(), itr)*200, ofGetHeight()-200);
  }
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
