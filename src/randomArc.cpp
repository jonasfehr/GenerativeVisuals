//
//  randomArc.cpp
//  GianaFactory
//
//  Created by Jonas Fehr on 16.10.14.
//
//

#include "randomArc.h"

randomArc::randomArc(){
    
}

void randomArc::setup(ofVec2f _center,float _radius, float _width){
    center = _center;
    radius = _radius;
    width = _width;
    speed = ofRandom(-1, 1);
    arcCenterAngle = ofRandom(360);
    
    centerAngleNew = ofRandom(360*2);
    lengthNew = ofRandom(maxLength);
    centerAngleOld = arcCenterAngle;
    lengthOld = ofRandom(maxLength);
}
void randomArc::update(float _timer){
    timer = _timer;
    startAngle = (centerAngleOld+(centerAngleNew-centerAngleOld)*timer);//%360;
    stopAngle = startAngle + (lengthOld+(lengthNew-lengthOld)*timer);//%360;*/
    
}
void randomArc::change(){
            centerAngleOld = centerAngleNew;
            lengthOld = lengthNew;
            centerAngleNew= ofRandom(360*2);
            lengthNew = ofRandom(maxLength)+2;

}
void randomArc::updateIndependent(){
    
    if ( rndRun == true){
    timer += (bpm/bpw/60/ofGetFrameRate());
    
    if (timer > 1) {
        timer = 0;
        
            centerAngleOld = centerAngleNew;
            lengthOld = lengthNew;
            centerAngleNew= ofRandom(360*2);
            lengthNew = ofRandom(maxLength)+2;
     
   }
    
    startAngle = (centerAngleOld+(centerAngleNew-centerAngleOld)*timer);//%360;
    stopAngle = startAngle + (lengthOld+(lengthNew-lengthOld)*timer);//%360;*/
    } else {
    
   /* if(ofRandom(0, 1) < 0.1){
        if ( prop == 1 ) prop = -1;
        if ( prop == -1 ) prop = 1;
    }
    speed+=ofRandom(0.1) * prop;*/
    if( speed > 2) speed = 2;
    if(speed < -2) speed = -2;
    centerAngleNew += speed;
    //lengthNew += ofRandom(10)*prop;
    startAngle = centerAngleNew - lengthNew/2;
    stopAngle = centerAngleNew + lengthNew/2;
    }
    
    
}

void randomArc::updateSize(float _radius, float _width){
    
    radius = _radius;
    width = _width;
}
void randomArc::updateRND(){
     if(ofRandom(0, 1) < 0.1){
     if ( prop == 1 ) prop = -1;
     if ( prop == -1 ) prop = 1;
     }
     speed+=ofRandom(0.1) * prop;
    if( speed > 2) speed = 2;
    if(speed < -2) speed = -2;
    centerAngleNew += speed;
    lengthNew += ofRandom(10)*prop;
}


void randomArc::draw(){
   // ofPizzaSlice(center, radius, startAngle, stopAngle);
    ofArcSlice(center, radius, width+1, startAngle, stopAngle);
}


//--------------------------------------------------------------
void randomArc::ofPizzaSlice(const ofPoint &p, float _radius, float _startAngle, float _stopAngle) {
   
    ofPushMatrix();
    
    ofTranslate(p);
    ofScale(_radius, _radius, 1);
    float resolution = 10;
    ofBeginShape();
    ofVertex(0, 0);
    if(_startAngle < _stopAngle){
        for(float theta = _startAngle; theta <= _stopAngle; theta += resolution) {
            ofVertex(cos(ofDegToRad(theta)), sin(ofDegToRad(theta)));
        }
    } else {
        for(float theta = _stopAngle; theta <= _startAngle; theta += resolution) {
            ofVertex(cos(ofDegToRad(theta)), sin(ofDegToRad(theta)));
        }
    }
    ofEndShape(false);
    
    ofPopMatrix();
}

void randomArc::ofArcSlice(const ofPoint &p, float _radius, float _width, float _startAngle, float _stopAngle) {
    
    ofPushMatrix();
    
    ofTranslate(p);
    ofScale(_radius, _radius, 1);
    float resolution = .5;
    float widthScale = 1-_width/_radius;
    ofBeginShape();
    //ofVertex(0, 0);
    for(float theta = _startAngle; theta <= _stopAngle; theta += resolution) {
        ofVertex(cos(ofDegToRad(theta)), sin(ofDegToRad(theta)));
    }

    for(float theta = _stopAngle; theta >= _startAngle; theta -= resolution) {
        ofPoint pos = ofVec2f(cos(ofDegToRad(theta)), sin(ofDegToRad(theta))).operator*=(widthScale);
        ofVertex(pos);
    
    }

    ofEndShape(false);
    
    ofPopMatrix();
}




