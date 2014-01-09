#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
int ConPin = 3;
int sensorPin = A4;
int set_rpm = 1; // RPM in (s/10)^-1
int step_pin = 8;
int dir_pin = 9;

int count_status = 0;

const int numReadings = 20;

int readings[numReadings];      // the readings from the analog input
int index = 0;                  // the index of the current reading
int total = 0;                  // the running total
int average = 0;        

float otacky = 0;
int prodleva = 2999;	


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
	  set_rpm = total / numReadings;
	    
	  set_rpm = map(set_rpm, 0, 1023, 1, 100); 
  }
  if((count_status%100)==0){
	  otacky = (float)set_rpm / 10.0; // set RPM kept in 1/10ths!
	  prodleva = (int)(300.0 / otacky) - 1; // 60000 ms in a minute / 200 pulses in a rev. = 300
	
	  lcd.setCursor(0, 1);
	  lcd.print(prodleva);lcd.print("ms   ");
	  lcd.setCursor(9, 1);
	  lcd.print(otacky);lcd.print("RPM");
  }
  
  if (count_status >= prodleva) { 
	  digitalWrite(step_pin, HIGH);  
	  // stop the program for <sensorValue> milliseconds:
	  delay(1);          
	  // turn the ledPin off:        
	  digitalWrite(step_pin, LOW);
	  count_status = 0;
  }

  else {
	  // stop the program for for <sensorValue> milliseconds:
	  delay(1); 
	  count_status++;
  }
  
}

