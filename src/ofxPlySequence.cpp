#include "ofxPlySequence.h"


//READING PNG TO PLY
void ofxPlySequence::setup(){
	ofDisableArbTex(); // aallows me to use sampler2d instead of sampler2drect (some nvidia bullshit???)

	// upload the transformation for each box using a
	// texture buffer.
	// for that we need to upload the matrices to the buffer
	// and allocate the texture using it

	index = 0;
	ix = 0;

	shader.load("vert.glsl","frag.glsl");

	plane.set(100, 100, 100, 100, OF_PRIMITIVE_TRIANGLES);

	mesh.load("base.ply");

	int s = 256;
	string path = "";
	dir.open(path);
	dir.allowExt("tif");
	dir.listDir(path);

	glPointSize(4);

	for (int i = 0; i < frameNum; i++) {
		images[i].load(path+"\\" + dir.getName(i));
	}
	camera.setDistance(ofGetWidth());
	camera.setFarClip(ofGetWidth()*12);
}

void ofxPlySequence::writePointCloudsAsImages(){
	ofSetBackgroundColor(0);
	
	ofDisableArbTex(); // aallows me to use sampler2d instead of sampler2drect (some nvidia bullshit???)
	w = ofGetWidth();
	h = ofGetHeight();
	// using GL_RGBA32F allows to read each row of each matrix
	// as a float vec4 from the shader.
	// Note that we're allocating the texture as a Buffer Texture:
	// https://www.opengl.org/wiki/Buffer_Texture

	glPointSize(1);

	pixels.allocate(w*2,h*2, OF_PIXELS_RGB); // times two because we are working with quadrents
	index = 0;
	ix = 0;
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a folder of ply files", true);

	//Check if the user opened a file
	if (openFileResult.bSuccess) {
		cout << "selected";
		ofLogVerbose("User selected a file");

	}
	else {
		cout << "cancel";
		ofLogVerbose("User hit cancel");
        exit(0);
	}

	ofLogVerbose("getName(): " + openFileResult.getName());
	ofLogVerbose("getPath(): " + openFileResult.getPath());

	string path = openFileResult.getPath();

	string startString = ofSystemTextBoxDialog("Start place (e.g. 0 for the first file in this folder, 10 for the tenth etc.)", "0");
	string frameNumString = ofSystemTextBoxDialog("How many frames to process", "3");

	start = std::stoi(startString);
	frameNum = std::stoi(frameNumString);

	dir.open(path);
	dir.allowExt("ply");
	
	dir.listDir();

	texture = new ofTexture[frameNum];
	images = new ofImage[frameNum];
	meshes = new ofVboMesh[frameNum];

	dir = dir.getSorted();
	int dirNum = dir.size();

	for (int j = 0; j < frameNum / block; j++) {
		place = j;
		for (int ii = 0; ii < block; ii++) {
			ix = ii;
			string name = (dir.getName(start + ii + (place * block)));
			meshes[ii].load(path + "\\" + name);
			ofLog((ofLogLevel)1, "gone process: " + name);
			compressAndSave(name);
		}
	}
	ofLog((ofLogLevel)1, "Done!");
	cout << "Done!\n";
}

// optional
void ofxPlySequence::loadBaseply(string filename){

    mesh.load(filename);
}

void ofxPlySequence::draw() {
	index = (index + 1) % (frameNum * 2);

	if (index >= frameNum) {
		ix = (frameNum - (index - frameNum)) - 1;
	}
	else {
		ix = index;
	}
}

//--------------------------------------------------------------
void ofApp::compressAndSave(string fileName){

	int size = meshes[ix].getNumVertices();

	for (int i = 0; i < size; i++) {

		auto v = meshes[ix].getVertex(i); // a point position v.x = the x position
		int x = i % w;
		int y = i / h;

		UINT64 red = (UINT32)(((long double)(v.x + 150)) * d); // get rid of decimal
		UINT16 red1 = (UINT16)(red & 0x0000ffff);
		UINT16 red2 = (UINT16)((red >> 16) & 0x0000ffff);// / pow(2, 16));
		UINT16 red3 = (UINT16)((red >> 32) & 0x0000ffff); // pow(2, 32));

		UINT64 green = (UINT64)(((long double)(-v.y)) * d); // get rid of decimal
		UINT16 green1 = (UINT16)(green & 0x0000ffff);
		UINT16 green2 = (UINT16)((green >> 16) & 0x0000ffff);
		UINT16 green3 = (UINT16)((green >> 32) & 0x0000ffff);

		UINT64 blue = (UINT64)(((long double)(v.z + 90)) * d); // get rid of decimal
		UINT16 blue1 = (UINT16)(blue & 0x0000ffff);;
		UINT16 blue2 = (UINT16)((blue >> 16) & 0x0000ffff);
		UINT16 blue3 = (UINT16)((blue >> 32) & 0x0000ffff);

		pixels.setColor(x,y, ofShortColor(red1, red2, red3));
		pixels.setColor(x+w,y, ofShortColor(green1, green2, green3));
		pixels.setColor(x, y + h, ofShortColor(blue1, blue2, blue3));
		pixels.setColor(x+w,y+h, meshes[ix].getColor(i));
		if (i > w*h) {
			break;
		}
		if (i == size - 1) {
			while (i < w * h) {
				int x = i % w;
				int y = i / h;
				pixels.setColor(x, y, ofColor((float)red1, (float)red2, (float)red3));
				pixels.setColor(x + w, y, ofColor((float)green1, (float)green2, (float)green3));
				pixels.setColor(x, y + h, ofColor((float)blue1, (float)blue2, (float)blue3));
				pixels.setColor(x + w, y + h, meshes[ix].getColor(0));
				i++;
			}
		}
	
	}

	floatImage.setFromPixels(pixels);
	string num = (ofToString(ix + (block*place) + (start + 500), 8, '0'));
	floatImage.save("encoded_" + fileName.substr(0, fileName.size() - 4) + ".tif");
}
