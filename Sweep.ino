/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>


//pin9 rudder
//pin10 11 thingy

Servo myservo0;  // create servo object to control a servo
// twelve servo objects can be created on most boards
Servo myservo1;
Servo myservo2; 

int ByteReceived;

int pos = 0;    // variable to store the servo position

void setup() {
  myservo0.attach(9);// attaches the servo on pin 9 to the servo object
  myservo1.attach(10);
  myservo2.attach(11);
  Serial.begin(9600);
  Serial.println("--- Start Serial Monitor SEND_RCVE ---");
  Serial.println(" Type in Box above, . ");
  Serial.println("(Decimal)(Hex)(Character)");  
  Serial.println(); 
  myservo1.write(90);
  myservo2.write(0);

}

void rotate_servos() {
    int possec;
    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of  1 degree
    possec = 90 - pos;
    myservo1.write(possec);
    myservo2.write(pos);// tell servo to go to position in variable 'pos'
    delay(2);                       // waits 15ms for the servo to reach the position
  }

  for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    possec = (90-pos);
    myservo1.write(possec);
    myservo2.write(pos);// tell servo to go to position in variable 'pos'
    delay(2);                       // waits 15ms for the servo to reach the position
  }
}


void loop() {
  if (Serial.available() > 0)
  {
    ByteReceived = Serial.read();
    Serial.print(ByteReceived);   
    Serial.print("        ");      
    Serial.print(ByteReceived, HEX);
    Serial.print("       ");     
    Serial.print(char(ByteReceived));
    if(ByteReceived == '1') // Single Quote! This is a character.
    {
      rotate_servos();
      myservo1.write(90);
      myservo2.write(0);
      Serial.print(" LED ON ");
    }
    if(ByteReceived == '2')
    {
     myservo0.write(0);
    }
    if(ByteReceived == '3')
    {
    myservo1.write(90);
      myservo2.write(0);
      }
    if(ByteReceived == '4')
    {
      myservo0.write(90);
    }
    Serial.println();    // End the line

  // END Serial Available
  }

}
