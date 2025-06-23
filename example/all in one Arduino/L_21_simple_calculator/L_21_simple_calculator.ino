// Include the IRSendRev library for IR signal processing
#include <IRSendRev.h>

// Define the pin connected to the IR receiver
#define IR_PIN 2

// Include the Adafruit LiquidCrystal library for LCD control
#include "Adafruit_LiquidCrystal.h"
// Initialize the LCD object using I2C interface
Adafruit_LiquidCrystal lcd(1);

// Strings to store parts of the input and the result
String num;
String num1;
String num2;
String num3;
// Flags to track the presence of '+' and '-'
int flag1 = 0;
int flag2 = 0;
// Variable to store the result of the operation
long value = 0;

void setup() {
  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);
  // Wait for the serial connection to be established
  while (!Serial);
  // Initialize the IR receiver on the defined pin
  IR.Init(IR_PIN);
  // Print a message indicating initialization is complete
  Serial.println("init over");
  // Initialize the LCD screen
  while (!lcd.begin(16, 2)) {
    // Print an error message if LCD initialization fails
    Serial.println("Could not init backpack. Check wiring.");
    // Wait for 50 milliseconds before retrying
    delay(50);
  }
  // Set the cursor position and print "Equal to:" on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Equal to:");
  // Set the cursor position for the second line
  lcd.setCursor(0, 1);
}

void loop() {
  // Array to store received IR data
  byte dta[10];
  // Check if IR data is available
  if (IR.IsDta()) {
    // Receive IR data into the array
    byte length = IR.Recv(dta);
    // Print a message indicating a button press
    Serial.print("- press -\t");
    // Switch case to handle different button presses
    switch (dta[8]) {
      case 224: Serial.println("[VOL-]");
        num += '-';  // Append '-' to the input string
        break;
      case 168: Serial.println("[VOL+]");
        num += '+';  // Append '+' to the input string
        break;
      case 144: Serial.println("[EQ]");
        num += '=';  // Append '=' to the input string
        num3 = "Equal to:";
        // Check if the input string can be sliced into two parts
        if (sliceString(num, num1, num2)) {
          // Print a message indicating valid data
          Serial.println("Valid data");
          // Check if the numbers are within the valid range
          if (num1.toInt() > 100000000 || num2.toInt() > 100000000 || num1.toInt() < 0 || num2.toInt() < 0) {
            // Print a message indicating invalid data
            Serial.println("Invalid data");
            num = "";
            num3 = "Out of range";
            // Clear the second line of the LCD and print the error message
            lcd.setCursor(0, 1);
            lcd.print("               ");
            lcd.setCursor(0, 1);
            lcd.print(num3);
            break;
          }
          // Perform the operation based on the flag
          if (flag1) {
            value = performOperation(num1.toInt(), num2.toInt(), '+');
            Serial.println("value");
          } else {
            value = performOperation(num1.toInt(), num2.toInt(), '-');
            Serial.println("-data");
          }
          // Clear the input string and update the result string
          num = "";
          num3 = String(value);
          // Clear the second line of the LCD and print the result
          lcd.setCursor(0, 1);
          lcd.print("               ");
          lcd.setCursor(0, 1);
          lcd.print(num3);
        } else {
          // Clear the input string and update the error message
          num = "";
          num3 = "Error";
          // Clear the second line of the LCD and print the error message
          lcd.setCursor(0, 1);
          lcd.print("               ");
          lcd.setCursor(0, 1);
          lcd.print(num3);
        }
        // Print the result and the input string for debugging
        Serial.println("value:");
        Serial.println(value);
        Serial.println();
        Serial.println(num);
        break;
      case 104: Serial.println("[0]");
        num += '0';  // Append '0' to the input string
        break;
      case 48:  Serial.println("[1]");
        num += '1';  // Append '1' to the input string
        break;
      case 24:  Serial.println("[2]");
        num += '2';  // Append '2' to the input string
        break;
      case 122: Serial.println("[3]");
        num += '3';  // Append '3' to the input string
        break;
      case 16:  Serial.println("[4]");
        num += '4';  // Append '4' to the input string
        break;
      case 56:  Serial.println("[5]");
        num += '5';  // Append '5' to the input string
        break;
      case 90:  Serial.println("[6]");
        num += '6';  // Append '6' to the input string
        break;
      case 66:  Serial.println("[7]");
        num += '7';  // Append '7' to the input string
        break;
      case 74:  Serial.println("[8]");
        num += '8';  // Append '8' to the input string
        break;
      case 82:  Serial.println("[9]");
        num += '9';  // Append '9' to the input string
        break;
    }
    // Check if the input string is too long and display only the last 14 characters
    if (num.length() > 14) {
      Serial.println(num.length());
      Serial.println(num.length());
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 0);
      lcd.print(num.substring(num.length()-14));
    } else {
      Serial.println(num.length());
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 0);
      lcd.print(num);
    }
  }
}

// Function to check if a string contains a specific character
bool containsCharacter(String str, char character) {
  return str.indexOf(character) != -1; // Return true if the character is found
}

// Function to slice the input string into two parts based on '+' or '-'
int sliceString(String input, String &part1, String &part2) {
  int plusIndex;
  int equalIndex;
  flag1 = containsCharacter(input, '+'); // Check if '+' is present
  flag2 = containsCharacter(input, '-'); // Check if '-' is present
  if ((flag1 || flag2) && containsCharacter(input, '=')) {
    if (flag1 == 1) {
      plusIndex = input.indexOf('+'); // Find the position of '+'
      equalIndex = input.indexOf('='); // Find the position of '='
    } else {
      plusIndex = input.indexOf('-'); // Find the position of '-'
      equalIndex = input.indexOf('='); // Find the position of '='
    }
  } else {
    return 0; // Return 0 if the string does not contain '+' or '-' and '='
  }
  if (plusIndex != -1) {
    part1 = input.substring(0, plusIndex); // Extract the part before '+'
  } else {
    part1 = ""; // Return an empty string if '+' is not found
  }
  if (plusIndex != -1 && equalIndex != -1 && equalIndex > plusIndex) {
    part2 = input.substring(plusIndex + 1, equalIndex); // Extract the part between '+' and '='
  } else {
    part2 = ""; // Return an empty string if the parts are not valid
  }
  return 1; // Return 1 if the string is successfully sliced
}

// Function to perform the arithmetic operation
long performOperation(long a, long b, char operation) {
  switch (operation) {
    case '+':
      return a + b; // Perform addition
    case '-':
      return a - b; // Perform subtraction
    default:
      return a; // Return the first operand if the operation is not valid
  }
}