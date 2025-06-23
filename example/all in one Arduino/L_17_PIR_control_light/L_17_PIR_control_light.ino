#define PIR_PIN A2      // Define PIR sensor input pin (analog pin A2 used as digital input)

static int oldState = 0;  // Previous state of PIR sensor (0 = no motion, 1 = motion detected)
int LedPin = 10;          // Define LED output pin

void setup() {
  Serial.begin(115200);   // Initialize serial communication at 115200 baud rate
  while(!Serial);         // Wait for serial monitor to connect (required for Leonardo/Micro)
  pinMode(PIR_PIN, INPUT);    // Set PIR sensor pin as input
  pinMode(LedPin, OUTPUT);    // Set LED pin as output
}

void loop() {
  byte state = digitalRead(PIR_PIN);  // Read current state of PIR sensor (HIGH=motion, LOW=no motion)
  
  // Check if motion is detected and state has changed from LOW to HIGH
  if( state && oldState != state ) {
    Serial.println("[-] Motion detected!");  // Print message to serial monitor
    oldState = state;                        // Update previous state to current state
    digitalWrite(LedPin, HIGH);              // Turn on LED
    delay(5000);                             // Keep LED on for 5 seconds (blocking delay)
  } 
  // Check if motion has stopped and state has changed from HIGH to LOW
  else if( !state && oldState != state ) {
    Serial.println("[-] No Motion!");        // Print message to serial monitor
    digitalWrite(LedPin, LOW);               // Turn off LED
    oldState = state;                        // Update previous state to current state
  }
  
  delay(20);  // Small delay to reduce CPU usage and debounce sensor readings
}