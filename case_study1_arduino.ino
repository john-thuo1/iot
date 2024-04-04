#include <LiquidCrystal.h>

// Ultrasonic sensor pins - used 3 pin sensors
int front_ultrasonic_signal = 8; 
int rear_ultrasonic_signal = 7;   

// LEDs and buzzer pins
int green_led = 13;
int red_led = 12;
int buzzer = 11;

// LCD Pins
int rs = 10, en = 9, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Flag to track if suspect is detected
bool suspectDetected = false;

void setup() {
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.clear();

  // Initialize LED and buzzer pins
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Initialize LCD message
  lcd.print("Safe");
}

void loop() {
  // Check for front sensor( in meters)
  float frontDistance = measureDistance(front_ultrasonic_signal);
  if (frontDistance <= 2) {
    displaySuspect("Front", frontDistance);
    activateAlarm();
    return;
  }

  // Check for rear sensor( in meters)
  float rearDistance = measureDistance(rear_ultrasonic_signal);
  if (rearDistance <= 2) {
    displaySuspect("Rear", rearDistance);
    activateAlarm();
    return;
  }

  // If no suspect detected, display "Safe" and turn on green LED
  if (!suspectDetected) {
    lcd.clear(); 
    lcd.setCursor(0, 0);
    lcd.print("Safe");
    digitalWrite(green_led, HIGH);
    delay(1000);
  }
}

float measureDistance(int signalPin) {
  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, LOW);
  delayMicroseconds(2);
  digitalWrite(signalPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(signalPin, LOW);

  pinMode(signalPin, INPUT);
  float duration = pulseIn(signalPin, HIGH);
  float distance = (duration * 0.034 / 2)/100;
  return distance;
}

void displaySuspect(String location, float distance) {
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Suspect at ");
  lcd.print(location);
  lcd.setCursor(0, 1);
  lcd.print("Distance:");
  lcd.print(distance);
  lcd.print("m");
  // Update suspect detected flag
  suspectDetected = true;
}

void activateAlarm() {
  // Turn on red LED and activate buzzer
  digitalWrite(red_led, HIGH);
  digitalWrite(buzzer, HIGH);
  
  // Blink red LED and sound buzzer every 2 seconds
  delay(1000); 
  while(true) {
    digitalWrite(red_led, LOW);
    digitalWrite(buzzer, LOW);
    delay(1000); 
    digitalWrite(red_led, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(1000); 
  }
}
