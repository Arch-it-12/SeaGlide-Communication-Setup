/*
 * Developed by:  Eduardo Zola - www.zolalab.com.br - egzola@gmail.com
 * Modified by: Archit Ashok
 * Copyright (c) 2015 Eduardo Zola.  All right reserved.
 * 
 * Ultrasonic Data Receiving Using PWM
 */

const int TRANS_PIN = 5; // Must be PWM (X~) Pin

const int UPPER = 200;
const int MID = 100;
const int LOWER = 20; // maxCount thresholds
  
void setup() {
  Serial.begin(9600);
  
  pinMode(TRANS_PIN, INPUT_PULLUP); // Activates pull up resistor
}

void loop() {
  if(digitalRead(TRANS_PIN)) {
    Serial.print((char)readByte());
  }
}

unsigned char readByte() {
  unsigned char comm = 0;
  
  int bytePos = 0;
  boolean checkBits = false;

  while(bytePos < 8) {
    if(!digitalRead(TRANS_PIN)){
      continue;
    }
    
    int maxCount = 0;
    unsigned long timeBegin = millis();

    while(millis() - timeBegin <= 10) {
      if(digitalRead(TRANS_PIN)) {
        maxCount++;
      }
    }

    if(checkBits) {
      if(maxCount > MID && maxCount < UPPER) {
        bitClear(comm, 7 - bytePos);
      } else if(maxCount > LOWER && maxCount < MID) {
        bitSet(comm, 7 - bytePos);
      }

      bytePos++;
    }

    if(maxCount > UPPER) {
      checkBits = true;
      bytePos = 0;
    }
  }

  return comm;
}
