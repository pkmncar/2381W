#include "main.h"
#include <math.h>
#include "motors.h"

void autonomous() {

		left_wheels_1.tare_position();
	  left_wheels_2.tare_position();
	  right_wheels_1.tare_position();
	  right_wheels_2.tare_position();

	  left_wheels_1.move_absolute(100, 100);
	  left_wheels_2.move_absolute(100, 100);
	  right_wheels_1.move_absolute(100, 100);
	  right_wheels_2.move_absolute(100, 100);
	  while (!((left_wheels_1.get_position() < 105) && (left_wheels_1.get_position() > 95))) {
	   // Continue running this loop as long as the motor is not within +-5 units of its goal
	   pros::delay(20);
	  }

	  left_wheels_1.move(0);
	  left_wheels_2.move(0);
	  right_wheels_1.move(0);
	  right_wheels_2.move(0);

		arm.tare_position();
	  arm.move_absolute(400, 100);
		while (!((arm.get_position() < 405) && (arm.get_position() > 395))) {
	   // Continue running this loop as long as the motor is not within +-5 units of its goal
	   pros::delay(20);
	  }
		angler.tare_position();
		angler.move_absolute(-50, -100);
		while (!((angler.get_position() < -45) && (angler.get_position() > -55))) {
	   // Continue running this loop as long as the motor is not within +-5 units of its goal
	   pros::delay(20);
	  }
		arm.move_absolute(0, -70);
		while (!((arm.get_position() < 5) && (arm.get_position() > -5))) {
	   // Continue running this loop as long as the motor is not within +-5 units of its goal
	   pros::delay(20);
	  }
		angler.move_absolute(0, 70);
		while (!((angler.get_position() < 5) && (angler.get_position() > -5))) {
	   // Continue running this loop as long as the motor is not within +-5 units of its goal
	   pros::delay(20);
	  }

		for(int i = 0; i < 4; i++)
		{
		  left_wheels_1.move_absolute(350, 100);
		  left_wheels_2.move_absolute(350, 100);
		  right_wheels_1.move_absolute(350, 100);
		  right_wheels_2.move_absolute(350, 100);
		  while (!((left_wheels_1.get_position() < 355) && (left_wheels_1.get_position() > 345))) {
		   // Continue running this loop as long as the motor is not within +-5 units of its goal
		   pros::delay(20);
		  }

		  left_wheels_1.move(0);
		  left_wheels_2.move(0);
		  right_wheels_1.move(0);
		  right_wheels_2.move(0);

		  intake_left.move(100);
		  intake_right.move(100);
			pros::delay(200);
		}

		//
	  // //sets current positions to zero
	  // left_wheels_1_2.tare_position();
	  // left_wheels_2_2.tare_position();
	  // right_wheels_1_2.tare_position();
	  // right_wheels_2_2.tare_position();
		//
	  // //Code to rotate ccw 90º
	  // left_wheels_1_2.move_absolute(0.5, -100);
	  // left_wheels_2_2.move_absolute(0.5, -100);
	  // right_wheels_1_2.move_absolute(0.5, 100);
	  // right_wheels_2_2.move_absolute(0.5, 100);
		// while (!((left_wheels_1_2.get_position() < 0.55) && (left_wheels_1_2.get_position() > 0.45))) {
	  //  // Continue running this loop as long as the motor is not within +-5 units of its goal
	  //  pros::delay(2);
	  // }
		//
	  // left_wheels_1_2.tare_position();
	  // left_wheels_2_2.tare_position();
	  // right_wheels_1_2.tare_position();
	  // right_wheels_2_2.tare_position();
		//
	  // left_wheels_1_2.move_absolute(1.7, 100);
	  // left_wheels_2_2.move_absolute(1.7, 100);
	  // right_wheels_1_2.move_absolute(1.7, 100);
	  // right_wheels_2_2.move_absolute(1.7, 100);
		//
	  // while (!((left_wheels_1_2.get_position() < 1.75) && (left_wheels_1_2.get_position() > 1.65))) {
	  //  // Continue running this loop as long as the motor is not within +-5 units of its goal
	  //  pros::delay(2);
	  // }
		//
	  // left_wheels_1_2.move(0);
	  // left_wheels_2_2.move(0);
	  // right_wheels_1_2.move(0);
	  // right_wheels_2_2.move(0);
		//
	  // //sets current positions to zero
	  // left_wheels_1_2.tare_position();
	  // left_wheels_2_2.tare_position();
	  // right_wheels_1_2.tare_position();
	  // right_wheels_2_2.tare_position();
		//
	  // //Code to rotate ccw 90º
	  // left_wheels_1_2.move_absolute(0.5, -100);
	  // left_wheels_2_2.move_absolute(0.5, -100);
	  // right_wheels_1_2.move_absolute(0.5, 100);
	  // right_wheels_2_2.move_absolute(0.5, 100);
		// while (!((left_wheels_1_2.get_position() < 0.55) && (left_wheels_1_2.get_position() > 0.45))) {
	  //  // Continue running this loop as long as the motor is not within +-5 units of its goal
	  //  pros::delay(2);
	  // }
		//
	  // left_wheels_1_2.move_absolute(2.3, 100);
	  // left_wheels_2_2.move_absolute(2.3, 100);
	  // right_wheels_1_2.move_absolute(2.3, 100);
	  // right_wheels_2_2.move_absolute(2.3, 100);
		//
	  // while (!((left_wheels_1_2.get_position() < 2.35) && (left_wheels_1_2.get_position() > 2.25))) {
	  //  // Continue running this loop as long as the motor is not within +-5 units of its goal
	  //  pros::delay(2);
	  // }
		//
	  // left_wheels_1_2.move(0);
	  // left_wheels_2_2.move(0);
	  // right_wheels_1_2.move(0);
	  // right_wheels_2_2.move(0);
		//
	  //Code to place the cubes in the goal zone
		angler.tare_position();
	  angler.move_absolute(-400, -100);
	  while (!((angler.get_position() < -395) && (angler.get_position() > -405))) {
	   // Continue running this loop as long as the motor is not within +-5 units of its goal
	   pros::delay(20);
	  }

	  angler.tare_position();
	  angler.move_absolute(-500, -75);
	  while (!((angler.get_position() < -495) && (angler.get_position() > -505))) {
	   // Continue running this loop as long as the motor is not within +-5 units of its goal
	   pros::delay(20);
	  }

	  angler.tare_position();
	  angler.move_absolute(-600, -50);
	  while (!((angler.get_position() < -595) && (angler.get_position() > -605))) {
	   // Continue running this loop as long as the motor is not within +-5 units of its goal
	   pros::delay(20);
	  }

	  angler.move(0);

	  left_wheels_1.tare_position();
	  left_wheels_2.tare_position();
	  right_wheels_1.tare_position();
	  right_wheels_2.tare_position();

	  //moves forward to make sure tht the the stack is stable
	  left_wheels_1.move_absolute(20, 20);
	  left_wheels_2.move_absolute(20, 20);
	  right_wheels_1.move_absolute(20, 20);
	  right_wheels_2.move_absolute(20, 20);
	  while (!((left_wheels_1.get_position() < 35) && (left_wheels_1.get_position() > 25))) {
	   // Continue running this loop as long as the motor is not within +-5 units of its goal
	   pros::delay(20);
	  }

	  left_wheels_1.move(0);
	  left_wheels_2.move(0);
	  right_wheels_1.move(0);
	  right_wheels_2.move(0);

	  left_wheels_1.tare_position();
	  left_wheels_2.tare_position();
	  right_wheels_1.tare_position();
	  right_wheels_2.tare_position();

	  //backs away
	  left_wheels_1.move_absolute(-200, -20);
	  left_wheels_2.move_absolute(-200, -20);
	  right_wheels_1.move_absolute(-200, -20);
	  right_wheels_2.move_absolute(-200, -20);
	  while (!((left_wheels_1.get_position() < -195) && (left_wheels_1.get_position() > -205))) {
	   // Continue running this loop as long as the motor is not within +-5 units of its goal
	   pros::delay(20);
	  }

	  left_wheels_1.move(0);
	  left_wheels_2.move(0);
	  right_wheels_1.move(0);
	  right_wheels_2.move(0);
}
