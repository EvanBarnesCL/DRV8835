/*
Example program for the DRV8835 motor driver library.
*/


#include <Arduino.h>
#include <DRV8835.h>


constexpr uint8_t MOTOR_1_SPEED_PIN = 6;
constexpr uint8_t MOTOR_1_DIR_PIN = 7;
constexpr uint8_t MOTOR_2_SPEED_PIN = 5;
constexpr uint8_t MOTOR_2_DIR_PIN = 4;

// set up motor 1 with a minimum PWM value of 85 and reversed direction direction of rotation
DRV8835 motor1(MOTOR_1_SPEED_PIN, MOTOR_1_DIR_PIN, 85, true);

// set up motor 2 with a minimum PWM value of 0 and default direction of rotation
DRV8835 motor2(MOTOR_2_SPEED_PIN, MOTOR_2_DIR_PIN, 0, false);

void setup() {

}

void loop() {
  motor1.setSpeed(100);
  motor2.setSpeed(-200);
  delay(4000);
  motor1.setSpeed(-200);
  motor2.setSpeed(200);
  delay(4000);
}