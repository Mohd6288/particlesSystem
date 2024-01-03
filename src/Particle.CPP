#include "Particle.h"

using namespace glm;
// Constructor
Particle::Particle()
{
}

// Destructor
Particle::~Particle()
{
    //cout << "Dead now" << endl;
};

// Initialize particle properties
void Particle::setup()
{
    color = ofColor(100, 150, 130, 1);
    pos.x = ofRandomWidth();
    pos.y = ofRandomHeight();
    vel.x = ofRandom(-1, 1);
    vel.y = ofRandom(-1, 1);
    frc = ofVec2f(0, 0);
    uniqueVal.x = ofRandom(-1000, 1000);
    uniqueVal.y = ofRandom(-1000, 1000);
    size = ofRandom(0.1, 1);
    lifetime = ofRandom(50, 200);  // Adjust the range based on your preference
    drag = ofRandom(0.95, 0.998);
    vel -= repelFrc;
    startColor = ofColor::fromHsb(ofRandom(255), 200, 255); // Random start color
    endColor = ofColor::fromHsb(ofRandom(255), 200, 255);   // Random end color
}

// Update particle position and velocity
void Particle::update(float speed, float noise , float msX, float msY, char key)
{
    pos += vel;
    vel *= drag;
    frc.x = ofSignedNoise(uniqueVal.x, pos.y * 0.01, ofGetElapsedTimef() * 0.2);
    frc.y = ofSignedNoise(uniqueVal.y, pos.x * 0.01, ofGetElapsedTimef() * 0.2);
    frc *= noise;
    vel += frc;

    // Bounce off walls
    if (pos.x + vel.x > ofGetWidth()) {
        pos.x = ofGetWidth();
        vel.x *= -1.0;
    }
    else if (pos.x + vel.x < 0) {
        pos.x = 0;
        vel.x *= -1.0;
    }

    if (pos.y + vel.y > ofGetHeight()) {
        pos.y = ofGetHeight();
        vel.y *= -1.0;
    }
    else if (pos.y + vel.y < 0) {
        pos.y = 0;
        vel.y *= -1.0;
    }

   
    if (lifetime <= 0) {
        // Optionally mark the particle as dead or reset its properties
        lifetime = ofRandom(50, 200);
        // Or you can remove it from the vector in ofApp::update
    }
    else {
        lifetime -= 1;
    }

    if (msX > 0 && msX < ofGetWidth() && msY > 0 && msY < ofGetHeight()) {
        if (key == '1') {
            moveAway(msX, msY);
        }
        else if (key == '2') {
            moveToPoint(msX, msY);
        }

    }

    pos += vel * speed;
}

// Draw the particle
void Particle::draw(float sizeDot)
{
    // Interpolate between startColor and endColor based on x position
    float pct = ofMap(pos.x, 0, ofGetWidth(), 0, 1);
    ofColor currentColor = startColor.getLerped(endColor, pct);
    ofSetColor(currentColor);

    // Map color of the particle based on position
    float redColor = ofMap(pos.x, 0, ofGetWidth(), 0, 255);
    float greenColor = ofMap(pos.y, 0, ofGetHeight(), 0, 255);
    float blueColor = ofMap(pos.x, 0, ofGetWidth(), 255, 0);
    ofSetColor(redColor, greenColor, blueColor);

    // Draw the particle as a circle
    ofDrawCircle(pos.x, pos.y, size * sizeDot);
}

// Repel the particle from a set of points
void Particle::repel(vector<ofVec2f> repelPt)
{
    repelFrc.set(0, 0);

    for (int i = 0; i < repelPt.size(); i++) {
        float dist = pos.distance(repelPt[i]);
        cout << dist << endl;
        // If the particle is close to a repelling point, apply force
        if (dist < 150) {
            vec2 newRepelPt = repelPt[i] - pos;
            repelFrc += newRepelPt * 0.0000002;
        }
    }
}

//move toward the repel X and Y point
void Particle::moveAway(float repelX, float repelY) {

    vec2 repel = ofVec2f(repelX, repelY);
    vec2 direction = pos - repel; // vector subtraction, the order matters!

    float directionMag = length(direction);
    //we have to make sure direction magnitude isn't 0 before normalizing
    if (directionMag > 0) {
        direction = normalize(direction);
    }

    if (directionMag < 200) {
        vel += direction * 2;
    }

}

//--------------------------------------------------------------
//move toward the attract X and Y point
void Particle::moveToPoint(float attractX, float attractY) {

    vec2 attractor = ofVec2f(attractX, attractY);
    vec2 direction = attractor - pos; // vector subtraction, the order matters!

    float directionMag = length(direction);
    //we have to make sure direction magnitude isn't 0 before normalizing
    if (directionMag > 0) {
        direction = normalize(direction);
    }

    vel += direction * 2;

}
