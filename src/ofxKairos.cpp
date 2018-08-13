#include "ofxKairos.h"

using namespace std;

//--------------------------------------------------------------
ofxKairos::ofxKairos() :
	app_id(""),
	app_key(""),
	sourceFilePath(""),
	outputJsonFilePath("result.json"),
	consoleLog(false),
	kairos(OFX_KAIROS_DETECT) {};


//--------------------------------------------------------------
ofxKairos::ofxKairos(
	const string& _app_id,
	const string& _app_key,
	const string& _sourceFilePath,
	const string& _outputJsonFilePath,
	const bool& _consoleLog,
	const OFX_KAIROS_API& _kairos) :
	app_id(_app_id),
	app_key(_app_key),
	sourceFilePath(_sourceFilePath),
	outputJsonFilePath(_outputJsonFilePath),
	consoleLog(_consoleLog),
	kairos(_kairos) 
{};

//--------------------------------------------------------------
ofxKairos::~ofxKairos() { while (isThreadRunning()) { stopThread(); } };

//--------------------------------------------------------------
void ofxKairos::request() {
	startThread();
}

//--------------------------------------------------------------
void ofxKairos::request(
	const string& _sourceFilePath,
	const string& _outputJsonFilePath,
	const bool& _consoleLog,
	const OFX_KAIROS_API& _kairos) {

	this->sourceFilePath = _sourceFilePath;
	this->outputJsonFilePath = _outputJsonFilePath;
	this->kairos = _kairos;

	startThread();
}

//--------------------------------------------------------------
void ofxKairos::threadedFunction() {

	if (lock()) {

		ofBuffer buf;
		buf.clear();


		if (ofxMyUtil::File::checkExitsFile(sourceFilePath, 3.0f)) {

			switch (kairos)
			{
			case OFX_KAIROS_ANALYTICS:
				
				//outputFileName = "kairos_analytics.json";
				buf = getAnalytics(sourceFilePath);
				
				break;
			
			case OFX_KAIROS_POST_MEDIA:
				
				//outputFileName = "kairos_post_media.json";
				buf = postMedia(sourceFilePath);
				
				break;
			
			case OFX_KAIROS_GET_MEDIA:
				
				//outputFileName = "kairos_get_media.json";

				break;
			
			case OFX_KAIROS_DELETE_MEDIA:
				
				//outputFileName = "kairos_delete_media.json";

				break;

			case OFX_KAIROS_ENROLL:
				
				//outputFileName = "kairos_enroll.json";

				break;

			case OFX_KAIROS_VERIFY:
				
				//outputFileName = "kairos_verify.json";

				break;

			case OFX_KAIROS_RECOGNIZE:
				
				//outputFileName = "kairos_recognize.json";

				break;

			case OFX_KAIROS_DETECT:
				
				//outputFileName = "kairos_detect.json";
				buf = postDetect(sourceFilePath);

				break;

			case OFX_KAIROS_LIST:
				
				//outputFileName = "kairos_list.json";

				break;

			case OFX_KAIROS_VIEW_GALLERY:
				
				//outputFileName = "kairos_view_gallery.json";

				break;

			case OFX_KAIROS_REMOVE_GALLERY:
				
				//outputFileName = "kairos_remove_gellery.json";

				break;

			case OFX_KAIROS_REMOVE_SUBJECT:
				
				//outputFileName = "kairos_remove_subject.json";

				break;

			case OFX_KAIROS_VIEW_SUBJEC:
				
				//outputFileName = "kairos_view_subject.json";

				break;

			}

			//save
			if (buf.size() != 0) ofxMyUtil::File::bufferToJsonFile(buf, outputJsonFilePath, consoleLog);
			else {
				ofxMyUtil::console::chengeConsollColor(12);
				cout << " buf keep initial state " << endl;
				ofxMyUtil::console::chengeConsollColor(7);
			}
		}
		else {
			ofxMyUtil::console::chengeConsollColor(12);
			cout << "there is no file : " << sourceFilePath << endl;
			ofxMyUtil::console::chengeConsollColor(7);
		}

		unlock();
	}

	//wait for responce
	sleep(500);

	//stop thread
	while (isThreadRunning()) { stopThread(); }

	//return complete event
	if (!isThreadRunning()) { ofNotifyEvent(complete); }

}

//--------------------------------------------------------------
void ofxKairos::setConsoleLog(const bool& _consoleLog) {

	this->consoleLog = _consoleLog;

}

//--------------------------------------------------------------
void ofxKairos::setApiKey(const string& _app_id,const string& _app_key) {

	this->app_id = _app_id;
	this->app_key = _app_key;

}

//--------------------------------------------------------------
void ofxKairos::setRequestData(const string& _sourceFilePath, const string& _outputJsonFilePath, const  OFX_KAIROS_API& _kairos) {

	this->sourceFilePath = _sourceFilePath;
	this->outputJsonFilePath = _outputJsonFilePath;
	this->kairos = _kairos;

}

//--------------------------------------------------------------
ofBuffer ofxKairos::getAnalytics(const string& id) {

	string url = baseURL + analytics;
	
	ofBuffer buf;
	
	buf.clear();

	ofxHTTP::Client client;
	ofxHTTP::Context context;

	ofxHTTP::GetRequest http(url, Poco::Net::HTTPMessage::HTTP_1_1);
	http.add("app_id", app_id);
	http.add("app_key", app_key);
	http.add("id", id);

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
		cout << "http error" << endl;
	}

	return buf;

}

//--------------------------------------------------------------
ofBuffer ofxKairos::postMedia(const string& imageFilePath) {

	string url = baseURL + p_media;
	ofBuffer buf;
	buf.clear();

	ofxHTTP::Client client;
	ofxHTTP::Context context;

	ofxHTTP::PostRequest http(url, Poco::Net::HTTPMessage::HTTP_1_1);
	http.add("app_id", app_id);
	http.add("app_key", app_key);
	http.addFormFile("source", sourceFilePath);

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
		cout << "  kairos postmedia http faild  " << endl;
		ofxMyUtil::console::chengeConsollColor(7);
	}

	return buf;

}


//--------------------------------------------------------------
ofBuffer ofxKairos::getMedia(const string& path) {

	ofBuffer buf;
	buf.clear();

	return buf;
}

//--------------------------------------------------------------
ofBuffer ofxKairos::deleteMedia(const string& path) {

	ofBuffer buf;
	buf.clear();

	return buf;

}

//--------------------------------------------------------------
ofBuffer ofxKairos::postVerify(const string& path) {

	ofBuffer buf;
	buf.clear();

	return buf;

}

//--------------------------------------------------------------
ofBuffer ofxKairos::postRecognize(const string& path) {

	ofBuffer buf;
	buf.clear();

	return buf;

}

//--------------------------------------------------------------
ofBuffer ofxKairos::postDetect(const string& jbase64JsonFilePath) {

	string url = baseURL + detect;
	ofBuffer buf;
	buf.clear();


	ofxHTTP::Client client;
	ofxHTTP::Context context;

	ofxHTTP::JSONRequest http(url, Poco::Net::HTTPMessage::HTTP_1_1);
	http.add("app_id", app_id);
	http.add("app_key", app_key);
	http.add("Content-kairos", "application/json");


	ofFile file(jbase64JsonFilePath);
	if (file.exists()) {

		ofJson json;
		json = ofLoadJson(file.getAbsolutePath());
		http.setJSON(json);

	}
	else {
		ofxMyUtil::console::chengeConsollColor(12);
		cout << jbase64JsonFilePath << ": json data is not found  " << endl;
		ofxMyUtil::console::chengeConsollColor(12);
		return buf;
	}

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
		ofLogError() << "  kairos detext http faild  ";
		ofxMyUtil::console::chengeConsollColor(7);
	}
	return buf;

}

//--------------------------------------------------------------
ofBuffer ofxKairos::postList(const string& path) {

	ofBuffer buf;
	buf.clear();

	return buf;

}

//--------------------------------------------------------------
ofBuffer ofxKairos::postView(const string& path) {

	ofBuffer buf;
	buf.clear();

	return buf;

}

//--------------------------------------------------------------
ofBuffer ofxKairos::postRemove(const string& path) {

	ofBuffer buf;
	buf.clear();

	return buf;

}

//--------------------------------------------------------------
ofBuffer ofxKairos::postRemoveSubject(const string& path) {

	ofBuffer buf;
	buf.clear();

	return buf;

}

//--------------------------------------------------------------
ofBuffer ofxKairos::postViewSubject(const string& path) {

	ofBuffer buf;
	buf.clear();

	return buf;

}

//--------------------------------------------------------------
bool ofxKairos::encodeImageFileToBase64(const string &imgPath, const string &jsonSavePath) {

	ofImage img(imgPath);
	stringstream ss;
	ofBuffer buf;

	if (!img.isAllocated()) {
		cout << imgPath << " not found" << endl;;
		return 0;
	}


	//image save as buffer
	ofSaveImage(img.getPixels(), buf, OF_IMAGE_FORMAT_JPEG);
	

	//encode
	Poco::Base64Encoder b64enc(ss);
	b64enc << buf;


	//for kairos detect layout
	ofxJSONElement json;
	json["image"] = ss.str();
	json["selector"] = "ROLL";
	

	if (json.save(jsonSavePath, true)) {
		cout << jsonSavePath << " : save success" << endl;
		return 1;
	}
	else cout << jsonSavePath << " : json save faild";
	

	return 0;

}