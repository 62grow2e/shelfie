#pragma once

#include "ofMain.h"
#include "capture_layer.h"
#include "movie_layer.h"
#include "alert_layer.h"
#include "detector.h"


class ofApp : public ofBaseApp{
  
public:
  
  // Basic methods
  ofApp();
  void setup();
  void update();
  void draw();
  void exit();
  
  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);
  
 private:
  // Properties
  ofVec2f crop_size_;
  // Data members
  unique_ptr<CaptureLayer> capture_layer_;
  unique_ptr<AlertLayer> alert_layer_;
  unique_ptr<MovieLayer> movie_layer_;
  Detector detector_;
};
