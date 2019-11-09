#include "main.h"

//defines the ports for each motor
#define MOTOR1 2 //L1
#define MOTOR2 3 //L2
#define MOTOR3 11 //R1
#define MOTOR4 12 //R2

#define MOTOR5 13 //Angler
#define MOTOR6 4 //Arm
#define MOTOR7 5 //LIntake
#define MOTOR8 14 //RIntake

/*DO WE NEED ENCODERS???

#define ENCODERLT 1
#define ENCODERLB 2
#define ENCODERRT 3
#define ENCODERRB 4
#define ENCODERCT 5
#define ENCODERCB 6

  WILL NEED TO DEFINE THE PORTS FOR THE OTHER MOTORS, SENSORS, ETC.

*/

void drive(void*) {
	//defines the ports that are associated with each wheel
	pros::Motor left_wheels_1(MOTOR1, 0); //L1
	pros::Motor right_wheels_1(MOTOR3, 1); //R1
	pros::Motor left_wheels_2(MOTOR2, 1); //L2
	pros::Motor right_wheels_2(MOTOR4, 0); //R2

	//defines controller
	pros::Controller master(CONTROLLER_MASTER);

	//loop reads the joystick controlls and powers the motors accordingly
	while (true) {
		int powerLeft = master.get_analog(ANALOG_LEFT_Y);
		int powerRight = master.get_analog(ANALOG_RIGHT_Y);

		//If there is a small difference, then program will assume person wants to go straight and will set power to motors as equal
		if ((powerLeft - powerRight) >= -7 && (powerLeft - powerRight) <= 7)
			powerLeft = powerRight;

		left_wheels_1.move(powerLeft);
		left_wheels_2.move(powerLeft);
		right_wheels_1.move(powerRight);
		right_wheels_2.move(powerRight);
		pros::delay(20);
	}
}

void liftingApparatus(void*) {
	pros::Motor intake_left(MOTOR7, 0);
	pros::Motor intake_right(MOTOR8, 1);
	pros::Motor angler(MOTOR5, 1);
	pros::Motor arm(MOTOR6, 1);
	//defines controller
	pros::Controller master(CONTROLLER_MASTER);

	int intake_power = 100;
	int angler_power = 100;
	int arm_power = 100;

	while (true) {
		//moves intakes
		if (master.get_digital(DIGITAL_R2)) {
			intake_left.move(intake_power);
			intake_right.move(intake_power);
		}
		else if (master.get_digital(DIGITAL_L2)) {
			intake_left.move(-intake_power);
			intake_right.move(-intake_power);
		}
		else {
			intake_left.move(0);
			intake_right.move(0);
		}

		//moves angler
		if (master.get_digital(DIGITAL_R1)) {
			angler.move(angler_power);
		}
		else if (master.get_digital(DIGITAL_L1)) {
			angler.move(-angler_power);
		}
		else {
			angler.move(0);
		}

		//moves arm
		if (master.get_digital(DIGITAL_UP)) {
			arm.move(arm_power);
		}
		else if (master.get_digital(DIGITAL_DOWN)) {
			arm.move(-arm_power);
		}
		else {
			arm.move(0);
		}

		pros::delay(20);
	}
}

void opcontrol() {
	pros::Task task1(drive, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Driving");
	pros::Task task2(liftingApparatus, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Lifting");
}
