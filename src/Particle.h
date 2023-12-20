#pragma once
#include "ofMain.h"

class Particle
{

public:
	Particle();
	~Particle();

	ofColor color;
	void setup();
	void update(float speed , float noise);
	void draw(float sizeDot);
	void repel(vector<ofVec2f>replePt);
	ofVec2f pos;
	ofVec2f vel;
	ofVec2f frc;
	float drag;
	ofVec2f repelFrc;
	ofVec2f uniqueVal;
	float size;
	float lifetime;
	ofColor startColor;
	ofColor endColor;


};

