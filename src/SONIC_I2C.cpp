#include "SONIC_I2C.h"

void SONIC_I2C::begin(TwoWire* wire, uint8_t addr, uint8_t sda, uint8_t scl,
                      uint32_t speed) {
    _wire  = wire;
    _addr  = addr;
    _sda   = sda;
    _scl   = scl;
    _speed = speed;
    _wire->begin((int)_sda, (int)_scl, (uint32_t)_speed);
}

float SONIC_I2C::getDistance() {
    uint32_t data;
    _wire->beginTransmission(_addr);  // Transfer data to 0x57. 将数据传输到0x57
    _wire->write(0x01);
    _wire->endTransmission();  // Stop data transmission with the Ultrasonic
                               // Unit. 停止与Ultrasonic Unit的数据传输
    delay(120);
    _wire->requestFrom(_addr,
                       (uint8_t)3);  // Request 3 bytes from Ultrasonic Unit.
                                     // 向Ultrasonic Unit请求3个字节。
    data = _wire->read();
    data <<= 8;
    data |= _wire->read();
    data <<= 8;
    data |= _wire->read();
    float Distance = float(data) / 1000;
    if (Distance > 4500.00) {
        return 4500.00;
    } else {
        return Distance;
    }
}
