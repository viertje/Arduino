#include <Keypad.h>
#include <Wire.h>
#include "rgb_lcd.h"
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

rgb_lcd lcd;

int count = 0;
char a[5] = {'1','2','3','4','#'};
char b[5] = "";
bool flag1 = false;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {

  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}

};

byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){

  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    lcd.print("Input Password  ");
    myservo.attach(1);  // attaches the servo on pin 1 to the servo object
}

void loop(){
  char customKey = customKeypad.getKey();

 for(int i = 0; i < 5; i++){
    Serial.print(b[i]);
    }

  Serial.println("");

  lcd.setCursor (0, 1);

  if (customKey != 0) {
    Serial.println(customKey);
    lcd.print(customKey);
    b[count] = customKey;
    count++;
    if (count == 5) {
      for (int i = 0; i < 5; i++) {
        if (a[i] == b[i]) {
          flag1 = true
        }
      }
      if (flag1 == true) {
        lcd.setCursor (0, 0);
        lcd.print("Correct Password");
        count = 0;
        for (pos = 0; pos <= 180; pos += 1) { 
            myservo.write(pos);
            }
      }
      else {
        lcd.setCursor (0, 0);
        lcd.print("Wrong Password  ");
        count = 0;
        delay(5000);
        lcd.print("Input Password  ");
      }

      Serial.println("delete");
      memset(b, 0, 5);
      for(int i = 0; i < 5; i++){
        Serial.print(b[i]);
      }
      delay(10000);
    }    
  }
}