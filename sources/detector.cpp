//
//  detector.cpp
//  shelfie
//
//  Created by YotaOdaka on 1/6/16.
//
//

#include "detector.h"

Detector::Detector() {
  const boost::filesystem::path path("../../../../resources/sample_icons");
  const auto directory_iterator = boost::filesystem::directory_iterator(path);
  for (auto itr = boost::filesystem::begin(directory_iterator);
      itr != boost::filesystem::end(directory_iterator); itr++) {
    ofImage sample;
    auto filename = itr->path().filename().string();
    if (sample.load("sample_icons/" + filename)) {
      samples_.emplace_back(sample);
    }
  }
  
}

Detector::~Detector() {

}

#pragma mark Accessors
void Detector::setInput(ofImage& input) {
  lock();
  input_ = input;
  unlock();
}

#pragma mark Routine
void Detector::run() {

}