#include <Crunchlabs_DRV8835.h>

DRV8835::DRV8835(uint8_t speedPin, uint8_t dirPin, uint8_t minOnPWMVal = 0, bool reverse = false) 
    :   _speedPin(speedPin), _dirPin(dirPin), _minPWM(minOnPWMVal), _reverse(reverse), 
        _speed(0), _speed8bit(0) {
    pinMode(_speedPin, OUTPUT);
    pinMode(_dirPin, OUTPUT);
}

void DRV8835::setMinOnPWM(uint8_t minPWM) {
    _minPWM = minPWM;
}

int16_t DRV8835::getSpeedCommand() {
    return _speed;
}

uint8_t DRV8835::getspeedActual() {
    return _speed8bit;
}

void DRV8835::setSpeed(int16_t speed) {
    _speed = speed;
    uint8_t direction = (_speed >= 0) ? 1 : 0;      // sets direction to 1 if speed >= 0;
    if (_reverse) direction ^= 1;                   // reverse direction via XOR operator   
    _speed8bit = abs(_speed);                       // convert to unsigned 8 bit speed value
    if (_speed8bit > 0 && _minPWM > 0) {            // map value to handle minimum PWM
        _speed8bit = map_uint8(_speed8bit, 0, 255, _minPWM, 255);
    }
    _speed8bit = constrain(_speed8bit, 0, 255);     // make sure it stays constrained properly
    digitalWrite(_dirPin, direction);               // set the direction
    analogWrite(_speedPin, _speed8bit);             // set the speed
}

uint8_t DRV8835::map_uint8(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max) {
    return (uint8_t)(((uint16_t)(x - in_min) * (out_max - out_min)) / (in_max - in_min) + out_min);
}
