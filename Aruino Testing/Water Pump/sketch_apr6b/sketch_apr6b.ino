const int relayPin = 7; // Define the pin used to control the relay module
void setup() {
  pinMode(relayPin, OUTPUT); // Set the relay pin as an OUTPUT pin
}
void loop() {
  digitalWrite(relayPin, HIGH); // Turn on the relay module and pump
  delay(5000); // Wait for 5 seconds
  digitalWrite(relayPin, LOW); // Turn off the relay module and pump
  delay(5000); // Wait for another 5 seconds
}