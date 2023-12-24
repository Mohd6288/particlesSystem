#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
	// Initialize particles
	//particles.reserve(1000);
	for (int i = 0; i < numPoint; i++) {
		Particle* p = new Particle(); // Create particle on the heap
		p->setup();
		particles.push_back(p);
	}

	// Set default value for the flag to draw lines between particles
	bDrawLines = true;

	// Set initial values for the particle emitter
	emitterPos.set(ofGetWidth() * 0.5, ofGetHeight() * 0.5); // Center of the screen
	emitterVel.set(2, 0); // Emit particles to the right

	emitterRate = 1; // Number of particles to emit per frame
	emitterLifespan = 3.0; // How long each particle lives for
	emitterMass = 1.0; // How massive each particle is
	emitterAge = 20;

	// Setup GUI parameters
	gui.setup();
	gui.add(overallSpeed.setup("#Speed", 1, 0, 30));
	gui.add(noiseScale.setup("#NoiseScale", 0.01, 0, 0.1));
	gui.add(trail.setup("#Trail", 6, 0, 20));
	gui.add(maxLineDistance.setup("LineDistance", 20, 10, 100));
	gui.add(lineThickness.setup("Thickness", 1.0, 10, 30));
	gui.add(numPoint.setup("Point", 10, 100, 200));
	gui.add(sizeDot.setup("Dot Size", 1, 1, 20));
	gui.add(labelInfo.setup("Press","1,2,3 And Mouse Drag to interact"));


	// Create color picker
	gui.add(redCol.setup("Red Color", 1, 1, 255));
	gui.add(greenCol.setup("Green Color", 1, 1, 255));
	gui.add(blueCol.setup("Blue Color", 1, 1, 255));

	// Initialize particles using assign and setup
	p.assign(numPoint, Particle());
	for (int i = 0; i < p.size(); i++) {
		p[i].setup();
	}

	// Disable automatic background clearing
	ofSetBackgroundAuto(false);
}



void ofApp::update() {
	// Emit new particles from the emitter
	for (int i = 0; i < emitterRate; i++) {
		Particle* p = new Particle(); // Create particle on the heap
		p->setup();
		p->pos.set(emitterPos); // Set the position of the particle to the emitter position
		p->vel.set(emitterVel);
		p->color = ofColor::fromHsb(ofRandom(255), 200, 255); // Random color for each emitted particle
		p->size = sizeDot;
		p->lifetime = emitterAge;
		p->update(overallSpeed, noiseScale,mouseX,mouseY,currentKey);
		particles.push_back(p); // Assuming 'particles' is a vector of particle pointers in ofApp.h
	}

	bool bNewFrame = false;

	// Background subtraction logic
	if (bLearnBackground == true) {
		// Background learning logic goes here if needed
		bLearnBackground = false;
	}

	vector<ofVec2f> blobPts; // Vector to store blob points

	// Set the frame rate
	ofSetFrameRate(60);

	// Update the particles
	if (p.size() != numPoint) {
		// If the number of particles is not equal to the specified number, reassign particles
		p.assign(int(numPoint), Particle());
		for (int i = 0; i < p.size(); i++) {
			p[i].setup();
		}
	}

	// Update each particle
	for (int i = 0; i < p.size(); i++) {
		p[i].repel(blobPts); // Repel particles based on blob points
		p[i].update(overallSpeed, noiseScale, mouseX, mouseY, currentKey);
	}



	if (emitterAge > 0) {
	// Delete all particles from the container
	for (Particle* a : particles) {
		delete a;
	}
	particles.clear();
	//cout << "Some of them are dead" << endl;
	}
}


//--------------------------------------------------------------
void ofApp::draw() {
	// Clear the background with a trail effect
	ofSetColor(0, 0, 0, trail);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	
	// Draw lines and contours if the flag is set
	if (bDrawLines) {
		ofSetColor(255, 255, 255);
	}

	// Draw lines between particles
	for (int i = 0; i < p.size(); i++) {
		for (int j = i + 1; j < p.size(); j++) {
			float distance = ofDist(p[i].pos.x, p[i].pos.y, p[j].pos.x, p[j].pos.y);
			if (distance < maxLineDistance) {
				// Draw lines between particles within the specified distance
				ofSetLineWidth(lineThickness);
				ofDrawLine(p[i].pos.x, p[i].pos.y, p[j].pos.x, p[j].pos.y);
			}
			else if (distance < maxLineDistance * 2) {
				// Draw lines with varying alpha based on distance
				float alpha = ofMap(distance, maxLineDistance, maxLineDistance * 2, 255, 0);
				ofSetColor(redCol, greenCol, blueCol, alpha);
				ofDrawLine(p[i].pos.x, p[i].pos.y, p[j].pos.x, p[j].pos.y);
			}
		}
		// Draw particles with color and size
		ofSetColor(p[i].color);
		p[i].draw(sizeDot);
	}

	// Draw GUI controls
	ofSetHexColor(0xf00ff); // Set color for GUI controls
	gui.draw();
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	currentKey = key;
	if (key == '3') {
	 bDrawLines = !bDrawLines;
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

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
