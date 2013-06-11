#include "testApp.h"

bool isPresent =false;
int k=0;
//--------------------------------------------------------------
void testApp::setup() {
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);  
	background.loadImage("BG.jpg");
	kinect.initialize();
	
//LOADING IMAGES
	for(int i=0;i<10;i++){
		text[i].loadImage(ofToString(i)+".jpg");
	}
	wave[0].loadImage("1.png");
	wave[1].loadImage("2.png");
	wave[2].loadImage("3.png");
//SETTING UP BOX 2D ELEMENTS
	box2d.init();
	box2d.setGravity(0, 1);
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
	
//DEFINING THE TEXT PLANKS
	for (int i=0; i<10; i++) {
		board[i].setPhysics(0.3, 0.3, 0.3);
		board[i].setup(box2d.getWorld(), 12+50+(i*100), 235, 40,40);
	}

	anchor1.setup(box2d.getWorld(), 12, 235, 4);
	anchor2.setup(box2d.getWorld(), 1012, 235, 4);

	joint[0].setup(box2d.getWorld(),anchor1.body,board[0].body);
	joint[0].setLength(75);
	joint[0].setDamping(0.8);
	for(int i=1;i<=9;i++){
		joint[i].setup(box2d.getWorld(),board[i-1].body,board[i].body);
		joint[i].setLength(75);
		joint[i].setDamping(0.8);
	}
	joint[10].setup(box2d.getWorld(),board[9].body,anchor2.body);
	joint[10].setLength(75);
	joint[10].setDamping(0.8);

//LOADING AUDIO
	sound[0].loadSound("leftHand.wav");
	sound[0].setMultiPlay(true);
	sound[0].setLoop(false);
	sound[1].loadSound("rightHand.wav");
	sound[1].setMultiPlay(true);
	sound[1].setLoop(false);
	for(int i=0;i<10;i++){
		notes[i].loadSound(ofToString(i)+".wav");
		notes[i].setMultiPlay(true);
		notes[i].setLoop(false);
	}

head.setup(box2d.getWorld(),ofGetMouseX(),768,600);
	waitCount=0;
	p1=0;
	p2=0;
}

//--------------------------------------------------------------
void testApp::update() {
//DRAW STATIC OBJECTS
	ofSetColor(255,255,255);
	ofFill();
	background.draw(0,0,ofGetWidth(),ofGetHeight());
	ofSetColor(148,5,5);
	ofFill();
	ofRect(0,746,ofGetWidth(),22);
	ofSetColor(176,14,14);
	ofFill();
	ofRect(0,701,ofGetWidth(),45);
	ofSetColor(255,0,0);
	ofFill();
	ofRect(0,565,ofGetWidth(),136);
	ofSetColor(233,130,106);
	ofFill();
	ofRect(0,535,ofGetWidth(),30);
	ofSetColor(255,255,255);
	ofFill();
	ofRect(0,518,ofGetWidth(),17);

//head.setPosition(ofGetMouseX(),768);
head.setPosition(skeletonX[1],768);
	kinect.getSkeleton(skeletonX,skeletonY);
	if(skeletonX[1]==-1 &&skeletonY[1]==-1){
		isPresent = false;
	}
	else{
		isPresent = true;
	}
	box2d.update();	

//GESTURE RECOGNITION
	if(skeletonY[6]>skeletonY[9] && skeletonY[6]<skeletonY[18]){
		if(waitCount==0){
			p1=skeletonY[6];
		}
		
		if(waitCount<30){
			waitCount++;
		}
		else{
			p2=skeletonY[6];
			if(p2-p1>8){
				int i=0;
				i=int(skeletonX[6]/102);
				board[i].setVelocity(0,9000);	
				notes[i].play();
			}
			else{
				//myfont.drawString("Nothing", 0,400);
			}
			waitCount=0;
		}
	}

	if(skeletonY[5]>skeletonY[2] && skeletonY[5]<skeletonY[11]){
		if(waitCount==0){
			p1=skeletonY[5];
		}
		
		if(waitCount<30){
			waitCount++;
		}
		else{
			p2=skeletonY[5];
			if(p2-p1<-8){
				int i=0;
				i=int(skeletonX[5]/102);
				board[i].setVelocity(0,9000);
				notes[i].play();
			}
			else{
				//myfont.drawString("Nothing", 0,400);
			}
			waitCount=0;
		}
	}
	
}
//--------------------------------------------------------------
void testApp::draw() {
//DRAW STATIC OBJECTS
	ofSetColor(255,255,255);
	ofFill();
	background.draw(0,0,ofGetWidth(),ofGetHeight());
	ofSetColor(148,5,5);
	ofFill();
	ofRect(0,746,ofGetWidth(),22);
	ofSetColor(176,14,14);
	ofFill();
	ofRect(0,701,ofGetWidth(),45);
	ofSetColor(255,0,0);
	ofFill();
	ofRect(0,565,ofGetWidth(),136);
	ofSetColor(233,130,106);
	ofFill();
	ofRect(0,535,ofGetWidth(),30);
	ofSetColor(255,255,255);
	ofFill();
	ofRect(0,518,ofGetWidth(),17);

	ofSetColor(255,255,255);
	//ofNoFill();
	if(isPresent){
	wave[2].draw(floor(float(skeletonX[1]-256)),floor(float(518-80)),512,80);
	wave[1].draw(floor(float(skeletonX[1]-256)),floor(float(535-80)),512,80);
	wave[0].draw(floor(float(skeletonX[1]-256)),floor(float(565-80)),512,80);
	}
	/*for(int i=0;i<20;i++){
		ofRect(skeletonX[i],skeletonY[i],10,10);
	}*/
	ofSetColor(255,0,0);
	ofFill();
	ofRect(skeletonX[1]-4-256,564,518,10);

//DRAWING THE TEXT PLANK
	ofSetColor(255,255,255);
	ofFill();
	for(int i=0;i<10;i++){
		glPushMatrix();  
		glTranslatef(board[i].getPosition().x,board[i].getPosition().y,0);  
		glRotatef(ofRadToDeg(board[i].getAngle()),0,0,1);  
		text[i].draw(-40,-40.0);  
		glPopMatrix();  
	}
	
//DRAWING THE ANCHORS	
	anchor1.draw();
	anchor2.draw();
	
//DRAWING THE JOINTS
	for(int i=0;i<=8;i++){
		joint[i].draw();
	}

ofPushMatrix();
ofRotate(30);
//ofSetRectMode(OF_RECTMODE_CENTER);
//text[2].draw(20,20,80,80);
ofPopMatrix();
//head.draw();
	ofSetColor(0,0,0);
	//ofDrawBitmapString(ofToString(ofGetMouseX(),2), 0,10);
	//ofDrawBitmapString(ofToString(ofGetMouseY(),2), 0,30); 
	ofDrawBitmapString(ofToString(skeletonX[1]), 0,30); 
}
//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	if(key=='a'){
		//board[0].setPosition(100,100);
		//board[0].addRepulsionForce(ofVec2f(62,200),400);
		//board[0].addRepulsionForce(ofVec2f(62,400),400);
		//board[0].addForce(ofVec2f(0,0),20);
		board[0].setVelocity(0,9000);
	}
	if(key=='a'){
		notes[0].play();
	}
	if(key=='s'){
		notes[1].play();
	}
	if(key=='d'){
		notes[2].play();
	}
	if(key=='f'){
		notes[3].play();
	}
	if(key=='g'){
		notes[4].play();
	}
	if(key=='h'){
		notes[5].play();
	}
	if(key=='j'){
		notes[6].play();
	}
	if(key=='k'){
		notes[7].play();
	}
	if(key=='l'){
		notes[8].play();
	}
	if(key==';'){
		notes[9].play();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){
}
