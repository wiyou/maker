/**
 * Configure in audrino studio
 * Board type: Pro Mini or Audrino Pro
 * Connnect port: /dev/cu.usbserial-xxxx
 * Use an FTDI programmer
 * Using: Turgiy Tower Pro MG905 micro servers
 * Integrated with: HC-06 Bluetooth LE 
 */
#include <Servo.h>
#include <SoftwareSerial.h>
Servo eyelid;
Servo eyeball;
SoftwareSerial mySerial(6,7); // RX | TX
String BluetoothData = "";
int posLid = 0; 
int posBall = 60;
int maxLeft = 150;
int maxRight = 30;
int maxClose = 174;
int maxOpen = 110;
int ledpin=13;
int EYELID=3;
int EYEBALL=4;

void setup() {
   Serial.begin(9600);
   Serial.println("Enter AT commands:");
 
    // HC-06 default serial speed is 9600
    mySerial.begin(9600);  

    pinMode(ledpin,OUTPUT);
    //attach servo to pin.
    eyelid.attach(EYELID);
    eyeball.attach(EYEBALL);
    
    eyeball.write(posBall);
    eyelid.write(maxClose);
}

void loop() {
    while (mySerial.available()) {                    // loop through while data is available
      char character = mySerial.read(); // Receive a single character from the software serial port
      BluetoothData.concat(character); // Add the received character to the receive buffer
      if (character == '\n')
      {
          Serial.print("Received: ");
          Serial.println(BluetoothData);
          int val = BluetoothData.toInt();
         if(val==1) { // if number 1 pressed ….blink
          blinkEye(3);
          openEyeNormal(2);
          Serial.println("Blink");
         }
        if( val==2) { // if number 2 pressed ….Wakeup
          Serial.println("Wake Up");
          Serial.print(posLid); Serial.println(" Lid position");
          book();
        }
         if( val==3) { // if number 3 pressed ….Sleep
          Serial.println("Sleep ");
          sleepEye();
        }
          if( val==4) { // if number 3 pressed ….Sleep
          Serial.println("Amok ");
          wakeup();
        }
          if( val==5) { // if number 3 pressed ….Sleep
          Serial.println("Open ");
          openEye(3);
          openEyeNormal(2);
        }
        if( val >= 30) {
          Serial.print("Eye move ");
          Serial.println(val);
          if(posBall >= val) {
            moveEyeBallRight(val,5);
          } else {
            moveEyeBalLeft(val,5);
          }
       }
          BluetoothData = "";
      }
        //            }
                                     

       /**/
    } 
}

void moveEyeBallCenter(int spd) {
   if(posBall < 90) {
    for (; posBall <= 90; posBall += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      eyeball.write(posBall);              // tell servo to go to position in variable 'pos'
      delay(spd);                       // waits 15ms for the servo to reach the positio 
   }
   if(posBall > 90) {
    for (; posBall >= 90; posBall -= 1) { // goes from 180 degrees to 0 degrees
     eyeball.write(posBall);              // tell servo to go to position in variable 'pos'
     delay(spd);                       // waits 15ms for the servo to reach the position
    } 
   }
   posBall = 90;
   }
}

void moveEyeBalLeft(int finalPos, int spd)
{
   for (; posBall <= finalPos; posBall += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
     eyeball.write(posBall);              // tell servo to go to position in variable 'pos'
     delay(spd);                       // waits 15ms for the servo to reach the position
   }
}

void moveEyeBallRight(int finalPos, int spd){
 for (; posBall >= finalPos; posBall -= 1) { // goes from 180 degrees to 0 degrees
     eyeball.write(posBall);              // tell servo to go to position in variable 'pos'
     delay(spd);                       // waits 15ms for the servo to reach the position
   }
}

void book() {
  if(posLid<=maxOpen-20) {
    shutEye(4);
    moveEyeBallCenter(4);
  }
    for (; posLid >= 130; posLid -= 1) { // goes from 0 degrees to 180 degrees
      eyelid.write(posLid);              // tell servo to go to position in variable 'pos'
      delay(3);
    }
    shutEye(10);
    for (; posLid >= 130; posLid -= 1) { // goes from 0 degrees to 180 degrees
      eyelid.write(posLid);              // tell servo to go to position in variable 'pos'
      delay(3);
    }
    openEyeNormal(4);
    for(int cnt=0; cnt<5; cnt++) {
      moveEyeBalLeft(maxLeft,4);
      delay(1000);
      moveEyeBallRight(maxRight,4);
    }
    moveEyeBallCenter(4);    
}    

  void wakeup() {
    if(posLid<=maxOpen-30) {
      shutEye(4);
      moveEyeBallCenter(4);
    }
    for (; posLid >= 145; posLid -= 1) { // goes from 0 degrees to 180 degrees
      eyelid.write(posLid);              // tell servo to go to position in variable 'pos'
      delay(5);
    }
    for(int cnt=0; cnt<3; cnt++) {
      moveEyeBalLeft(maxLeft-10,10);
      delay(500);
      moveEyeBallRight(maxRight+10,10);
      delay(500);
    }
    shutEye(10);
    for (; posLid >= 130; posLid -= 1) { // goes from 0 degrees to 180 degrees
      eyelid.write(posLid);              // tell servo to go to position in variable 'pos'
      delay(3);
    }
    openEyeNormal(4);
    for(int cnt=0; cnt<2; cnt++) {
      moveEyeBalLeft(maxLeft,4);
      delay(1000);
      moveEyeBallRight(maxRight,4);
    }
    moveEyeBallCenter(4);       
}

void sleepEye(void) {
  moveEyeBallCenter(4); 
  blinkEye(3); 
  for (; posLid <= 150; posLid += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
     eyelid.write(posLid);              // tell servo to go to position in variable 'pos'
     delay(14);                       // waits 15ms for the servo to reach the position
   }
   openEyeNormal(3);
   shutEye(10);
}

void shutEye(int spd) {
     for (; posLid <= maxClose; posLid += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
     eyelid.write(posLid);              // tell servo to go to position in variable 'pos'
     delay(spd);                       // waits 15ms for the servo to reach the position
   }
}

void closeEye(int spd, int closeDistance) {
     for (; posLid <= closeDistance; posLid += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
     eyelid.write(posLid);              // tell servo to go to position in variable 'pos'
     delay(spd);                       // waits 15ms for the servo to reach the position
   }
}

void openEye(int spd){
  for (; posLid >= maxOpen-5; posLid -= 1) { // goes from 180 degrees to 0 degrees
     eyelid.write(posLid);              // tell servo to go to position in variable 'pos'
     delay(spd);                       // waits 15ms for the servo to reach the position
   }
}

void openEyeNormal(int spd){
  if(posLid <= maxOpen) {
    closeEye(5, 140);
  }
  for (; posLid >= 120; posLid -= 1) { // goes from 180 degrees to 0 degrees
     eyelid.write(posLid);              // tell servo to go to position in variable 'pos'
     delay(spd);                       // waits 15ms for the servo to reach the position
   }
}

void blinkEye(int spd) {
    if(posLid < 150) {
      shutEye(spd);
      openEye(spd);
    } else {
      openEye(spd);
    }
}
