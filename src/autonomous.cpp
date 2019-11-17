#include "main.h"
#include "tracking.h"
#include "pid.h"

#include <math.h>

#define PI 3.14159265


/*
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

//define ports for motors
#define MOTOR1 2 //L1
#define MOTOR2 3 //L2
#define MOTOR3 11 //R1
#define MOTOR4 12 //R2

#define MOTOR5 13 //Angler
#define MOTOR6 4 //Arm
#define MOTOR7 5 //LIntake
#define MOTOR8 14 //RIntake

//define ports for encoders (TRACKING WHEELS)
#define ENCODERLT 1
#define ENCODERLB 2
#define ENCODERRT 3
#define ENCODERRB 4
#define ENCODERCT 5
#define ENCODERCB 6

void expand(void*){
	pros::Motor arm(MOTOR6, 1);
	pros::Motor angler(MOTOR5, 1);
	int armPosition = 0; //SET A VALUE
	int anglerPosition = 0; //SET A VALUE
	/*
	We have to set the motors of the arm and angler to move automatically for a set amount of seconds (or to a set position) and then back to the original for Ayan to drive
	*/
	//Moves motors to let robot expand. I DON'T WANT TO BREAK THE MOTORS SO WE HAVE TO CHANGE THE VALUES LATER
	arm.move_absolute(armPosition, 50); //change values later
	angler.move_absolute(anglerPosition, 50); //change values later

	//Moves motors to original position
	arm.move_absolute(armPosition, 50); //change values later
	angler.move_absolute(anglerPosition, 50); //change values later

	pros::delay(20);
}

//Will be used to call functions which will run the robot
void autonomous() {}
  pros::lcd::initialize();
  //resetPosition(gPosition);
  //pros::Task task1(trackPositionTask, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "TrackingPosition");

  //Define motors
  pros::Motor left_wheels_1(MOTOR1, 0); //L1
  pros::Motor right_wheels_1(MOTOR3, 1); //R1
  pros::Motor left_wheels_2(MOTOR2, 1); //L2
  pros::Motor right_wheels_2(MOTOR4, 0); //R2
  pros::Motor intake_left(MOTOR7, 0);
	pros::Motor intake_right(MOTOR8, 1);
	pros::Motor angler(MOTOR5, 1);
	pros::Motor arm(MOTOR6, 1);

  expand();

  //basically, robot moves to cubes, picks up, stops to let cube go up, moves towards next cube, picks up and stops, and it repeats that. We can change #of repeats or if the robot has to stop at all
  left_wheels_1.move(70);
  left_wheels_2.move(70);
  right_wheels_1.move(70);
  right_wheels_2.move(70);
  intake_left.move(100);
  intake_right.move(100);
  pros::delay(1000); //idk change this value later
  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);
  pros::delay(1000); //idk change this value later
  left_wheels_1.move(20);
  left_wheels_2.move(20);
  right_wheels_1.move(20);
  right_wheels_2.move(20);
  pros::delay(1000); //idk change this value later
  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);
  pros::delay(1000); //idk change this value later
  left_wheels_1.move(20);
  left_wheels_2.move(20);
  right_wheels_1.move(20);
  right_wheels_2.move(20);
  pros::delay(1000); //idk change this value later
  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);
  pros::delay(1000);
  intake_left.move(0);
  intake_right.move(0);

  //Robot turns around CCW
  left_wheels_1.move(-70);
  left_wheels_2.move(-70);
  right_wheels_1.move(70);
  right_wheels_2.move(70);
  pros::delay(1000); //idk change this value later
  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);

  //Robot moves to the goal zone
  left_wheels_1.move(70);
  left_wheels_2.move(70);
  right_wheels_1.move(70);
  right_wheels_2.move(70);
  pros::delay(1000); //idk change this value later
  left_wheels_1.move(0);
  left_wheels_2.move(0);
  right_wheels_1.move(0);
  right_wheels_2.move(0);

  //THERE IS A CHANCE WE NEED TO DO THe last part DIFFERENTLY SO THAT THE ROBOT IS ALIGNED MORE PROPERLY. LET'S JUST PRAY THAT THIS WORKS

  //Robot places cubes in the goal zone
  arm.move(30); //arm moves out to protect the blocks from falling
  angler.move(30);
  pros::delay(1000); //idk change this value later
  arm.move(0);
  pros::delay(1000); //idl change this value later
  angler.move(0);
  pros::delay(100);
  arm.move(100); //moves arms all the way up so that they go over the blocks (hopefully)... if they don't, we will have a very tricky situation on our hands...
  pros::delay(1000); //idk change this value later
  arm.move(0);

  //Robot moves away from the stack :)
  left_wheels_1.move(-20);
  left_wheels_2.move(-20);
  right_wheels_1.move(-20);
  right_wheels_2.move(-20);
}
