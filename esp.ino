#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>

HTTPClient http;

const char* WIFINAME = "realme2pro";
const char* PASS = "bakiabad123";
//int led = D0;
WiFiServer server(80);

void setup() {
Serial.begin(115200);
delay(10);
Serial.println("");
pinMode(D1, OUTPUT);
pinMode(D2,OUTPUT);
pinMode(D3,OUTPUT);
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
http.begin("http://server.shoolinlabs.com/1/bulb.txt");
int httpCode = http.GET();

if (httpCode > 0) {

String payload = http.getString();
Serial.println(payload);
if (payload.indexOf("1") > -1) {
digitalWrite(D1, HIGH);
Serial.println("LED ON");
}
else {
digitalWrite(D1, LOW);
Serial.println("LED OFF");
}
http.begin("http://server.shoolinlabs.com/2/bulb.txt");
int httpCode = http.GET();
if (httpCode > 0) {

String payload = http.getString();
Serial.println(payload);
if (payload.indexOf("1") > -1) {
digitalWrite(D2,1);
Serial.println("LED ON");
}
else {
digitalWrite(D2, LOW);
Serial.println("LED OFF");
}
http.begin("http://server.shoolinlabs.com/3/bulb.txt");
int httpCode = http.GET();
if (httpCode > 0) {

String payload = http.getString();
Serial.println(payload);
if (payload.indexOf("1") > -1) {
digitalWrite(D3,1);
Serial.println("LED ON");
}
else {
digitalWrite(D3, LOW);
Serial.println("LED OFF");
}
}
}
}
http.end();
}
delay(100);
}
