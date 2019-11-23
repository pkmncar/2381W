#include "main.h"
#include "pid.h"
#include "motors.h"

PID pid = PID(0.1, 75, -75, 0.1, 0.01, 0.5);//constructs PID object
pros::Mutex mutex;

//defines controller
pros::Controller master (CONTROLLER_MASTER);

//defines the ports that are associated with each wheel

void drive(void*) {

	//loop reads the joystick controlls and powers the motors accordingly
	while (true) {
		std::string d1 = std::to_string(left_wheels_1.get_position());
		pros::lcd::set_text(0, d1);
		std::string d2 = std::to_string(right_wheels_1.get_position());
		pros::lcd::set_text(1, d2);
		std::string d3 = std::to_string(left_wheels_2.get_position());
		pros::lcd::set_text(2, d3);
		std::string d4 = std::to_string(right_wheels_2.get_position());
		pros::lcd::set_text(3, d4);

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

void intake(void*) {

	int intake_power = 100;
	//moves intakes
	while(true) {
		std::string il = std::to_string(intake_left.get_position());
		pros::lcd::set_text(4, il);
		std::string ir = std::to_string(intake_right.get_position());
		pros::lcd::set_text(5, ir);

	if(master.get_digital(DIGITAL_R2)) {
		intake_left.move(intake_power);
		intake_right.move(intake_power);
	}
	else if(master.get_digital(DIGITAL_L2)) {
		intake_left.move(-intake_power);
		intake_right.move(-intake_power);
	}
	else if(master.get_digital(DIGITAL_B)) {
		intake_left.move(intake_power/3);
		intake_right.move(intake_power/3);
		while (!master.get_digital(DIGITAL_B)) {
	    pros::delay(20);
	  }
	}
	else {
		intake_left.move(0);
		intake_right.move(0);
	}
		pros::delay(20);
	}
}

void arms(void*) {

		int arm_power = 100;

		while(true) {
			std::string b = std::to_string(arm.get_position());
			pros::lcd::set_text(6, b);
	//moves arm
	if(master.get_digital(DIGITAL_UP)) {
		arm.move(arm_power);
	}
	else if(master.get_digital(DIGITAL_DOWN)) {
		arm.move(-arm_power);
	}
	else {
		arm.move(0);
	}
		pros::delay(20);
	}


}

void anglerMove(void*) {

	int angler_power = 100;
	angler.tare_position();

	while(true) {
		std::string a = std::to_string(angler.get_position());
		pros::lcd::set_text(7, a);
	//moves angler
	if(master.get_digital(DIGITAL_R1)) {
		angler.move(angler_power);
 }
	else if(master.get_digital(DIGITAL_L1)) {
		if(angler.get_position() > -450)
			angler.move(-angler_power);
		else if(angler.get_position() < -600)
			angler.move(0);
		else
			angler.move(-50);
	}
	else {
		angler.move(0);
	}
	pros::delay(20);
	}
}

void opcontrol() {
	autonomous();
	pros::Task task1 (drive, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Driving");
	pros::Task task2 (intake, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Intake");
	pros::Task task3 (anglerMove, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Angler");
	pros::Task task4 (arms, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Arms");
}
