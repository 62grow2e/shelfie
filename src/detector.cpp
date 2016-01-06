//
//  detector.cpp
//  shelfie
//
//  Created by YotaOdaka on 1/6/16.
//
//

#include "detector.h"

Detector::Detector() {

}

Detector::~Detector() {

}

#pragma mark Accessors
void Detector::setInput(ofImage input) {
  lock();
  input_ = input;
  unlock();
}

#pragma mark Routine
void Detector::search() {

}