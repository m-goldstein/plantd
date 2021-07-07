#define PH_PROBE 13
#define BAUD_RATE 115200
const byte pH_pin = A0;
float Po;
void setup() {
  // put your setup code here, to run once:
  pinMode(PH_PROBE, OUTPUT);
  Serial.begin(BAUD_RATE);
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(PH_PROBE, HIGH);
  //delay(1000);
  //digitalWrite(PH_PROBE, LOW);
  //delay(1000);
  Po = 1023 - analogRead(pH_pin);
  Po = map(Po, 0, 1023, 0, 14);
  Serial.print(Po);
  Serial.println("\n");
  delay(1000);
}
