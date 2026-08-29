#include <Wire.h>
#include <Adafruit_BNO08x.h>

#define SDA_PIN 13
#define SCL_PIN 14
#define BNO085_ADDR 0x4B

Adafruit_BNO08x bno08x(-1);
sh2_SensorValue_t sensorValue;

unsigned long lastPrint = 0;

float r = 0;
float i = 0;
float j = 0;
float k = 0;

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

    if (!bno08x.enableReport(SH2_ROTATION_VECTOR, 100000))
    {
        Serial.println("Could not enable rotation vector");
        while (1) delay(10);
    }

    Serial.println("Rotation vector enabled!");
}

void loop()
{
    if (bno08x.wasReset())
    {
        Serial.println("BNO085 reset!");
        bno08x.enableReport(SH2_ROTATION_VECTOR, 100000);
    }

    if (bno08x.getSensorEvent(&sensorValue))
    {
        if (sensorValue.sensorId == SH2_ROTATION_VECTOR)
        {
            r = sensorValue.un.rotationVector.real;
            i = sensorValue.un.rotationVector.i;
            j = sensorValue.un.rotationVector.j;
            k = sensorValue.un.rotationVector.k;
        }
    }

    // Print every 500 ms
    if (millis() - lastPrint >= 500)
    {
        lastPrint = millis();

        Serial.print("R: ");
        Serial.print(r, 3);

        Serial.print("   I: ");
        Serial.print(i, 3);

        Serial.print("   J: ");
        Serial.print(j, 3);

        Serial.print("   K: ");
        Serial.println(k, 3);
    }
}