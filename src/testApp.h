#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "Kinect.h"


// -------------------------------------------------

class testApp : public ofBaseApp {

public:

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);

	
	ofImage background;
	ofImage wave[3];
	ofImage text[10];
	ofSoundPlayer sound[2];
	ofSoundPlayer notes[10];

//BOX2D STUFF
	ofxBox2d box2d;
	ofxBox2dRect board[10];

	ofxBox2dJoint joint[11];
	ofxBox2dCircle head;

	ofxBox2dCircle anchor1,anchor2;


//KINECT STUFF
	Kinect kinect;

	float skeletonX[21];
	float skeletonY[21];
	int waitCount;
	float p1,p2;
};