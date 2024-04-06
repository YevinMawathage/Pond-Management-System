void setup() {
  Serial.begin(9600); // Initialize the Serial at 9600 baud rate to match the Arduino Mega setup
  Serial.println("ESP8266 Ready");
}

void loop() {
  if (Serial.available() > 0) {
    String received = Serial.readStringUntil('\n'); // Read the incoming data until newline
    Serial.print("Received: "); // Prefix to indicate incoming data
    Serial.println(received); // Print the received data to the Serial Monitor
  }
}
