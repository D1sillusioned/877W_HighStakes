/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       whcar                                                     */
/*    Created:      6/24/2024, 3:56:37 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "main.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  while (1) {
    // DRIVETRAIN
//Drivetrain Grouping
driveRb.setVelocity(100, percent);
driveRf.setVelocity(100, percent);
driveLb.setVelocity(100, percent);
driveLf.setVelocity(100, percent);
motor_group leftDrive(driveLf, driveLb);
motor_group rightDrive(driveRf, driveRb);

// Speed Drivetrain Settings
double turnImportance = 1;

// Pre Drivetrain Code
double turnVal = Controller1.Axis3.position();
double forwardVal = Controller1.Axis1.position();
double turnVolts = turnVal * 0.10;
double forwadVolts = forwardVal * -0.12 * (1 - (std::abs(turnVolts)/12) * turnImportance);

// During Drivetrain Code
leftDrive.spin(reverse, forwadVolts - turnVolts, voltageUnits::volt);
rightDrive.spin(forward, forwadVolts + turnVolts, voltageUnits::volt);

// INTAKE
intake.setReversed(false);

if (Controller1.ButtonR1.pressing()) {
intake.spin(vex::directionType::rev, 100, percent);
} else if (Controller1.ButtonL2.pressing()) {
intake.spin(vex::directionType::fwd, 100, percent);
} else {
intake.stop();
}



// Clamp Button A
    bool toggleEnabled1 = false; // two-choice toggle, so we use bool
    bool buttonPressed1 = false; // IGNORE, logic variable
    bool buttonA = Controller1.ButtonA.pressing();
    ////////////////////////////////////////////////////////////////////
    // Toggle Logic
    if (buttonA && !buttonPressed1){
      buttonPressed1 = true; 
      toggleEnabled1 = !toggleEnabled1;
    }
    else if (!buttonA) buttonPressed1 = false;
    ////////////////////////////////////////////////////////////////////
    // Code For toggle Enabled or Disabled
    if(toggleEnabled1){
      clamp_left.set(false);
      clamp_right.set(false);
    }
    else{
      clamp_left.set(true);
      clamp_right.set(true);
    }



//Intake Lift
    bool toggleEnabled2 = false; // two-choice toggle, so we use bool
    bool buttonPressed2 = false; // IGNORE, logic variable
    bool buttonA = Controller1.ButtonA.pressing();
    ////////////////////////////////////////////////////////////////////
    // Toggle Logic
    if (buttonA && !buttonPressed2){
      buttonPressed2 = true; 
      toggleEnabled2 = !toggleEnabled2;
    }
    else if (!buttonA) buttonPressed2 = false;
    ////////////////////////////////////////////////////////////////////
    // Code For toggle Enabled or Disabled
    if(toggleEnabled2){
      intake_lift.set(false);
    }
    else{
      intake_lift.set(true);
    }

//Pulldown Bar
    bool toggleEnabled3 = false; // two-choice toggle, so we use bool
    bool buttonPressed3 = false; // IGNORE, logic variable
    bool buttonA = Controller1.ButtonA.pressing();
    ////////////////////////////////////////////////////////////////////
    // Toggle Logic
    if (buttonA && !buttonPressed3){
      buttonPressed3 = true; 
      toggleEnabled3 = !toggleEnabled3;
    }
    else if (!buttonA) buttonPressed3 = false;
    ////////////////////////////////////////////////////////////////////
    // Code For toggle Enabled or Disabled
    if(toggleEnabled3){
      pulldown_bar.set(false);
    }
    else{
      pulldown_bar.set(true);
    }

// user();

    wait(20, msec);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
