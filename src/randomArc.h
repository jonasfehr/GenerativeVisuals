//
//  randomArc.h
//  GianaFactory
//
//  Created by Jonas Fehr on 16.10.14.
//
//


#pragma once

#include "ofMain.h"

class randomArc{
public:
    randomArc();
    void setup( ofVec2f _center, float _radius, float _width );
    
    void update(float _timer);
    void change();
    void updateIndependent();
    void updateSize(float _radius, float _width);
    void updatePos(ofVec2f _center);

    void updateRND();
    void draw();
    
    void ofPizzaSlice( const ofPoint &p, float _radius, float _startAngle, float _stopAngle );
    void ofArcSlice(const ofPoint &p, float _radius, float _widthInPct, float _startAngle, float _stopAngle);
    
    ofVec2f center;
    float radius;
    float width;
    float speed;
    float arcCenterAngle;
    float startAngle = 0;
    float stopAngle = 0;
    
    
    // variables for trial movie
    float bpm = 60;
    float bpw = 4;
    
    
    float centerAngleNew;
    float lengthNew;
    float centerAngleOld;
    float lengthOld;
    float timer=0;
    int maxLength=180;
    int alphalines = 255;
    
    float prop;
    bool rndRun;
    
};




