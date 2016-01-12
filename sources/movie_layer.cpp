//
//  movie_layer.cpp
//  shelfie
//
//  Created by YotaOdaka on 1/6/16.
//
//

#include "movie_layer.h"

MovieLayer::MovieLayer() {
  const boost::filesystem::path path("../../../data/videos");
  const auto directory_iterator = boost::filesystem::directory_iterator(path);
  for (auto itr = boost::filesystem::begin(directory_iterator);
      itr != boost::filesystem::end(directory_iterator); itr++) {
    ofVideoPlayer video;
    auto filename = itr->path().filename().string();
    if (filename.find(".m4v") == string::npos) {
      continue;
    }
    video.load("videos/" + filename);
    video.setLoopState(OF_LOOP_NORMAL);
    videos_.emplace_back(video);
  }

}

MovieLayer::~MovieLayer() {
}

void MovieLayer::update() {
}

void MovieLayer::draw() {
  if (playing_) {
    
  }
}

void MovieLayer::startVideo() {
  preparing_ = true;
  playing_ = true;
}

void MovieLayer::finishVideo() {
  playing_ = false;
}