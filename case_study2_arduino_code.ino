#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include <ThingSpeak.h>

// WiFi credentials
const char* ssid = "May";
const char* password = "22156827254";

// ThingSpeak credentials
const char* write_apiKey = "8V5RH4IY6ZXO1PVU";
const unsigned long channelID = 2491003;

// Define pins for sensors
const int dhtPin = D4;
const int soilMoisturePin = A0;

// Define sensor types
#define DHTTYPE DHT11   // DHT 11
DHT dht(dhtPin, DHTTYPE);

// Define pins for LCD corresponding to GPIO pins
const int rs = D6;
const int en = D5;
const int d4 = D3;
const int d5 = D2;
const int d6 = D1;
const int d7 = D0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define WiFi client
WiFiClient client;

void setup() {
  Serial.begin(115200);

  // Initialize DHT sensor
  dht.begin();

  // Initialize LCD
  lcd.begin(16, 2);  // Adjust the LCD size according to your display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // Read sensor data
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int soilMoisture = readSoilMoisture();

  // Print sensor data to serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  Serial.print("Soil Moisture:");
  Serial.println(soilMoisture);


  // Display sensor data on LCD
  displayOnLCD(temperature, humidity, soilMoisture);

  // Send data to ThingSpeak
  sendToThingSpeak(temperature, soilMoisture);

  delay(60000); // Wait for 1 minute before sending data again
}



int readSoilMoisture() {
  // Read soil moisture sensor
  return analogRead(soilMoisturePin);
}

void displayOnLCD(float temperature, float humidity, int soilMoisture) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print("C|H:");
  lcd.print(humidity);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Moisture:");
  lcd.print(soilMoisture);

}

void sendToThingSpeak(float temperature, int soilMoisture) {
  // Update ThingSpeak fields
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, soilMoisture);

  // Write to ThingSpeak
  int status = ThingSpeak.writeFields(channelID, write_apiKey);

  if (status == 200) {
    Serial.println("Data sent to ThingSpeak!");
  } else {
    Serial.println("Failed to send data to ThingSpeak");
  }
}
