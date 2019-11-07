#include "main.h"

//RIGHT AND LEFT BASED ON LOOKING AT THE ROBOT FROM THE BACK

//defines the ports for each motor and encoder
#define MOTOR1 2 //L1
#define MOTOR2 3 //L2
#define MOTOR3 14 //R1
#define MOTOR4 13 //R2

//CHANGE PORT NUMBERS LATER
#define MOTOR5 15 //Angler
#define MOTOR6 5 //Arm
#define MOTOR7 8 //intakeL
#define MOTOR8 17 //intakeR

/*DO WE NEED ENCODERS???

#define ENCODERLT 1
#define ENCODERLB 2
#define ENCODERRT 3
#define ENCODERRB 4
#define ENCODERCT 5
#define ENCODERCB 6

  WILL NEED TO DEFINE THE PORTS FOR THE OTHER MOTORS, SENSORS, ETC.

*/

void drive() {

	//defines the ports that are associated with each wheel
	pros::Motor left_wheels_1 (MOTOR1, 0);
	pros::Motor right_wheels_1 (MOTOR3, 1);
	pros::Motor left_wheels_2 (MOTOR2, 1);
	pros::Motor right_wheels_2 (MOTOR4, 0);

	//defines controller
	pros::Controller master (CONTROLLER_MASTER);

	//loop reads the joystick controlls and powers the motors accordingly
	while (true) {
		int powerLeft = master.get_analog(ANALOG_LEFT_Y);
		int powerRight = master.get_analog(ANALOG_RIGHT_Y);
		//If there is a small difference, then program will assume person wants to go straight and will set pwoer to motors as equal
		if((powerLeft - powerRight) >= -7 && (powerLeft - powerRight) <= 7){ //CHANGE VALUES LATER
			powerLeft = powerRight;
		}
		left_wheels_1.move(powerLeft);
		left_wheels_2.move(powerLeft);
		right_wheels_1.move(powerRight);
		right_wheels_2.move(powerRight);
		pros::delay(20);
	}
}

void LiftingApparatus(){
	pros::Motor intake_left (MOTOR7, 0);
	pros::Motor intake_right (MOTOR8, 1);
	pros::Motor angler (MOTOR5, 1);
	pros::Motor arm (MOTOR6, 1);

	//defines controller
	pros::Controller master (CONTROLLER_MASTER);
	/*
	pros::Controller r1 (E_CONTROLLER_DIGITAL_R1);
	pros::Controller l1 (E_CONTROLLER_DIGITAL_L1);
	pros::Controller aUp (E_CONTROLLER_DIGITAL_R2);
	pros::Controller aDown (E_CONTROLLER_DIGITAL_L2);
	pros::Controller armUp (E_CONTROLLER_DIGITAL_UP);
	pros::Controller armDown (E_CONTROLLER_DIGITAL_DOWN);
	*/


	int intake_power = 20; //SET SOME VALUE FOR POWER LATER
	int angler_power = 20; //SET SOME VALUE FOR POWER LATER
	int arm_power = 20; //SET SOME VALUE FOR POWER LATER

	while(true){

			//int lift = E_CONTROLLER_DIGITAL_R1.get_digital(DIGITAL_R1);
			//int lower = E_CONTROLLER_DIGITAL_L1.get_digital(DIGITAL_L1);
			if(master.get_digital(DIGITAL_R1)){
				intake_left.move(intake_power);
				intake_right.move(intake_power);
			}
			else if(master.get_digital(DIGITAL_L1)){
				intake_left.move(-intake_power);
				intake_right.move(-intake_power);
			}
			//int anglerUp = E_CONTROLLER_DIGITAL_R2.get_digital(DIGITAL_R2);
			//int anglerDown = E_CONTROLLER_DIGITAL_L2.get_digital(DIGITAL_L2);
			if(master.get_digital(DIGITAL_R2)){
				angler.move(angler_power);
			}
			else if(master.get_digital(DIGITAL_L2)){
				angler.move(-angler_power);
			}
			//int armUp1 = E_CONTROLLER_DIGITAL_UP.get_digital(DIGITAL_UP);
			//int armDown1 = E_CONTROLLER_DIGITAL_DOWN.get_digital(DIGITAL_DOWN);
			if(master.get_digital(DIGITAL_UP)){
				angler.move(angler_power);
			}
			else if(master.get_digital(DIGITAL_DOWN)){
				angler.move(-angler_power);
			}
			pros::delay(20);
		}
}



//this function measures the rotations that the tracking wheels have undergone
/*
void encoding() {
  pros::ADIEncoder enc1 (ENCODERLT, ENCODERLB, false); //left wheel
	pros::ADIEncoder enc2 (ENCODERRT, ENCODERRB, false); //right wheel
	pros::ADIEncoder enc3 (ENCODERCT, ENCODERCB, false); //back wheel
	while (true) {
    std::cout << "Left Side Encoder Value: " << enc1.get_value();
		std::cout << "Right Side Encoder Value: " << enc2.get_value();
		std::cout << "Back Encoder Value: " << enc3.get_value();
    pros::delay(20);
	}
}
*/


void opcontrol() {

		//I am using tasks because I feel that using functions will not work. This is because only one function can run at a time whereas multiple tasks can run at the same time.
		drive();
		LiftingApparatus();
		//encoding();

}
