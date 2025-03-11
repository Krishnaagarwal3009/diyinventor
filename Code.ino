/*
 * Author: Krishna Agarwal
 * Description: Ultrasonic distance measurement system with risk indication using LEDs and a buzzer.
 */

#include <LiquidCrystal.h>

// Define sensor and output pins
const int trig = 8;
const int echo = 7;
const int ledPin1 = 6;
const int ledPin2 = 9;
const int ledPin3 = 12;
const int ledPin4 = 13;
const int norisk = A2;
const int buzz = A0;

// LCD initialization (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(11, 10, 5, 4, 3, 2);

void setup() {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT);
    pinMode(ledPin4, OUTPUT);
    pinMode(norisk, OUTPUT);
    pinMode(buzz, OUTPUT);
    
    lcd.begin(16, 2);
    Serial.begin(9600);
    
    lcd.print("Starting System");
    delay(1500);
    lcd.clear();
    lcd.print("System On");
    delay(4000);
}

void loop() {
    long duration;
    int distance;
    
    // Trigger ultrasonic sensor
    digitalWrite(trig, LOW);
    delayMicroseconds(5);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    
    // Measure echo duration
    duration = pulseIn(echo, HIGH);
    distance = duration * 0.034 / 2;
    
    Serial.print("Distance: ");
    Serial.println(distance);
    
    // Risk level detection and response
    lcd.clear();
    lcd.setCursor(0, 0);
    
    if (distance <= 25) {
        lcd.print("Extreme Risk");
        lcd.setCursor(0, 11);
        lcd.print("Glowing 4 LED");
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, HIGH);
        digitalWrite(ledPin4, HIGH);
        digitalWrite(norisk, LOW);
        tone(buzz, 900);
        delay(100);
        noTone(buzz);
        delay(100);
    } else if (distance >= 26 && distance <= 100) {
        lcd.print("High Risk");
        lcd.setCursor(0, 11);
        lcd.print("Glowing 3 LED");
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, HIGH);
        digitalWrite(ledPin4, LOW);
        digitalWrite(norisk, LOW);
        tone(buzz, 900);
        delay(700);
        noTone(buzz);
        delay(700);
    } else if (distance >= 101 && distance <= 150) {
        lcd.print("Medium Risk");
        lcd.setCursor(0, 11);
        lcd.print("Glowing 2 LED");
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, LOW);
        digitalWrite(ledPin4, LOW);
        digitalWrite(norisk, LOW);
        tone(buzz, 1200);
        delay(100);
        noTone(buzz);
        delay(1200);
    } else if (distance >= 151 && distance <= 250) {
        lcd.print("Low Risk");
        lcd.setCursor(0, 11);
        lcd.print("Glowing 1 LED");
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
        digitalWrite(ledPin4, LOW);
        digitalWrite(norisk, LOW);
        tone(buzz, 900);
        delay(300);
        noTone(buzz);
        delay(2000);
    } else {
        lcd.print("Safe No Risk");
        lcd.setCursor(0, 11);
        lcd.print("Glowing Safe LED");
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
        digitalWrite(ledPin4, LOW);
        digitalWrite(norisk, HIGH);
        noTone(buzz);
    }
}
