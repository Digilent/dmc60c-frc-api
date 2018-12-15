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
 * This project uses a joystick to control a DMC60C in position mode.
 * When the A button is held down, the motor is moved to a position based on the left joystick.
 * When the B button is pressed, the motor's zero position is reset.
 */

class Robot: public frc::IterativeRobot {
public:
	//Create a joystick object to control the motor.
	Joystick * _joy = new Joystick(0);

	//Create a DMC60C object with device number 1, wheel diameter of 203.2mm,
	//on the input of a gearbox with a ratio of 12:1, and an encoder that has 20 pulses per channel per revolution.
	DMC60::WPI_DMC60C * _dmc = new DMC60::WPI_DMC60C(5, 203.2, 12, 20);

	bool _btn2 = false;
	bool _startbutton = false;

	void RobotInit(){
		//Disable limit switches.
		_dmc->setLimitSwitches(true, false, false);
		//Set the active PID Slot to 0.
		_dmc->setPIDSlot(0);
		//Configure the PID values on slot 0 to P=5, I=.001, D=4. This may also be done in the web configuration utility.
		_dmc->configPID(0, 10, .001, 6, 0);
		//Sets the current encoder position to 0.
		_dmc->zeroEncoderPosition();
		_dmc->invertEncoder(true);//If the motor is not responding correctly, the encoder might need to be inverted.
		_dmc->SetInverted(false);//Change this to change the direction of forward and backward.
	}

	void DisabledInit(){
		//Disable motor.
		_dmc->Disable();
	}

	void TeleopPeriodic() {
		//Get Inputs.
		bool btn1 = _joy->GetRawButton(1);
		bool btn2 = _joy->GetRawButton(2);
		bool startbutton = _joy->GetRawButton(8);

		double stick = -1 * _joy->GetY();

		if (btn1) {//A button on XBox controller.
			_dmc->drivePosition(stick);
		}
		if (btn2 && !_btn2) {//B button sets the current position of the wheel to 0.
			_dmc->zeroEncoderPosition();
		}
		if (startbutton & !_startbutton){
			_dmc->Disable();
		}

		//Save last btn state.
		_btn2=btn2;
		_startbutton=startbutton;
	}

private:
};


START_ROBOT_CLASS(Robot)
