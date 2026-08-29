#include <Wire.h>

#define SDA_PIN 13
#define SCL_PIN 14

#define TCA_ADDR 0x70
#define AS5600_ADDR 0x36

void tcaSelect(uint8_t channel)
{
    Wire.beginTransmission(TCA_ADDR);
    Wire.write(1 << channel);

    uint8_t error = Wire.endTransmission();

    Serial.print("Selected channel ");
    Serial.print(channel);
    Serial.print(" | TCA write result = ");
    Serial.println(error);
}

bool deviceFound(uint8_t address)
{
    Wire.beginTransmission(address);
    return (Wire.endTransmission() == 0);
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Wire.begin(SDA_PIN, SCL_PIN);

    Serial.println();
    Serial.println("TCA9548A CHANNEL TEST");
    Serial.println();

    // -------------------------
    // Channel 0
    // -------------------------
    tcaSelect(0);
    delay(10);

    Serial.print("Channel 0, AS5600: ");

    if (deviceFound(AS5600_ADDR))
        Serial.println("FOUND");
    else
        Serial.println("NOT FOUND");

    // -------------------------
    // Channel 1
    // -------------------------
    tcaSelect(1);
    delay(10);

    Serial.print("Channel 1, AS5600: ");

    if (deviceFound(AS5600_ADDR))
        Serial.println("FOUND");
    else
        Serial.println("NOT FOUND");
}

void loop()
{
}