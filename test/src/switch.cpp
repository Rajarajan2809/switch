#include "switch.h"

ESP8266WebServer server(80);
//ESP8266WiFiMulti wifiMulti;

//wifiMulti.addAP("", "your_password_for_AP_1");

//const char* ssid = "Gemicates";
//const char* passphrase = "admin@123";

//String staticIp[] = {"192","168","1","120"};
//IPAddress mystaticip(staticIp[0].toInt(), staticIp[1].toInt(), staticIp[2].toInt(), staticIp[3].toInt());
//IPAddress mygateway(staticIp[0].toInt(), staticIp[1].toInt(), staticIp[2].toInt(), 1);
//IPAddress mysubnet(255, 255, 255, 0);

String host = "192.168.1.122";       // Server IP
const int port = 80;                    // Server Port
const int watchdog = 5000;                // Watchdog frequency
unsigned long previousMillis = millis();

/* gpio config
	D3 -> 0 -> GPIO0
	1 -> GPIO1#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;
	2 -> GPIO2
	3 -> GPIO3
	5 -> GPIO5
	6 -> GPIO4
	9 -> GPIO9
	10 -> GPIO10
	12 -> GPIO12
	13 -> GPIO13
	14 -> GPIO14
	15 -> GPIO15
	16 -> GPIO16
*/

//Button state
boolean butSta0 = HIGH;
boolean butSta2 = HIGH;
boolean butSta4 = HIGH;
boolean butSta5 = HIGH;
boolean butSta9 = HIGH;
boolean butSta10 = HIGH;
boolean butSta12 = HIGH;
boolean butSta14 = HIGH;

// function to create web server
void createWebServer(int webtype)
{
	if ( webtype == 0 )
	{
		server.on("/", []()
		{
			String stip,content,ssid = server.arg("ssid"),password = server.arg("passWord");
			String ip = server.arg("ip"),mask = server.arg("mask"),gateway = server.arg("gateway"),dns = server.arg("dns");
			content = "<!DOCTYPE HTML>\r\n<html><head><title>Gem Tech</title></head><br>";
			if(ssid != "" && password != "")
			{
				eepromStore(ssid,1,21);
				eepromStore(password,21,41);
				Serial.print("ssid:");Serial.print(eepromRead(1,21)+"\n");
				Serial.print("password:");Serial.print(eepromRead(21,41)+"\n");

				if(ip != "" && mask != "" && gateway != "" && dns != "")
				{
					Serial.println("address type:static,");

					//ip cmd30
					//string  info[] = ipDivide(ip);
					eepromStore(ip,41,61);
					Serial.print("ip:"+ipDivide(ip,0)+"."+ipDivide(ip,1)+"."+ipDivide(ip,2)+"."+ipDivide(ip,3)+"\n");
					IPAddress mystaticip(ipDivide(ip,0).toInt(), ipDivide(ip,1).toInt(), ipDivide(ip,2).toInt(), ipDivide(ip,3).toInt());

					eepromStore(mask,61,81);
					Serial.print("mask:"+ipDivide(mask,0)+"."+ipDivide(mask,1)+"."+ipDivide(mask,2)+"."+ipDivide(mask,3)+"\n");
					IPAddress mysubnet(ipDivide(mask,0).toInt(), ipDivide(mask,1).toInt(), ipDivide(mask,2).toInt(), ipDivide(mask,3).toInt());

					eepromStore(gateway,81,101);
					Serial.print("gateway:"+ipDivide(gateway,0)+"."+ipDivide(gateway,1)+"."+ipDivide(gateway,2)+"."+ipDivide(gateway,3)+"\n");
					IPAddress mygateway(ipDivide(gateway,0).toInt(), ipDivide(gateway,1).toInt(), ipDivide(gateway,2).toInt(), ipDivide(gateway,3).toInt());

					//mask cmd
					//Serial.print("mask:"+ipDivide[0](ip)+ipDivide[1]+ipDivide[2]+ipDivide[3]"\n");
					eepromStore(dns,101,121);
					//IPAddress mysubnet(255, 255, 255, 0);

					Serial.print("ip:");Serial.print(eepromRead(41,61)+"\n");
					Serial.print("mask:");Serial.print(eepromRead(61,81)+"\n");
					Serial.print("gateway:");Serial.print(eepromRead(81,101)+"\n");
					Serial.print("dns:");Serial.print(eepromRead(101,121)+"\n\n");
					//WiFi.config(mystaticip, mygateway, mysubnet);
					Serial.print("IP address: ");
					Serial.println(ip);
					content += "<style type=\"text/css\">";
					content += "body{font-family: \"Times New Roman\", Georgia, Serif;background-color: #5076b7;}";
					content += ".box{background:white;width:300px;border-radius:6px;margin: 0 auto 0 auto;padding:0px 50px 70px 70px;border: #2980b9 4px solid;}";
					content += ".container{height: 200px;width: 400px;position: fixed;top: 40%;left: 50%;margin-top: -200px;margin-left: -200px;}";
					content += "input{width:100%;}</style>";
					content += "<body><div class=\"container\">";
					content += "<span class=\"psw\">IP address has been changed,click here to go to <a href=\"http://"+ip+"/\">login</a> page.</span>";
					content += "</div></body></html>";
					content += "</body></html>";
					Serial.println(content);
					server.send(200, "text/html", content);
					WiFi.config(mystaticip, mygateway, mysubnet);
					return;
				}
			}
			//CSS
			content += "<style type=\"text/css\">";
			content += "body{font-family: \"Times New Roman\", Georgia, Serif;background-color: #5076b7;}";
			content += ".box{background:white;width:300px;border-radius:6px;margin: 70px 70px 70px 70px;padding: 10px 30px 30px 60px;border: 0px solid;margin-top: auto;margin-left: auto;margin-right: auto;}";
			content += ".container{height: 200px;width: 400px;position: fixed;top: 40%;left: 50%;margin-top: -100px;margin-left: -200px;}</style>";
			//html body
			content += "<body><div class=\"container\">";
			content += "<form method=\"get\" action=\"config\"><br/>";
			content += "<div class=\"box\"><h1 align=\"center\">GEM LOGIN</h1>";
			content += "Username&nbsp;&nbsp;&nbsp;<input type=\"text\" name=\"user\" class=\"email\" placeholder=\"Enter Username\" required />";
			content += "<br/><br/>";
			content += "Password&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"password\" name=\"passWord\" class=\"email\" placeholder=\"Enter Password\" required/>";
			content += "<br/><br/>";
			content += "<div align=\"center\"><button type=\"submit\" class=\"btn btn-success\" style=\" background-color: #cebf39;  padding: 5px 15px;\">Log In</button></div>";
			content += "</div></form></div></body></html>";

			/*content += "<form method='get' action='config'>";
			content += "<div class=\"container\">";
			content += "      <label><b><center>Username</b></label>";
			content += "      <input type=\"text\" name=\"user\" required>";
			content += "      <br><br><label><b>Password</b></label>";
			content += "      <input type=\"password\" name=\"passWord\" required>";
			content += "      <br><br><button type=\"submit\">Login</button></center>";
			content += "</div>";
			content += "</form>";
			content += "</html>";*/
			server.send(200, "text/html", content);
		});
		server.on("/config", []()
		{
			String user = server.arg("user"),password = server.arg("passWord"),content;
			content = "<!DOCTYPE HTML>\r\n<html><head><title>Gem Tech</title></head><br>";
			if (user == "admin"  && password == "password")
			{
				content += "<style type=\"text/css\">";
				content += "body{font-family: \"Times New Roman\", Georgia, Serif;background-color: #5076b7;}";
				content += ".box{background:white;width:300px;border-radius:6px;margin: 70px 70px 70px 70px;padding: 10px 60px 30px 70px;border: 0px solid;margin-top: auto;margin-left: auto;margin-right: auto;}";
				content += ".container{height: 100px;width: 400px;position: absolute; height: 100%; width: 100% top: 30%;left: 35%; margin-top: auto; margin-left: auto; margin-right: auto;}";
				content += "input{width:100%;}</style>";
				content += "<body><div class=\"container\">";
				content += "<form method=\"post\" action='/'><br/><div class=\"box\">";
				content += "<h1>IP Configuration</h1>";
				content += "<label><b>SSID</b></label><input type=\"text\" name=\"ssid\" placeholder=\""+eepromRead(1,21)+"\" required />";
				content += "<br/><br/>";
				content += "<label><b>Password</b></label><input type=\"password\" name=\"passWord\" placeholder=\""+eepromRead(21,41)+"\" required/>";
				content += "<br/><br/>";
				content += "<label><b>IP Address</b></label><input type=\"ip\" name=\"ip\" placeholder=\""+eepromRead(41,61)+"\" />";
				content += "<br/><br/>";
				content += "<label><b>Subnet mask</b></label><input type=\"mask\" name=\"mask\" placeholder=\""+eepromRead(61,81)+"\" />";
				content += "<br/><br/>";
				content += "<label><b>Gateway</b></label><input type=\"gateway\" name=\"gateway\" placeholder=\""+eepromRead(81,101)+"\" />";
				content += "<br/><br/>";
				content += "<label><b>DNS</b></label><input type=\"dns\" name=\"dns\" placeholder=\""+eepromRead(101,121)+"\" />";
				content += "<br/><br/>";
				content += "<div align=\"center\">";
				content += "<button type=\"submit\" class=\"btn btn-success\" style=\" background-color: #cebf39;  padding: 5px 15px;\">SUBMIT</button>";
				content += "</div></div></form></div></body></html>";


				/*content += "<form method=\"post\" action='/'><div>";
				content += "<div class=\"container\">";
				content += "<label><b><center>ssid:</b></label>";
				content += "<input type=\"text\" name=\"ssid\"  required>";
				content += "<br><br><label><b>Password:</b></label>";
				content += "<input type=\"password\" name=\"passWord\" required>";
				content += "<br><br><label><b>ip address:</label>";
				content += "<input type=\"text\" name=\"ip\">";
				content += "<br><br><label><b>subnet mask:</label>";
				content += "<input type=\"text\" name=\"mask\">";
				content += "<br><br><label><b>gateway:</label>";
				content += "<input type=\"text\" name=\"gateway\">";
				content += "<br><br><label><b>dns:</label>";
				content += "<input type=\"text\" name=\"dns\">";
				content += "<br><br><center><button type=\"submit\">submit</button></center></div></form></html>";*/
				server.send(200, "text/html", content);
			}
			else
			{
				content += "<style type=\"text/css\">";
				content += "body{font-family: \"Times New Roman\", Georgia, Serif;background-color: #5076b7;}";
				content += ".box{background:white;width:300px;border-radius:6px;margin: 0 auto 0 auto;padding:0px 50px 70px 70px;border: #2980b9 4px solid;}";
				content += ".container{height: 200px;width: 400px;position: fixed;top: 40%;left: 50%;margin-top: -200px;margin-left: -200px;}";
				content += "input{width:100%;}</style>";
				content += "<body><div class=\"container\">";
				content += "<span class=\"psw\">Password incorrect,click here to go to <a href=\"/\">login</a> page.</span>";
				content += "</div></body></html>";
				content += "</body></html>";
				server.send(200, "text/html", content);
				Serial.println("Password Incorrect");
			}
		});
		server.on("/show", []()
		{
			String content;
			content = "<!DOCTYPE HTML>\r\n<html><head><title>Gem Tech</title></head><br>";
			content += "<style type=\"text/css\">";
			content += "body{font-family: \"Times New Roman\", Georgia, Serif;background-color: #5076b7;}";
			content += ".box{background:white;width:300px;border-radius:6px;margin: 0 auto 0 auto;padding:0px 30px 50px 20px;border: #2980b9 4px solid;}";
			content += ".container {height: 200px;width: 400px;position: fixed;top: 40%;left: 50%;margin-top: -200px;margin-left: -200px;}</style>";
			content += "<body><div class=\"container\">";
			//content += "<form method=\"get\" action=\"/\"><br/><div class=\"box\"><h1>Contents in Memory</h1>";
			content += "<br/><div class=\"box\"><center><h1>Contents in Memory</h1></center>";
			content += "SSID&emsp;&emsp;&nbsp;&nbsp;&emsp;:&emsp;"+eepromRead(1,21)+"<br/><br/>";
			content += "Password&nbsp;&nbsp;&nbsp;&nbsp;&emsp;:&emsp;"+eepromRead(21,41)+"<br/><br/>";
			content += "IP Address&nbsp;&nbsp;&emsp;:&emsp;"+eepromRead(41,61)+"<br/><br/>";
			content += "Subnet Mask&nbsp;&nbsp;&nbsp;:&emsp;"+eepromRead(61,81)+"<br/><br/>";
			content += "Gateway&emsp;&emsp;&nbsp;&nbsp;:&emsp;"+eepromRead(81,101)+"<br/><br/>";
			content += "DNS&emsp;&emsp;&emsp;&emsp;:&emsp;"+eepromRead(101,121)+"<br/><br/>";
			content += "</div></body></html>";

			/*content += "<body>";
			content += "ssid&nbsp;&nbsp;&nbsp;:"+eepromRead(0,20)+"<br>";
			content += "password&nbsp;&nbsp;&nbsp;:"+eepromRead(20,40)+"<br>";
			content += "ip&nbsp;&nbsp;&nbsp;:"+eepromRead(40,60)+"<br>";
			content += "mask&nbsp;&nbsp;&nbsp;:"+eepromRead(60,80)+"<br>";
			content += "gateway&nbsp;&nbsp;&nbsp;:"+eepromRead(80,100)+"<br>";
			content += "dns&nbsp;&nbsp;&nbsp;:"+eepromRead(100,120)+"<br>";
			//Serial.print("ssid:");Serial.print(eepromRead(0,20)+",\n");
			//Serial.print("password:");Serial.print(eepromRead(20,40)+",\n");
			content += "<label><b><center>ssid:</b></label>";
			content += "<input type=\"text\" name=\"ssid\"  required>";
			content += "<br><br><label><b>Password:</b></label>";
			content += "<input type=\"password\" name=\"passWord\" required>";
			content += "<br><br><label><b>ip address:</label>";
			content += "<input type=\"text\" name=\"ip\">";
			content += "<br><br><label><b>subnet mask:</label>";
			content += "<input type=\"text\" name=\"mask\">";
			content += "<br><br><label><b>gateway:</label>";
			content += "<input type=\"text\" name=\"gateway\">";
			content += "<br><br><label><b>dns:</label>";
			content += "<input type=\"text\" name=\"dns\">";
			content += "</body></html>";*/
			server.send(200, "text/html", content);
		});
        server.on("/control", []()
		{
			if(server.uri() == "/feedback")
			{
				if(server.method() != HTTP_GET)
				{
					if(server.args() == 1)
					{
						if(server.argName(0) == "plain")
						{
							Serial.println("JSON received:"+server.arg(0));
							jsonParse(server.arg(0));
							server.send(200, "application/json", "{\"status\":\"feedback received successfully\"}");
						}
					}
				}
			}
		});
	}
}

//function to load web pages
void launchWeb(int webtype)
{
	createWebServer(webtype);
	server.begin();
}

bool softSwitch()
{
	//switch gpio0
	if (digitalRead(0) == HIGH)
	{
		if(butSta0 == LOW)
		{
			//Condition for 0 ON
			butSta0 = HIGH;
			Serial.println("0 is low");
			curl(host,jsonCons("Control","0","0"));
		}
	}
	else if (digitalRead(0) == LOW)
	{
		if(butSta0 == HIGH)
		{
			//Condition for S0 OFF
			butSta0 = LOW;
			Serial.println("0 is high");
			curl(host,jsonCons("Control","0","255"));
		}
	}

	//switch gpio2
	if (digitalRead(2) == HIGH)
	{
		if(butSta2 == LOW)
		{
			//Condition for 2 ON
			butSta2 = HIGH;
			//switch gpio2
			Serial.println("2 is low");
			curl(host,jsonCons("Control","2","0"));
		}
	}
	else if (digitalRead(2) == LOW)
	{
		if(butSta2 == HIGH)
		{
			//Condition for 2 OFF
			butSta2 = LOW;
			Serial.println("2 is high");
			jsonCons("Control","2","255");
			curl(host,jsonCons("Control","2","255"));
		}
	}

	//switch gpio4
	if (digitalRead(4) == HIGH)
	{
		if(butSta4 == LOW)
		{
			//Condition for 4 ON
			butSta4 = HIGH;
			Serial.println("4 is low");
			curl(host,jsonCons("Control","4","0"));
		}
	}
	else if (digitalRead(4) == LOW)
	{
		if(butSta4 == HIGH)
		{
			//Condition for 4 OFF
			butSta4 = LOW;
			Serial.println("4 is high");
			curl(host,jsonCons("Control","2","255"));
		}
	}

	//switch gpio5
	if (digitalRead(5) == HIGH)
	{
		if(butSta5 == LOW)
		{
			//Condition for 5 ON
			butSta5 = HIGH;
			Serial.println("5 is low");
			curl(host,jsonCons("Control","5","0"));
		}
	}
	else if (digitalRead(5) == LOW)
	{
		if(butSta5 == HIGH)
		{
			//Condition for 5 OFF
			butSta5 = LOW;
			Serial.println("5 is high");
			curl(host,jsonCons("Control","5","255"));
		}
	}

	//switch gpio9
	if (digitalRead(9) == HIGH)
	{
		if(butSta9 == LOW)
		{
			//Condition for 9 ON
			butSta9 = HIGH;
			Serial.println("9 is low");
			curl(host,jsonCons("Control","9","0"));
		}
	}
	else if (digitalRead(9) == LOW)
	{
		if(butSta9 == HIGH)
		{
			//Condition for 9 OFF
			butSta9 = LOW;
			Serial.println("9 is high");
			curl(host,jsonCons("Control","9","255"));
		}
	}

	//switch gpio10
	if (digitalRead(10) == HIGH)
	{
		if(butSta10 == LOW)
		{
			//Condition for 10 ON
			butSta10 = HIGH;
			Serial.println("10 is low");
			curl(host,jsonCons("Control","10","0"));
		}
	}
	else if (digitalRead(10) == LOW)
	{
		if(butSta10 == HIGH)
		{
			//Condition for 10 OFF
			butSta10 = LOW;
			Serial.println("10 is high");
			curl(host,jsonCons("Control","10","255"));
		}
	}

	//switch gpio12
	if (digitalRead(12) == HIGH)
	{
		if(butSta12 == LOW)
		{
			//Condition for 12 ON
			butSta12 = HIGH;
			Serial.println("12 is low");
			curl(host,jsonCons("Control","12","0"));
		}
	}
	else if (digitalRead(12) == LOW)
	{
		if(butSta12 == HIGH)
		{
			//Condition for 12 OFF
			butSta12 = LOW;
			Serial.println("12 is high");
			curl(host,jsonCons("Control","12","255"));
		}
	}

	//switch gpio14
	if (digitalRead(14) == HIGH)
	{
		if(butSta14 == LOW)
		{
			//Condition for 14 ON
			butSta14 = HIGH;
			Serial.println("14 is low");
			curl(host,jsonCons("Control","14","0"));
		}
	}
	else if (digitalRead(14) == LOW)
	{
		if(butSta14 == HIGH)
		{
			//Condition for 14 OFF
			butSta14 = LOW;
			curl(host,jsonCons("Control","14","255"));
		}
	}
    return 0;
}

//function to initiate settings
void setup()
{
	pinMode(0, INPUT_PULLUP);
	pinMode(2, INPUT_PULLUP);
	pinMode(4, INPUT_PULLUP);
	pinMode(5, INPUT_PULLUP);
	pinMode(9, INPUT_PULLUP);
	pinMode(10, INPUT_PULLUP);
	pinMode(12, INPUT_PULLUP);
	pinMode(14, INPUT_PULLUP);

	Serial.begin(19200);
	delay(3000);
	EEPROM.begin(512);
	if(eepromRead(0,1) == "1")
	{
		Serial.println("not first time");
		String ssid,password,ip,mask,gateway,dns;
		ssid = eepromRead(1,21);
		password = eepromRead(21,41);
		if((ip.length() != 0) && (password.length() != 0))
		{
		      Serial.println("ssid:"+ssid);
		      Serial.println("password:"+password);
		      WiFi.begin(ssid.c_str(), password.c_str());
		}

		ip = eepromRead(41,61);
		mask = eepromRead(61,81);
		gateway = eepromRead(81,101);
		dns = eepromRead(101,121);

		/*ip = charRemove(ip," ");
		mask = charRemove(mask," ");
		gateway = charRemove(gateway," ");
		dns = charRemove(dns," ");*/

		//Serial.println("\nip:"+ip);

		if (testWifi())
		{
			if((ip.length() != 0) && (mask.length() != 0) && (gateway.length() != 0) && (dns.length() != 0))
			{
				Serial.println("\nip:"+ipDivide(ip,0)+"."+ipDivide(ip,1)+"."+ipDivide(ip,2)+"."+ipDivide(ip,3));
				Serial.println("mask:"+ipDivide(mask,0)+"."+ipDivide(mask,1)+"."+ipDivide(mask,2)+"."+ipDivide(mask,3));
				Serial.println("gateway:"+ipDivide(gateway,0)+"."+ipDivide(gateway,1)+"."+ipDivide(gateway,2)+"."+ipDivide(gateway,3));

				IPAddress mystaticip(ipDivide(ip,0).toInt(), ipDivide(ip,1).toInt(), ipDivide(ip,2).toInt(), ipDivide(ip,3).toInt());
				IPAddress mysubnet(ipDivide(mask,0).toInt(), ipDivide(mask,1).toInt(), ipDivide(mask,2).toInt(), ipDivide(mask,3).toInt());
				IPAddress mygateway(ipDivide(gateway,0).toInt(), ipDivide(gateway,1).toInt(), ipDivide(gateway,2).toInt(), ipDivide(gateway,3).toInt());

				//IPAddress mystaticip(192, 168, 1, 120);
				//IPAddress mysubnet(255, 255, 255, 0);
				//IPAddress mygateway(192, 168, 1, 1);
				eepromStore(ip,41,61);
				eepromStore(mask,61,81);
				eepromStore(gateway,81,101);
				eepromStore(gateway,101,121);
				WiFi.config(mystaticip, mygateway, mysubnet);
			}
            launchWeb(0);//OK
		}
		Serial.print("\nConnected to ");
		Serial.println(WiFi.SSID());
		Serial.print("IP address: ");
		Serial.println(WiFi.localIP());
	}
	else
	{
		Serial.println("first time");
		eepromStore("1",0,1);
		Serial.println("data stored"+eepromRead(0,1));
		eepromStore("",1,121);
		//WiFi.begin("GC_OFFICE", "gems@123");

		WiFi.mode(WIFI_STA);
		delay(500);

		WiFi.beginSmartConfig();

		while (WiFi.status() != WL_CONNECTED)
		{
			delay(500);
			Serial.print(".");
			Serial.println(WiFi.smartConfigDone());
		}

		Serial.println("\nIP address: ");
		Serial.println(WiFi.localIP());

		if (testWifi())
		{
			//WiFi.config(mystaticip, mygateway, mysubnet);
			launchWeb(0);//OK
			Serial.print("\nConnected to ");
			Serial.println(WiFi.SSID());
			Serial.print("IP address: ");
			Serial.println(WiFi.localIP());
			String ip = ipToString(WiFi.localIP()),mask="255.255.255.0",gateway;
			gateway = ipDivide(ip,0)+"."+ipDivide(ip,1)+"."+ipDivide(ip,2)+".1";
			eepromStore("Gemicates",1,21);
			eepromStore("admin@123",21,41);
			eepromStore(ip,41,61);
			eepromStore(mask,61,81);
			eepromStore(gateway,81,101);
			eepromStore(gateway,101,121);
		}
	}
}

void loop()
{
	server.handleClient();
	softSwitch();
}
