//
//  detector.h
//  shelfie
//
//  Created by YotaOdaka on 1/6/16.
//
//

#pragma once


//#include "ofMain.h"
#include "ofThread.h"
#include "ofxOpenCv.h"

class Detector : public ofThread {
 public:
  // Constructor and destructor
  Detector();
  ~Detector();

  // Disallow copy and assign
  Detector(const Detector&) = delete;
  Detector& operator=(const Detector&) = delete;

  // Accessors
  void setInput(ofImage& input);

  // Status
  bool running();
  bool detecting();

  // Routine
  void start(ofImage& input);
  void threadedFunction();


 private:
  // Properties
  bool running_;
  bool detecting_;

  // Data members
  ofImage input_;
  vector<ofImage> samples_;
};
