//
//  capture_layer.h
//  shelfie
//
//  Created by YotaOdaka on 1/6/16.
//
//

#ifndef capture_layer_h
#define capture_layer_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxSvg.h"

class CaptureLayer {
 public:
  // Constructor and destructor
  CaptureLayer(int frame_width = ofGetWidth(),
    int frame_height = ofGetHeight());
  ~CaptureLayer();

  // Disallow copy and assign
  CaptureLayer(const CaptureLayer&) = delete;
  CaptureLayer& operator=(CaptureLayer&) = delete;

  // Accessors
  ofImage& getCroppedFrame();

  // Routine
  void update();
  void draw(int x = 0, int y = 0);

 private:
  // Visual management
  void drawCropAssistant();
  void cropFrame();

  // Properties
  ofVec2f frame_size_;
  ofVec2f cropped_frame_position_;
  ofVec2f cropped_frame_size_;

  // Data members
  ofVideoGrabber capture_;
  ofImage cropped_frame_;
  ofxSVG crop_assistant_; // inner size: 650x650
  vector<ofPolyline> crop_assistant_lines_;
  const size_t original_inner_width_ = 650;
  const size_t original_inner_height_ = 650;
  ofVec2f crop_assistant_scale_;
};

#endif /* capture_layer_h */
