#include <SPI.h>

const int chipSelectPin = 13; // Use this pin to select the sensor before communication

void setup() {
  Serial.begin(9600);
  SPI.begin(); // Initialize SPI communication
  
  pinMode(chipSelectPin, OUTPUT);
  digitalWrite(chipSelectPin, HIGH); // Deselect the sensor
}

void loop() {
  digitalWrite(chipSelectPin, LOW); // Select the sensor
  delay(10); // Short delay to ensure the sensor is ready

  // Assuming the sensor sends a 16-bit pressure value, read it
  byte msb = SPI.transfer(0x00); // Clock out the MSB (most significant byte)
  byte lsb = SPI.transfer(0x00); // Clock out the LSB (least significant byte)

  digitalWrite(chipSelectPin, HIGH); // Deselect the sensor

  // Combine the MSB and LSB into a single integer
  int pressureRaw = (msb << 8) | lsb;

  // Define the conversion factor based on your sensor's specifications
  // This is an example conversion factor; replace it with the correct value from your sensor's datasheet
  float conversionFactor = 40.0 / 4095;

  // Calculate the pressure using the raw data and conversion factor
  float pressure = pressureRaw * conversionFactor;

  // Print the calculated pressure to the Serial Monitor
  Serial.print("Pressure: ");
  Serial.println(pressure);

  delay(4000); // Delay before the next read
}
