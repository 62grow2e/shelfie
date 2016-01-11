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
  int& getMatchID() { return match_id_; };

  // Status
  bool running();
  bool detecting();
  void raiseThreshold(int diff = 1);
  void reduceThreshold(int diff = 1);
  void raiseBlackWhiteLevel(int diff = 1);
  void reduceBlackWhiteLevel(int diff = 1);

  // Routine
  void start(ofImage& input);
  void stop();
  void threadedFunction();
  void draw();


 private:
  // Properties
  bool running_;
  bool detecting_;
  int match_id_;

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
  size_t black_white_level_;
};
