//
//  alert_layer.h
//  shelfie
//
//  Created by YotaOdaka on 1/11/16.
//
//

#ifndef alert_layer_h
#define alert_layer_h

#include <ofMain.h>
#include "ofxSvg.h"

class AlertLayer {
 public:
  // Constructor and destructor
  AlertLayer();
  ~AlertLayer();

  // Disallow copy and assign
  AlertLayer(const AlertLayer&) = delete;
  AlertLayer& operator=(const AlertLayer&) = delete;

  // Accessors
  void setMatchID(int& match_id) { match_id_ = match_id; };
  void setShowText(bool show_text) { show_text_ = show_text; };

  // Routine
  void update();
  void draw();

 private:
  // Properties
  int match_id_;
  bool show_text_;
  // Data members
  ofTrueTypeFont font_;
  vector<ofxSVG> tools_;
};

#endif /* alert_layer_h */
