void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int tub = analogRead(A0);
  float volt = tub*(5.0/1024.0)*3;
  Serial.println(volt);
  delay(2000);
} 
