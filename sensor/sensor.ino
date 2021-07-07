/* PIN 13 := PIN/LED for pH Sensor
 * PIN 12 := PIN/LED for Moisture Sensor
 * PIN A0 := ANALOG PIN for pH Sensor
 * PIN A1 := ANALOG PIN for Moisture Sensor
 */
#define BAD_PH_OUT  13
#define BAUD_RATE 9600
#define SLOPE -0.038002458513
//#define OFFSET 28.0111420719
#define OFFSET 39.3585679164

const int pH_pin = A0;
void setup() {
  pinMode(BAD_PH_OUT, OUTPUT);
  Serial.begin(BAUD_RATE);
}

void loop() {
  int measure = analogRead(pH_pin);  
  Serial.print("measurement reading: ");
  Serial.print(measure);
  Serial.println("");
  double pH = ((SLOPE)*measure)+(OFFSET);
  Serial.print("pH: ");
  Serial.print(pH,2);
  Serial.println("");
  if (pH < 6 or pH > 7) {
    Serial.println("Bad pH detected!");
    digitalWrite(BAD_PH_OUT, HIGH);
  } else if (pH >= 6 and pH <= 7) {
    Serial.println("pH in range!");
    digitalWrite(BAD_PH_OUT, LOW);
  }
  delay(1000);
}
