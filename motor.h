/*
 * MOTOR FUNCTIONS
 * Designed by Guanting, looked at reference from adafruit.com
 * uses millis() to help multitask things, written entirely from scratch
 * [1]: https://learn.adafruit.com/multi-tasking-the-arduino-part-1/a-clean-sweep
*/

#include <Servo.h> // Servo main functions, inside library
//#include <string> // allows me to type strings

class motor {
	Servo uMotor; // short for umbrella motor
	
	int pos = 0;
	int isSonarTriggered = 0;
	int conditionFulfilled = 0;
	int delayLength = 10; // for safety purposes
	int functionToChoose = 0;
	int loopTimes = 0;
	int delta = 1;
	unsigned long previousTime = 0;
	
	int swivelNumber = 1;
	
	private: 
		void reset() {
			// initializes motor, also resets things
			// comes with built-in 100ms system hang
      pos = 1;
			uMotor.write(pos); // writes where our motor's head is
			delay(100);
			previousTime = millis(); // just for safekeeping purposes
			swivelNumber = 1; // resets the number of loops since initialization
		}
		
		int isConditionFulfilled() {
			// checks if we can run our motor
			return ((millis() - previousTime) > delayLength);
		}
	
	public:
		void Attach(int pin) {
      uMotor.attach(pin);
		}

    void Detach() {
      uMotor.detach();
    }
    
		void setFunction(int delayTime, String s, int numberOfRevolutions) {
			// sets our functions with how long delay is, what function to use,
			// and how many iterations to do this action for
			
			delayLength = delayTime; // sets our delay time
			reset(); // clears things out
			if (s == "swivel") {
				functionToChoose = 1;
				loopTimes = numberOfRevolutions;
				delta = 1;
			}
			if (s == "shortswivel") {
				functionToChoose = 2;
				loopTimes = numberOfRevolutions;
				delta = 1;
			}
			if (s == "perpetualswivel") {
				functionToChoose = 1;
				loopTimes = 32767; // max value of arduino int; gg if this runs out
				delta = 1;
			}

      if (s == "perpetualshortswivel") {
        functionToChoose = 2;
        loopTimes = 32767;
        delta = 1;
      }
		}
		
		void update() {
			// main function for actions, iterative calls mean that things
			// would need to be pretty separated
			if (isConditionFulfilled()) {
				previousTime = millis();
				// delay time is met, perform action according to what was set
				if (functionToChoose == 0) {
					// do nothing
				}
				else if (loopTimes > 0) {
					// we can still do actions with our loop!
					if (functionToChoose == 1) {
						// swivel, see below to see non-multitasking solution
						
						if (pos == 0) {
              delta = 1;
              loopTimes--; // stops this function
              pos = 1; // reset the head
              Serial.println("Swivel number " +  String(swivelNumber) + " completed!");
              swivelNumber++;
						}
						if (pos < 180) {
							pos += delta; // change position
						}
						if (pos >= 180) {
							delta = -delta;
              pos += delta;
						}
						uMotor.write(pos);
					}
					if (functionToChoose == 2) {
            if (pos == 1) {
              // initial state
              pos = 61;
              uMotor.write(pos);
            }
						if (pos == 60) {
              delta = 1;
              loopTimes--; // stops this function
              pos = 61; // reset the head
              Serial.println("Short swivel number " +  String(swivelNumber) + " completed!");
              swivelNumber++;
            }
            if (pos < 120) {
              pos += delta; // change position
            }
            if (pos >= 120) {
              delta = -delta;
              pos += delta;
            }
            uMotor.write(pos);
					}
				}
				else {
					loopTimes = 0; // just making sure it's not negative
					functionToChoose = 0; // do nothing now!
          Serial.println("Gonna do nothing now");
				}
			}
			
		}
		
		
		/*
		* DEPRECATED FUNCTIONS BELOW
		* No longer compatible with multitasking, but may be fun to have
		* Can still function! It just hangs the system from everything else
		* May also help readers understand what update() was trying to do
		*/
		void revolve(int times, int delayTime) {
			/*
			* Inputs: times, the number of revolutions.
			*         delayTime, the amount of delay between each step (in milliseconds)
			* Outputs: void. revolutions in stepper motor
			* Rotates a user-specified number of times, with delay in between.
      * DOES NOT WORK. MOTOR ONLY RECOGNIZES 0-180 DEGREES.
			*/
			
			for (int i=times; i>0; i--) {
				for (pos=0; pos<=360; pos++) {
					uMotor.write(pos);
					delay(delayTime);
				}
			}
		}
		
		void swivel(int delayTime) {
			/*
			* Inputs: delayTime, the amount of delay between each step (in milliseconds)
			* Outputs: void. revolutions in stepper motor
			* Rotates 180 degrees clockwise, then 180 degrees counterclockwise.
			*/
			for (pos=0; pos<=180; pos++) {
				uMotor.write(pos);
				delay(delayTime);
			}
			for (pos=180; pos>=0; pos--) {
				uMotor.write(pos);
				delay(delayTime);
			}
		}
};
