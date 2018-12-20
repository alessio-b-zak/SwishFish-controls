#include <Servo.h>
#include <TimedAction.h>


//pin9 rudder
//pin10 11 thingy

Servo myservo0;  // create servo object to control a servo
// twelve servo objects can be created on most boards
Servo myservo1;
Servo myservo2;

int ByteReceived;

int turn;
int forward;



void read_serial() {
  if (Serial.available() > 0)
    {
        ByteReceived = Serial.read();
        Serial.print(ByteReceived);
        Serial.print("        ");
        Serial.print(ByteReceived, HEX);
        Serial.print("       ");
        Serial.print(char(ByteReceived));
        if(ByteReceived == '2') // Single Quote! This is a character.
        {
            forward = 1;
            turn = 1;
        }
        if(ByteReceived == '1')
        {
          turn = 0;
          forward = 1;
        }
        if(ByteReceived == '0')
        {
          turn = 2;
          forward = 1;
        }
        if(ByteReceived == '3')
        {
          forward = 0;
        }
}
}

void rotate_flippers() {
  if (forward == 1) {
    rotate_servos();
    myservo1.write(90);
    myservo2.write(0);
  }
}

void turn_flipper() {
  if (turn == 1) {
      myservo0.write(90);
  }
    if (turn == 0) {
      myservo0.write(180);
  }
    if (turn == 2) {
      myservo0.write(0);
  }
}

char data = 0; // From BTs

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
    pinMode(13, OUTPUT);

}

void flash_led(int n) {
    for(int i = 0; i < n; i++) {
        digitalWrite(13, HIGH);
        delay(100);
        digitalWrite(13, LOW);
        delay(100);
    }
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


TimedAction turnforward = TimedAction(100, rotate_flippers);
TimedAction turnturn = TimedAction(100, turn_flipper);
TimedAction readserial = TimedAction(100, read_serial);

void loop() {
  readserial.check();
  turnforward.check();
  turnturn.check();  
}
