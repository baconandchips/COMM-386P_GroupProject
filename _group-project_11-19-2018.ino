/*
   PROJECT CODE FOR COMM 386P FINAL PROJECT
   Copyright Guanting, Pammy, Mica, Marco and Nick

   Previously: (Added multitasking abilities- please read Motor.h! Kinda proud of it, it's 100% designed from scratch by yours truly
     Basically, everything below (apart from pitches.h, and the contents of isAtThrehold() and titanic()) are made from scratch)

   Now: regular functions with delay() implemented when needed. Let x be the distance of an object. When photocell below threshold: if 80cm<x<150cm,
     show red light; if 10cm<x<80cm, show green light; if x<10cm, make sound. We had major remake of codebase! See v2 for other implementation, which is 85% complete
   References listed below:
   [1]: https://circuitdigest.com/microcontroller-projects/playing-melodies-on-piezo-buzzer-using-arduino-tone-function
   ^ basically only used their function names, and the header for pitches. Self-designed melodies.
   [2]: https://www.hackster.io/faweiz/arduino-radar-69b8fe
   [3]: https://www.hackster.io/ammaratef45/detecting-obstacles-and-warning-arduino-and-ultrasonic-13e5ea
   ^ above two sources referenced on how to incorporate sonar into my features
   [4]: https://learn.sparkfun.com/tutorials/photocell-hookup-guide/all
   ^ above source helped me with photocell, there were parts I cannot change because they were constants
*/

/*
   MEETING NOTES
   if not dark enough, it could say "come here" or sth
   "enjoy the sunshine"
   "quotes"
*/
#include "pitches.h"  // in case we need sounds
//#include "themes.h"
//#include "motor.h"
//#include <Servo.h>

// -----Constants-----
// Sonar
#define TRIGGER_PIN 11
#define ECHO_PIN 12
#define MAX_DISTANCE 150 // as noted by faweiz, max distance we want to ping for in cm. The specified max is 400-500 cm
#define MID_DISTANCE 80
#define TOUCH_DISTANCE 10
// LED
#define RED_PIN 4
#define GREEN_PIN 5
#define BLUE_PIN 6

// Motor
//#define MOTOR_PIN 9
//motor doesItsOwnThing;

int loopDelayTime = 500; // our delay time in milliseconds
// Photosensor


const float VOLT_INPUT = 5.00;
const float R_DIV = 4660.0; // not going to touch this
const float RTHRESHOLD = 6000.0; //our triggering resistance threshold
const int LIGHT_PIN = A0; // Pin connected to voltage divider output

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("I'm ready!"); // ready for debugging!

  pinMode(TRIGGER_PIN, OUTPUT); // sonar pings from trigger pin
  pinMode(ECHO_PIN, INPUT); // we get our pong'd signal back from here
  pinMode(RED_PIN, OUTPUT); // LED's pin, for flashing
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(10, HIGH);
  digitalWrite(13, LOW);
}

int distance = 80;

int ping() {
  /* DEPRECATED FUNCTION. Works but uses delay(time), replaced with multitask function. UN-DEPRECATED NOW.
     input: nothing. Requires sonar module and
       global constants TRIGGER_PIN, ECHO_PIN
     output: distance of object from sonar, in integer form (int)
  */
  int duration, distance;
  // sonarTime = millis();
  digitalWrite(TRIGGER_PIN, HIGH);
  delay(1); // 1ms delay
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH); // measures how long it took us
  distance = (duration / 2) / 29.1; // the 29.1 is a constant used for our sonar,
  // and we halve the time to get the proper distance
  Serial.println("Distance away: " + String(distance) + "cm");
  return distance;
}

boolean isAtThreshold() {
  /*
     inputs: void, global constants LIGHT_PIN, R_DIV, VOLT_INPUT and RTHRESHOLD
     outputs: lightR>resistance threshold, boolean form
  */
  // checks to see if we have reached resistance threshold from photocell
  int inputValue = analogRead(LIGHT_PIN);
  if (inputValue > 0) {
    // calculate our voltage and resistance!
    // from [4], transcribed
    float lightV = inputValue * VOLT_INPUT / 1023.0;
    float lightR = R_DIV * (VOLT_INPUT / lightV - 1.0);
    Serial.println("Resistance: " + String(lightR) + " ohms? I think");
    return (lightR < RTHRESHOLD);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(loopDelayTime); // loop iteration time
  int distance = ping(); // grab our sonar's readings
  int thresholdAchieved = 0; // for optimizing speed (no repeated function calls), int treated as boolean
  thresholdAchieved = isAtThreshold(); // updates every loop!

  if ((distance <= MAX_DISTANCE) && (distance > MID_DISTANCE)) {
    if (thresholdAchieved) {
      lightHelper(150, 0, 0); // soft red, easier on user's eyes
    }
  } else if ((distance <= MID_DISTANCE) && (distance > TOUCH_DISTANCE)) {
    // changes our color from red to green
    if (thresholdAchieved) {
      lightHelper(0, 150, 0); // soft green, it corresponds to UI where we ask the user to come closer
      // to the cup, and the user walks in for the photo
    }
  } else if (distance <= TOUCH_DISTANCE) {
    if (thresholdAchieved) {
      lightHelper(100, 200, 0);
      // play song!
      void playPowerup(); // smile++
      delay(3200);
      tone(8, NOTE_E6, 125);
      delay(130);
      tone(8, NOTE_G6, 125);
      delay(130);
      tone(8, NOTE_E7, 125);
      delay(130);
      tone(8, NOTE_C7, 125);
      delay(130);
      tone(8, NOTE_D7, 125);
      delay(130);
      tone(8, NOTE_G7, 125);
      delay(125);
      noTone(8);
    }
  } else {
    // outside of range, turn off our light!
    lightHelper(0, 0, 0);
  }

  
}

void lightHelper(int red, int green, int blue) {
  // makes our life easier by reusing code
  Serial.println("in lightHelper, with values (RGB): " + String(red) + ", " + String(green) + ", " + String(blue) + ". ");
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}

void playPowerup() {

}
