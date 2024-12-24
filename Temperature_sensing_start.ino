const int refresh=10; //10seconds

/* Dht settings */

/* 
GPIO PIN REFERENCE
 D0   = 16;
 D1   = 5;
 D2   = 4;
 D3   = 0;
 D4   = 2;
 D5   = 14;
 D6   = 12;
 D7   = 13;
 D8   = 15;
 D9   = 3;
 D10  = 1;
*/

/* Dht settings */

#include "DHT.h"
#define DHTPIN 14 /*Pin GPIO 14 (D5) connected to sensor*/
#define DHTTYPE DHT22  /*Specific sensor being used */

DHT dht(DHTPIN, DHTTYPE);
//end of DHT Code

float tValue;
float hValue;

//define relay controls
/*
#define HRELAYPIN 14 //Pin connected to ultrasonic humidifier relay (D1)
#define TEMPRELAYPIN 4 /*Pin connected to temperature mat relay (D2)*/

const int relay1 = 5;
const int relay2 = 4;
const int relay3 = 0;
const int relay4 = 2;


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "Lamoureux" /* THIS IS WHERE CHANGES NEED TO BE MADE WHEN CHANGING THE NETWORK CONNECTED TO Wifi SSID*/
#define STAPSK "@Lillypad01" /*WiFi password*/
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80); /*http port uses port 80*/

void sendTemp() {

 String page = "<!DOCTYPE html>\n\n"; /*\n\n = 2 new lines*/
  page +="  <meta http-equiv='refresh' content='"; /* += is progressively building the page */ 
  page += String(refresh); /* How often temperature is read */
  page +="'/>\n"; /* new line */
  page +="<html>\n"; /* open html page */
  page +="<body>\n"; /*open html body */
  page +="<p style=\"font-size:50px;\">Temperature<br/>\n"; /*define font size for "temperature" readout */
  page +="<p style=\"color:purple; font-size:50px;\">"; /*define font for temperature value readout */
  page += String(tValue, 2); /* temperature value readout*/
  page +="<p style=\"font-size:50px;\">Humidity<br/>\n";
  page +="<p style=\"color:blue; font-size:50px;\">";
  page += String(hValue, 2);
  page +="</p>\n"; /*close paragraph*/
  page +="</body>\n"; /*close body*/
  page +="</html>\n"; /*close html page*/
 server.send(200, "text/html",page); /*Send page to server, 200 means its okay, browser will read text/html, including the page definition */
  
}

/*
void handleNotFound () {
  String message = "File not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i);
  }
  server.send(404, "text/plain", message);
/*if something goes wrong with web-page this will be printed */

void setup() {
  
  dht.begin(); /*initialize dht sensing*/
  Serial.begin(115200); /*serial handles 115200 watts/second */
  WiFi.mode(WIFI_STA); /*WiFi station is defined mode */
  WiFi.begin(ssid, password); /*Pass SSID & Password so that the wifi connection can begin */
  Serial.println(""); /*Prints a new line */

  /*while the wifi status is not equal to connected ... printed every 500 miliseconds thorugh serial communication */
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } /*when WiFi is connected */
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if(MDNS.begin("DHTBegins")) { /*Multicast DNS begins */
    Serial.println("MDNS responder started");
  }

  server.on("/", sendTemp); /*Goes to root of server and runs sendTemp page content */

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

 /* server.onNotFound(handleNotFound); */

  server.begin();
  Serial.println("HTTP server started");
  
pinMode(relay1, OUTPUT);
pinMode(relay2, OUTPUT);
pinMode(relay3, OUTPUT);
pinMode(relay4, OUTPUT);

digitalWrite(relay1, HIGH);
digitalWrite(relay2, HIGH);
digitalWrite(relay3, LOW);
digitalWrite(relay4, HIGH);

}



void loop() {
  server.handleClient();
  MDNS.update();
  float c = dht.readTemperature(); /* reads temperature as Celsius, stores as float value c */
  float h = dht.readHumidity(true); /* reads humidity, stores as float value h */
  float f = dht.readTemperature(true); /* reads temperature as Farhenheight, stores as float value f */
    Serial.println(f);
    Serial.println(h);
  tValue = f;
  hValue = h;

//Control Temperature
    
 if (f >= 84) {
  digitalWrite(relay4, LOW);
  Serial.println("Current not flowing...Relay is off");
 } else {
    digitalWrite(relay4, HIGH);
 }

 //Control humidity portion of loop
 
 if(h >= 90) {
  digitalWrite(relay3, LOW);
  Serial.println("Ultrasonic Humidifier is off");
 }else {
  digitalWrite(relay3, HIGH);
 }

 delay(1000);
}



























  
 
