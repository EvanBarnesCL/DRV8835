#ifndef CRUNCHLABS_DRV8835_H
#define CRUNCHLABS_DRV8835_H

#include <Arduino.h>

/**
 * @class DRV8835
 * @brief A class for controlling a motor with the DRV8835 motor driver.
 * @note Currently this only works with the DRV8835 in the phase/enable (aka speed/direction) mode,
 * where one pin for a motor controls the speed with PWM and the other controls direction with
 * a digital low/high. The h-bridge mode that requries two PWM pins per motor is currently not
 * supported with this code. 
 */
class DRV8835 {
public:
    /**
     * @brief Constructor to initialize a DRV8835 motor driver object.
     * @param speedPin The PWM pin used to control motor speed.
     * @param dirPin The pin used to control motor direction.
     * @param minOnPWMVal The minimum PWM value that will turn on the motor.
     * @param reverse If true, reverses the default direction of the motor.
     */
    DRV8835(uint8_t speedPin, uint8_t dirPin, uint8_t minOnPWMVal = 0, bool reverse = false);

    /**
     * @brief Sets the minimum PWM value that will turn on the motor.
     * @param minPWM Minimum PWM value.
     */
    void setMinOnPWM(uint8_t minPWM);

    /**
     * @brief Sets the motor speed.
     * @param speed Speed value (signed). Negative values reverse the motor direction.
     */
    void setSpeed(int16_t speed);

    /**
     * @brief Returns the current commanded motor speed.
     * @return Current speed as a 16-bit signed integer.
     */
    int16_t getSpeedCommand();

    /**
     * @brief Returns the actual speed value applied to the motor (mapped to minPWM-255).
     * @return Current speed as an 8-bit unsigned integer.
     */
    uint8_t getspeedActual();

private:
    /**
     * @brief Maps a value from one range to another using uint8_t, instead of long like the default map() function uses.
     * @param x Input value.
     * @param in_min Minimum input range.
     * @param in_max Maximum input range.
     * @param out_min Minimum output range.
     * @param out_max Maximum output range.
     * @return Mapped value as a uint8_t.
     */
    uint8_t map_uint8(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max);

    uint8_t _speedPin, _dirPin;                 ///< Pins for speed and direction control.
    uint8_t _minPWM;                            ///< Minimum PWM value that will turn on the motor.
    bool _reverse;                              ///< Reverses the default motor direction if true.
    int16_t _speed;                             ///< Stores the set motor speed (signed 16-bit value).
    uint8_t _speed8bit;                         ///< Constrained to 0-255 for setting PWM speed value.
};

#endif
