/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package org.usfirst.frc.team1234.robot;

import com.dmc60c.DMC60C;
import edu.wpi.first.wpilibj.IterativeRobot;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

/**
 * This project demonstrates the use of Position mode. When the A button is held
 * the motor position will be controlled by the left joystick.
 */
public class Robot extends IterativeRobot {
	private DMC60C _dmc60c = new DMC60C(5);//DMC60C with devicenum 5
	private Joystick _joy = new Joystick(0);//Controller on USB slot 0
	private double Y;

	public void robotInit() {
		_dmc60c.ConfigWheel(200, 12, 20);//20cm wheel, with encoder on the output of the gearbox (1:1), and 20 encoder ticks per revolution.
		//The PID constants can be configured here or in the web configuration utility.
		_dmc60c.ConfigPID(0, (float)10, (float).001, (float)6, (float)0);//Slot 0, P=10, I=.001, D=6, F=0.
		_dmc60c.SetPIDSlot(0);//Set current PID slot to 0.
		_dmc60c.InvertEncoder(true);//If the motor is not responding correctly, the encoder might need to be inverted.
		_dmc60c.setInverted(false);//Change this to change the direction of forward and backward.
	}

	public void teleopInit() {
		
		_dmc60c.ZeroEncoderPosition();//Sets the current position to zero
	}
	

	public void teleopPeriodic() {
		Y = -_joy.getY()*2;
		if (_joy.getRawButton(1)) {//If A button is held
			_dmc60c.DriveDistance(Y);//Move the position of the wheel from -2 meters to 2 meters.
			SmartDashboard.putNumber("Position", _dmc60c.GetDistanceTraveled());
			
		}
		else {//No button is held
			_dmc60c.disable();
		}
	}
	
	public void disabledInit() {
		_dmc60c.disable();
	}

}
