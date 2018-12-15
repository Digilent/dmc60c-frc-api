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
 * This demo uses a joystick to control a DMC60C to drive in open loop voltage mode.
 * When the A button is held, the motor is driven based on the left joystick position.
 * When the start button is pressed, the motor is stopped.
 */

class Robot: public frc::IterativeRobot {
public:
	//Create a joystick object to control the motor.
	Joystick * _joy = new Joystick(0);

	//Create a DMC60C object with device number 1.
	DMC60::WPI_DMC60C * _dmc = new DMC60::WPI_DMC60C(1);

	bool _btn2 = false;
	bool _startbutton = false;

	void RobotInit(){
		//Disable limit switches.
		_dmc->setLimitSwitches(true, false, false);
	}

	void DisabledInit(){
		//Disable motor.
		_dmc->Disable();
	}
	void TeleopInit() {
	}

	void TeleopPeriodic() {
		bool A = _joy->GetRawButton(1);

		double stick = -1 * _joy->GetY();//Scale the joystick -1 to 1.

		if (A) {//A button on XBox controller.
			_dmc->driveVoltage(stick * 100);//Scale duty cycle from -100 to 100.
		}
		else{
			_dmc->Disable();
		}

	}



private:
};


START_ROBOT_CLASS(Robot)
