#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

HTTPClient http;

const char* WIFINAME = "D-Link_DIR-816";
const char* PASS = "";

int echo=D1;
int trigger=D2;
void setup()
{
  pinMode(trigger,OUTPUT);
pinMode(echo,INPUT);
  Serial.begin(9600);
  delay(10);
  Serial.println("");
  
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
  //code to read data from A0 pin of the nodemcu attched
  //to the LM35 Temprature Sensor
   int t,d;
 digitalWrite(trigger,1);  
delayMicroseconds(10);
digitalWrite(trigger,0);
t=pulseIn(echo,1);
d=t*0.034/2;
Serial.print(d);
  
  
  //check if wifi is still connected,
  //if yes, then carry on further Internte work.
  if (WiFi.status() == WL_CONNECTED) {

    ////////////////////////////////////////////////////////////////////////////////////
    ///////////////////http client to send data of Temprature///////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////
    
    //First we make our web address to send data
    String stringTempratureURL = "http://iot-dashboard.shoolinlabs.com/1/?temprature=";
    
    // we add our celsius data to above web address as "?temprature=ourvaluetosend"
    stringTempratureURL = stringTempratureURL + d+ "cm";
    
    //Again doing same thing as before
    http.begin(stringTempratureURL);
    int httpCode = http.GET();
    if (httpCode > 0) {
      
      //String payload = http.getString();
      //Serial.println(payload);
      Serial.println(httpCode);
      
    }

  }

  delay(3000);
}
