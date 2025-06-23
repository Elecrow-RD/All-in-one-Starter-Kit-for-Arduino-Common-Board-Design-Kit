//**************
//IR receive demo v1.0
//Connect the IR sent pins to D2 for this demo
//******************************
#include <IRSendRev.h>              // Include IR receiver library (note: may be spelled incorrectly)

#define IR_PIN 2                     // Define IR receiver pin as D2

#include <Servo.h>                  // Include servo motor control library
int pos = 0;                       // Variable to store servo position
Servo myservo;                     // Create servo object

/*******************LCD function*******************/
#include "Adafruit_LiquidCrystal.h" // Include LCD library
Adafruit_LiquidCrystal lcd(1);    // Create LCD object with I2C address 1

int value = 0;                     // Variable to store servo angle value
int i = 0;                         // Counter variable

unsigned long previousMillis = 0;  // Last update time for timing operations
const long interval = 10;          // Interval for LED blinking (ms, not used in this code)
String num;                        // String to build numeric input from IR remote
String num1;                       // String to display on LCD

void setup() {
  Serial.begin(115200);            // Initialize serial communication at 115200 baud
  while (!lcd.begin(16, 2)) {      // Attempt to initialize LCD (16 columns, 2 rows)
    Serial.println("Could not init backpack. Check wiring.");  // Error message if LCD init fails
    delay(50);                    // Delay 50ms before retrying
  }
  Serial.println("Backpack init'd.");  // Success message when LCD is initialized
  IR.Init(IR_PIN);                  // Initialize IR receiver on pin D2
  Serial.println("init over");      // Indicate IR receiver initialization complete
  
  // myservo.attach(9, 600, 2520);  // (Commented) Attach servo to pin 9 with custom pulse range
  // myservo.write(180);             // (Commented) Set servo to 180 degrees initially
  
  num1 = "Angle:";                 // Initialize LCD display prefix
  lcd.setCursor(0, 0);             // Set LCD cursor to row 0, column 0
  lcd.print(num1);                 // Print "Angle:" on LCD
}

void loop() {
  byte dta[10];                    // Buffer to store received IR data
  if (IR.IsDta()) {                // Check if IR data is available
    byte length = IR.Recv(dta);    // Read IR data into buffer
    
    Serial.print("- press -\t");   // Indicate received button press in serial
    switch (dta[8]) {              // Process IR command based on button code (dta[8])
      case 2:                      // Button code 2 (NEXT)
        Serial.println("[NEXT]");   // Log button press in serial
        myservo.attach(9, 600, 2520);  // Attach servo to pin 9 with pulse range 600-2520μs
        myservo.write(180);        // Set servo to 180 degrees (fully open)
        lcd.setCursor(0, 0);       // Clear and update LCD
        lcd.print("             ");
        lcd.setCursor(0, 0);
        lcd.print("Servo Open");   // Display "Servo Open" on LCD
        break;
        
      case 194:                    // Button code 194 (PLAY/PAUSE)
        Serial.println("[PLAY/PAUSE]");  // Log button press
        myservo.detach();         // Detach servo to stop control
        lcd.setCursor(0, 0);       // Clear and update LCD
        lcd.print("             ");
        lcd.setCursor(0, 0);
        lcd.print("Servo Close");  // Display "Servo Close" on LCD
        break;
        
      case 144:                    // Button code 144 (EQ) - set custom angle
        Serial.println("[EQ]");     // Log button press
        if (num.toInt() >= 0 && num.toInt() <= 180) {  // Validate angle is 0-180
          Serial.println(num);      // Log entered angle in serial
          num1 = "Angle:";          // Reset LCD display prefix
          myservo.write(num.toInt());  // Set servo to entered angle
          num = "";                 // Clear input string
          value = myservo.read();   // Get current servo angle
          num1 += String(value);    // Append angle to LCD display string
          lcd.setCursor(0, 0);       // Update LCD with new angle
          lcd.print("             ");
          lcd.setCursor(0, 0);
          lcd.print(num1);
        } else {                    // Handle invalid angle input
          num1 = "Angle:";
          num1 += "Error";          // Display error message on LCD
          num = "";                 // Clear input string
          lcd.setCursor(0, 0);
          lcd.print("             ");
          lcd.setCursor(0, 0);
          lcd.print(num1);
        }
        break;
        
      // Number buttons (0-9): append digit to input string
      case 104: Serial.println("[0]"); num = num + '0'; break;
      case 48:  Serial.println("[1]"); num = num + '1'; break;
      case 24:  Serial.println("[2]"); num = num + '2'; break;
      case 122: Serial.println("[3]"); num = num + '3'; break;
      case 16:  Serial.println("[4]"); num = num + '4'; break;
      case 56:  Serial.println("[5]"); num = num + '5'; break;
      case 90:  Serial.println("[6]"); num = num + '6'; break;
      case 66:  Serial.println("[7]"); num = num + '7'; break;
      case 74:  Serial.println("[8]"); num = num + '8'; break;
      case 82:  Serial.println("[9]"); num = num + '9'; break;
    }
    
    lcd.setCursor(0, 1);           // Update second row of LCD
    lcd.print("                ");  // Clear row
    lcd.setCursor(0, 1);
    lcd.print(num);                 // Display current numeric input
  }
  delay(100);                       // Delay 100ms to reduce CPU load
}