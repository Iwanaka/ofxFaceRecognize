#include "ofxEyeris.h"

using namespace std;

//--------------------------------------------------------------
ofxEyeris::ofxEyeris() : 
	api_key(""), 
	sourceImageFilePath(""), 
	outputJsonFilePath("eyeris.json"),
	eyeris(OFX_EYERIS_IMAGE), 
	console(false) 
{}

//--------------------------------------------------------------
ofxEyeris::ofxEyeris(
	const string& _api_key, 
	const string& _sourceImageFilePath,
	const string& _outputJsonFilePath,
	const OFX_EYERIS_API& _eyeris, 
	const bool& _console) :
	api_key(_api_key),
	sourceImageFilePath(_sourceImageFilePath),
	outputJsonFilePath(_outputJsonFilePath),
	eyeris(_eyeris),
	console(_console)
{}

//--------------------------------------------------------------
ofxEyeris::~ofxEyeris() {}

//--------------------------------------------------------------
void ofxEyeris::request() {

	startThread();

}

//--------------------------------------------------------------
void ofxEyeris::request(
	const string& _sourceImageFilePath,
	const string& _outputJsonFilePath,
	const OFX_EYERIS_API& _eyeris) {

	this->sourceImageFilePath = _sourceImageFilePath;
	this->outputJsonFilePath = _outputJsonFilePath;
	this->eyeris = _eyeris;

	startThread();

}

//--------------------------------------------------------------
void ofxEyeris::threadedFunction() {

	if (lock()) {

		if (ofxMyUtil::File::checkExitsFile(sourceImageFilePath, 3.0f)) {

			ofBuffer buf;
			buf.clear();

			switch (eyeris)
			{
			case OFX_EYERIS_IMAGE:

				buf = postImage(sourceImageFilePath);

				break;
			case OFX_EYERIS_IMAGEFRAME:

				buf = postFrameImage(sourceImageFilePath);

				break;
			}

			if (buf.size() != 0) ofxMyUtil::File::bufferToJsonFile(buf, outputJsonFilePath, console);
			else {
				ofxMyUtil::console::chengeConsollColor(12);
				cout << " buf keep initial state " << endl;
				ofxMyUtil::console::chengeConsollColor(7);
			}
		}
		else {
			ofxMyUtil::console::chengeConsollColor(12);
			cout << "there is no file : " << sourceImageFilePath << endl;
			ofxMyUtil::console::chengeConsollColor(7);
		}
		unlock();
	}


	//wait for responce
	sleep(500);

	//stop thread
	while (isThreadRunning()) stopThread();

	//return complete event
	if (!isThreadRunning()) ofNotifyEvent(complete);

}

//--------------------------------------------------------------
void ofxEyeris::setConsoleLog(bool _console) {

	this->console = _console;

}

//--------------------------------------------------------------
void ofxEyeris::setApiKey(const string& _api_key) {

	this->api_key = _api_key;

}

//--------------------------------------------------------------
void ofxEyeris::setRequestData(const string& _sourceImageFilePath, const string& _outputJsonFilePath, const OFX_EYERIS_API& _eyeris) {

	this->sourceImageFilePath = _sourceImageFilePath;
	this->outputJsonFilePath = _outputJsonFilePath;
	this->eyeris = _eyeris;

}

//--------------------------------------------------------------
ofBuffer ofxEyeris::postImage(const string& path) {

	const string& url = baseURL + imageURL;

	ofBuffer buf;
	buf.clear();

	ofxHTTP::Client client;
	ofxHTTP::Context context;

	ofxHTTP::PostRequest http(url, Poco::Net::HTTPMessage::HTTP_1_1);

	http.add("X-Mashape-Key", api_key);
	http.addFormFile("imageFile", path);
	http.addFormField("faceAnalysisType", "AnalyzeAllDetectedFaces");

	try
	{
		auto response = client.execute(context, http);

		if (response->getStatus() == Poco::Net::HTTPResponse::HTTP_OK) {

			buf.set(response->stream());

			return buf;
		}

	}
	catch (const std::exception&)
	{
		ofxMyUtil::console::chengeConsollColor(12);
		cout << "eyeris HTTP faild" << endl;;
		ofxMyUtil::console::chengeConsollColor(7);
	}

	return buf;

}

//--------------------------------------------------------------
ofBuffer ofxEyeris::postFrameImage(const string& path) {

	ofBuffer buf;
	buf.clear();

	//frame post

	return buf;

}