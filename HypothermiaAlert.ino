#include "DHT.h"
#include "LiquidCrystal_I2C.h"
#include "Buzzer.h"
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define DHTPIN 3       // what pin we're connected to
#define DHTTYPE DHT22  // DHT 22 (AM2302)
#define buzzerPin 2

int maxHum = 70;
float t0 = 29.0;
float t1 = 28.0;
float t2 = 27.0;
float t3 = 26.0;
float t4 = 25.0;
float t5 = 24.0;
float t6 = 23.0;
float t7 = 22.0;
float t8 = 21.0;
float t9 = 20.0;
float t10 = 19.0;
float told;
DHT dhtSensor(DHTPIN, DHTTYPE);

void setup(){
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  dhtSensor.begin();

  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  // Print a message to the LCD.
  lcd.setBacklight(HIGH);
  lcd.setCursor(1, 0);
  lcd.print("Hypothermia Alert!");
  lcd.setCursor(0, 1);
  lcd.print("By: Subhajit Debnath");
  lcd.setCursor(0, 3);
  lcd.print("Severity:");
}

void loop(){
  // Wait a few seconds between measurements.
  delay(500);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dhtSensor.readHumidity();
  // Read temperature as Celsius
  float t = dhtSensor.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  unsigned int row = 3;
  unsigned int col = 10;
  // t10 = 22.0;
  if (t < t10) {
    lcd.setCursor(col, row);
    lcd.print("##########");
    // playtone(4);
  }
  // t10 = 22.5;
  else if (t >= t10 && t < t9) {
    lcd.setCursor(col, row);
    lcd.print("#########_");
    // playtone(3);
  }
  // t10 = 23.0;
  else if (t >= t9 && t < t8) {
    lcd.setCursor(col, row);
    lcd.print("########__");
    // playtone(2);
  }
  // t10 = 23.5;
  else if (t >= t8 && t < t7) {
    lcd.setCursor(col, row);
    lcd.print("#######___");
    // playtone(1);
  }
  // t10 = 24.0;
  else if (t >= t7 && t < t6) {
    lcd.setCursor(col, row);
    lcd.print("######____");
  }
  // t10 = 24.5;
  else if (t >= t6 && t < t5) {
    lcd.setCursor(col, row);
    lcd.print("#####_____");
  }
  // t10 = 25.0;
  else if (t >= t5 && t < t4) {
    lcd.setCursor(col, row);
    lcd.print("####______");
  }
  // t10 = 25.5;
  else if (t >= t4 && t < t3) {
    lcd.setCursor(col, row);
    lcd.print("###_______");
  }
  // t10 = 26.0;
  else if (t >= t3 && t < t2) {
    lcd.setCursor(col, row);
    lcd.print("##________");
  }
  // t10 = 26.5;
  else if (t >= t2 && t < t1) {
    lcd.setCursor(col, row);
    lcd.print("#_________");
  }
  // t10 = 27.0;
  else if (t >= t1 && t < t0) {
    lcd.setCursor(col, row);
    lcd.print("__________");
  }
  //LCD LIGHT CONTROL
  // =================
  // if (told != t) {
  // lcd.setBacklight(HIGH);
  // }
  // else {
  // lcd.setBacklight(LOW);
  // }
  // told = t;
  // =================
  // =====================
  // LCD PRINT COMMANDS
  // =====================
  // PRINT TEMPERATURE
  //-------------------
  lcd.setCursor(0, 2);
  lcd.print("T=");
  char tStr[5];
  dtostrf(t, 5, 2, tStr);
  lcd.print(tStr);
  lcd.print("c || ");
  //-------------------
  // PRINT HUMIDITY
  //-------------------
  lcd.print("H=");
  char hStr[5];
  dtostrf(h, 5, 2, hStr);
  lcd.print(hStr);
  lcd.print("%");
  //-------------------// =====================
  // SERIAL PRINT COMMANDS
  // =====================
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  // =====================
}

// void playtone(unsigned int p){
//   unsigned int i;
//   for (i = 0; i < 80; i++) {
//     digitalWrite(buzzerPin, HIGH);
//     delay(p);  //wait for 1ms
//     digitalWrite(buzzerPin, LOW);
//     delay(p);  //wait for 1ms
//   }
// }