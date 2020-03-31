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
int BluetoothData; // the data given from Computer
int posLid = 0; 
int posBall = 0;
int maxLeft = 150;
int maxRight = 30;
int maxClose = 180;
int maxOpen = 30;
int ledpin=13;
int EYELID=3;
int EYEBALL=4;

void setup() {
   Serial.begin(9600);
   Serial.println("Enter AT commands:");
 
    // HC-06 default serial speed is 9600
    mySerial.begin(9600);  

    pinMode(ledpin,OUTPUT);
    
  eyelid.attach(EYELID);
  eyeball.attach(EYEBALL);
  // put your setup code here, to run once:
  //pinMode(LED_BUILTIN, OUTPUT);
  eyeball.write(maxRight);
  eyelid.write(maxClose);
}

void loop() {
   if (mySerial.available())
    {
        BluetoothData = mySerial.read();
        Serial.write(BluetoothData);
        if(BluetoothData=='1') { // if number 1 pressed ….blink
          blinkEye(5);
          Serial.println("Blink");
       }
        if(BluetoothData=='2') { // if number 2 pressed ….Wakeup
          Serial.println("Wake Up");
          Serial.print(posLid); Serial.println(" Lid position");
          wakeUp();
        }
         if(BluetoothData=='3') { // if number 3 pressed ….Sleep
          Serial.println("Sleep ");
          closeEye(10);
        }
          if(BluetoothData=='4') { // if number 3 pressed ….Sleep
          Serial.println("Amok ");
          closeEye(10);
        }
          if(BluetoothData=='5') { // if number 3 pressed ….Sleep
          Serial.println("Open ");
          openEye(4);
        }
    }
     
 // delay(100);// prepare for next data …
 /*openEye(5);
 Serial.println("open:");
 delay(1000);
 closeEye(5);
 Serial.println("close:");
 delay(2000);
 
 blinkEye(4);
 delay(3000);*/
 /*openEye(5);
  moveEyeBalLeft(maxLeft,10);
  delay(3000);  
  moveEyeBallRight(0,10);
  closeEye(5);
 // delay(4000);
  //moveEyeBallCenter(5);
  //blinkEye(5);
  // blinkEye(4);
  delay(1000);
 // wakeUp();
  delay(3000);*/
 
  
}

void moveEyeBallCenter(int spd) {
   if(posBall < 90) {
    for (; posBall <= 90; posBall += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      eyeball.write(posBall);              // tell servo to go to position in variable 'pos'
      delay(spd);                       // waits 15ms for the servo to reach the position
    }
   }
   if(posBall > 90) {
    for (; posBall >= 90; posBall -= 1) { // goes from 180 degrees to 0 degrees
     eyeball.write(posBall);              // tell servo to go to position in variable 'pos'
     delay(spd);                       // waits 15ms for the servo to reach the position
    } 
   }
   posBall = 90;
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

void wakeUp() {
  if(posLid=maxOpen) {
    closeEye(4);
    moveEyeBallCenter(4);
    for (; posLid >= 70; posLid -= 1) { // goes from 0 degrees to 180 degrees
      eyelid.write(posLid);              // tell servo to go to position in variable 'pos'
      delay(3);
    }
    closeEye(10);
    for (; posLid >= 70; posLid -= 1) { // goes from 0 degrees to 180 degrees
      eyelid.write(posLid);              // tell servo to go to position in variable 'pos'
      delay(3);
    }
    openEye(4);
    for(int cnt=0; cnt<5; cnt++) {
      moveEyeBalLeft(maxLeft,5);
      moveEyeBallRight(maxRight,5);
    }
    moveEyeBallCenter(4);
  }        
}

void closeEye(int spd) {
     for (; posLid <= maxClose; posLid += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
     eyelid.write(posLid);              // tell servo to go to position in variable 'pos'
     delay(spd);                       // waits 15ms for the servo to reach the position
   }
}

void openEye(int spd){
  for (; posLid >= maxOpen; posLid -= 1) { // goes from 180 degrees to 0 degrees
     eyelid.write(posLid);              // tell servo to go to position in variable 'pos'
     delay(spd);                       // waits 15ms for the servo to reach the position
   }
}

void blinkEye(int spd) {
    if(posLid < 90) {
      closeEye(spd);
      openEye(spd);
    } else {
      openEye(spd);
    }
}
