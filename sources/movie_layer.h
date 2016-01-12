//
//  movie_layer.h
//  shelfie
//
//  Created by YotaOdaka on 1/6/16.
//
//

#ifndef movie_layer_h
#define movie_layer_h

#include <stdio.h>
#include "ofMain.h"

class MovieLayer {
 public:
  // Constructor and destructor
  MovieLayer();
  ~MovieLayer();

  // Disallow copy and assign
  MovieLayer(const MovieLayer&) = delete;
  MovieLayer& operator=(MovieLayer&) = delete;

  // Accessor
  bool playing() { return playing_; }

  // Routine
  void update();
  void draw();
  void toggleVideo(int match_id_ = 0);
  void startVideo(int match_id_ = 0);
  void finishVideo();

 private:
  // Player
  // Properties
  int match_id_;
  bool video_start_;
  bool playing_;
  bool preparing_;
  // Data members
  vector<ofVideoPlayer*> videos_;
};

#endif /* movie_layer_h */
