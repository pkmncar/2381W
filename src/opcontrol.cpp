#include "main.h"

#define MOTOR1 1
#define MOTOR2 2
#define MOTOR3 9
#define MOTOR4 10
#define ENCODERLT 1
#define ENCODERLB 2
#define ENCODERRT 3
#define ENCODERRB 4
#define ENCODERCT 5
#define ENCODERCB 6

void drive() {

	pros::Motor left_wheels_1 (MOTOR1);
	pros::Motor right_wheels_1 (MOTOR3, true);
	pros::Motor left_wheels_2 (MOTOR2, true);
	pros::Motor right_wheels_2 (MOTOR4);
	pros::Controller master (CONTROLLER_MASTER);

	while (true) {
		int power = master.get_analog(ANALOG_LEFT_Y);
		int turn = master.get_analog(ANALOG_RIGHT_X);
		int left = power + turn;
		int right = power - turn;
		left_wheels_1.move(left);
		left_wheels_2.move(left);
		right_wheels_1.move(right);
		right_wheels_2.move(right);
		pros::delay(20);
	}
}

void encoding() {
  pros::ADIEncoder enc1 (ENCODERLT, ENCODERLB, false);
	pros::ADIEncoder enc2 (ENCODERRT, ENCODERRB, false);
	pros::ADIEncoder enc3 (ENCODERCT, ENCODERCB, false);
	while (true) {
    std::cout << "Left Side Encoder Value: " << enc1.get_value();
		std::cout << "Right Side Encoder Value: " << enc2.get_value();
		std::cout << "Back Encoder Value: " << enc3.get_value();
    pros::delay(20);
	}
}

void opcontrol() {

		drive();
		encoding();

  }
