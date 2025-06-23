/*******************Light Sensor*******************/
#include <BH1750.h>            // Include BH1750 light sensor library
BH1750 lightMeter(0x5c);      // Create sensor object with I2C address 0x5c
float lux;                    // Stores measured light intensity in lux

/*******************LED Control*******************/
int LedPin = 10;              // LED control pin (PWM capable)

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);   
  
  // Initialize I2C communication (required for BH1750)
  Wire.begin();

  // Initialize BH1750 sensor in continuous high-resolution mode (1 lux precision)
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x5c, &Wire)) {
    Serial.println(F("BH1750 Advanced begin"));  // Success message
  } else {
    Serial.println(F("Error initialising BH1750"));  // Error message
  }
  
  // Configure LED pin as output
  pinMode(LedPin, OUTPUT);
}

void loop() {
  // Check if light measurement is ready (blocking wait if true)
  if (lightMeter.measurementReady(true)) {
    lux = lightMeter.readLightLevel();  // Read light level in lux
    Serial.print("[-] Light: [");
    Serial.print(lux);
    Serial.println("] lx");             // Print light level to serial monitor
  }
  
  // Small delay to avoid excessive loop iterations
  delay(10);

  // Control LED based on light level:
  // Turn ON if light is <= 100 lux (dark environment)
  // Turn OFF if light is > 100 lux (bright environment)
  if (lux <= 100)
    digitalWrite(LedPin, HIGH);
  else
    digitalWrite(LedPin, LOW);
}
