#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"
#include "ofxSyphon.h"
#include "randomArc.h"
#include "randomLine.h"
#include "ofxAutoReloadedShader.h"
#include "defines.h"
#include "ofxParameterMidiSync.h"
#include "ofxMidiIn.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();

    
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
    
    void minMaxGui();
    
    void receiveOscParam(ofParameterGroup params);
    void sendOscParam(ofParameterGroup params);

    ofxParameterMidiSync sync;
    ofxMidiIn midiIn;
    
    //Shaders
    ofxAutoReloadedShader voronoiseShader;
    ofxAutoReloadedShader perlinShader;
    ofxAutoReloadedShader simplexShader;
    ofxAutoReloadedShader ikedaShader;
    ofxAutoReloadedShader cloudShader;
    
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
    ofxSyphonServer syphonOutIkeda;
    ofxSyphonServer syphonOutCloud;

    
    // GUI / Controlpanel
    bool guiShow;
    ofxPanel gui;
    ofParameterGroup parameters;
    
    //define RenderSize
    ofParameterGroup screenSize;
    ofParameter<int> render_width;
    ofParameter<int> render_height;
    
    // Enable the different renderers
    ofParameterGroup paramEnable;

    ofParameter<bool>  previews;
    ofParameter<bool>  linesHorizontal;
    ofParameter<bool>  linesVertical;
    ofParameter<bool>  arcs;
    ofParameter<bool>  voronoise;
    ofParameter<bool>  perlin;
    ofParameter<bool>  simplex;
    ofParameter<bool>  ikeda;
    ofParameter<bool>  cloud;


    
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
    ofParameter<float> heightAdjust;
    ofParameter<float> possibility;
    float numOfArcsLast;
    ofParameter<bool> width_height;
    
    
    ofParameterGroup paramVoronoise;
    ofParameter<float> tempoVoronoise;
    ofParameter<float> scaleVoronoise;
    ofParameter<int> octavesVoronoise;
    ofParameter<int> function;
    ofParameter<int> distance_type;
    ofParameter<bool>  multiply_by_F1;
    ofParameter<bool>  multiply_by_F2;
    ofParameter<bool>  inverse;

    
    ofParameterGroup paramPerlin;
   // ofParameter<float> tempoPerlin;
    ofParameter<float> density;
    ofParameter<float> fRatio;
    ofParameter<float> FirstDivision;
    ofParameter<float> rotationSpeed;
    ofParameter<float> fallingSpeed;
    ofParameter<float> rotCenterX;
    ofParameter<float> rotCenterY;

    
    ofParameterGroup paramSimplex;
    ofParameter<float> tempoSimplex;
    ofParameter<float> in1;
    ofParameter<float> zoom;
    
    ofParameterGroup paramIkeda;
    ofParameter<float> tempoIkeda;
    ofParameter<float> amount;
    ofParameter<float> xGrid;
    ofParameter<float> yGrid;
    
    ofParameterGroup paramCloud;
    ofParameter<float> tempoCloud;
    ofParameter<float> zoomCloud;
    ofParameter<float> balance;
    ofParameter<float> contrast;
    ofParameter<bool>  enableFBM;
    ofParameter<bool>  enableRMF;
    ofParameter<bool>  enableCircle;

    
    // tempo for noises
    float counterVoronoise;
    float counterPerlin;
    float counterSimplex;
    float counterPerlinRot;
    float counterIkeda;
    float counterCloud;


    
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
    ofFbo renderIkeda;
    ofFbo renderCloud;



    
    ofColor bgColor;
    ofColor drawColor;
    
    float timer = 0;
    int port;
    int numPorts;
    bool rndPoints[33];
    
    
    int draggedX, draggedY, clickX, clickY;
    
    bool keyIsDown[255];
    
    bool fCloud;
    bool fIkeda;
    bool fPerlin;
    bool fVoronoise;
    bool fArcs;
    bool fLines;
    bool fSimplex;


};