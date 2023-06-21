#include <SoftwareSerial.h>

void setup() {
  //Initialize serial ports
  Serial.begin(9600); //USB Serial Port 0
  pinMode(8, OUTPUT);
}

void loop() {
  String msg = "";
  //check for data byte on USB Serial Port
  if (Serial.available()) {
    //get byte from USB Serial Port
    while(Serial.available()) {
      msg = Serial.readString(); //Read the incoming data as string
 
      if(msg == "1") {
        digitalWrite(8, HIGH);
        delay(1000);
      }

      else if(msg=="2") {
        digitalWrite(8, LOW);
        delay(1000);
      }

      else if(msg=="3") {
        for(int i=0; i<=2; i++) {
          digitalWrite(8, HIGH);
          delay(500);
          digitalWrite(8, LOW);
          delay(500);
        }
      }

      else if(msg=="0") {
        exit(0);
      }
      
      else {
        //Send data to usb serial port
        Serial.write("Please send correct message\n");
      }
    }
  } 
}
