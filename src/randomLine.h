//
//  randomArc.h
//  GianaFactory
//
//  Created by Jonas Fehr on 16.10.14.
//
//


#pragma once

#include "ofMain.h"

class randomLine{
public:
    randomLine();
    void setup(bool _direction, float _pathlength, float _maxWidth, float _length);
    void update(float _timer);
    void change();
    void updateIndependent();
    void draw();
    
    
    
    float bpm = 125;
    float bpw = 1;
    
    float pathlength, maxWidth, length;
    bool direction;
    
    float posNew, posOld, posCurrent;
    float widthNew, widthOld, widthCurrent;
    
    float timer;
};




