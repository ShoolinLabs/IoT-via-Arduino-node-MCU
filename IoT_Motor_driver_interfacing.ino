#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>

HTTPClient http;

const char* WIFINAME = "D-Link_DIR-816";
const char* PASS = "";

WiFiServer server(80);

void setup() {
Serial.begin(115200);
delay(10);
Serial.println("");
pinMode(D1, OUTPUT);
pinMode(D2,OUTPUT);
pinMode(D3,OUTPUT);
pinMode(D4,OUTPUT);
Serial.print("Connecting To ");
Serial.println(WIFINAME);

if (WiFi.status() != WL_CONNECTED) {

WiFi.begin(WIFINAME, PASS);
}

while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi Connected");
Serial.print("IP address: ");
Serial.println(WiFi.localIP());
}

void loop() {

if (WiFi.status() == WL_CONNECTED) {

HTTPClient http;

/////////////////http client to read data for LED//////////////////////////////
http.begin("http://iot-dashboard.shoolinlabs.com/1/bulb.txt");
int httpCode = http.GET();

if (httpCode > 0) {

String payload = http.getString();
Serial.println(payload);
if (payload.indexOf("1") > -1) {
digitalWrite(D1, 1);
digitalWrite(D2, 0);
digitalWrite(D3, 1);
digitalWrite(D4, 0);
Serial.println("Motor On");
}
else {
digitalWrite(D1, 0);
digitalWrite(D2, 0);
digitalWrite(D3, 0);
digitalWrite(D4, 0);
Serial.println("Motor OFF");
}
}

http.end();
}
delay(100);
}
