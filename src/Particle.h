#pragma once
#include "ofMain.h"

class Particle
{

public:
	Particle();
	~Particle();
	void setup();
	void update(float speed , float noise,float msX, float msY, char key);
	void draw(float sizeDot);
	void repel(vector<ofVec2f>replePt);

	ofColor color;
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
	void moveAway(float repelX, float repelY);
	void moveToPoint(float attractX, float attractY);


};

