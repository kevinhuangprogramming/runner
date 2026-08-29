#include <Wire.h>

#define SDA_PIN 13
#define SCL_PIN 14

#define TCA_ADDR 0x70
#define AS5600_ADDR 0x36
#define RAW_ANGLE_REG 0x0C


// Select a channel on the TCA9548A
void tcaSelect(uint8_t channel)
{
    if (channel > 7)
        return;

    Wire.beginTransmission(TCA_ADDR);
    Wire.write(1 << channel);
    Wire.endTransmission();
}


// Read raw angle from AS5600
uint16_t readAS5600()
{
    Wire.beginTransmission(AS5600_ADDR);
    Wire.write(RAW_ANGLE_REG);
    Wire.endTransmission(false);

    Wire.requestFrom(AS5600_ADDR, 2);

    if (Wire.available() < 2)
        return 0;

    uint8_t highByte = Wire.read();
    uint8_t lowByte = Wire.read();

    uint16_t angle = ((uint16_t)highByte << 8) | lowByte;

    return angle & 0x0FFF;
}


void setup()
{
    Serial.begin(115200);

    Wire.begin(SDA_PIN, SCL_PIN);

    Serial.println("TCA9548A + AS5600 test");

    // Select TCA9548A channel 1
    tcaSelect(1);
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