#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {

	//screen frame rate
	ofSetFrameRate(45);
    ofSetBackgroundColor(0,0,0);
	sound1.load("music.mp3");
	
	// Initialize particles
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
	ofSetBackgroundAuto(true);
}



void ofApp::update() {

    ofSetBackgroundAuto(bDrawLines);
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
	ofSetFrameRate(45);

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
	//increments framecount by 1 for each draw loop
	frameCount++;
	std::cout << frameCount << std::endl;


    //--------------------------------------------------------------
    //      THIS IS MY DEMONSTRATION OF A PARTICLE SYSTEM
    //--------------------------------------------------------------
    //Using a incrementing framecount i trigger a soundfile then many ofDrawBitmapString to explain the concept of a particle system.
    ofSetColor(100, 0, 250);
    if (frameCount > 0 && frameCount <= 5) {
        sound1.play();
    }
    else if (frameCount > 5 && frameCount <= 25) {
        for (int i = 0; i < 45; i++) {
            for (int j = 0; j < 30; j++) {
                ofDrawBitmapString("HELLO!!!", 0 + (50 * j), 0 + (25 * i));
            }
        }
    }
    else if (frameCount >= 25 && frameCount <= 125) {
        ofDrawBitmapString("WELCOME TO MY PARTICLE SYSTEM", ofGetWidth() / 2 - 125, ofGetHeight() / 2);
        ofDrawBitmapString("TO SKIP INTRO PRESS SPACE BAR", ofGetWidth() / 2 - 125, 50);
    }
    else if (frameCount >= 125 && frameCount <= 225) {
        ofDrawBitmapString("ARE YOU READY TO LEARN???", ofGetWidth() / 2 - 100, ofGetHeight() / 2);
        ofDrawBitmapString("TO SKIP INTRO PRESS SPACE BAR", ofGetWidth() / 2 - 125, 50);
    }
    else if (frameCount >= 230 && frameCount <= 240) {
        for (int i = 0; i < 35; i++) {
            for (int j = 0; j < 35; j++) {
                ofSetColor(255, 10, 255);
                ofDrawBitmapString(":(  :(  :(  :(  :(  :(", 0 + (185 * j), 0 + (25 * i));
            }
        }
    }
    else if (frameCount >= 240 && frameCount <= 330) {
        ofSetColor(100, 0, 250);
        ofDrawBitmapString("IT SHOULD BE FUN I PROMISE", ofGetWidth() / 2 - 100, ofGetHeight() / 2);
    }
    else if (frameCount >= 330 && frameCount <= 445) {
        ofSetColor(100, 0, 250);
        ofDrawBitmapString("FIRSTLY WHAT IS A PARTICLE SYSTEM??", ofGetWidth() / 2 - 125, ofGetHeight() / 2);
    }
    else if (frameCount >= 445 && frameCount <= 460) {
        for (int i = 0; i < 35; i++) {
            for (int j = 0; j < 30; j++) {
                ofSetColor(255, 10, 255);
                ofDrawBitmapString("? ? ? ? ? ? ? ? ? ? ?", 0 + (175 * j), 0 + (25 * i));
            }
        }
    }
    else if (frameCount >= 460 && frameCount <= 1000) {
        ofSetColor(100, 0, 250);
        ofDrawBitmapString("A PARTICLE SYSTEM IS A TECHNIQUE IN GAME PHYSICS,", ofGetWidth() / 2 - 225 + 25, ofGetHeight() / 2 - 100);
        ofDrawBitmapString("MOTION GRAPHICS, AND COMPUTER GRAPHICS.", ofGetWidth() / 2 - 190 + 25, ofGetHeight() / 2 - 75);
        ofDrawBitmapString("IT USES A LARGE NUMBER OF SMALL PARTICLES (SPRITES) OR", ofGetWidth() / 2 - 225, ofGetHeight() / 2 - 25);
        ofDrawBitmapString("OTHER GRAPHIC OBJECTS TO SIMULATE CERTAIN TYPES OF 'FUZZY' PHENOMENA", ofGetWidth() / 2 - 285 + 25, ofGetHeight() / 2 - 0);
        ofDrawBitmapString("FOR EXAMPLE - SMOKE, FIRE, STARS CAN ALL BE GENERATED BY USING A PARTICLE SYSTEM", ofGetWidth() / 2 - 335 + 25, ofGetHeight() / 2 + 50);
    }
    else if (frameCount >= 1000 && frameCount <= 1100) {
        ofSetColor(100, 0, 250);
        ofDrawBitmapString("MY SYSTEM IS A SIMPLE PATTERN GENERATOR", ofGetWidth() / 2 - 150, ofGetHeight() / 2);
    }
    else if (frameCount >= 1100 && frameCount <= 1200) {
        ofSetColor(100, 0, 250);
        ofDrawBitmapString("I'LL SHOW YOU!!!", ofGetWidth() / 2 - 75, ofGetHeight() / 2);
    }
    else if (frameCount >= 1200 && frameCount <= 1250) {
        for (int i = 0; i < 35; i++) {
            for (int j = 0; j < 30; j++) {
                ofSetColor(255, 10, 255);
                ofDrawBitmapString("LETS START WITH IT!!", 0 + (230 * j), 0 + (25 * i));
            }
        }
    }
    else if (frameCount >= 1250 && frameCount <= 1350) {
        ofSetColor(100, 0, 250);
        ofDrawBitmapString("Imagin ONE PARTICLE", ofGetWidth() / 2 - 75, 200);
    }
    else if (frameCount >= 1400 && frameCount <= 1600) {
        ofSetColor(100, 0, 250);
        ofDrawBitmapString("WHEN THE PARTICLE 'DIES'", ofGetWidth() / 2 - 85, 200);
        ofDrawBitmapString("A NEW ONE IS BORN", ofGetWidth() / 2 - 65, 220);
    }
    else if (frameCount >= 1600 && frameCount <= 1800) {
        ofSetColor(100, 0, 250);
        ofDrawBitmapString("EACH PARTICLE SPAWNS DEPENDING", ofGetWidth() / 2 - 115, 200);
        ofDrawBitmapString("ON A SET OF PARAMETERS", ofGetWidth() / 2 - 90, 220);
    }
    else if (frameCount >= 1800 && frameCount <= 2000) {
        ofSetColor(100, 0, 250);
        ofDrawBitmapString("AND EACH PARAMETERS MANIPULATES", ofGetWidth() / 2 - 125, 200);
        ofDrawBitmapString("THE PARTICLE", ofGetWidth() / 2 - 55, 220);
    }
    else if (frameCount >= 2000 && frameCount <= 2150) {
        ofSetColor(100, 0, 250);
        ofDrawBitmapString("WHAT CAN WE MANIPULATE I HEAR YOU ASK??", ofGetWidth() / 2 - 150, 200);
    }
    else if (frameCount >= 2150 && frameCount <= 2550) {
        for (int i = 0; i < 35; i++) {
            ofSetColor(255, 10, 255);
            ofDrawBitmapString("VELOCITY    ANGLE    LIFESPAN    ROTATE    FORCE    SPINNING    HISTORY    BORN RATE    FRICTION", 140, 0 + (25 * i));
        }
    }
    else if (frameCount >= 2550 && frameCount <= 2700) {
        ofSetColor(100, 0, 250);
        ofDrawBitmapString("EACH OF THESE PARAMETERS DETEMINE THE RULES FOR EACH OF THE NEXT BORN PARTICLE", ofGetWidth() / 2 - 275, 200);
    }
    else if (frameCount >= 2700 && frameCount <= 2825) {
        ofSetColor(100, 0, 250);
        ofDrawBitmapString("NOW LETS SEE HOW THESE PARTICLES REACT WHEN THERE'S MORE THAN ONE", ofGetWidth() / 2 - 275, 200);
    }
    else if (frameCount >= 2825 && frameCount <= 3020) {
        ofSetColor(100, 0, 250);
        ofDrawBitmapString("BUT!!!!!! I THINK THE BEST WAY OF LEARNING IS BY TEACHING YOURSELF", ofGetWidth() / 2 - 275, 200);
    }
    else if (frameCount >= 3020 && frameCount <= 3150) {
        ofSetColor(100, 0, 250);
        ofDrawBitmapString("WOULDN'T YOU AGREE????", ofGetWidth() / 2 - 100, 200);
    }
    else if (frameCount >= 3150 && frameCount <= 3300) {
        ofSetColor(100, 0, 250);
        ofDrawBitmapString("LOOK TO YOUR LEFT AND YOU'LL SEE AN INTERFACE TO CONTROL THESE PARAMETERS", ofGetWidth() / 2 - 270, 200);
    }
    else if (frameCount >= 3300 && frameCount <= 3500) {
        ofSetColor(100, 0, 250);
        ofDrawBitmapString("CLICK AND DRAG ON ANY PARAMETER YOU WANT", ofGetWidth() / 2 - 175, 200);
        ofDrawBitmapString("I'D SUGGEST PUTTING THE Speed UP And press 3 FOR A START!!!", ofGetWidth() / 2 - 200, 220);
    }
    else if (frameCount >= 3500 && frameCount <= 3550) {
        for (int i = 0; i < 35; i++) {
            for (int j = 0; j < 30; j++) {
                ofSetColor(255, 10, 255);
                ofDrawBitmapString("ENJOY!!!", 0 + (50 * j), 0 + (25 * i));
            }
        }
    }

    //Drawing Interface at a certain time in the demonstration
    if (frameCount > 3150) {
            ofSetColor(0, 0, 0);
            ofDrawBitmapString("Particles: " + ofToString(p.size()), 20, 40);

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
 }
    



//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	currentKey = key;
    //taggle the effect
	if (key == '3') {
	 bDrawLines = !bDrawLines;
	}
    // to skip the instractions
    if (key == ' ') {
        frameCount = 3500;
        sound1.stop();
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
