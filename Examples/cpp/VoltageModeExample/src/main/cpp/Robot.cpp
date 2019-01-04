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

//Create a new DMC60C object with device number 5.
DMC60::WPI_DMC60C * _dmc = new DMC60::WPI_DMC60C(5);

frc::Joystick * _joy = new frc::Joystick(0);

void Robot::RobotInit() {
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


void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
  bool A = _joy->GetRawButton(1);
  double stick = -1*_joy->GetY();

  //If A button is pressed
  if(A){
    //Drive with values from -100 to 100.
    _dmc->driveVoltage(stick*100);
  }
  else{
    _dmc->Disable();
  }
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
