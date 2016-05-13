

#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor


// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

int stepCount = 0;  // number of steps the motor has taken

//shiftReg setup for segment display
//Pin connected to ST_CP of 74HC595
int latchPin = 5;
//Pin connected to SH_CP of 74HC595
int clockPin = 7;
////Pin connected to DS of 74HC595
int dataPin = 6;

int displayNumber = 123; //number you want on the display
int lastDisplayNumber = 111; //last displayNumber ---------------------------------------

const int numberOfDigits = 3; //number of displays you use

void setup() {
  
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);

    clearDisplays();
    Serial.begin(9600);
    
}

void loop() {
  // read the sensor value:
  int sensorReading = analogRead(A0);
  // map it to a range from 0 to 100:
  int motorSpeed = map(sensorReading, 0, 1023, 0, 100);
  // set the motor speed:
  if (motorSpeed > 0) {
    myStepper.setSpeed(motorSpeed);
    // step 1/100 of a revolution:
    myStepper.step(stepsPerRevolution / 100); 
  }

  displayNumber = motorSpeed;

  //whatever number you want to display, save it in displayNumber
  //update the display if the number changed, if not, dont update ----------------------
  if(lastDisplayNumber != displayNumber){
    
    writeDisplayAll(displayNumber);
       
    lastDisplayNumber = displayNumber; 
  }

  
}
