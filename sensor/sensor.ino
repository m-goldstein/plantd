/* PIN 13 := PIN/LED for pH Sensor
 * PIN 12 := PIN/LED for Soil Moisture Sensor
 * PIN 11 := PIN/LED for (Check) Soil Moisture Sensor
 * PIN A0 := ANALOG PIN for pH Sensor
 * PIN A1 := ANALOG PIN for Soil Moisture Sensor
 */
#define BAD_PH_OUT           13
#define BAD_SOIL_MOIST_OUT   12
#define CHECK_SOIL_MOIST_OUT 11
#define BAD_RUNOFF_MOIST_OUT 10
#define BAUD_RATE            9600
#define SLOPE                -0.038002458513
#define OFFSET               39.3585679164

const int pH_pin = A0;
const int soil_moisture_pin = A1;
const int runoff_moisture_pin = A2;
void setup() {
  /* Setup pH and moisture sensor pin outs */
  pinMode(BAD_PH_OUT, OUTPUT);
  pinMode(BAD_SOIL_MOIST_OUT, OUTPUT);
  pinMode(BAD_RUNOFF_MOIST_OUT, OUTPUT);
  pinMode(CHECK_SOIL_MOIST_OUT, OUTPUT);
  Serial.begin(BAUD_RATE);
}

void loop() {
  float ph_val = analogRead(pH_pin);
  float soil_moist_val = 1023 - analogRead(soil_moisture_pin);
  float runoff_moist_val = 1023 - analogRead(runoff_moisture_pin);
  
  //Serial.print("[pre] moisture measurement reading: ");
  //Serial.print(moist_val);
  
  /* Map moisture value to [0,100] */
  soil_moist_val = map(soil_moist_val, 0 , 1023, 0, 100);
  runoff_moist_val = map(runoff_moist_val, 0 , 1023, 0, 100);
  
  Serial.print("\npH measurement reading: ");
  Serial.print(ph_val);
  Serial.println("");
  Serial.print("soil moisture measurement reading: ");
  Serial.print(soil_moist_val);
  Serial.println("");
  
  Serial.print("runoff moisture measurement reading: ");
  Serial.print(runoff_moist_val);
  Serial.println("");
  /* Calculate pH using regression (determined by hand) */
  double pH = ((SLOPE)*ph_val)+(OFFSET);
  Serial.print("pH: ");
  Serial.print(pH,2);
  Serial.println("");
  /* Check pH ranges */
  if (pH < 6.0 or pH > 7.0) {
    Serial.println("Bad pH detected!");
    digitalWrite(BAD_PH_OUT, HIGH);
  } else if (pH >= 6.0 and pH <= 7.0) {
    Serial.println("pH in range!");
    digitalWrite(BAD_PH_OUT, LOW);
  }
  /* Check soil moisture reading */
  if (soil_moist_val >= 50 and soil_moist_val <= 100) {
    Serial.println("Soil moisture is sufficient!");
    digitalWrite(BAD_SOIL_MOIST_OUT, LOW);
    digitalWrite(CHECK_SOIL_MOIST_OUT, LOW);
  } else if (soil_moist_val >= 40 and soil_moist_val <= 50) {
    Serial.println("Soil is starting to dry out!");
    digitalWrite(BAD_SOIL_MOIST_OUT, LOW);
    digitalWrite(CHECK_SOIL_MOIST_OUT, HIGH);
  } else if (soil_moist_val < 40) {
    Serial.println("Soil is dry!");
    digitalWrite(BAD_SOIL_MOIST_OUT, HIGH);
    digitalWrite(CHECK_SOIL_MOIST_OUT, HIGH);
  }

  /* Check runoff moisture reading */
  if (runoff_moist_val >= 30 and soil_moist_val <= 100) {
    Serial.println("Runoff is present!");
    digitalWrite(BAD_RUNOFF_MOIST_OUT, HIGH);
  } else {
    Serial.println("No runoff is present!");
    digitalWrite(BAD_RUNOFF_MOIST_OUT, LOW);
  }
  
  delay(1000);
}
