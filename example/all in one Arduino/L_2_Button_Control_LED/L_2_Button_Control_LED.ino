// Define the pin number connected to the button (Digital Pin 7)
int buttonPin = 7;
// Define the pin number connected to the LED (Digital Pin 10)
int LedPin = 10;

// Initialization function, runs once when the Arduino starts
void setup() {
  // Configure the LED pin as an output to control the LED
  pinMode(LedPin, OUTPUT);
  // Configure the button pin as an input to read button state
  pinMode(buttonPin, INPUT);
}

// Main loop function, runs repeatedly after setup completes
void loop() {
  // Read the button pin state (HIGH = pressed, LOW = released)
  // Assumes button is configured as pull-up (LOW when not pressed)
  if (digitalRead(buttonPin))
    // When button is pressed, set LED pin LOW to turn LED off
    digitalWrite(LedPin, LOW);
  else
    // When button is released, set LED pin HIGH to turn LED on
    digitalWrite(LedPin, HIGH);

  // Delay for 100ms to debounce the button and reduce CPU usage
  delay(100);
}