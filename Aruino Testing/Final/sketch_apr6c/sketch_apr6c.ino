#include <SPI.h>

// Define the pin numbers
const int floatSwitchPin = 2;  // Float switch connected to pin 2
const int relayPin = 7;        // Relay module connected to pin 7
const int turbiditySensorPin = A0;  // Turbidity sensor connected to A0
const int flowSensorPin = 3;       // Flow sensor connected to pin 3
const int chipSelectPin = 10; // Use pin 10 for chip select (CS)

volatile int pulseCount;  // Use volatile for variables accessed within an interrupt
unsigned long flowRate;

void setup() {
  Serial1.begin(9600);
  SPI.begin();

  pinMode(chipSelectPin, OUTPUT);
  digitalWrite(chipSelectPin, HIGH); // Deselect the sensor

  pinMode(floatSwitchPin, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);  // Start with the pump turned off

  pinMode(flowSensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, RISING);  // Increment pulseCount on each pulse
}

void loop() {
  pulseCount = 0;  // Reset pulse count
  interrupts();  // Enable interrupts
  delay(3000);  // Wait for a moment
  noInterrupts();  // Disable interrupts to safely read pulseCount
  
  // Calculate the flow rate in liters per minute (L/min)
  flowRate = (pulseCount * 1000) / 2.25 / 60;
  Serial1.print("Flow Rate: ");
  Serial1.print(flowRate);
  Serial1.println(" L/min");

  int turbidityValue = analogRead(turbiditySensorPin);
  Serial1.print("Turbidity: ");
  Serial1.println(turbidityValue);

  bool waterLevelIsLow = digitalRead(floatSwitchPin) == LOW;
  bool waterTooDirty = turbidityValue < 300;

  if (waterLevelIsLow && !waterTooDirty) {
    digitalWrite(relayPin, LOW);  // Turn pump ON
    Serial1.println("Pump ON");
  } else {
    digitalWrite(relayPin, HIGH); // Turn pump OFF
    Serial1.println("Pump OFF");
  }

  // SPI Communication for Air Pressure Sensor
  digitalWrite(chipSelectPin, LOW); // Select the sensor
  delay(10); // Short delay to ensure the sensor is ready

  byte msb = SPI.transfer(0x00); // Clock out the MSB (most significant byte)
  byte lsb = SPI.transfer(0x00); // Clock out the LSB (least significant byte)

  digitalWrite(chipSelectPin, HIGH); // Deselect the sensor

  int pressureRaw = (msb << 8) | lsb; // Combine the MSB and LSB into a single integer

  float conversionFactor = 40.0 / 4095; // Example conversion factor
  float pressure = pressureRaw * conversionFactor; // Calculate the pressure

  Serial1.print("Pressure: ");
  Serial1.println(pressure);

  Serial1.println("---------------------------------");
  Serial1.println(" ");

  delay(3000);  // Delay for readability
}

void pulseCounter() {
  pulseCount++;
}