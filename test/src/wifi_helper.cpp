#include "switch.h"

//function to divide ip for esp8266-12E command
String ipDivide(String data,int i)
{
	String info[4];
	info[0] = data.substring(0,data.indexOf("."));
	data.remove(0,data.indexOf(".")+1);
	info[1] = data.substring(0,data.indexOf("."));
	data.remove(0,data.indexOf(".")+1);
	info[2] = data.substring(0,data.indexOf("."));
	data.remove(0,data.indexOf(".")+1);
	info[3] = data.substring(0,data.indexOf("."));
	data.remove(0,data.length());
	return info[i];
}

//convert ipAddres to String
String ipToString(IPAddress ip)
{
	String s="";
	for (int i=0; i<4; i++)
		s += i  ? "." + String(ip[i]) : String(ip[i]);
	return s;
}

//function to test wifi connection
bool testWifi()
{
	int c = 0;
	Serial.println("Waiting for Wifi to connect");
	while ( c < 20 )
	{
		if (WiFi.status() == WL_CONNECTED)
		{
			return true;
		}
		delay(500);
		Serial.print(WiFi.status());
		c++;
		WiFi.mode(WIFI_STA);
	}
	return false;
}
