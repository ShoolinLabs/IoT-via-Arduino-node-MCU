#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
HTTPClient http;

#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11

#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE); 

const char* WIFINAME = "priyanka";
const char* PASS = "priyanka";

int led = D0;

void setup()
{
  dht.begin();
  Serial.begin(9600);
  delay(10);
  Serial.println("");
  pinMode(led, OUTPUT);
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

void loop()
{

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;
   
      

    /////////////////http client to read data for LED//////////////////////////////
    http.begin("http://goutiest-workloads.000webhostapp.com/bulb.txt");
    int httpCode = http.GET();

    if (httpCode > 0) {

      String payload = http.getString();
      Serial.println(payload);
      if (payload.indexOf("1") > -1) {
        digitalWrite(led, HIGH);
      }
      else {
        digitalWrite(led, LOW);
        int humidity = dht.readHumidity();
        int temp = dht.readTemperature();  
        int mo=analogRead(A0); 
        int mot = (( 100.00 - ( mo/1023.00) * 100.00 ) );
       // String data= humidity;
        String stringTempratureURL = "http://goutiest-workloads.000webhostapp.com/?temprature=";
    stringTempratureURL = stringTempratureURL +"T="+temp+"H="+humidity+"M="+mot;
    http.begin(stringTempratureURL);
    int httpCode = http.GET();
        
      }

    }

    http.end();

  }

  delay(3000);
}

