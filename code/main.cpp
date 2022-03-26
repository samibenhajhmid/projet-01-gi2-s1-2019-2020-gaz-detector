#include "Arduino.h"
#include <esp8266wifi.h>
#include <esp8266httpclient.h>
int buzzer = D5;
int smokeA0 = A0;

// Your threshold value. You might need to change it.
int sensorThres = 400;
const char* ssid ="WifiM2M";
const char* password ="0wifim2m";
void setup() {

 pinMode(buzzer, OUTPUT);
 pinMode(smokeA0, INPUT);
 Serial.begin(9600);
WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {

delay(1000);
Serial.print("Connecting..");


}
Serial.println("");
 Serial.println("WiFi connected");

}

void loop() {
 int analogSensor = analogRead(smokeA0);

 Serial.print("Pin A0: ");
 Serial.println(analogSensor);
 // Checks if it has reached the threshold value
 if (analogSensor > sensorThres)
 {
    tone(buzzer, 5000, 2000);
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
       HTTPClient http;//Declare an object of class HTTPClient
       WiFiClient client;
      http.begin(client,"http://192.168.13.113:8080/index"); //Specify request destination
       int httpCode = http.GET();

       if (httpCode > 0) { //Check the returning code

      String payload = http.getString();   //Get the request response payload
    Serial.println(payload);
    http.end();   //Close connection
    delay(30000);
      }  //Send a request every 30 seconds

       }
  }
 else
 {
   noTone(buzzer);
 }

 delay(100);
}
