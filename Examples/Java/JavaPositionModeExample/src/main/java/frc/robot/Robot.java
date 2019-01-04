/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot;

import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
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

  private DMC60C _dmc = new DMC60C(2);
  private Joystick _joy = new Joystick(0);

  /**
   * This function is run when the robot is first started up and should be
   * used for any initialization code.
   */
  @Override
  public void robotInit() {
    //Set wheel parameters
    //203mm diameter wheel, encoder on output of gearbox (1), 1024 cycles
    //per channel per revolution
    _dmc.ConfigWheel(203, 1, 1024);

    //Invert motor and encoder based on the hardware configuration.
    _dmc.setInverted(true);
    _dmc.InvertEncoder(true);

    //Using PID settings on slot 1.
    _dmc.SetPIDSlot(1);
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


  @Override
  public void teleopInit() {
    //Reset the Encoder position to zero.
    _dmc.ZeroEncoderPosition();
  }
  /**
   * This function is called periodically during operator control.
   */
  @Override
  public void teleopPeriodic() {
    boolean A = _joy.getRawButton(1);
    double stick = -1*_joy.getY();
  
  //If A button is pressed
    if(A){
      //Drive up to 5 revolutions in either direction.
      _dmc.DrivePosition(stick*5);
      //Report closed loop error on Smart Dashboard.
      SmartDashboard.putNumber("Closed Loop Error", _dmc.GetClosedLoopError());
    }
    else{
      _dmc.disable();
    }
  }

  /**
   * This function is called periodically during test mode.
   */
  @Override
  public void testPeriodic() {
  }
}
