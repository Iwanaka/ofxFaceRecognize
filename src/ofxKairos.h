#pragma once

#include "Poco\Base64Decoder.h"
#include "Poco\Base64Encoder.h"

#include "ofThread.h"
#include "ofEventUtils.h"

#include "ofxMyUtil.h"
#include "ofxHTTP.h"

enum OFX_KAIROS_API
{
	OFX_KAIROS_ANALYTICS = 0x00,
	OFX_KAIROS_POST_MEDIA = 0x01,
	OFX_KAIROS_GET_MEDIA = 0x02,
	OFX_KAIROS_DELETE_MEDIA = 0x03,

	OFX_KAIROS_ENROLL = 0x04,
	OFX_KAIROS_VERIFY = 0x05,
	OFX_KAIROS_RECOGNIZE = 0x06,
	OFX_KAIROS_DETECT = 0x07,
	OFX_KAIROS_LIST = 0x08,
	OFX_KAIROS_VIEW_GALLERY = 0x09,
	OFX_KAIROS_REMOVE_GALLERY = 0x10,
	OFX_KAIROS_REMOVE_SUBJECT = 0x11,
	OFX_KAIROS_VIEW_SUBJEC = 0x12
};


class ofxKairos : public ofThread
{
public:

	ofEvent<void> complete;

	ofxKairos();
	ofxKairos(
		const std::string& _app_id, 
		const std::string& _app_key, 
		const std::string& _sourceFilePath, 
		const std::string& outputJsonFilePath,
		const bool& consoleLog, 
		const OFX_KAIROS_API& _kairos);
	
	~ofxKairos();

	void request();
	void request(
		const std::string& _sourceFilePath,
		const std::string& _outputJsonFilePath,
		const bool& _consoleLog,
		const OFX_KAIROS_API& _kairos);

	void threadedFunction();

	void setConsoleLog(const bool& _consoleLog);
	void setApiKey(const std::string& _app_id, const std::string& _app_key);
	void setRequestData(
		const std::string& _sourceFilePath,
		const std::string& _outputJsonFilePath,
		const OFX_KAIROS_API& _kairos);


	//for kairos detect 
	bool encodeImageFileToBase64(const std::string& imgPath, const std::string& jsonSavePath);


private:

	const std::string baseURL = "https://api.kairos.com";

	const std::string analytics = "/v2/analytics"; // + id
	const std::string p_media = "/v2/media"; // you need post of json
	const std::string g_media = "/v2/media"; //+ id get
	const std::string d_media = "/v2/media"; // + id delete

	const std::string enroll = "/enroll"; //picture registration
	const std::string verify = "/verify"; //check to gallery
	const std::string recognize = "/recognize"; //recognize to gallery picture
	const std::string detect = "/detect"; //detect of face on picture
	const std::string list = "/gallery/list_all"; //get gallery's picture list
	const std::string view = "/gallery/view"; //get subject id's of picture in gallery
	const std::string remove = "/gallery/remove"; //remove picture in gallery
	const std::string removeSubject = "/gallery/remove_subject"; //remove gallery's subject
	const std::string viewSubject = "/gallery/view_subject"; //get face's id on picture

	std::string app_id;
	std::string app_key;

	std::string sourceFilePath;
	std::string outputJsonFilePath;
	

	//responce
	bool consoleLog;
	

	OFX_KAIROS_API kairos;


	//request type
	ofBuffer getAnalytics(const std::string& id);
	ofBuffer postMedia(const std::string& imageFilePath);
	ofBuffer getMedia(const std::string& path);
	ofBuffer deleteMedia(const std::string& path);
	ofBuffer postVerify(const std::string& path);
	ofBuffer postRecognize(const std::string& path);
	ofBuffer postDetect(const std::string& base64JsonFilePath);
	ofBuffer postList(const std::string& path);
	ofBuffer postView(const std::string& path);
	ofBuffer postRemove(const std::string& path);
	ofBuffer postRemoveSubject(const std::string& path);
	ofBuffer postViewSubject(const std::string& path);

};