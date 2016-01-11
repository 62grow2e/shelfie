//
//  alert_layer.cpp
//  shelfie
//
//  Created by YotaOdaka on 1/11/16.
//
//

#include "alert_layer.h"

AlertLayer::AlertLayer() : match_id_(-1), show_text_(false) {
  ofTrueTypeFont::setGlobalDpi(72);
  font_.load("verdana.ttf", 30, true, true);
  font_.setLineHeight(34.0f);
  font_.setLetterSpacing(1.035);
}

AlertLayer::~AlertLayer() {
}

void AlertLayer::update() {
  
}

void AlertLayer::draw() {
  if (show_text_ && match_id_ != -1) {
    string text = "Open the video of " +
      ofToString(ofApp::MatchTypeString.at(match_id_)) +
      "?    y / n";
    font_.drawString(text, 200, 600);
  }
}