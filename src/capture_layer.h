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

class CaptureLayer {
 public:
  // Constructor and destructor
  CaptureLayer(int frame_width = ofGetWidth(), int frame_height = ofGetHeight());
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
};

#endif /* capture_layer_h */
