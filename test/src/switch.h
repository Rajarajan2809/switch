//for using inbuilt arduino functions
#include <Arduino.h>

//for using json constuction and parsing
#include <ArduinoJson.h>

//for using storing data in EEPROM
#include <EEPROM.h>

//for using esp8266 native functions
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>

//program to store data in eeprom in given address
bool eepromStore(String data,size_t addr_start,size_t addr_end);

//function to retrieve data in eeprom in given address
String eepromRead(int addr_start,int addr_end);

//function to parse json
bool jsonParse(String json);

//function to construct json
String jsonCons(String type,String id,String value);\

//function to divide ip and store it in array
String ipDivide(String data,int i);

//convert ipAddress to String
String ipToString(IPAddress ip);

//function to test wifi connection
bool testWifi();

//function to remove specific char
String charRemove(String data,String ch);

// function to create web server
void createWebServer(int webtype);

//function to make url request
int curl(String host,String message);
