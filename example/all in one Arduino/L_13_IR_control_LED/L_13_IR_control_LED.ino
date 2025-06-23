//**************
//IR receive demo v1.0
//Connect the IR sent pins to D2 for this demo
//******************************

#include <IRSendRev.h>  // Include the IRSendRev library for IR signal processing
#include <TimerOne.h>   // Include the TimerOne library for timer functionality
#define IR_PIN 2        // Define the pin connected to the IR receiver

int LedPin = 10;         // Define the pin connected to the LED

bool ledState = true;    // Variable to store the state of the LED (true for on, false for off)
bool timerRunning = false; // Variable to track whether the timer is running

void setup() {
  Serial.begin(115200);  // Initialize serial communication at 115200 baud rate
  while (!Serial);       // Wait for the serial connection to be established
  IR.Init(IR_PIN);       // Initialize the IR receiver on the defined pin
  Serial.println("init over");  // Print a message indicating initialization is complete

  pinMode(LedPin, OUTPUT);  // Set the LED pin as an output
  Timer1.initialize(1000000); // Initialize the timer with a period of 1 second (1000000 microseconds)
  Timer1.attachInterrupt(toggleLED); // Attach the toggleLED function to the timer interrupt
  Timer1.stop();           // Stop the timer initially
  timerRunning = false;    // Set the timer running state to false
}

void loop() {
  byte dta[10];           // Array to store received IR data
  if (IR.IsDta()) {       // Check if IR data is available
    byte length = IR.Recv(dta); // Receive IR data into the array
   
    Serial.print("- press -\t"); // Print a message indicating a button press was detected
    switch (dta[8]) {            // Use the 9th byte of the received data (usually the button code) to determine action

      case 48:  // Button code for button 1
        Serial.println("[1]");
        digitalWrite(LedPin, HIGH); // Turn on the LED
        if (timerRunning) {
          stopTimer(); // Stop the timer if it is running
        }
        break;
      case 24:  // Button code for button 2
        Serial.println("[2]");
        if (!timerRunning) {
          startTimer(); // Start the timer if it is not running
        } 
        break;
      case 122: // Button code for button 3
        Serial.println("[3]");
        digitalWrite(LedPin, LOW); // Turn off the LED
        if (timerRunning) {
          stopTimer(); // Stop the timer if it is running
        }
        break;
    }
  }
}

void toggleLED() {
  // Toggle the state of the LED
  ledState = !ledState; // Invert the LED state
  digitalWrite(LedPin, ledState); // Update the LED with the new state
}

void stopTimer() {
  Timer1.stop(); // Stop the timer
  timerRunning = false; // Update the timer running state to false
}

void startTimer() {
  Timer1.start(); // Start the timer
  timerRunning = true; // Update the timer running state to true
}
