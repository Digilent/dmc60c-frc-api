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
 * This project demonstrates the use of the Open-Loop driveVoltage function.
 * It requires an XBox controller and a DMC60C. When A is pressed, the motor spins
 * depending on the left joystick position.
 */
public class Robot extends IterativeRobot {
	private Joystick _joy = new Joystick(0);//Controller on USB slot 0
	private DMC60C _dmc60c = new DMC60C(2);//DMC60C device with devicenum 2
	private double YAxis;
	private boolean A;
	/**
	 * This function is run when the robot is first started up and should be
	 * used for any initialization code.
	 */
	@Override
	public void robotInit() {
	}

	/**
	 * This function is called when teleop mode is enabled
	 */
	@Override
	public void teleopInit() {
	}

	/**
	 * This function is called periodically during operator control.
	 */
	@Override
	public void teleopPeriodic() {
		YAxis = _joy.getY()*-100;//Get left joystick Y axis. 1 to -1 scaled to -100 to 100
		A = _joy.getRawButton(1);//Get 'A' button
		if (A) {//If 'A' button is held
			_dmc60c.DriveVoltage(YAxis);
			SmartDashboard.putNumber("Duty Cycle", YAxis);
		}
		else {//No button is pressed
			_dmc60c.disable();
		}
	}
	
	public void disabledInit() {
		_dmc60c.disable();
	}
}
