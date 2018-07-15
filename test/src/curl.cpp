#include "switch.h"

//function to make url request
int curl(String host,String message)
{
	if(WiFi.status()== WL_CONNECTED)
	{
		//Check WiFi connection status
		HTTPClient http;    //Declare object of class HTTPClient
		http.begin("http://"+host+"/feedback");      //Specify request destination
		http.addHeader("Content-Type", "application/json");  //Specify content-type header
		int httpCode = http.POST(message);   //Send the request
		String payload = http.getString();                  //Get the response payload
		Serial.println("Response code:"+String(httpCode));   //Print HTTP return code
		Serial.println("Server Response:"+payload);    //Print request response payload
		http.end();  //Close connection
	}
	else
	{
		Serial.println("Error in WiFi connection");
	}
	delay(500);  //Send a request every .5 second
	return 1;
	/*unsigned long currentMillis = millis();
	if ( currentMillis - previousMillis > watchdog )
	{
		previousMillis = currentMillis;
		WiFiClient client;

		if (!client.connect(host, port))
		{
			Serial.println("connection failed");
			return -1;
		}
		unsigned long timeout = millis();
		while (client.available() == 0)
		{
			if (millis() - timeout > 5000)
			{
				Serial.println(">>> Client Timeout !");
				client.stop();
				retu/controlrn -2;
			}
		}

		// Read all the lines of the reply from server and print them to Serial
		while(client.available())
		{
			//String line = client.readStringUntil('\r');
			//Serial.print(line);
			client.print(message);
			//for(size_t i=0;i<sizeof(message);i++)
			//client.print(message[i]);
		}
	}
	return 1;*/
}
