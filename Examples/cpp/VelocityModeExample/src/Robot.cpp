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

/*
 * This project uses a joystick to control a DMC60C in velocity mode.
 * When the A button is held down, the left joystick controls the velocity of the motor.
 */

class Robot: public frc::IterativeRobot {
public:
	//Create a joystick object to control the motor.
	Joystick * _joy = new Joystick(0);

	//Create a DMC60C object with device number 1, wheel diameter of 203.2mm,
	//the encoder is on the output of the gearbox, so put a 1 for gearbox ratio.
	//The encoder has 20 pulses per channel per revolution.
	DMC60::WPI_DMC60C * _dmc = new DMC60::WPI_DMC60C(1, 203.2, 1, 20);

	bool _startbutton = false;

	void RobotInit(){
		//Disable limit switches.
		_dmc->setLimitSwitches(true, false, false);
		//Set the active PID Slot to 0.
		_dmc->setPIDSlot(0);
		//Configure the PID values on slot 0 to P=5, I=.1, D=4. This may also be done in the web configuration utility.
		_dmc->configPID(0, 5, .1, 4, 0);
	}

	void DisabledInit(){
		//Disable motor.
		_dmc->Disable();
	}
	void TeleopInit() {

	}

	void TeleopPeriodic() {
		//Get inputs.
		bool btn1 = _joy->GetRawButton(1);

		double stick = -1 * _joy->GetY();

		if (btn1) {//A button on XBox controller.
			_dmc->driveVelocity(stick);
		}
		else{
			_dmc->Disable();
		}

	}

private:
};

START_ROBOT_CLASS(Robot)
