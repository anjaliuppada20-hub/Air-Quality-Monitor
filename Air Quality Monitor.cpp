#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define MQ135_PIN A0
#define DHT_PIN 2
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int airQuality = 0;
float temperature = 0;
float humidity = 0;

void setup() {
  Serial.begin(9600);

  dht.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Air Quality");
  lcd.setCursor(0, 1);
  lcd.print("Monitor Starting");

  delay(2000);
  lcd.clear();
}

void loop() {
  // Read MQ-135
  airQuality = analogRead(MQ135_PIN);

  // Read DHT11
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  // Check DHT sensor
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT11 Error");
    return;
  }

  // Determine air quality level
  String quality;

  if (airQuality < 200) {
    quality = "GOOD";
  }
  else if (airQuality < 400) {
    quality = "MODERATE";
  }
  else if (airQuality < 600) {
    quality = "POOR";
  }
  else if (airQuality < 800) {
    quality = "BAD";
  }
  else {
    quality = "DANGER";
  }

  // LCD display
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("AQ:");
  lcd.print(airQuality);

  lcd.setCursor(8, 0);
  lcd.print(quality);

  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print("C H:");
  lcd.print(humidity, 0);
  lcd.print("%");

  // Serial Monitor
  Serial.println("----------------------");

  Serial.print("Air Quality Value: ");
  Serial.println(airQuality);

  Serial.print("Air Quality: ");
  Serial.println(quality);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(2000);
}
