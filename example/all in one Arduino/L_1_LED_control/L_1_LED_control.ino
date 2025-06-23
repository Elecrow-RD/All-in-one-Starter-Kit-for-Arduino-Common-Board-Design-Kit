// Define the pin number connected to the LED
int LedPin = 10;

// Initialization function, runs once when the Arduino starts
void setup() {
  // Configure the LED pin as an output
  pinMode(LedPin, OUTPUT);
}

// Main loop function, runs repeatedly after setup
void loop() {
  // Set the LED pin HIGH (5V), turning the LED on
  digitalWrite(LedPin, HIGH);
  // Pause the program for 1000 milliseconds (1 second)
  delay(1000);
  
  // Set the LED pin LOW (0V), turning the LED off
  digitalWrite(LedPin, LOW);
  // Pause the program for another 1000 milliseconds
  delay(1000);
}