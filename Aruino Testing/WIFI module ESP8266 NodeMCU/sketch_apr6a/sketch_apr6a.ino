#include <ESP8266WiFi.h>

const char* ssid = "SLT_FIBRE";     // Replace 'yourSSID' with your WiFi network's SSID
const char* password = "DAD20201221"; // Replace 'yourPassword' with your WiFi network's password

void setup() {
  Serial.begin(115200); // Start the Serial communication to debug
  
  WiFi.begin(ssid, password); // Connect to the WiFi network

  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the serial port
}

void loop() {
  // put your main code here, to run repeatedly:
  // This could be empty if you're just testing the WiFi connection
}
