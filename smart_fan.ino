#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);  // RS, E, D4–D7

#define tempPin A0
#define fanPin 9
#define buzzerPin 13

float temperature = 0;
float lowTemp = 25.0;
float highTemp = 40.0;
int dutyCycle = 0;

void setup() {
  pinMode(tempPin, INPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Smart Fan Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  int reading = analogRead(tempPin);
  float voltage = reading * 5.0 / 1023.0;
  temperature = (voltage - 0.5) * 100;

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print((char)223); // degree symbol
  lcd.print("C   ");

  if (temperature < lowTemp) {
    dutyCycle = 0;
  } else if (temperature > highTemp) {
    dutyCycle = 255;
  } else {
    dutyCycle = map(temperature * 10, lowTemp * 10, highTemp * 10, 0, 255);
  }

  analogWrite(fanPin, dutyCycle);

  lcd.setCursor(0, 1);
  lcd.print("Fan: ");
  lcd.print(map(dutyCycle, 0, 255, 0, 100));
  lcd.print("%     ");

  if (temperature > highTemp) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  delay(500);
}
