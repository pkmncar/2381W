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

void trackPosition(int left, int right, int back, sPos& position){
  float L = (left - position.leftLst) * SPIN_TO_IN_LR; // The amount the left side of the robot moved
	float R = (right - position.rightLst) * SPIN_TO_IN_LR; // The amount the right side of the robot moved
	float S = (back - position.backLst) * SPIN_TO_IN_S; // The amount the back side of the robot moved

	// Update the last values
	position.leftLst = left;
	position.rightLst = right;
	position.backLst = back;

	float h; // The hypotenuse of the triangle formed by the middle of the robot on the starting position and ending position and the middle of the circle it travels around
	float i; // Half on the angle that I've traveled
	float h2; // The same as h but using the back instead of the side wheels
  float a = (L - R) / (L_DISTANCE_IN + R_DISTANCE_IN); // The angle that I've traveled
  if (a){
		float r = R / a; // The radius of the circle the robot travel's around with the right side of the robot
		i = a / 2.0;
		float sinI = sin(i);
		h = ((r + R_DISTANCE_IN) * sinI) * 2.0;

		float r2 = S / a; // The radius of the circle the robot travel's around with the back of the robot
		h2 = ((r2 + S_DISTANCE_IN) * sinI) * 2.0;
	}
	else {
		h = R;
		i = 0;

		h2 = S;
	}
	float p = i + position.a; // The global ending angle of the robot
	float cosP = cos(p);
	float sinP = sin(p);

	// Update the global position
	position.y += h * cosP;
	position.x += h * sinP;

	position.y += h2 * -sinP; // -sin(x) = sin(-x)
	position.x += h2 * cosP; // cos(x) = cos(-x)

	position.a += a;

  //prints on LCD
  pros::lcd::set_text(1, position.x);
  pros::lcd::set_text(2, position.y);
  pros::lcd::set_text(3, position.a);

  pros::delay(1000);

  pros::lcd::clear_line(1);
  pros::lcd::clear_line(2);
  pros::lcd::clear_line(3);
}

task trackPositionTask(){
  /*
    WE HAVE TO DEFINE ENCODERS AND ALL HERE. ALSO HOW THE FUCK ARE WE MEASURING MOVEMENT AND ALL????
  */

  while(true){
    //get values from encoders
    trackPosition(left, right, back, gPosition);
    pros::delay(20);
  }
}

void resetPosition(sPos& position){
  position.leftLst = 0;
  position.rightLst = 0;
  position.backLst = 0;
  position.y = 0;
  position.x = 0;
  position.a = 0;
}

void scoopCupe(){
  int currentArmPosition = arm.getPosition();
  int currentAnglerPosition = angler.getPosition();
  int armPosition = 0; //SET A VALUE
  int anglerPosition = 0; //SET A VALUE
  //have to set position for the arm and angler too...
  arm.move_absolute(armPosition, 50);//change values later
  angler.move_absolute(anglerPosition, 50);//change values later
  intake_left.move(70);//change values later
  intake_right.move(70);//change values later
  pros::delay(1000);
  intake_left.move(0);
  intake_right.move(0);
  arm.move_absolute(currentArmPosition, 50);//change values later
  angler.move_absolute(currentAnglerPosition, 50);//change values later
}

void placeCubeInTower(){
  int currentArmPosition = arm.getPosition();
  int currentAnglerPosition = angler.getPosition();
  int armPosition = 0; //SET A VALUE
  int anglerPosition = 0; //SET A VALUE

  arm.move_absolute(armPosition, 50);//change values later
  angler.move_absolute(anglerPosition, 50);//change values later
  intake_left.move(100);//change values later
  intake_right.move(100);//change values later
  pros::delay(1000);
  intake_left.move(0);
  intake_right.move(0);
  arm.move_absolute(currentArmPosition, 50);//change values later
  angler.move_absolute(currentAnglerPosition, 50);//change values later
}

void placeCubesInGoal(){
  //make robot place cubes in goal zone
}

void moveToTarget(float xD /*desired x coordinate*/, float yD /*desired y coordinate*/, sPos& position, int scoopRequired, int placeInTowerRequired, int placeInGoalRequired /*These will all call sepaarate functions which will make the robot place stuff in goal zones, etc.*/){
  //Make robot get appropriate angle, then make robot move to correct location, then make robot do appropriate action
  //get angle of direction needed to reach the desired coordinates
  float diffX = position.x - xD;
  float diffY = position.y - yD;
  float aD = atan2(diffY, diffX) * 180.0 / PI;

  //Set the angle of the robot
  while(aD < (position.a - 1) || aD > (position.a + 1)){ //we may need to allow for some uncertainty
    //Determne which way to turn the robot
    if(aD > position.a){
      while(aD > (position.a - 10)){ //fast, coarse movement
          left_wheels_1.move(-70);
          left_wheels_2.move(-70);
          right_wheels_1.move(70);
          right_wheels_2.move(70);
      }
      while(aD > position.a){ //slow, finer movement
          left_wheels_1.move(-10);
          left_wheels_2.move(-10);
          right_wheels_1.move(10);
          right_wheels_2.move(10);
      }
    }
    else if(aD < position.a){
      while(aD < (position.a - 10)){ //fast, coarse movement
          left_wheels_1.move(70);
          left_wheels_2.move(70);
          right_wheels_1.move(-70);
          right_wheels_2.move(-70);
      }
      while(aD < position.a){ //slow, finer movement
          left_wheels_1.move(10);
          left_wheels_2.move(10);
          right_wheels_1.move(-10);
          right_wheels_2.move(-10);
      }
    }
  }

  //calculates distance to destination point
  float distanceToPoint = 0.0;
  float toSquare = diffX*diffX + diffY*diffY;
  distanceToPoint = sqrt(toSquare);

  //incorporate PID controller at a later time

  while(distanceToPoint > 1){ //allowing for uncertainty of 1. We can fine tune later
    diffX = position.x - xD;
    diffY = position.y - yD;
    toSquare = diffX*diffX + diffY*diffY;
    distanceToPoint = sqrt(toSquare);
    if(distanceToPoint > 10){ //if it is far away, robot moves quickly
      left_wheels_1.move(70);
      left_wheels_2.move(70);
      right_wheels_1.move(70);
      right_wheels_2.move(70);
    }
    else if(distanceToPoint < 10){ //if it is close, robot moves slowly
      left_wheels_1.move(10);
      left_wheels_2.move(10);
      right_wheels_1.move(10);
      right_wheels_2.move(10);
    }
  }

  //checks if secondary functions need to be called
  if(scoopRequired == 1){
    scoopCupe();
  }
  if(placeInTowerRequired == 1){
    placeCubeInTower();
  }
  if(placeInGoalRequired == 1){
    placeCubesInGoal();
  }
  pros::delay(20);
}

//Will be used to call functions which will run the robot
void autonomous() {}
  pros::lcd::initialize();
  resetPosition(gPosition);
  pros::Task task1(trackPositionTask, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "TrackingPosition");

  //Define motors
  pros::Motor left_wheels_1(MOTOR1, 0); //L1
  pros::Motor right_wheels_1(MOTOR3, 1); //R1
  pros::Motor left_wheels_2(MOTOR2, 1); //L2
  pros::Motor right_wheels_2(MOTOR4, 0); //R2
  pros::Motor intake_left(MOTOR7, 0);
	pros::Motor intake_right(MOTOR8, 1);
	pros::Motor angler(MOTOR5, 1);
	pros::Motor arm(MOTOR6, 1);
  //repetition of moveToTarget() functions to command the robot to move and collect items
  moveToTarget(0.0, 0.0, gPosition, 0, 0, 0); //set the coordinates for desired x and y adn if you want the robot to scoop blocks, place them in the tower, or place them in the goal zone

}
