#include "ofMain.h"
#include "ofApp.h"

namespace match_type {
enum ID {
  TAPE = 0,
  SCISSORS = 1,
  HEATGUN = 2,
  RULER = 3
};
vector<string>Names = {
  "Tape", "Scissors", "HeatGun", "Ruler"
};
} // namespace match_type
//========================================================================
int main( ){
 ofSetupOpenGL(1280,720,OF_WINDOW);   // <-------- setup the GL context

 // this kicks off the running of my app
 // can be OF_WINDOW or OF_FULLSCREEN
 // pass in width and height too:
 ofRunApp(new ofApp());

}
