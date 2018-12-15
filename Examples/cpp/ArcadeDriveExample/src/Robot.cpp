/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <string>

#include <IterativeRobot.h>
#include "Joystick.h"
#include "digilent/DMC60/WPI_DMC60C.h"

/**
 * This project uses a joystick to control 2 DMC60c's on a robot with Arcade drive.
 * The triggers are used to move forward and backward, and the left joystick is used to steer.
 */

class Robot: public frc::IterativeRobot {
public:
	//Create a joystick object to control the motor.
	Joystick * _joy = new Joystick(0);

	//Create a DMC60C object with device number 5 and 2.
	//Since this is open loop, we don't need wheel and gearbox measurements.
	DMC60::WPI_DMC60C * _dmc = new DMC60::WPI_DMC60C(5);
	DMC60::WPI_DMC60C * _dmc2 = new DMC60::WPI_DMC60C(2);

	bool _btn2 = false;
	bool _startbutton = false;

	void RobotInit(){
		//Invert second motor
		_dmc2->SetInverted(true);
	}

	void DisabledInit(){
		//Disable motor.
		_dmc->Disable();
	}

	void TeleopPeriodic() {
		double Ltrigger = -100*_joy->GetRawAxis(2);//0 to 100
		double Rtrigger = 100*_joy->GetRawAxis(3);//0 to -100
		double stickL = _joy->GetRawAxis(0); //Left stick -1 left to 1 right

		double throttle = Ltrigger+Rtrigger;

		if (stickL>0){//Right turn (left motor on, right motor less on)
			_dmc->driveVoltage(throttle);
			//Right motor is scaled based on how far the left stick is turned right. If the left stick is full right, stickL=1, so the motor will be throttle-throttle=0.
			_dmc2->driveVoltage(throttle - throttle * stickL);
		}
		else{//Left or straight (right motor on, left motor less on)
			//Left motor is scaled based on how far the left stick is turned left. If it is all the way left, stickL=-1, so the motor will be throttle + (throttle * -1) = 0.
			_dmc->driveVoltage(throttle + throttle * stickL);
			_dmc2->driveVoltage(throttle);
		}
	}

private:
};


START_ROBOT_CLASS(Robot)
