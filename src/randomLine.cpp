//
//  randomLine.cpp
//  GianaFactory
//
//  Created by Jonas Fehr on 16.10.14.
//
//

#include "randomLine.h"

randomLine::randomLine(){
    
}

void randomLine::setup(bool _direction, float _pathlength, float _maxWidth, float _length){
    
    pathlength  = _pathlength;
    maxWidth = _maxWidth;
    length = _length;
    direction = _direction;
    
    posNew = ofRandom(pathlength-maxWidth);
    widthNew = ofRandom(maxWidth);
    
    posOld = ofRandom(pathlength-maxWidth);
    widthOld = ofRandom(maxWidth);
    
    
    
    
}

void randomLine::update(float _timer){
    
        timer = _timer;
    posCurrent = posOld+(posNew-posOld)*timer;
    widthCurrent = widthOld+(widthNew-widthOld)*timer;
    
}
void randomLine::change(){

        posOld = posNew;
        widthOld = widthNew;
        posNew = ofRandom(pathlength-maxWidth);
        widthNew = ofRandom(maxWidth);
    
}
void randomLine::updateIndependent(){
    timer += (bpm/bpw/60/ofGetFrameRate());
    
    
    if (timer>1) {
        timer = 0;
        
        posOld = posNew;
        widthOld = widthNew;
        
        posNew = ofRandom(pathlength-maxWidth);
        widthNew = ofRandom(maxWidth);
    }
    
    
    
}



void randomLine::draw(){
    
    if(direction){
        ofDrawRectangle(0,posCurrent, length, widthCurrent);
    }else{
        ofDrawRectangle(posCurrent, 0, widthCurrent, length);
    }
}
