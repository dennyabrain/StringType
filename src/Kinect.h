#pragma once
#include <windows.h>
#include "ofMain.h" 
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>
#include "NuiApi.h"
using namespace std;

class Kinect{
public:
	Kinect();
	~Kinect();
	void initialize();
	ofPoint getRightHand();
	void getSkeleton(float* x, float* y);
	
private:
	HANDLE colorStreamHandle;
	HANDLE colorEvent;
	HANDLE skeletonEvent;
	const NUI_IMAGE_FRAME* image;
	INuiFrameTexture* pTexture;
	NUI_LOCKED_RECT LockedRect;
	NUI_SKELETON_FRAME skeletonFrame;
};