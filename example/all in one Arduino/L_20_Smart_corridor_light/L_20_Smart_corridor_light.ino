#include <BH1750.h>           // Include BH1750 light sensor library
#include <Wire.h>             // Include I2C communication library

BH1750 lightMeter(0x5c);     // Create BH1750 object with I2C address 0x5c
#define PIR_PIN A2            // Define PIR sensor pin as analog pin A2
int LedPin = 10;             // Define LED control pin as pin 10
#define SOUND_PIN A1          // Define sound sensor pin as analog pin A1

void setup() {
  Serial.begin(115200);       // Initialize serial communication at 115200 baud
  Wire.begin();               // Initialize I2C bus (required for BH1750)
  
  // Initialize BH1750 in continuous high-resolution mode
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x5c, &Wire)) {
    Serial.println(F("BH1750 Advanced begin"));  // Print initialization success
  } else {
    Serial.println(F("Error initialising BH1750"));  // Print initialization error
  }
  
  pinMode(PIR_PIN, INPUT);    // Set PIR pin as input
  pinMode(LedPin, OUTPUT);    // Set LED pin as output
  pinMode(SOUND_PIN, INPUT);  // Set sound sensor pin as input
}

void loop() {
  // Check if BH1750 measurement is ready
  if (lightMeter.measurementReady(true)) {
    int lux = lightMeter.readLightLevel();  // Read light intensity in lux
    
    // Print light level to serial monitor
    Serial.print("[-] Light: [");
    Serial.print(lux);
    Serial.println("] lx");
    
    // If light level is less than 100 lux (dark environment)
    if (lux < 100) {
      while (1) {  // Enter loop to monitor PIR and sound sensor
        int state = digitalRead(PIR_PIN);  // Read PIR sensor state
        
        // If PIR detects motion or sound sensor detects sound
        if (state == HIGH || digitalRead(SOUND_PIN)) {
          Serial.println("[-] Motion detected!");  // Print detection message
          digitalWrite(LedPin, HIGH);            // Turn on LED
          delay(10000);                           // Keep LED on for 10 seconds
        } 
        // If no motion and no sound detected
        else if (state == LOW && digitalRead(SOUND_PIN) == LOW) {
          Serial.println("[-] No Motion!");      // Print no detection message
          digitalWrite(LedPin, LOW);             // Turn off LED
        }
        
        // Recheck light level, break loop if light is sufficient
        lux = lightMeter.readLightLevel();
        if (lux >= 100) break;
      }
    } 
    // If light level is sufficient (≥100 lux)
    else if (lux >= 100) {
      digitalWrite(LedPin, LOW);  // Turn off LED
    }
  }
  delay(100);  // Delay for 100ms to reduce CPU usage
}