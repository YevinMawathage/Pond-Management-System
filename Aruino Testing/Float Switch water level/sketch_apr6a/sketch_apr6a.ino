// Define the pin that the float switch is connected to
const int floatSwitchPin = 2;

// Variable for storing the float switch state
int floatSwitchState = 0;

void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // Set the float switch pin as input
  pinMode(floatSwitchPin, INPUT_PULLUP);  
}

void loop() {
  // Read the state of the float switch
  floatSwitchState = digitalRead(floatSwitchPin);

  // Check if the float switch is triggered (assuming low when triggered)
  if (floatSwitchState == HIGH) {
    Serial.println("Water level HIGH");
  } else {
    Serial.println("Water level LOW");
  }

  // Wait for a second before checking again
  delay(1000);
}
