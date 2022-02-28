/*
 * Developed by:  Eduardo Zola - www.zolalab.com.br - egzola@gmail.com
 * Modified by: Archit Ashok
 * Copyright (c) 2015 Eduardo Zola.  All right reserved.
 * 
 * Ultrasonic Data Transmission Using PWM
 */

const int TRANS_PIN = 5; // Must be PWM (X~) Pin
const int TRANS_FREQ = 40000; // 40kHz

void setup() {
  Serial.begin(9600);
  
  pinMode(TRANS_PIN, OUTPUT);
}

void loop() {
  transmitString("Hello");
}

void transmit(byte code) {
  sendTone(10); // Initiates Reading

  for(int i = 0; i < 8; i++) {
    if(bitRead(code, 7-i)) {
      sendTone(2);
    } else {
      sendTone(4);
    }

    delay(11); // Seperates bits
  }
  
}

void transmitString(String toTrans) {
  for(int i = 0; i < toTrans.length(); i++) {
    unsigned char letter = toTrans.charAt(i);
    
    Serial.println(letter);
    transmit(letter);
  }
}

void sendTone(int duration) {
  tone(TRANS_PIN, TRANS_FREQ);
  delay(duration);
  noTone(TRANS_PIN);
}
