#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
	auto param = glm::vec3(15, 0, 0);
	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

	for (int i = 0; i < 500; i++) {

		auto location = glm::vec3(
			ofMap(ofNoise(noise_seed.x, (i + ofGetFrameNum()) * 0.01), 0, 1, -500, 500),
			ofMap(ofNoise(noise_seed.y, (i + ofGetFrameNum()) * 0.01), 0, 1, -500, 500),
			ofMap(ofNoise(noise_seed.z, (i + ofGetFrameNum()) * 0.01), 0, 1, -500, 500));

		this->face.addVertex(location + param);
		this->face.addVertex(location - param);
		this->face.addColor(ofColor(ofMap(i, 0, 500, 239, 39)));
		this->face.addColor(ofColor(ofMap(i, 0, 500, 239, 39)));

		this->frame.addVertex(location + param);
		this->frame.addVertex(location - param);

		if (i > 0) {

			this->face.addIndex(i * 2); this->face.addIndex(i * 2 - 1); this->face.addIndex(i * 2 - 2);
			this->face.addIndex(i * 2); this->face.addIndex(i * 2 + 1); this->face.addIndex(i * 2 - 1);

			this->frame.addIndex(i * 2); this->frame.addIndex(i * 2 - 2);
			this->frame.addIndex(i * 2 + 1); this->frame.addIndex(i * 2 - 1);
		}
	}

	this->frame.addIndex(0); this->frame.addIndex(1);
	this->frame.addIndex(frame.getNumVertices() - 1); this->frame.addIndex(frame.getNumVertices() - 2);
}

//--------------------------------------------------------------
void ofApp::draw() {

	auto target = this->face.getVertex(this->face.getNumVertices() - 1);
	auto camera_location = this->face.getVertex(0) + glm::vec3(0, 0, 660);

	this->cam.setPosition(camera_location);
	this->cam.setTarget(target);
	this->cam.lookAt(target);

	this->cam.begin();

	this->face.drawFaces();

	ofSetColor(239);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}