#include "main.h"

//RIGHT AND LEFT BASED ON LOOKING AT THE ROBOT FROM THE BACK

//defines the ports for each motor and encoder
#define MOTOR1 1 //L1
#define MOTOR2 2 //L2
#define MOTOR3 9 //R1
#define MOTOR4 10 //R2

//CHANGE PORT NUMBERS LATER
#define MOTOR5 3 //Angler
#define MOTOR6 7 //Arm
#define MOTOR7 5 //ScooperL
#define MOTOR8 9 //ScooperR

/*DO WE NEED ENCODERS???

#define ENCODERLT 1
#define ENCODERLB 2
#define ENCODERRT 3
#define ENCODERRB 4
#define ENCODERCT 5
#define ENCODERCB 6

  WILL NEED TO DEFINE THE PORTS FOR THE OTHER MOTORS, SENSORS, ETC.

*/

task drive() {

	//defines the ports that are associated with each wheel
	pros::Motor left_wheels_1 (MOTOR1);
	pros::Motor right_wheels_1 (MOTOR3, true);
	pros::Motor left_wheels_2 (MOTOR2, true);
	pros::Motor right_wheels_2 (MOTOR4);

	//defines controller
	pros::Controller master (CONTROLLER_MASTER);

	//loop reads the joystick controlls and powers the motors accordingly
	while (true) {
		int powerLeft = master.get_analog(ANALOG_LEFT_Y);
		int powerRight = master.get_analog(ANALOG_RIGHT_Y);
		//If there is a small difference, then program will assume person wants to go straight and will set pwoer to motors as equal
		if((powerLeft - PowerRight) >= -4 && (powerLeft - PowerRight) <= 4){ //CHANGE VALUES LATER
			powerLeft = powerRight;
		}
		left_wheels_1.move(powerLeft);
		left_wheels_2.move(powerLeft);
		right_wheels_1.move(powerRight);
		right_wheels_2.move(powerRight);
		pros::delay(20);
	}
}

task LiftingApparatus(){
	pros::Motor scooper_left (MOTOR7);
	pros::Motor scooper_right (MOTOR8);
	pros::Motor angler (MOTOR5);
	pros::Motor arm (MOTOR6);

	//defines controller
	pros::Controller master (CONTROLLER_MASTER);
	pros::E_CONTROLLER_DIGITAL_R1 r1 (CONTROLLER_MASTER);
	pros::E_CONTROLLER_DIGITAL_L1 l1 (CONTROLLER_MASTER);
	pros::E_CONTROLLER_DIGITAL_R2 aUp (CONROLLER_MASTER);
	pros::E_CONTROLLER_DIGITAL_L2 aDown (CONROLLER_MASTER);
	pros::E_CONTROLLER_DIGITAL_UP armUp (CONROLLER_MASTER);
	pros::E_CONTROLLER_DIGITAL_DOWN armDown (CONROLLER_MASTER);

	int scooper_power = 0; //SET SOME VALUE FOR POWER LATER
	int angler_power = 0; //SET SOME VALUE FOR POWER LATER
	int arm_power = 0; //SET SOME VALUE FOR POWER LATER

	while(true){
			int lift = r1.get_digital(DIGITAL_R1);
			int lower = l1.get_digital(DIGITAL_L1);
			if(lift == 1 && lower == 0){
				scooper_left.move(scooper_power);
				scooper_right.move(scooper_power);
			}
			else if(lift == 0 && lower == 1){
				scooper_left.move(scooper_power);
				scooper_right.move(scooper_power);
			}
			int anglerUp = aUp.get_digital(DIGITAL_R2);
			int anglerDown = aDown.get_digital(DIGITAL_L2);
			if(anglerUp == 1 && anglerDown == 0){
				angler.move(angler_power);
			}
			else if(anglerUp == 0 && anglerDown == 1){
				angler.move(-angler_power);
			}
			int armUp1 = armUp.get_digital(DIGITAL_UP);
			int armDown1 = armDown.get_digital(DIGITAL_DOWN);
			if(armUp1 == 1 && armDown1 == 0){
				angler.move(angler_power);
			}
			else if(armUp1 == 0 && armDown1 == 1){
				angler.move(-angler_power);
			}
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

		tStart(drive);
		tStart(LiftingApparatus);
		//encoding();

}
