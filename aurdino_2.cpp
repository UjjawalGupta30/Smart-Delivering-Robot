#include <IRremote.h>
#include <Servo.h>

/* define IR sensor pin */
int IRsensorPin = 9;

/* define the some functions used by the library */
IRrecv irrecv(IRsensorPin);
decode_results results;

Servo myservo;
/* define L298N motor drive control pins */
int RightMotorForward = 2;    // IN1
int RightMotorBackward = 3;   // IN2
int LeftMotorForward = 4;     // IN3
int LeftMotorBackward = 7;    // IN4
int servoPin = 8;
void setup(){
  
  /* initialize motor control pins as output */
  pinMode(LeftMotorForward,OUTPUT);
  pinMode(RightMotorForward,OUTPUT);
  pinMode(LeftMotorBackward,OUTPUT);
  pinMode(RightMotorBackward,OUTPUT);
  myservo.attach(servoPin);
  irrecv.enableIRIn();
}

void loop(){
  
  /* if the sensor is receive any signal */
  if (irrecv.decode(&results)){

    irrecv.resume();
  }
 
  if(results.value == 0xFD50AF) MotorForward();
  if(results.value == 0xFD10EF) MotorBackward();
  if(results.value == 0xFD20DF) TurnRight();
  if(results.value == 0xFD609F) TurnLeft();
  if(results.value == 0xFD00FF) MotorStop();
  if(results.value == 0xFD08F7) LidClose();
  if(results.value == 0xFD8877) LidOpen();

}

void LidClose(){

  myservo.write(0);
  delay(250);
}

void LidOpen(){

  myservo.write(90);
  delay(250);
}

/* FORWARD */
void MotorForward(){

  digitalWrite(LeftMotorForward,HIGH);
  digitalWrite(RightMotorForward,HIGH);
  digitalWrite(LeftMotorBackward,LOW);
  digitalWrite(RightMotorBackward,LOW); 
}

/* BACKWARD */
void MotorBackward(){

  digitalWrite(LeftMotorBackward,HIGH);
  digitalWrite(RightMotorBackward,HIGH);
  digitalWrite(LeftMotorForward,LOW);
  digitalWrite(RightMotorForward,LOW);
}

/* TURN RIGHT */
void TurnRight(){
 
  digitalWrite(LeftMotorForward,HIGH); 
  digitalWrite(RightMotorForward,LOW);
  digitalWrite(LeftMotorBackward,LOW);
  digitalWrite(RightMotorBackward,HIGH);
 
}

/* TURN LEFT */
void TurnLeft(){

  digitalWrite(RightMotorForward,HIGH);  
  digitalWrite(LeftMotorForward,LOW);
  digitalWrite(LeftMotorBackward,HIGH);
  digitalWrite(RightMotorBackward,LOW);

}

/* STOP */
void MotorStop(){

  digitalWrite(LeftMotorBackward,LOW);
  digitalWrite(RightMotorBackward,LOW);
  digitalWrite(LeftMotorForward,LOW);
  digitalWrite(RightMotorForward,LOW);
}

