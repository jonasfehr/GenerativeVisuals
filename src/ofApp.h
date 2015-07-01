#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"
#include "ofxSyphon.h"
#include "randomArc.h"
#include "randomLine.h"
#include "ofxAutoReloadedShader.h"
#include "defines.h"



class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();

    
    void addNewArc();
    void deleteArc();
    void addNewHorizontalLine();
    void deleteHorizontalLine();
    void addNewVerticalLine();
    void deleteVerticalLine();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void receiveOscParam(ofParameterGroup params);
    void sendOscParam(ofParameterGroup params);

    
    //Shaders
    ofxAutoReloadedShader voronoiseShader;
    ofxAutoReloadedShader perlinShader;
    ofxAutoReloadedShader simplexShader;
    
    // OSC
   // ofxOscReceiver oscReceiver;
   // ofxOscSender oscSender;
    ofxOscParameterSync syncOSC;
        
    
    // Syphon
    ofxSyphonServer syphonOutLines;
    ofxSyphonServer syphonOutArcs;
    ofxSyphonServer syphonOutVoronoise;
    ofxSyphonServer syphonOutPerlin;
    ofxSyphonServer syphonOutSimplex;

    
    ofTexture syphonLines;
    ofTexture syphonArcs;
    ofTexture syphonVoronoise;
    ofTexture syphonPerlin;
    ofTexture syphonSimplex;

    
    // GUI / Controlpanel
    bool guiShow;
    ofxPanel gui;
    ofParameterGroup parameters;
    
    ofParameterGroup paramEnable;

    ofParameter<bool>  linesHorizontal;
    ofParameter<bool>  linesVertical;
    ofParameter<bool>  arcFlag;
    ofParameter<bool>  voronoise;
    ofParameter<bool>  perlin;
    ofParameter<bool>  simplex;

    
    ofParameterGroup paramGeneral;
    ofParameter<float> BPM;
    ofParameter<int> BPW;
    ofParameter<bool> bwSwitch;
    ofParameter<bool> bgTransparent;
    
    ofParameterGroup paramLines;
    ofParameter<float> numOfLinesHorizontal;
    float numOfLinesHorizontalLast;
    ofParameter<float> numOfLinesVertical;
    float numOfLinesVerticalLast;
    ofParameter<float> linesMaxWidth;
    
    
    ofParameterGroup paramArcs;
    ofParameter<float> numOfArcs;
    float numOfArcsLast;
    ofParameter<bool> width_height;
    
    
    ofParameterGroup paramVoronoise;
    ofParameter<float> function;
    ofParameter<bool>  multiply_by_F1;
    ofParameter<bool>  multiply_by_F2;

    ofParameter<bool>  inverse;
    ofParameter<float> distance_type;
    

    
    ofParameter<float>  posibility;
    
    
    ofParameterGroup paramSimplex;
    ofParameter<float> in1;
    ofParameter<float> tempo;
    ofParameter<float> zoom;

    
    // initialise Circle
    ofVec2f center;
    int radius;
    
    vector <randomArc> rndArc;
    vector <randomLine> horizontalLines;
    vector <randomLine> verticalLines;
    //randomArc rndArc[10];
    
    
    ofFbo renderLines;
    ofFbo renderArcs;
    ofFbo renderVoronoise;
    ofFbo renderPerlin;
    ofFbo renderSimplex;



    
    ofColor bgColor;
    ofColor drawColor;
    
    float timer = 0;
    
    bool rndPoints[33];
    
    
    int draggedX, draggedY, clickX, clickY;


};