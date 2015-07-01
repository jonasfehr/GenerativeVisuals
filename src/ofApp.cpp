#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetWindowTitle("GenerativeVisuals");
    ofEnableSmoothing();
    ofDisableArbTex();
    ofSetVerticalSync(true);
    ofSetCircleResolution(10);

    
    
    
    // FBO renders
    renderLines.allocate(RENDERWIDTH, RENDERHEIGHT);
    renderArcs.allocate(RENDERWIDTH, RENDERHEIGHT);
    renderVoronoise.allocate(RENDERWIDTH, RENDERHEIGHT);
    renderPerlin.allocate(RENDERWIDTH, RENDERHEIGHT);
    renderSimplex.allocate(RENDERWIDTH, RENDERHEIGHT);

    
    
    
    // Syphon
    syphonOutLines.setName("Lines");
    syphonOutArcs.setName("Arcs");
    syphonOutVoronoise.setName("Voronoise");
    syphonOutPerlin.setName("Perlin");
    syphonOutSimplex.setName("Simplex");

    
    syphonLines.allocate(RENDERWIDTH, RENDERHEIGHT, GL_RGBA);
    syphonArcs.allocate(RENDERWIDTH, RENDERHEIGHT, GL_RGBA);
    syphonVoronoise.allocate(RENDERWIDTH, RENDERHEIGHT, GL_RGBA);
    syphonPerlin.allocate(RENDERWIDTH, RENDERHEIGHT, GL_RGBA);
    syphonSimplex.allocate(RENDERWIDTH, RENDERHEIGHT, GL_RGBA);
    
    
    syphonLines = renderLines.getTextureReference();
    syphonArcs = renderArcs.getTextureReference();
    syphonVoronoise = renderVoronoise.getTextureReference();
    syphonPerlin = renderPerlin.getTextureReference();
    syphonSimplex = renderSimplex.getTextureReference();
    
    
    //VoronoiseRender
    voronoiseShader.load("shaders/voronoiseShader");
    perlinShader.load("shaders/perlinShader");
    simplexShader.load("shaders/simplexShader");
    
    // setup Gui
    
    paramGeneral.setName("Enable");
    paramGeneral.add(linesHorizontal.set("linesHorizontal", true));
    paramGeneral.add(linesVertical.set("linesVertical", true));
    paramGeneral.add(arcFlag.set("arcFlag", true));
    paramGeneral.add(voronoise.set("voronoise", true));
    paramGeneral.add(perlin.set("perlin", true));
    paramGeneral.add(simplex.set("simplex", true));
    
    paramGeneral.add(BPM.set("BPM", 120, 10, 180));
    paramGeneral.add(BPW.set("BPW", 4, 1, 16));
    paramGeneral.add(bwSwitch.set("bwSwitch", false));
    paramGeneral.add(bgTransparent.set("bgTransparent", false));
    
    // param Lines
    paramLines.setName("paramLines");
    paramLines.add(numOfLinesHorizontal.set("numOfLinesHorizontal", 10, 1, 140));
    paramLines.add(numOfLinesVertical.set("numOfLinesVertical", 10, 1, 140));
    paramLines.add(linesMaxWidth.set("linesMaxWidth", 10, 1, 140));
    
    
    // param Arcs
    paramArcs.setName("paramArcs");
    paramArcs.add(numOfArcs.set("numOfArcs", 10, 1, 140));
    paramArcs.add(heightAdjust.set("heightAdjust", 0.5, 0., 1.));
    paramArcs.add(width_height.set("width_height", false));
    
    
    
    // param for voronoiseShader
    paramVoronoise.setName("paramVoronoise");
    paramVoronoise.add(tempoVoronoise.set("tempoVoronoise", 0.5, 0., 1));
    paramVoronoise.add(function.set("function", 1, 0., 10));
    paramVoronoise.add(multiply_by_F1.set("multiply_by_F1", false));
    paramVoronoise.add(multiply_by_F2.set("multiply_by_F2", false));
    paramVoronoise.add(inverse.set("inverse", false));
    paramVoronoise.add(distance_type.set("distance_type", 1, 0., 10));
    
    
    // param for voronoiseShader
    paramPerlin.setName("paramPerlin");
    paramPerlin.add(tempoPerlin.set("tempoPerlin", 0.1, 0., 1));

    
    // param for simplexShader
    paramSimplex.setName("paramSimplex");
    paramSimplex.add(tempoSimplex.set("tempoSimplex", 0.1, 0., 1));
    paramSimplex.add(in1.set("in1", 1, 0., 1000));
    paramSimplex.add(zoom.set("zoom", 0.1, 0., 1));


    // setGui
    parameters.setName("parameters");
    parameters.add(paramGeneral);
    parameters.add(paramLines);
    parameters.add(paramArcs);
    parameters.add(paramVoronoise);
    parameters.add(paramPerlin);
    parameters.add(paramSimplex);
    
    gui.setup(parameters);
    guiShow = true;
    
    // OSC
   // oscReceiver.setup(OSCRECEIVEPORT);
   // oscSender.setup(OSCHOSTIP, OSCSENDPORT);
    syncOSC.setup((ofParameterGroup&)gui.getParameter(),OSCRECEIVEPORT,OSCHOSTIP,OSCSENDPORT);

    
    // Initialise the images
    numOfLinesHorizontalLast = 0;
    for(int i = 0; i<numOfLinesHorizontal; i++){
        addNewHorizontalLine();
        numOfLinesHorizontalLast++;
    }
    
    numOfLinesVerticalLast = 0;
    for(int i = 0; i<numOfLinesVertical; i++){
        addNewVerticalLine();
        numOfLinesVerticalLast++;
    }
    
    center = ofVec2f(renderArcs.getWidth()/2, renderArcs.getHeight()*heightAdjust);
    radius = renderArcs.getHeight();
    numOfArcsLast = 0;
    for(int i = 0; i<numOfArcs; i++){
        addNewArc();
        numOfArcsLast++;
    }
    for(int i = 0; i<rndArc.size(); i++){
        rndArc[i].updateSize(radius*(i+1)/numOfArcs, radius/numOfArcs);
        rndArc[i].updatePos(center);
    }
    
    bgColor = ofColor::white;
    drawColor = ofColor::black;
    
    
    
    
    for(int i = 0; i < renderArcs.getHeight(); i++){
        if(ofRandom(100)>possibility*100){
            if(rndPoints[i]){
                rndPoints[i] = false;
            }else{
                rndPoints[i] = true;
            }
        }
    }
    
    
    counterVoronoise = 0;
    counterPerlin = 0;
    counterVoronoise = 0;
    
    
}

//-------------------



//-------------------------------------------
void ofApp::update(){
    
    // send & receive OSC
   // receiveOscParam();
   // sendOscParam();
    syncOSC.update();

    
    if(numOfLinesHorizontal > numOfLinesHorizontalLast){
        for (int n = 1; n<numOfLinesHorizontal-numOfLinesHorizontalLast; n++){
            addNewHorizontalLine();
            
        }
        numOfLinesHorizontalLast = horizontalLines.size();
        
    }
    else if(numOfLinesHorizontal < numOfLinesHorizontalLast){
        for (int n = 0; n<numOfLinesHorizontalLast-numOfLinesHorizontal; n++){
            deleteHorizontalLine();
            numOfLinesHorizontalLast--;
        }
    }
    
    if(numOfLinesVertical > numOfLinesVerticalLast){
        for (int n = 1; n<numOfLinesVertical-numOfLinesVerticalLast; n++){
            addNewVerticalLine();
            
        }
        numOfLinesVerticalLast = verticalLines.size();
        
    }
    else if(numOfLinesVertical < numOfLinesVerticalLast){
        for (int n = 0; n<numOfLinesVerticalLast-numOfLinesVertical; n++){
            deleteVerticalLine();
            numOfLinesVerticalLast--;
        }
    }
    
    
    
    // ARCS
    radius = renderArcs.getHeight()/2;
    center = ofVec2f(renderArcs.getWidth()/2, renderArcs.getHeight()*heightAdjust);
    if(width_height)radius = renderArcs.getWidth()/2;
    for(int i = 0; i<rndArc.size(); i++){
        rndArc[i].updateSize(radius*(i+1)/numOfArcs, radius/numOfArcs);
        rndArc[i].updatePos(center);
    }
    
    
    // ARCs
    if(numOfArcs > numOfArcsLast){
        for (int n = 1; n<numOfArcs-numOfArcsLast; n++){
            addNewArc();
            
        }
        numOfArcsLast = rndArc.size();
    }
    else if(numOfArcs < numOfArcsLast){
        for (int n = 0; n<numOfArcsLast-numOfArcs; n++){
            deleteArc();
            numOfArcsLast--;
        }

    }

    
    // Updates per BPM
    
    timer += (BPM/BPW/60/ofGetFrameRate());
    if(timer>=1){
        for(int i = 0; i<horizontalLines.size(); i++){
            horizontalLines[i].change();
        }
        for(int i = 0; i<verticalLines.size(); i++){
            verticalLines[i].change();
        }
        for(int i = 0; i<rndArc.size(); i++){
            rndArc[i].change();
        }
        timer = 0;
    }
    
    
    if(linesHorizontal){
        for(int i = 0; i<horizontalLines.size(); i++){
            horizontalLines[i].update(timer);
            //   horizontalLines[i].bpm = BPM;
            //   horizontalLines[i].bpw = BPW;
            horizontalLines[i].maxWidth = linesMaxWidth;
        }
    }
    
    if(linesVertical){
        for(int i = 0; i<verticalLines.size(); i++){
            verticalLines[i].update(timer);
            //   verticalLines[i].bpm = BPM;
            //   verticalLines[i].bpw = BPW;
            verticalLines[i].maxWidth = linesMaxWidth;
        }
    }
    
    
    
    
    if(arcFlag){
        for(int i = 0; i<rndArc.size(); i++){
            rndArc[i].update(timer);
            //   rndArc[i].bpm = BPM;
        }
        
        
    }
    
    // Counter for noises
    
    counterVoronoise += tempoVoronoise;
    counterPerlin   += tempoPerlin;
    counterSimplex += tempoSimplex/5;
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(bwSwitch){
        bgColor = ofColor::white;
        drawColor = ofColor::black;
    }else{
        bgColor = ofColor::black;
        drawColor = ofColor::white;
    }
    
    if(linesHorizontal || linesVertical){
        renderLines.begin();
        
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if(!bgTransparent) ofBackground(bgColor); // make background color if wished;
        
        
        
        if(linesHorizontal){
            ofSetColor(drawColor);
            ofFill();
            for(int i = 0; i<horizontalLines.size(); i++){
                horizontalLines[i].draw();
            }
        }
        
        if(linesVertical){
            ofSetColor(drawColor);
            ofFill();
            for(int i = 0; i<verticalLines.size(); i++){
                verticalLines[i].draw();
            }
        }
        renderLines.end();
    }
    
    if(arcFlag){
        renderArcs.begin();
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if(!bgTransparent) ofBackground(bgColor); // make background color if wished;
        
        ofSetColor(drawColor);
        ofFill();
        
        for(int i = 0; i<rndArc.size(); i++){
            
            rndArc[i].draw();
        }
        renderArcs.end();
    }
    
    if(voronoise){
        
        renderVoronoise.begin();
            glClearColor(0.0, 0.0, 0.0, 0.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            if(!bgTransparent){// ofBackground(bgColor);
                
                ofSetColor(bgColor);
                ofFill();
                ofRect(0, 0, renderPerlin.getWidth(), renderPerlin.getHeight());
            }
        
            voronoiseShader.begin();
            
                voronoiseShader.setUniform3f("iResolution", RENDERWIDTH, RENDERHEIGHT, 0.0);
                voronoiseShader.setUniform1f("iGlobalTime", counterVoronoise);
                voronoiseShader.setUniform1f("function", function);
                voronoiseShader.setUniform1i("multiply_by_F1", multiply_by_F1);
                voronoiseShader.setUniform1i("multiply_by_F2", multiply_by_F2);
                voronoiseShader.setUniform1i("inverse", inverse);
                voronoiseShader.setUniform1f("distance_type", distance_type);
                voronoiseShader.setUniform1i("bwSwitch", bwSwitch);
                voronoiseShader.setUniform1i("bgTransparent", bgTransparent);
        
                
                ofSetColor(255,255,255);
                ofFill();
                ofRect(0, 0, renderVoronoise.getWidth(), renderVoronoise.getHeight());
            
            voronoiseShader.end();
        
        renderVoronoise.end();
        
    }
    
    if(perlin){
        
        renderPerlin.begin();
            glClearColor(0.0, 0.0, 0.0, 0.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
            if(!bgTransparent){// ofBackground(bgColor);
                
            ofSetColor(bgColor);
            ofFill();
            ofRect(0, 0, renderPerlin.getWidth(), renderPerlin.getHeight());
            }
        
            perlinShader.begin();
            
                perlinShader.setUniform3f("iResolution", RENDERWIDTH, RENDERHEIGHT, 0.0);
                perlinShader.setUniform1f("iGlobalTime", counterPerlin);
        
                perlinShader.setUniform1i("bwSwitch", bwSwitch);
                perlinShader.setUniform1i("bgTransparent", bgTransparent);
                
                
                ofSetColor(255,255,255);
                ofFill();
                ofRect(0, 0, renderPerlin.getWidth(), renderPerlin.getHeight());
            
            perlinShader.end();
        
        renderPerlin.end();
        
    }
    
    if(simplex){
        
        renderSimplex.begin();
            glClearColor(0.0, 0.0, 0.0, 0.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            if(!bgTransparent){// ofBackground(bgColor);
                
                ofSetColor(bgColor);
                ofFill();
                ofRect(0, 0, renderPerlin.getWidth(), renderPerlin.getHeight());
            }
        
            simplexShader.begin();
            
                simplexShader.setUniform3f("iResolution", RENDERWIDTH, RENDERHEIGHT, 0.0);
                simplexShader.setUniform1f("time", counterSimplex);
                simplexShader.setUniform1f("in1", in1);
                simplexShader.setUniform1f("zoom", zoom);
                simplexShader.setUniform1i("bwSwitch", bwSwitch);
                simplexShader.setUniform1i("bgTransparent", bgTransparent);
    
        
                ofSetColor(255,255,255);
                ofFill();
                ofRect(0, 0, renderSimplex.getWidth(), renderSimplex.getHeight());
            
            simplexShader.end();
        
        renderSimplex.end();
        
    }
    
    ofBackground(bgColor);
    if(bgTransparent) ofBackground(100);
    
    ofPushMatrix();
    
    ofSetColor(255);
    int previewWidth = RENDERWIDTH/10;
    int previewHeight = RENDERHEIGHT/10;
    
    ofTranslate(220, 10);
    ofFill();
    ofSetColor(255);
    if(linesHorizontal || linesVertical) renderLines.draw(0, 0, previewWidth, previewHeight);
    ofNoFill();
    ofSetColor(drawColor);
    ofRect(0, 0, previewWidth, previewHeight);
    
    ofTranslate(0, 10+previewHeight);
    ofFill();
    ofSetColor(255);
    if( arcFlag ) renderArcs.draw(0, 0, previewWidth, previewHeight);
    ofNoFill();
    ofSetColor(drawColor);
    ofRect(0, 0, previewWidth, previewHeight);
    
    ofTranslate(0, 10+previewHeight);
    ofFill();
    ofSetColor(255);
    if( voronoise ) renderVoronoise.draw(0, 0, previewWidth, previewHeight);
    ofNoFill();
    ofSetColor(drawColor);
    ofRect(0, 0, previewWidth, previewHeight);
    
    ofTranslate(0, 10+previewHeight);
    ofFill();
    ofSetColor(255);
    if( perlin ) renderPerlin.draw(0, 0, previewWidth, previewHeight);
    ofNoFill();
    ofSetColor(drawColor);
    ofRect(0, 0, previewWidth, previewHeight);
    
    ofTranslate(0, 10+previewHeight);
    ofFill();
    ofSetColor(255);
    if( simplex ) renderSimplex.draw(0, 0, previewWidth, previewHeight);
    ofNoFill();
    ofSetColor(drawColor);
    ofRect(0, 0, previewWidth, previewHeight);
    
    ofPopMatrix();
    
    if( guiShow ){
        gui.draw();
    }
    
    ofSetColor(drawColor);
    string info = " - "+ofToString(ofGetFrameRate(), 0)+ " fps";
    ofSetWindowTitle("GenerativeVisuals"+ info);
    
    
    
    // Output Syphon
    ofFill(); // 10.9 fix
    syphonOutLines.publishTexture(&syphonLines);
    syphonOutArcs.publishTexture(&syphonArcs);
    syphonOutVoronoise.publishTexture(&syphonVoronoise);
    syphonOutPerlin.publishTexture(&syphonPerlin);
    syphonOutSimplex.publishTexture(&syphonSimplex);

    
}




void ofApp::addNewArc(){
    
    randomArc _randomArc = *new randomArc();
    
    
    _randomArc.setup(center, radius, radius/numOfArcs);
    rndArc.push_back(_randomArc);
    
}

void ofApp::deleteArc(){
    rndArc.pop_back();
}

void ofApp::addNewHorizontalLine(){
    
    randomLine _randomLine = *new randomLine();
    
    
    _randomLine.setup(true, renderLines.getHeight(), 40, renderLines.getWidth());
    horizontalLines.push_back(_randomLine);
    
}

void ofApp::deleteHorizontalLine(){
    horizontalLines.pop_back();
}

void ofApp::addNewVerticalLine(){
    
    randomLine _randomLine = *new randomLine();
    
    
    _randomLine.setup(false, renderLines.getWidth(), 40, renderLines.getHeight());
    verticalLines.push_back(_randomLine);
    
}

void ofApp::deleteVerticalLine(){
    verticalLines.pop_back();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'h' ){
        guiShow = !guiShow;
    }
    if(key == 's') {
        gui.saveToFile("settings.xml");
    }
    if(key == 'l') {
        gui.loadFromFile("settings.xml");
    }
    if(key == '-') {
        if(numOfArcs > 1) numOfArcs--;
    }
    if(key == '.') {
        if(numOfArcs < 1000) numOfArcs++;
    }
    if(key == 'x') {
        timer = 1;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    draggedX = x;
    draggedY = y;
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    clickX = x;
    clickY = y;
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
//--------------------------------------------------------------
