#pragma once

#include "ofThread.h"
#include "ofxMyUtil.h"
#include "ofxHTTP.h"

enum OFX_EYERIS_API {

	OFX_EYERIS_IMAGE = 0x00,
	OFX_EYERIS_IMAGEFRAME = 0x01

};

class ofxEyeris : public ofThread
{
public:

	ofEvent<void> complete;

	ofxEyeris();
	ofxEyeris(
		const std::string& _api_key,
		const std::string& _sourceImageFilePath,
		const std::string& _outputJsonFilePath,
		const OFX_EYERIS_API& _eyeris,
		const bool& _console);

	~ofxEyeris();

	void request();
	void request(
		const std::string& _sourceImageFilePath,
		const std::string& _outputJsonFilePath,
		const OFX_EYERIS_API& _eyeris);

	void threadedFunction();

	void setConsoleLog(bool seeLog);
	void setApiKey(const std::string& api_key);
	void setRequestData(
		const std::string& _sourceImageFilePath,
		const std::string& _outputJsonFilePath,
		const OFX_EYERIS_API& _eyeris);


private:

	const const std::string& baseURL = "https://eyeris-emovu1.p.mashape.com/api";
	
	const const std::string& imageURL = "/image"; //detect face's and emotion
	const const std::string& imageFrameURL = "/iamgeFrame"; //sequence, may be no use it


	std::string api_key;
	std::string sourceImageFilePath;
	std::string outputJsonFilePath;

	OFX_EYERIS_API eyeris;
	bool console;

	ofBuffer postImage(const std::string& imageFilePath);
	ofBuffer postFrameImage(const std::string& ImageFilePath);

};


