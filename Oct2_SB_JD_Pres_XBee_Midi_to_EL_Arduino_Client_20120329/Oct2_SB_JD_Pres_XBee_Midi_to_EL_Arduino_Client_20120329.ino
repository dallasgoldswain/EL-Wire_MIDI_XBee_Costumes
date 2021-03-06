/* 
 // ===== EL Wire Dress =====
 //  Presence, Joey Doucette, Steve Beyer
 //  20120329
 //  tech@sbeyer.com
 //  Octave 2 (Notes 24~35, I use notes 25~32)
 */

#include <EL_Escudo.h>
//The EL_Escudo library uses letters A-H to reference each EL string.
//Each EL string output has a corresponding label on the EL Escudo shield.

byte incomingByte;  // first byte, command (144 == note on, 128 == note off)
byte note;      // 2nd byte     (36==middle_C)
byte velocity;  // 3rd byte     (100==omg go on fast, 0==off / Note Off command does not have velocity)

int action=2;   // 0==note off ; 1==note on ; 2==nothing

void setup() {
  Serial.begin(57600);
  pinMode(10, OUTPUT);
  blinkAwake();
  EL.all_off();  // turns off all, but turns on F.
  EL.off(7);  // 7, aka "F"
}

void loop() {
  if (Serial.available() > 0) {
    // blinkStatus(); //once to signal at least something arrived
    statusGlow(1);
    // read the incoming byte:
    incomingByte = Serial.read();
    // wait for as status-byte, channel 1, note on or off
    if (incomingByte== 144){ // note on message starting starting
      action=1;
    }
    else if (incomingByte== 128){ // note off message starting
      action=0;
    }
    else if (incomingByte== 208){ // aftertouch message starting
      //not implemented yet
    }
    else if (incomingByte== 160){ // polypressure message starting
      //not implemented yet
    }
    else if ( (action==0)&&(note==0) ){ // if we received a "note off", we wait for which note (databyte)
      note=incomingByte;
      playNote(note, 0);
      note=0;
      velocity=0;
      action=2;
    }
    else if ( (action==1)&&(note==0) ){ // if we received a "note on", we wait for the note (databyte)
      note=incomingByte;
    }
    else if ( (action==1)&&(note!=0) ){ // ...and then the velocity
      velocity=incomingByte;
      playNote(note, velocity);
      note=0;
      velocity=0;
      action=0;
    }
    else{
      // no MIDI input
      statusGlow(0);
    }
  }
}

void playNote(byte note, byte velocity){
  int value=LOW;
  if (velocity >10){
    value=HIGH;
  } else{
    value=LOW;
  }
  if (note==25 && value==HIGH) { 
    EL.on(A); 
  } else if (note==25) { 
    EL.off(A); 
  }
  if (note==26 && value==HIGH) { 
    EL.on(B); 
  } else if (note==26) { 
    EL.off(B); 
  }
  if (note==27 && value==HIGH) { 
    EL.on(C); 
  } else if (note==27) { 
    EL.off(C); 
  }
  if (note==28 && value==HIGH) { 
    EL.on(D); 
  } else if (note==28) { 
    EL.off(D); 
  }
  if (note==29 && value==HIGH) { 
    EL.on(E); 
  } else if (note==29) { 
    EL.off(E); 
  }
  if (note==30 && value==HIGH) { 
    EL.on(7);  // yeah, it's "7", not F, dunno.
  } else if (note==30) { 
    EL.off(7);   // it's 7, not F.
  }
  if (note==31 && value==HIGH) { 
    EL.on(G); 
  } else if (note==31) { 
    EL.off(G); 
  }
  if (note==32 && value==HIGH) { 
    EL.on(H); 
  } else if (note==32) { 
    EL.off(H); 
  }
}

void blinkAwake() {
  // .--.  .-.  .  ...  .  -.  -.-.  . 
  digitalWrite(10,HIGH);
  delay(100); // .
  digitalWrite(10, LOW);
  delay(100);
  digitalWrite(10,HIGH);
  delay(300); // -
  digitalWrite(10,LOW);
  delay(100);
  digitalWrite(10,HIGH);
  delay(300); // -
  digitalWrite(10,LOW);
  delay(100);
  digitalWrite(10, HIGH);
  delay(100); // .
  digitalWrite(10, LOW);
  delay(300); //letter break
  digitalWrite(10, HIGH);
  delay(300); // .
  digitalWrite(10,LOW);
  delay(100);
  digitalWrite(10, HIGH);
  delay(300); // -
  digitalWrite(10,LOW);
  delay(100);
  digitalWrite(10,HIGH);
  delay(100); // .
  digitalWrite(10,LOW);
  delay(300); // letter break
  digitalWrite(10,HIGH);
  delay(100); // .
  digitalWrite(10,LOW);
  delay(100);
  digitalWrite(10,HIGH);
  delay(100); // .
  digitalWrite(10,LOW);
  delay(100);
  digitalWrite(10,HIGH);
  delay(100); // .
  digitalWrite(10,LOW);
  delay(700); // word end
}

void blinkStatus() {
  digitalWrite(10,HIGH);
  delay(10);
  digitalWrite(10,LOW);
}

void statusGlow(int intOnOff) {
  if (intOnOff) {  // turn on the Status LED
    digitalWrite(10, HIGH);
  } 
  else { // or not.
    digitalWrite(10, LOW);
  }
}

