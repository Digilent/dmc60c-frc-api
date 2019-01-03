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
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  frc::SmartDashboard::PutNumber("Closed Loop Error", _dmc->getClosedLoopError());
  _dmc->setLimitSwitches(true, false, false);
  
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

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

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
