#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    
    ofSetFrameRate(60);
    ofSetWindowTitle("GenerativeVisuals");
    ofEnableSmoothing();
    ofDisableArbTex();
    ofSetVerticalSync(true);
    ofSetCircleResolution(10);

    
    /*
    
    // FBO renders
    renderLines.allocate(render_widthIDTH, render_heightEIGHT);
    renderArcs.allocate(render_widthIDTH, render_heightEIGHT);
    renderVoronoise.allocate(render_widthIDTH, render_heightEIGHT);
    renderPerlin.allocate(render_widthIDTH, render_heightEIGHT);
    renderSimplex.allocate(render_widthIDTH, render_heightEIGHT);

    
    
    
    // Syphon
    syphonOutLines.setName("Lines");
    syphonOutArcs.setName("Arcs");
    syphonOutVoronoise.setName("Voronoise");
    syphonOutPerlin.setName("Perlin");
    syphonOutSimplex.setName("Simplex");

    
    syphonLines.allocate(render_widthIDTH, render_heightEIGHT, GL_RGBA);
    syphonArcs.allocate(render_widthIDTH, render_heightEIGHT, GL_RGBA);
    syphonVoronoise.allocate(render_widthIDTH, render_heightEIGHT, GL_RGBA);
    syphonPerlin.allocate(render_widthIDTH, render_heightEIGHT, GL_RGBA);
    syphonSimplex.allocate(render_widthIDTH, render_heightEIGHT, GL_RGBA);
    
    
    syphonLines = renderLines.getTextureReference();
    syphonArcs = renderArcs.getTextureReference();
    syphonVoronoise = renderVoronoise.getTextureReference();
    syphonPerlin = renderPerlin.getTextureReference();
    syphonSimplex = renderSimplex.getTextureReference();
    */
    
    //VoronoiseRender
    voronoiseShader.load("shaders/voronoiseShader");
    perlinShader.load("shaders/perlinShader");
    simplexShader.load("shaders/simplexShader");
    ikedaShader.load("shaders/ikeda");
    cloudShader.load("shaders/cloud");

    
    // setup Gui
    
    screenSize.setName("Screen Size");
    screenSize.add(render_width.set("render_width",100,10,3000));
    screenSize.add(render_height.set("render_height",100,10,3000));
    
    paramGeneral.setName("Enable");
    paramGeneral.add(linesHorizontal.set("linesHorizontal", true));
    paramGeneral.add(linesVertical.set("linesVertical", true));
    paramGeneral.add(arcFlag.set("arcFlag", true));
    paramGeneral.add(voronoise.set("voronoise", true));
    paramGeneral.add(perlin.set("perlin", true));
    paramGeneral.add(simplex.set("simplex", true));
    paramGeneral.add(ikeda.set("ikeda", true));
    paramGeneral.add(cloud.set("cloud", true));
    
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
    paramArcs.add(width_height.set("width_height", true));
    
    
    
    // param for voronoiseShader
    paramVoronoise.setName("paramVoronoise");
    paramVoronoise.add(tempoVoronoise.set("tempoVoronoise", 0.5, 0., 1));
    paramVoronoise.add(scaleVoronoise.set("scaleVoronoise", 10, 0., 40));
    paramVoronoise.add(octavesVoronoise.set("octavesVoronoise", 8, 1, 16));
    paramVoronoise.add(function.set("function", 1, 0., 3));
    paramVoronoise.add(distance_type.set("distance_type", 1, 0., 3));
    paramVoronoise.add(multiply_by_F1.set("multiply_by_F1", false));
    paramVoronoise.add(multiply_by_F2.set("multiply_by_F2", false));
    paramVoronoise.add(inverse.set("inverse", false));

    
    
    // param for perlinShader
    paramPerlin.setName("paramPerlin");
 //   paramPerlin.add(tempoPerlin.set("tempoPerlin", 0.1, 0., 1));
    paramPerlin.add(density.set("density", 1, 0.3, 10));

    paramPerlin.add(fRatio.set("fRatio", 0.5, 0.1, 0.9));
    paramPerlin.add(FirstDivision.set("FirstDivision", 1, 1., 10));
    paramPerlin.add(rotationSpeed.set("rotationSpeed", 0.1, -1., 1));
    paramPerlin.add(rotCenterX.set("rotCenterX", 0.5, 0., 1.));
    paramPerlin.add(rotCenterY.set("rotCenterY", 0.5, 0., 1));


    
    // param for simplexShader
    paramSimplex.setName("paramSimplex");
    paramSimplex.add(tempoSimplex.set("tempoSimplex", 0.1, 0., 1));
    paramSimplex.add(in1.set("in1", 1, 0., 1000));
    paramSimplex.add(zoom.set("zoom", 0.1, 0., 1));
    
    // param for Ikeda
    paramIkeda.setName("ikeda");
    paramIkeda.add(tempoIkeda.set("tempoIkeda", 0.1, 0., 1));
    paramIkeda.add(amount.set("amount", 0.1, 0., 1));
    paramIkeda.add(xGrid.set("xGrid",10,10,200));
    paramIkeda.add(yGrid.set("yGrid",10,10,200));
    
    // param for Cloud
    paramCloud.setName("cloud");
    paramCloud.add(tempoCloud.set("tempoCloud", 0.1, 0., 1));
    paramCloud.add(zoomCloud.set("zoomCloud", 0.1, 0., 1));
    paramCloud.add(balance.set("balance",0.5,0.,1.));
    paramCloud.add(contrast.set("contrast",0.,-1,1.));


    // setGui
    parameters.setName("parameters");
    parameters.add(screenSize);
    parameters.add(paramGeneral);
    parameters.add(paramLines);
    parameters.add(paramArcs);
    parameters.add(paramVoronoise);
    parameters.add(paramPerlin);
    parameters.add(paramSimplex);
    parameters.add(paramIkeda);
    parameters.add(paramCloud);


    
    gui.setup(parameters);
    guiShow = true;
    
    //
    gui.loadFromFile("settings.xml");

    
    renderLines.allocate(render_width, render_height);
    renderArcs.allocate(render_width, render_height);
    renderVoronoise.allocate(render_width, render_height);
    renderPerlin.allocate(render_width, render_height);
    renderSimplex.allocate(render_width, render_height);
    renderIkeda.allocate(render_width, render_height);
    renderCloud.allocate(render_width, render_height);

    
    // Syphon
    syphonOutLines.setName("Lines");
    syphonOutArcs.setName("Arcs");
    syphonOutVoronoise.setName("Voronoise");
    syphonOutPerlin.setName("Perlin");
    syphonOutSimplex.setName("Simplex");
    syphonOutIkeda.setName("Ikeda");
    syphonOutCloud.setName("Cloud");


    
    ofSetWindowShape(render_width/10+230, (render_height/10+10)*7+10);
    
    
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
    counterIkeda = 0;
    counterCloud = 0;
    
    
    for(int i = 0; i<255; i++ ){
        keyIsDown[i] = false;
    }

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
 //   counterPerlin   += tempoPerlin/2;
    counterSimplex += tempoSimplex/10;
    
    counterPerlinRot += rotationSpeed/100;
    
    counterIkeda += tempoIkeda/10;
    counterCloud += tempoCloud/10;


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
                ofDrawRectangle(0, 0, renderPerlin.getWidth(), renderPerlin.getHeight());
            }
        
            voronoiseShader.begin();
            
                voronoiseShader.setUniform3f("iResolution", render_width, render_height, 0.0);
                voronoiseShader.setUniform1f("time", counterVoronoise);
                voronoiseShader.setUniform1f("SCALE", scaleVoronoise);
                voronoiseShader.setUniform1i("OCTAVES", octavesVoronoise);
                voronoiseShader.setUniform1f("function", function);
                voronoiseShader.setUniform1i("multiply_by_F1", multiply_by_F1);
                voronoiseShader.setUniform1i("multiply_by_F2", multiply_by_F2);
                voronoiseShader.setUniform1i("inverse", inverse);
                voronoiseShader.setUniform1f("distance_type", distance_type);
                voronoiseShader.setUniform1i("bwSwitch", bwSwitch);
                voronoiseShader.setUniform1i("bgTransparent", bgTransparent);
        
                
                ofSetColor(255,255,255);
                ofFill();
                ofDrawRectangle(0, 0, renderVoronoise.getWidth(), renderVoronoise.getHeight());
            
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
            ofDrawRectangle(0, 0, renderPerlin.getWidth(), renderPerlin.getHeight());
            }
        
            perlinShader.begin();
            
                perlinShader.setUniform3f("iResolution", render_width, render_height, 0.0);
                perlinShader.setUniform1f("time", counterPerlin);
                perlinShader.setUniform1f("density", density);

                perlinShader.setUniform1f("fRatio", fRatio);
                perlinShader.setUniform1f("FirstDivision", FirstDivision);
                perlinShader.setUniform1f("theta", counterPerlinRot);
                perlinShader.setUniform2f("rotCenter", rotCenterX, rotCenterY);
                perlinShader.setUniform1i("bwSwitch", bwSwitch);
                perlinShader.setUniform1i("bgTransparent", bgTransparent);
                
                
                ofSetColor(255,255,255);
                ofFill();
                ofDrawRectangle(0, 0, renderPerlin.getWidth(), renderPerlin.getHeight());
            
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
            ofDrawRectangle(0, 0, renderPerlin.getWidth(), renderPerlin.getHeight());
        }
        
        simplexShader.begin();
        
        simplexShader.setUniform3f("iResolution", render_width, render_height, 0.0);
        simplexShader.setUniform1f("time", counterSimplex);
        simplexShader.setUniform1f("in1", in1);
        simplexShader.setUniform1f("zoom", zoom);
        simplexShader.setUniform1i("bwSwitch", bwSwitch);
        simplexShader.setUniform1i("bgTransparent", bgTransparent);
        
        
        ofSetColor(255,255,255);
        ofFill();
        ofDrawRectangle(0, 0, renderSimplex.getWidth(), renderSimplex.getHeight());
        
        simplexShader.end();
        
        renderSimplex.end();
        
    }
    
    if(ikeda){
        
        renderIkeda.begin();
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if(!bgTransparent){// ofBackground(bgColor);
            
            ofSetColor(bgColor);
            ofFill();
            ofDrawRectangle(0, 0, renderIkeda.getWidth(), renderIkeda.getHeight());
        }
        
        ikedaShader.begin();
        
        ikedaShader.setUniform2f("u_resolution",render_width, render_height);
        ikedaShader.setUniform1f("u_time", counterIkeda);
        ikedaShader.setUniform1f("u_amount", amount);
        ikedaShader.setUniform1f("u_xGrid", xGrid);
        ikedaShader.setUniform1f("u_yGrid", yGrid);
        ikedaShader.setUniform1i("bwSwitch", bwSwitch);
        ikedaShader.setUniform1i("bgTransparent", bgTransparent);
        
        
        
        ofSetColor(255,255,255);
        ofFill();
        ofDrawRectangle(0, 0, renderIkeda.getWidth(), renderIkeda.getHeight());
        
        ikedaShader.end();
        
        renderIkeda.end();
        
    }
    
    if(cloud){
        
        renderCloud.begin();
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if(!bgTransparent){// ofBackground(bgColor);
            
            ofSetColor(bgColor);
            ofFill();
            ofDrawRectangle(0, 0, renderCloud.getWidth(), renderCloud.getHeight());
        }
        
        cloudShader.begin();
        
        cloudShader.setUniform2f("u_resolution",render_width, render_height);
        cloudShader.setUniform1f("u_time", counterCloud);
        cloudShader.setUniform1f("u_zoom", zoomCloud);
        cloudShader.setUniform1f("u_balance", balance);
        cloudShader.setUniform1f("u_contrast", contrast+1.0);
        cloudShader.setUniform1i("bwSwitch", bwSwitch);
        cloudShader.setUniform1i("bgTransparent", bgTransparent);
        
        
        
        ofSetColor(255,255,255);
        ofFill();
        ofDrawRectangle(0, 0, renderCloud.getWidth(), renderCloud.getHeight());
        
        cloudShader.end();
        
        renderCloud.end();
        
    }
    
    ofBackground(bgColor);
    if(bgTransparent) ofBackground(100);
    
    ofPushMatrix();
    
    ofSetColor(255);
    int previewWidth = render_width/10;
    int previewHeight = render_height/10;
    
    ofTranslate(220, 10);
    ofFill();
    ofSetColor(255);
    if(linesHorizontal || linesVertical) renderLines.draw(0, 0, previewWidth, previewHeight);
    ofNoFill();
    ofSetColor(drawColor);
    ofDrawRectangle(0, 0, previewWidth, previewHeight);
    
    ofTranslate(0, 10+previewHeight);
    ofFill();
    ofSetColor(255);
    if( arcFlag ) renderArcs.draw(0, 0, previewWidth, previewHeight);
    ofNoFill();
    ofSetColor(drawColor);
    ofDrawRectangle(0, 0, previewWidth, previewHeight);
    
    ofTranslate(0, 10+previewHeight);
    ofFill();
    ofSetColor(255);
    if( voronoise ) renderVoronoise.draw(0, 0, previewWidth, previewHeight);
    ofNoFill();
    ofSetColor(drawColor);
    ofDrawRectangle(0, 0, previewWidth, previewHeight);
    
    ofTranslate(0, 10+previewHeight);
    ofFill();
    ofSetColor(255);
    if( perlin ) renderPerlin.draw(0, 0, previewWidth, previewHeight);
    ofNoFill();
    ofSetColor(drawColor);
    ofDrawRectangle(0, 0, previewWidth, previewHeight);
    
    ofTranslate(0, 10+previewHeight);
    ofFill();
    ofSetColor(255);
    if( simplex ) renderSimplex.draw(0, 0, previewWidth, previewHeight);
    ofNoFill();
    ofSetColor(drawColor);
    ofDrawRectangle(0, 0, previewWidth, previewHeight);
    
    ofTranslate(0, 10+previewHeight);
    ofFill();
    ofSetColor(255);
    if( ikeda ) renderIkeda.draw(0, 0, previewWidth, previewHeight);
    ofNoFill();
    ofSetColor(drawColor);
    ofDrawRectangle(0, 0, previewWidth, previewHeight);
    
    ofTranslate(0, 10+previewHeight);
    ofFill();
    ofSetColor(255);
    if( cloud ) renderCloud.draw(0, 0, previewWidth, previewHeight);
    ofNoFill();
    ofSetColor(drawColor);
    ofDrawRectangle(0, 0, previewWidth, previewHeight);
    
    ofPopMatrix();
    
    if( guiShow ){
        gui.draw();
    }
    
    ofSetColor(drawColor);
    string info = " - "+ofToString(ofGetFrameRate(), 0)+ " fps";
    ofSetWindowTitle("GenerativeVisuals"+ info);
    
    
    
    // Output Syphon
    ofFill(); // 10.9 fix
    syphonOutLines.publishTexture(&renderLines.getTexture());
    syphonOutArcs.publishTexture(&renderArcs.getTexture());
    syphonOutVoronoise.publishTexture(&renderVoronoise.getTexture());
    syphonOutPerlin.publishTexture(&renderPerlin.getTexture());
    syphonOutSimplex.publishTexture(&renderSimplex.getTexture());
    syphonOutIkeda.publishTexture(&renderIkeda.getTexture());
    syphonOutCloud.publishTexture(&renderCloud.getTexture());

    
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
//    if( key == 'h' ){
//        guiShow = !guiShow;
//    }
    keyIsDown[key] = true;
    
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
    
    if(keyIsDown['h'] && key == OF_KEY_LEFT) {
        render_height--;
    }
    if(keyIsDown['h'] && key == OF_KEY_RIGHT) {
        render_height++;
    }
    if(keyIsDown['w'] && key == OF_KEY_LEFT) {
        render_width--;
    }
    if(keyIsDown['w'] && key == OF_KEY_RIGHT) {
        render_width++;
    }
    
}
//--------------------------------------------------------------
void ofApp::exit(){
    gui.saveToFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    keyIsDown[key] = false;
    
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
