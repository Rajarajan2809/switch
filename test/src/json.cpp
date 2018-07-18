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

	//relay gpio9
	if (id == "1")
	{
		if(value == "0")
		{
			//Condition for 9 OFF
			digitalWrite(9, LOW);
			Serial.println("9 is low");
		}
		else if(value == "100")
		{
			digitalWrite(9, HIGH);
			Serial.println("9 is high");
		}
	}
	//relay gpio10
	else if (id == "2")
	{
		if(value == "0")
		{
			//Condition for 10 OFF
			digitalWrite(10, LOW);
			Serial.println("10 is low");
		}
		else if(value == "100")
		{
			digitalWrite(10, HIGH);
			Serial.println("10 is high");
		}
	}
	//relay gpio12
	else if (id == "3")
	{
		if(value == "0")
		{
			//Condition for 9 ON
			digitalWrite(12, LOW);
			Serial.println("12 is low");
		}
		else if(value == "100")
		{
			digitalWrite(12, HIGH);
			Serial.println("12 is high");
		}
	}
	//relay gpio14
	else if (id == "4")
	{
		if(value == "0")
		{
			//Condition for 14 OFF
			digitalWrite(14, LOW);
			Serial.println("14 is low");
		}
		else if(value == "100")
		{
			digitalWrite(14, HIGH);
			Serial.println("14 is high");
		}
	}

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
