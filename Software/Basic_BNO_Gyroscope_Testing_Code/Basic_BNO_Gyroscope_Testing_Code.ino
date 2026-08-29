#include <Wire.h>
#include <Adafruit_BNO08x.h>

#define SDA_PIN 13
#define SCL_PIN 14
#define BNO085_ADDR 0x4B

Adafruit_BNO08x bno08x(-1);
sh2_SensorValue_t sensorValue;

unsigned long lastPrint = 0;

float gx = 0;
float gy = 0;
float gz = 0;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Wire.begin(SDA_PIN, SCL_PIN);

    Serial.println("Starting BNO085...");

    if (!bno08x.begin_I2C(BNO085_ADDR, &Wire))
    {
        Serial.println("BNO085 not found!");
        while (1) delay(10);
    }

    Serial.println("BNO085 found!");

    if (!bno08x.enableReport(SH2_GYROSCOPE_CALIBRATED, 100000))
    {
        Serial.println("Could not enable gyroscope");
        while (1) delay(10);
    }

    Serial.println("Gyroscope enabled!");
}

// void loop()
// {
//     if (bno08x.wasReset())
//     {
//         Serial.println("BNO085 reset!");
//         bno08x.enableReport(SH2_GYROSCOPE_CALIBRATED, 100000);
//     }

//     if (bno08x.getSensorEvent(&sensorValue))
//     {
//         if (sensorValue.sensorId == SH2_GYROSCOPE_CALIBRATED)
//         {
//             gx = sensorValue.un.gyroscope.x;
//             gy = sensorValue.un.gyroscope.y;
//             gz = sensorValue.un.gyroscope.z;
//         }
//     }

//     if (millis() - lastPrint >= 500)
//     {
//         lastPrint = millis();

//         Serial.print("GX: ");
//         Serial.print(gx, 5);

//         Serial.print("   GY: ");
//         Serial.print(gy, 5);

//         Serial.print("   GZ: ");
//         Serial.println(gz, 5);
//     }
// }

void loop()
{
    if (bno08x.getSensorEvent(&sensorValue))
    {
        // Serial.print("Sensor ID: 0x");
        // Serial.println(sensorValue.sensorId, HEX);

        // if (sensorValue.sensorId == SH2_GYROSCOPE_CALIBRATED)
        // {
        //     Serial.print("GX = ");
        //     Serial.print(sensorValue.un.gyroscope.x, 5);

        //     Serial.print("  GY = ");
        //     Serial.print(sensorValue.un.gyroscope.y, 5);

        //     Serial.print("  GZ = ");
        //     Serial.println(sensorValue.un.gyroscope.z, 5);
        // }

        if (sensorValue.sensorId == SH2_GYROSCOPE_CALIBRATED)
        {
            Serial.print("GX = ");
            Serial.print(sensorValue.un.gyroscope.x, 5);

            Serial.print("  GY = ");
            Serial.print(sensorValue.un.gyroscope.y, 5);

            Serial.print("  GZ = ");
            Serial.println(sensorValue.un.gyroscope.z, 5);
        }
    }
}