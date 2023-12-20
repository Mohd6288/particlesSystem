#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		vector <Particle> p;	
		//vector<Particle> particles; // Add this line to declare the vector of particles
		vector<Particle*> particles; // Vector of particle pointers
		ofxPanel gui;
		ofxFloatSlider overallSpeed;
		ofxFloatSlider noiseScale;
		ofxFloatSlider trail;
		ofxFloatSlider maxLineDistance;
		ofxFloatSlider lineThickness;
		ofxFloatSlider numPoint;
		ofxFloatSlider sizeDot;

		//color picker
		ofxFloatSlider blueCol;
		ofxFloatSlider redCol;
		ofxFloatSlider greenCol;

		ofxToggle bLearnBackground;
		ofVec2f emitterPos;
		ofVec2f emitterVel;
		int emitterRate; // Number of particles to emit per frame
		float emitterLifespan; // How long each particle lives for
		float emitterMass; // How massive each particle is
		float emitterAge;
		bool bDrawLines;	
};
