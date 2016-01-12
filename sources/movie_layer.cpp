//
//  movie_layer.cpp
//  shelfie
//
//  Created by YotaOdaka on 1/6/16.
//
//

#include "movie_layer.h"

MovieLayer::MovieLayer() : match_id_(-1), playing_(false), preparing_(false) {
  const boost::filesystem::path path("../../../data/videos");
  const auto directory_iterator = boost::filesystem::directory_iterator(path);
  for (auto itr = boost::filesystem::begin(directory_iterator);
      itr != boost::filesystem::end(directory_iterator); itr++) {
    ofVideoPlayer* video = new ofVideoPlayer();
    auto filename = itr->path().filename().string();
    if (filename.find(".m4v") == string::npos) {
      continue;
    }
    video->load("videos/" + filename);
    video->setLoopState(OF_LOOP_NORMAL);
    video->setVolume(0);
    videos_.emplace_back(video);
  }
  ofEnableAlphaBlending();
}

MovieLayer::~MovieLayer() {
}

void MovieLayer::update() {
  if (playing_) {
    if (videos_.size() <= match_id_ || match_id_ < 0) {
      match_id_ = 0;
    }
    videos_.at(match_id_)->update();
  }
}

void MovieLayer::draw() {
  if (playing_) {
    if (videos_.size() <= match_id_ || match_id_ < 0) {
      match_id_ = 0;
    }
//    ofSetColor(255, 255, 255, 0.5);
//    ofFill();
    videos_.at(match_id_)->draw(0, 0);
  }
  ofSetHexColor(0xffffff);
}

void MovieLayer::toggleVideo(int match_id) {
  if (!playing_) {
    startVideo(match_id);
  }
  else {
    finishVideo();
  }
}

void MovieLayer::startVideo(int match_id) {
  preparing_ = true;
  playing_ = true;
  match_id_ = match_id;
  videos_.at(match_id_)->play();
}

void MovieLayer::finishVideo() {
  playing_ = false;
  videos_.at(match_id_)->setPosition(0);
  videos_.at(match_id_)->stop();
}

