#include "switch.h"

//function to parse json
bool jsonParse(String json)
{
	//{"type":"Control","id":"0","value":"0"}
	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& jsonStruct = jsonBuffer.parseObject(json);
	if (!jsonStruct.success())
	{
		Serial.println("parseObject() failed");
		return -1;
	}
	String type = jsonStruct["type"];
	String id = jsonStruct["id"];
	String value = jsonStruct["value"];
	return 1;
}

//function to construct json
String jsonCons(String type,String id,String value)
{
	StaticJsonBuffer<200> jsonBuffer;
	String msg;
	JsonObject& root = jsonBuffer.createObject();
	root["type"] = type;
	root["id"] = id;
	root["value"] = value;
	root.printTo(msg);
	Serial.println("Client:"+msg);
	return msg;
}
