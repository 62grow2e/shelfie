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
  font_.load("fonts/verdana.ttf", 30, true, true);
  font_.setLineHeight(34.0f);
  font_.setLetterSpacing(1.035);

  const boost::filesystem::path path("../../../data/img/sample_svg");
  const auto directory_iterator = boost::filesystem::directory_iterator(path);
  for (auto itr = boost::filesystem::begin(directory_iterator);
      itr != boost::filesystem::end(directory_iterator); itr++) {
    ofxSVG sample;
    auto filename = itr->path().filename().string();
    if (filename.find(".svg") == string::npos) {
      continue;
    }
    sample.load("img/sample_svg/" + filename);
    tools_.emplace_back(sample);
  }
}

AlertLayer::~AlertLayer() {
}

void AlertLayer::update() {
  
}

void AlertLayer::draw() {
  if (show_text_ && match_id_ != -1) {
    ofPushMatrix();
    ofSetHexColor(0xffffff);
    ofFill();
    ofTranslate(250, 600);
    tools_.at(match_id_).draw();
    ofPopMatrix();
    string text = "Open the video of ";
    switch (match_id_) {
      case 0:
        text += "Tape";
        break;
      case 1:
        text += "Scissors";
        break;
      case 2:
        text += "HeatGun";
        break;
      case 3:
        text += "Ruler";
        break;
      default:
        break;
    }
    text += "?";
    font_.drawString(text, 400, 680);
  }
}