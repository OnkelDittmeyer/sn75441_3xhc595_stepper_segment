void writeDisplay(int number){
  long emptyBinary = 0b11111111; //binary for an empty digit display
  String numberString = String(number);

  // walk through digits backwards and write them into displays
  if(numberString.length() <= numberOfDigits){
    for(int i = numberString.length()-1; i >= 0 ; i--){
      writeReg(convertNumber(number, i));
    
//      //fill left displays with empty space
//      if(numberString.length() < numberOfDigits){
//        for(int n= 0; n < (numberOfDigits - numberString.length()); n++){
//
//            writeReg(emptyBinary);
//
//          }
//    }
     }
   
  }else{
    Serial.println("Number too large for display segments");
  }
}


long convertNumber(int number, int pos) {
  String numberString = String(number);
  pos = pos - 1;
  if (pos < numberString.length()) {
    switch (numberString.charAt(pos)) {
      case '0':
        return 0b11000000;  //change to bitcode for 0
        break;
      case '1':
        return 0b11101101;  // change to bitcode for 1
        break;
      case '2':
        return 0b10110000;  // change to bitcode for 2
        break;
      case '3':
        return 0b10101000;  // change to bitcode for 3
        break;
      case '4':
        return 0b10001101;  // change to bitcode for 4
        break;
      case '5':
        return 0b10001010;  // change to bitcode for 5
        break;
      case '6':
        return 0b10000010;  // change to bitcode for 6
        break;
      case '7':
        return 0b11101100;  // change to bitcode for 7
        break;
      case '8':
        return 0b00000000;  // change to bitcode for 8
        break;
      case '9':
        return 0b00001000;  // change to bitcode for 9
        break;
      default:
        return 0b11111111;  // change to bitcode for nothing
        break;

    }


  } else {
    return 0;
  }
}


void clearDisplays() {
  writeRegAll(0b11111111, 0b11111111, 0b11111111);
}

void writeReg(long regNum) {
  digitalWrite(latchPin, 0);
  //move 'em out
  shiftOut(dataPin, clockPin, regNum);
  //shiftOut(dataPin, clockPin, regNum2);
  //shiftOut(dataPin, clockPin, regNum3);
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(latchPin, 1);
  //delay(300); // uncomment this delay ---------------------------------------------------------------------------

}

void writeDisplayAll(int number) {
  if(number <= 9){
          writeRegAll(0b11111111, 0b11111111, convertNumber(number, 1));

  }
  
  if(number <= 99){
      writeRegAll(0b11111111, convertNumber(number, 1), convertNumber(number, 2));
  }
  
  writeRegAll(convertNumber(number, 1), convertNumber(number, 2), convertNumber(number, 3));

}

void writeRegAll(long regNum, long regNum2, long regNum3) {
  digitalWrite(latchPin, 0);
  //move 'em out
  shiftOut(dataPin, clockPin, regNum);
  shiftOut(dataPin, clockPin, regNum2);
  shiftOut(dataPin, clockPin, regNum3);
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(latchPin, 1);
  //delay(300); // uncomment this delay ---------------------------------------------------------------------------

}


void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first,
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i = 0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights.
  for (i = 7; i >= 0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1 << i) ) {
      pinState = 1;
    }
    else {
      pinState = 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}





