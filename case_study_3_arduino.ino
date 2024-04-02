#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <LiquidCrystal.h>
#include <ThingSpeak.h>


// Header file containing credentials such as SSID,PASS, AIO_USERNAME & AIO_KEY
#include "Credentials.h" 


WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe switchbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/switchbutton");

 unsigned long myChannelNumber =2494362; 

 const char * myWriteAPIKey ="75EPXYFOYF1TAQPI"; 

const int lightSensorPin = A0;
const int ledPin = D7;

// LCD pins matching GPIO pins
const int rs = D5;
const int en = D4;
const int d4 = D3;
const int d5 = D2;
const int d6 = D1;
const int d7 = D0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// Function to connect to Mobile Hotspot/WIFI
void connectWiFi() {
  Serial.println();
  Serial.println("Connecting to Mobile WiFi...");
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi Connection Established");
}


// Function to connect to MQTT
void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }
  Serial.println("Connecting to MQTT");
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 3 seconds...");
    mqtt.disconnect();
    delay(3000);
  }
  Serial.println("MQTT Connected!");
}


// Function to Initialize Board, WIFI, LED Output & LCD & MQTT Subscription
void setup() {
  Serial.begin(115200);
  connectWiFi();
  ThingSpeak.begin(client); 

  pinMode(ledPin, OUTPUT);

  // Set up the LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Light:");

  // Setup MQTT subscriptions
  mqtt.subscribe(&switchbutton);
}


void loop() {
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &switchbutton) {
      Serial.print("Received MQTT message: ");
      Serial.println((char *)switchbutton.lastread);

      int switchState = atoi((char *)switchbutton.lastread);
      Serial.print("Switch state: ");
      Serial.println(switchState); // debugging purposes

      if (switchState == 1) {
        digitalWrite(ledPin, HIGH); // Turn on LED
      } else if (switchState == 0) {
        digitalWrite(ledPin, LOW); // Turn off LED
      } else {
        Serial.println("Invalid switch state received!");
      }
    }
  }

  int lightIntensity = analogRead(lightSensorPin);

  Serial.print("Light Intensity(lux): ");
  Serial.println(lightIntensity);


  lcd.setCursor(7, 0); 
  lcd.print("    ");   
  lcd.setCursor(7, 0); 
  lcd.print(lightIntensity); 
  lcd.print(" lux"); 

  // Publish light intensity value to Adafruit IO feed using key value
  if (!mqtt.publish(AIO_USERNAME "/feeds/light-intensity", String(lightIntensity).c_str())) {
    Serial.println("Failed to publish light intensity value!");
  }

  ThingSpeak.writeField(2494362, 1,lightIntensity,"75EPXYFOYF1TAQPI"); 

  delay(6000); 
}
