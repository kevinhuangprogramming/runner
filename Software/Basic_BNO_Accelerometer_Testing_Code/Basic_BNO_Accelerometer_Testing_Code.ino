#include <Wire.h>
#include <Adafruit_BNO08x.h>

#define SDA_PIN 13
#define SCL_PIN 14
#define BNO085_ADDR 0x4B

Adafruit_BNO08x bno08x(-1);
sh2_SensorValue_t sensorValue;

unsigned long lastPrint = 0;

float ax = 0;
float ay = 0;
float az = 0;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Wire.begin(SDA_PIN, SCL_PIN);

    Serial.println("Starting BNO085...");

    if (!bno08x.begin_I2C(BNO085_ADDR, &Wire))
    {
        Serial.println("BNO085 not found!");
        while (1)
        {
            delay(10);
        }
    }

    Serial.println("BNO085 found!");

    if (!bno08x.enableReport(SH2_ACCELEROMETER, 100000))
    {
        Serial.println("Could not enable accelerometer");
        while (1)
        {
            delay(10);
        }
    }

    Serial.println("Accelerometer enabled!");
}

void loop()
{
    if (bno08x.wasReset())
    {
        Serial.println("BNO085 reset!");

        bno08x.enableReport(SH2_ACCELEROMETER, 100000);
    }

    if (bno08x.getSensorEvent(&sensorValue))
    {
        if (sensorValue.sensorId == SH2_ACCELEROMETER)
        {
            ax = sensorValue.un.accelerometer.x;
            ay = sensorValue.un.accelerometer.y;
            az = sensorValue.un.accelerometer.z;
        }
    }

    if (millis() - lastPrint >= 500)
    {
        lastPrint = millis();

        Serial.print("X: ");
        Serial.print(ax, 2);

        Serial.print("   Y: ");
        Serial.print(ay, 2);

        Serial.print("   Z: ");
        Serial.println(az, 2);
    }
}