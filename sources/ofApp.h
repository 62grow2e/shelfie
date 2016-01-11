#pragma once

#include "ofMain.h"
#include "capture_layer.h"
#include "alert_layer.h"
#include "detector.h"

class ofApp : public ofBaseApp{
  
public:
  // Shered data definitions
  static enum MatchType {
    TAPE = 0,
    SCISSORS = 1,
    HEATGUN = 2,
    RULER = 3
  };
  static std::unordered_map<int, std::string> MatchTypeString;

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
  unique_ptr<CaptureLayer> capture_layer_;
  unique_ptr<AlertLayer> alert_layer_;
  Detector detector_;
  // Properties
  ofVec2f crop_size_;
};
