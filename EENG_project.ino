#include <HCSR04.h>
//pin decalartion for motors 
#define PWM1 5
#define PWM2 6
#define AIN1 7
#define AIN2 8
#define BIN1 4
#define BIN2 9
#define EN1 A0
#define EN2 A1
//pin declaration for ultrasonic 
#define trig_mid 45
#define echo_mid 44
#define trig_left 47
#define echo_left 46
#define trig_right 49
#define echo_right 48
#define threshold_dis 15
UltraSonicDistanceSensor distanceSensorMid(trig_mid, echo_mid);
UltraSonicDistanceSensor distanceSensorLeft(trig_left, echo_left);
UltraSonicDistanceSensor distanceSensorRight(trig_right, echo_right);
//pin declaration for ir sensors 
#define ir_right A9
#define ir_left A8
#define ir_middle A10
#define threshold 100

//pin declarations for colour sensor
#define S2 2
#define S3 3
#define OUT 13
int frequency;
String detectedcolor= " ";

const int redThresh = 300;
const int greenThresh = 350;
const int blueThresh = 400;


 
void setup(){
// pin mode for motors 
pinMode(AIN1,OUTPUT);
pinMode(AIN2,OUTPUT);
pinMode(PWM1,OUTPUT);
pinMode(A0,OUTPUT); 
pinMode(BIN1,OUTPUT);
pinMode(BIN2,OUTPUT);
pinMode(PWM2,OUTPUT);
pinMode(A1,OUTPUT);

// pin mode for ultrasonic 
pinMode(trig_mid, OUTPUT);
pinMode(echo_mid, INPUT);
pinMode(trig_left, OUTPUT);
pinMode(echo_left, INPUT);
pinMode(trig_right, OUTPUT);
pinMode(echo_right, INPUT);

// pin mode for ir sensors 
pinMode(ir_right,INPUT);
pinMode(ir_left,INPUT);
pinMode(ir_middle,INPUT);

// pin mode for colour sensor 
pinMode(S2, OUTPUT);
pinMode(S3, OUTPUT);
pinMode(OUT, INPUT);


Serial.begin(9600); 
}
// functions for the movement 
void moveForward()
{
  digitalWrite(A0,HIGH);
  digitalWrite(AIN1,HIGH); //Motor will rotate in one direction
  digitalWrite(AIN2,LOW);
  analogWrite(PWM1,125); //Speed control of Motor A// put your main code here, to run repeatedly:
  digitalWrite(A1,HIGH);
  digitalWrite(BIN1,HIGH); //Motor will rotate in one direction
  digitalWrite(BIN2,LOW);
  analogWrite(PWM2,125);
}

void moveBackward()
{
  digitalWrite(A0,HIGH);
  digitalWrite(AIN1,LOW); //Motor will rotate in one direction
  digitalWrite(AIN2,HIGH);
  analogWrite(PWM1,125); //Speed control of Motor A// put your main code here, to run repeatedly:
  digitalWrite(A1,HIGH);
  digitalWrite(BIN1,LOW); //Motor will rotate in one direction
  digitalWrite(BIN2,HIGH);
  analogWrite(PWM2,125); 
}

void moveRight()
{
  digitalWrite(A0,HIGH);
  digitalWrite(AIN1,HIGH); //Motor will rotate in one direction
  digitalWrite(AIN2,LOW);
  analogWrite(PWM1,125); //Speed control of Motor A// put your main code here, to run repeatedly:
  digitalWrite(A1,HIGH);
  digitalWrite(BIN1,LOW); //Motor will rotate in one direction
  digitalWrite(BIN2,HIGH);
  analogWrite(PWM2,50);
  
}

void moveleft()
{
  digitalWrite(A0,HIGH);
  digitalWrite(AIN1,LOW); //Motor will rotate in one direction
  digitalWrite(AIN2,HIGH);
  analogWrite(PWM1,125); //Speed control of Motor A// put your main code here, to run repeatedly:
  digitalWrite(A1,HIGH);
  digitalWrite(BIN1,HIGH); //Motor will rotate in one direction
  digitalWrite(BIN2,LOW);
  analogWrite(PWM2,50);
}

void stopMoving()
{
  digitalWrite(A0,LOW);
  digitalWrite(AIN1,LOW); //Motor will rotate in one direction
  digitalWrite(AIN2,LOW);
  analogWrite(PWM1,0); //Speed control of Motor A// put your main code here, to run repeatedly:
  digitalWrite(A1,LOW);
  digitalWrite(BIN1,LOW); //Motor will rotate in one direction
  digitalWrite(BIN2,LOW);
  analogWrite(PWM2,0);
}

void rotate180() {
    Serial.println("Rotating 180 degrees...");
    stopMoving();       // Ensure the robot is stationary before rotating
    moveRight();          // Or moveLeft(), depending on your robot's setup
    delay(1000);          // Adjust the delay for a complete 180° turn
    //stopMoving();       // Stop the robot after rotation
}


//function to return the colour detected by the colour sensor 
// String detectColor()
// {
//   digitalWrite(S2, LOW);
//   digitalWrite(S3, LOW);
//   frequency = pulseIn(OUT, LOW);
//   if (frequency < redThresh) 
//   {
//     return "red";
//   }
//   digitalWrite(S2, LOW);
//   digitalWrite(S3, HIGH);
//   frequency = pulseIn(OUT, LOW);
//   if (frequency < blueThresh) 
//   {
//     return "blue";
//   }
//   digitalWrite(S2, HIGH);
//   digitalWrite(S3, HIGH);
//   frequency = pulseIn(OUT, LOW);
//   if (frequency < greenThresh) 
//   {
//     return "green";
//   }
//   digitalWrite(S2, HIGH);
//   digitalWrite(S3, LOW);
//   frequency = pulseIn(OUT, LOW);
//   if (frequency > greenThresh) 
//   {
//     return "black";
  // }
  // return "unknown";


// }


void loop(){

  // print the  IR sensor values 
  int sensor_valueright = analogRead(ir_right);
  Serial.print("right :");
  Serial.println(sensor_valueright);

  int sensor_valueleft = analogRead(ir_left);
  Serial.print("left :");
  Serial.println(sensor_valueleft);

  int sensor_valuemiddle = analogRead(ir_middle);
  Serial.print("middle :");
  Serial.println(sensor_valuemiddle);

  //check the threshold and move the robot accordingaly 
  if (sensor_valueright<threshold && sensor_valuemiddle > threshold && sensor_valueleft<threshold )
  {
    moveForward();
  }
  else if (sensor_valueright < threshold && sensor_valuemiddle < threshold && sensor_valueleft >= threshold )
  {
    moveleft();
  }
  else if (sensor_valueright >= threshold && sensor_valuemiddle < threshold && sensor_valueleft < threshold )
  {
    moveRight();
  }
  // else 
  // {
  //   stopMoving();
  // }

//print ultrasonic distances 
  Serial.print("Mid distance :");
  Serial.println(distanceSensorMid.measureDistanceCm());
  Serial.print("left distance :");
  Serial.println(distanceSensorLeft.measureDistanceCm());
  Serial.print("right distance :");
  Serial.println(distanceSensorRight.measureDistanceCm());
  // put your main code here, to run repeatedly:
  
  int mid_dist = distanceSensorMid.measureDistanceCm();
  int left_dist = distanceSensorLeft.measureDistanceCm();
  int right_dist = distanceSensorRight.measureDistanceCm();
//check the distance and move the robot accordingaly 
// if (mid_dist < threshold_dis && left_dist+right_dist >=40 ) 
// {

//     // Dead end detected
//     // Serial.println("Dead end detected. Rotating to follow path back.");
//     moveBackward();
//     delay(500);
//     rotate180();

// } else 
if (mid_dist < threshold_dis) {
    // Obstacle directly ahead

    moveBackward();
    delay(100);
    if (right_dist > left_dist) 
    {
        moveRight();
    } 
    else 
    {
        moveleft();
    }
    delay(500);
} 
else if (right_dist < threshold_dis   && left_dist >= threshold_dis ) 
{
    // Obstacle on the right

    moveleft();
    delay(500);
} else if (left_dist < threshold_dis && right_dist >= threshold_dis) 
{
    // Obstacle on the left
    moveRight();
    delay(500);
} 
else 
{
    // Path is clear

    moveForward();
}
  // if (mid_dist < threshold_dis ) 
  // {
    
  //   moveBackward();
  //   delay(100);
  //   moveRight();
  //   delay(100);

  // }
  // else if (right_dist < threshold_dis)
  // {
  //   moveleft();
  //   delay(100);
  // }
  // else if (left_dist < threshold_dis)
  // {
  //   moveRight();
  //   delay(100);
  // }
  // else 
  // {
  //   moveForward();
  // }

  // //detect the colour and move accordingaly 
  // detectedcolor = detectColor();
  
  // if (detectedcolor == "blue")
  // {
  //   moveForward();
  // }
  // else if (detectedcolor == "red")
  // {
  //   moveBackward();
  // }
  // else if (detectedcolor == "black")
  // {
  //   moveForward();
  // }
  // else 
  // {
  //   stopMoving();
  // }

// delay(100);
 

}

