#include "main.h"
#include "motors.h"

pros::Motor left_wheels_1 (MOTOR1, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_DEGREES); //L1
pros::Motor right_wheels_1 (MOTOR3, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_DEGREES); //R1
pros::Motor left_wheels_2 (MOTOR2, pros::E_MOTOR_GEARSET_18, 1, pros::E_MOTOR_ENCODER_DEGREES); //L2
pros::Motor right_wheels_2 (MOTOR4, pros::E_MOTOR_GEARSET_18, 0, pros::E_MOTOR_ENCODER_DEGREES); //R2

pros::Motor intake_left (MOTOR7, pros::E_MOTOR_GEARSET_36, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake_right (MOTOR8, pros::E_MOTOR_GEARSET_36, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor arm (MOTOR6, pros::E_MOTOR_GEARSET_36, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor angler (MOTOR5, pros::E_MOTOR_GEARSET_36, 1, pros::E_MOTOR_ENCODER_DEGREES);
