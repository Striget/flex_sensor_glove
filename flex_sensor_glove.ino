// Flex sensor glove -project
// Kajaani University of Applied Sciences
// Miika Laeslehto
// KKT18S

#include <Servo.h>  // Servo library
Servo thumb;        // Thumb finger servo
Servo index;        // Index finger servo
Servo middle;       // Middle finger servo
Servo ring;         // Ring finger servo
Servo little;       // Little finger servo 

const int servoMin[5] = {0, 10, 0, 110, 130};       // minimum value for each finger
const int servoMax[5] = {90, 90, 90, 15, 45};       // maximum value for each finger
const int analogMin[5] = {690, 690, 740, 705, 740}; // minimum read from sensor
const int analogMax[5] = {765, 830, 840, 840, 875}; // maximum read from sensor
const int mapMin = 0;                               // Minimum value for mapping
const int mapMax[5] = {75, 140, 100, 135, 135};     // Maximum value for mapping

void setup() {
  Serial.begin(9600);   // Serial monitor
  pinMode(A0, INPUT);   // Thumb Finger read
  pinMode(A1, INPUT);   // Index Finger read
  pinMode(A2, INPUT);   // Middle Finger read
  pinMode(A3, INPUT);   // Ring Finger read
  pinMode(A4, INPUT);   // Little Finger read
  
  pinMode(3, OUTPUT);   // Thumb Finger    
  pinMode(5, OUTPUT);   // Index Finger
  pinMode(6, OUTPUT);   // Middle Finger
  pinMode(9, OUTPUT);   // Ring Finger
  pinMode(10, OUTPUT);  // Little Finger
  
  thumb.attach(3);      // Define servos
  index.attach(5);  
  middle.attach(6); 
  ring.attach(9);   
  little.attach(10); 
  
  thumb.write(servoMin[0]);       // Reset Servos to starting position
  index.write(servoMin[1]);    
  middle.write(servoMin[2]);   
  ring.write(servoMin[3]);     
  little.write(servoMin[4]);
}

void loop() {  
  // Servo order
  // 0 = thumb
  // 1 = index
  // 2 = middle
  // 3 = ring
  // 4 = little
  int fingerServo[5] = {analogRead(A0), analogRead(A1), analogRead(A2), analogRead(A3), analogRead(A4)}; // Read finger position

  // Change analogRead values writable to each servo
  for(int i = 0; i < 5; i++){
    fingerServo[i] = map(fingerServo[i], analogMin[i], analogMax[i], mapMin, mapMax[i]); // Change value 575-825 from flex resistor to 0-250
    if(fingerServo[i] < mapMin){  // Change everything below 0 to 0
      fingerServo[i] = mapMin;
    }
    else if(fingerServo[i] > mapMax[i]){ // Change all values from over 250 to 250
      fingerServo[i] = mapMax[i];
    } 
    fingerServo[i] = map(fingerServo[i], mapMin, mapMax[i], servoMin[i], servoMax[i]); // map value 0-250 usabe for each servo's own min and max values
  }
  
  thumb.write(fingerServo[0]);  // Rotate finger servos
  index.write(fingerServo[1]);
  middle.write(fingerServo[2]);
  ring.write(fingerServo[3]);
  little.write(fingerServo[4]);
  
  Serial.println(fingerServo[0]);
  Serial.println(fingerServo[1]);
  Serial.println(fingerServo[2]);
  Serial.println(fingerServo[3]);
  Serial.println(fingerServo[4]);
  Serial.println("---------------");

  delay(10);  // delay for stability
}
