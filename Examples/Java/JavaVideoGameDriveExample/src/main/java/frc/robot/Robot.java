/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot;

import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.Joystick;
import com.dmc60c.DMC60C;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the TimedRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the build.gradle file in the
 * project.
 */
public class Robot extends TimedRobot {
  private DMC60C _dmc60cR = new DMC60C(5);//DMC60C with devicenum 5
	private DMC60C _dmc60cL = new DMC60C(2);//DMC60C with devicenum 2
	private Joystick _joy = new Joystick(0);//Controller on USB slot 0

  /**
   * This function is run when the robot is first started up and should be
   * used for any initialization code.
   */
  @Override
  public void robotInit() {
    _dmc60cR.setInverted(true);
  }

  /**
   * This function is called every robot packet, no matter the mode. Use
   * this for items like diagnostics that you want ran during disabled,
   * autonomous, teleoperated and test.
   *
   * <p>This runs after the mode specific periodic functions, but before
   * LiveWindow and SmartDashboard integrated updating.
   */
  @Override
  public void robotPeriodic() {
  }

  /**
   * This function is called periodically during operator control.
   */
  @Override
  public void teleopPeriodic() {
    double Ltrigger = -100*_joy.getRawAxis(2);//0 to 100
    double Rtrigger = 100*_joy.getRawAxis(3);//0 to -100
    double stickL = _joy.getRawAxis(0); //Left stick -1 left to 1 right

    double throttle = Ltrigger+Rtrigger;

    if (stickL>0){//Right turn (left motor on, right motor less on)
      _dmc60cL.DriveVoltage(throttle);

      //Right motor is scaled based on how far the left stick is turned right.
      //If the left stick is full right, stickL=1, so the motor will be
      //throttle-throttle=0.
      _dmc60cR.DriveVoltage(throttle - throttle * stickL);
    }
    else{//Left or straight (right motor on, left motor less on)

      //Left motor is scaled based on how far the left stick is turned left.
      //If it is all the way left, stickL=-1, so the motor will be
      //throttle + (throttle * -1) = 0.
      _dmc60cL.DriveVoltage(throttle + throttle * stickL);
      _dmc60cR.DriveVoltage(throttle);
    }
  }

  /**
   * This function is called periodically during test mode.
   */
  @Override
  public void testPeriodic() {
  }
}
