#include <Wire.h>

#define SDA_PIN 13
#define SCL_PIN 14

#define AS5600_ADDR 0x36
#define RAW_ANGLE_REG 0x0C

uint16_t readAS5600()
{
    // Tell AS5600 that we want to read from register 0x0C
    Wire.beginTransmission(AS5600_ADDR);
    Wire.write(RAW_ANGLE_REG);
    Wire.endTransmission(false);

    // Request the two bytes containing the 12-bit angle
    Wire.requestFrom(AS5600_ADDR, 2);

    if (Wire.available() < 2)
    {
        return 0;
    }

    uint8_t highByte = Wire.read();
    uint8_t lowByte = Wire.read();

    uint16_t angle = ((uint16_t)highByte << 8) | lowByte;

    // AS5600 is a 12-bit sensor
    return angle & 0x0FFF;
}

void setup()
{
    Serial.begin(115200);

    Wire.begin(SDA_PIN, SCL_PIN);

    Serial.println("AS5600 test");
}

void loop()
{
    uint16_t rawAngle = readAS5600();

    float degrees = rawAngle * 360.0 / 4096.0;

    Serial.print("Raw: ");
    Serial.print(rawAngle);

    Serial.print("    Angle: ");
    Serial.print(degrees, 2);
    Serial.println(" deg");

    delay(50);
}