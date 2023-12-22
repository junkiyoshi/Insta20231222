#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("openFrameworks");
	ofSetFrameRate(25);

	ofBackground(39);
	ofSetColor(255);
	ofNoFill();
	ofSetLineWidth(1);

	this->font_size = 60;
	this->font.loadFont("fonts/msgothic.ttc", this->font_size, true, true, true);

	this->charactor_list = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	int sample_count = 200;

	for (int x = -360; x <= 360 ; x += 72) {

		for (int y = -288; y <= 288; y += 72) {
			
			int frame_param = ofGetFrameNum() * 8;

			int charactor_index = 0;
			charactor_index = (charactor_index + frame_param / sample_count) % this->charactor_list.size();
			ofPath path = this->font.getCharacterAsPoints(this->charactor_list[charactor_index], true, false);
			vector<ofPolyline> outline = path.getOutline();
			 
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				outline[outline_index] = outline[outline_index].getResampledByCount(sample_count);
				vector<glm::vec3> vertices = outline[outline_index].getVertices();

				ofBeginShape();
				for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

					glm::vec3 vertex = glm::vec3(x + 18, y + 27 , 0) + glm::vec3(vertices[vertices_index].x, vertices[vertices_index].y, vertices[vertices_index].z);

					if (frame_param % (sample_count * 2) < sample_count) {

						if (vertices_index < frame_param % sample_count) {

							ofVertex(vertex);
						}
					}
					else {

						if (vertices_index > frame_param % sample_count) {

							ofVertex(vertex);
						}
					}

					if (vertices_index == frame_param % sample_count) {

						ofFill();
						ofDrawSphere(vertex, 2);
						ofNoFill();
					}

				}
				ofEndShape();
			}

		}
	}

	this->cam.end();

	/*
	int start = 25;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}