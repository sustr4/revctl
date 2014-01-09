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
int current_pot = 0;

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
	  current_pot = analogRead(sensorPin);
	  readings[index] = current_pot;
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
	  lcd.print(current_pot);lcd.print("ms   ");
	  lcd.setCursor(9, 1);
	  otacky = (float(60000)/float(current_pot))/200.0;
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

  else {
	  // stop the program for for <sensorValue> milliseconds:
	  delay(1); 
	  count_status++;
  }
  
}

