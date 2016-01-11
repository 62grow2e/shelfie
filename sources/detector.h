//
//  detector.h
//  shelfie
//
//  Created by YotaOdaka on 1/6/16.
//
//

#pragma once

#include "ofThread.h"
#include "ofxOpenCv.h"
#include "ofxTemplateMatching.h"

class Detector : public ofThread {
 public:
  // Constructor and destructor
  Detector(int crop_width = 650, int crop_height = 650);
  ~Detector();

  // Disallow copy and assign
  Detector(const Detector&) = delete;
  Detector& operator=(const Detector&) = delete;

  // Accessors
  void setInput(ofImage& input);

  // Status
  bool running();
  bool detecting();
  void raiseThreshold(int diff = 1);
  void reduceThreshold(int diff = 1);

  // Routine
  void start(ofImage& input);
  void threadedFunction();
  void draw();


 private:
  // Properties
  bool running_;
  bool detecting_;

  // Data members
  ofxTemplateMatching matcher_;
  vector<MatchObject> samples_;
  vector<TemplateMatch> matches_;
  ofxCvColorImage color_image_;
  ofxCvGrayscaleImage gray_image_;
  ofImage input_;
  vector<ofImage> samples_origin_;
  size_t num_found_;
  size_t threshold_;
};
