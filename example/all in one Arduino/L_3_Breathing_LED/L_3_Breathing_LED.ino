// Define the analog pin connected to the linear sensor (A0)
int LinearPin = A0;
// Define the PWM pin connected to the LED (D10)
int LedPin = 10;

void setup() {
  // Initialize serial communication at 115200bps
  Serial.begin(115200);
  // Print initialization message to Serial Monitor
  Serial.println("Backpack init'd.");
  
  // Configure LED pin as PWM output
  pinMode(LedPin, OUTPUT);
  // Configure sensor pin as analog input
  pinMode(LinearPin, INPUT);
}

void loop() {
  // Variable to store raw ADC value (0-1023)
  int adcValue;
  // Variable to store mapped PWM value (0-255)
  int mappedValue;
  
  // Read analog input value from sensor
  adcValue = analogRead(LinearPin);
  
  // Map ADC value (0-1023) to PWM range (0-255)
  mappedValue = map(adcValue, 0, 1023, 0, 255);
  // Set LED brightness via PWM (0=off, 255=full brightness)
  analogWrite(LedPin, mappedValue);
  
  // Re-map ADC value to a different range (0-10)
  mappedValue = map(adcValue, 0, 1023, 0, 10);
  
  // Convert integer value to String for Serial output
  String Value = String(mappedValue);
  
  // Delay 100ms to control sampling rate and stabilize visual effects
  delay(100);
}
