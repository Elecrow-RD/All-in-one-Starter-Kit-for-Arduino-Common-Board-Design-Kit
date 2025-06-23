#define SOUND_PIN A1      // Define sound sensor input pin (analog pin A1)
int buzzerPin = 3;         // Define buzzer output pin (PWM-supported pin 3)

void setup() {
  Serial.begin(115200);    // Initialize serial communication at 115200 baud
  while (!Serial);         // Wait for serial monitor connection (for debugging)
  pinMode(SOUND_PIN, INPUT);  // Set sound sensor pin as input
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
}

void loop() {
  // Check if sound level exceeds threshold (400)
  if (analogRead(SOUND_PIN) >= 400) {
    Serial.println("[-] Detect Sound!");  // Print sound detection message
    tone(buzzerPin, 1300);               // Activate buzzer at 1300Hz frequency
    delay(1000);                         // Keep buzzer on for 1000ms (blocking delay)
    
    // Enter infinite loop to monitor sound sustainability
    while (1) {
      if (analogRead(SOUND_PIN) >= 400) {
        // tone(buzzerPin, 1300);  // Commented: buzzer control is inactive here
        Serial.println(analogRead(SOUND_PIN));  // Log current sound value
      } else {
        noTone(buzzerPin);       // Stop buzzer when sound drops below threshold
        break;                   // Exit infinite loop
      }
    }
  }
}