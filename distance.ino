#include <ESP8266WiFi.h>

const int trigPin = D5;
const int echoPin = D6;
long duration;
int distance; 

const char* ssid = "SSID"; 
const char* password = "password";

WiFiServer server(80);

void setup() {
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 Serial.begin(9600);

 Serial.print("Connecting to Wifi Network");
 Serial.println(ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }

 Serial.println("");
 Serial.println("Successfully connected to WiFi.");
 Serial.println("IP address is : ");
 Serial.println(WiFi.localIP());
 server.begin();
 Serial.println("Server started");
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0340 / 2;
  delay(1000);
  WiFiClient client = server.available();
  if (client) 
  { 
    Serial.println("Web Client connected ");
    String request = client.readStringUntil('\r'); 
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.println();
    client.print("{\"distance\":\"");
    client.print(distance);
    client.print("\"}");
  }
}