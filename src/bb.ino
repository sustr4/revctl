/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
int ConPin = 3;
int sensorPin = A4;
int delay_time = 0;
int delay_time2 = 0;
int delay_time3 = 0;
int step_pin = 8;
int dir_pin = 9;

int count_status = 0;

const int numReadings = 20;

int readings[numReadings];      // the readings from the analog input
int index = 0;                  // the index of the current reading
int total = 0;                  // the running total
int average = 0;        

float otacky = 0;

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  pinMode(step_pin, OUTPUT); 
  pinMode(dir_pin, OUTPUT); 
  analogWrite(ConPin, '55'); 
  lcd.print("Prodleva Otacky");
  digitalWrite(dir_pin, LOW); 
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0; 
}

void loop() {
  if((count_status%100)==0){
    // subtract the last reading:
  total= total - readings[index];         
  // read from the sensor:  
  readings[index] = analogRead(sensorPin); 
  // add the reading to the total:
  total= total + readings[index];       
  // advance to the next position in the array:  
  index = index + 1;                    

  // if we're at the end of the array...
  if (index >= numReadings)              
    // ...wrap around to the beginning: 
    index = 0;                           

  // calculate the average:
  delay_time = total / numReadings;
    
  //delay_time = analogRead(sensorPin);
  //delay_time =(delay_time+delay_time2+delay_time3)/3;
  delay_time = map(delay_time, 0, 1023, 30, 200); 
  }
  if((count_status%100)==0){
  lcd.setCursor(0, 1);
  lcd.print(delay_time);lcd.print("ms   ");
  lcd.setCursor(9, 1);
  otacky = (float(60000)/float(delay_time))/200.0;
  lcd.print(otacky);lcd.print("RPM");
  }
  
  if (count_status >= int(float(delay_time)*0.92)){ 
  digitalWrite(step_pin, HIGH);  
  // stop the program for <sensorValue> milliseconds:
  delay(1);          
  // turn the ledPin off:        
  digitalWrite(step_pin, LOW);
  count_status = 0;
  }
  // stop the program for for <sensorValue> milliseconds:
  delay(1); 
  count_status++;
  
}

