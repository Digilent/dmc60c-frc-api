/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>
#include <digilent/dmc60/WPI_DMC60C.h>
#include <frc/Joystick.h>

//Create a DMC60C Object with Device number 5, wheel diameter 200mm,
//encoder on the output of the gearbox (1), and an encoder with 1024
//cycles per channel per rotation.
DMC60::WPI_DMC60C * _dmc = new DMC60::WPI_DMC60C(5, 200, 1, 1024);

frc::Joystick * _joy = new frc::Joystick(0);

void Robot::RobotInit() {  
  //Invert motor and encoder based on the hardware configuration.
  _dmc->SetInverted(false);
  _dmc->invertEncoder(true);

  //Using PID settings on slot 1.
  _dmc->setPIDSlot(1);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

void Robot::TeleopInit() {
  _dmc->zeroEncoderPosition();
}

void Robot::TeleopPeriodic() {
  bool A = _joy->GetRawButton(1);
  double stick = -1*_joy->GetY();

//If A button is pressed
  if(A){
    //Drive up to 5 revolutions in either direction.
    _dmc->drivePosition(stick*5);
    //Report closed loop error on Smart Dashboard.
    frc::SmartDashboard::PutNumber("Closed Loop Error", _dmc->getClosedLoopError());
  }
  else{
    _dmc->Disable();
  }
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
