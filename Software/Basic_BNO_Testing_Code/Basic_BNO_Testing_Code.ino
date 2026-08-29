// #include <Wire.h>
// #include <Adafruit_BNO08x.h>

// #define SDA_PIN 13
// #define SCL_PIN 14
// #define BNO085_ADDR 0x4B

// // We are using I2C, so reset is not controlled by the library.
// #define BNO08X_RESET -1

// Adafruit_BNO08x bno08x(BNO08X_RESET);
// sh2_SensorValue_t sensorValue;


// void setup()
// {
//     Serial.begin(115200);
//     delay(1000);

//     Serial.println("BNO085 test");

//     // Start I2C on GPIO13 (SDA) and GPIO14 (SCL)
//     Wire.begin(SDA_PIN, SCL_PIN);

//     // Initialise BNO085
//     if (!bno08x.begin_I2C(BNO085_ADDR, &Wire))
//     {
//         Serial.println("Failed to find BNO085!");
//         while (1)
//         {
//             delay(10);
//         }
//     }

//     Serial.println("BNO085 found!");

//     // Enable orientation report
//     if (!bno08x.enableReport(SH2_ROTATION_VECTOR))
//     {
//         Serial.println("Could not enable rotation vector");
//     }

//     // Enable accelerometer
//     if (!bno08x.enableReport(SH2_ACCELEROMETER))
//     {
//         Serial.println("Could not enable accelerometer");
//     }

//     // Enable gyroscope
//     if (!bno08x.enableReport(SH2_GYROSCOPE_CALIBRATED))
//     {
//         Serial.println("Could not enable gyroscope");
//     }

//     Serial.println("Reports enabled!");
//     Serial.println();
// }


// void loop()
// {
//     if (bno08x.wasReset())
//     {
//         Serial.println("BNO085 was reset!");

//         // Re-enable reports after reset
//         bno08x.enableReport(SH2_ROTATION_VECTOR);
//         bno08x.enableReport(SH2_ACCELEROMETER);
//         bno08x.enableReport(SH2_GYROSCOPE_CALIBRATED);
//     }

//     if (bno08x.getSensorEvent(&sensorValue))
//     {
//         switch (sensorValue.sensorId)
//         {
//             case SH2_ROTATION_VECTOR:

//                 Serial.print("Rotation quaternion: ");
//                 Serial.print("r = ");
//                 Serial.print(sensorValue.un.rotationVector.real, 3);

//                 Serial.print("  i = ");
//                 Serial.print(sensorValue.un.rotationVector.i, 3);

//                 Serial.print("  j = ");
//                 Serial.print(sensorValue.un.rotationVector.j, 3);

//                 Serial.print("  k = ");
//                 Serial.println(sensorValue.un.rotationVector.k, 3);

//                 break;


//             case SH2_ACCELEROMETER:

//                 Serial.print("Acceleration: ");
//                 Serial.print("X = ");
//                 Serial.print(sensorValue.un.accelerometer.x, 2);

//                 Serial.print("  Y = ");
//                 Serial.print(sensorValue.un.accelerometer.y, 2);

//                 Serial.print("  Z = ");
//                 Serial.println(sensorValue.un.accelerometer.z, 2);

//                 break;


//           case SH2_GYROSCOPE_CALIBRATED:
//             Serial.print("Gyroscope: ");
//             Serial.print("X = ");
//             Serial.print(sensorValue.un.gyroscope.x, 2);

//             Serial.print("  Y = ");
//             Serial.print(sensorValue.un.gyroscope.y, 2);

//             Serial.print("  Z = ");
//             Serial.println(sensorValue.un.gyroscope.z, 2);

//             break;
//         }
//     }

//     delay(10);
// }


#include <Wire.h>
#include <Adafruit_BNO08x.h>

#define SDA_PIN 13
#define SCL_PIN 14
#define BNO085_ADDR 0x4B

#define BNO08X_RESET -1

Adafruit_BNO08x bno08x(BNO08X_RESET);
sh2_SensorValue_t sensorValue;

unsigned long lastPrint = 0;
const unsigned long PRINT_INTERVAL = 500;  // Print every 1s

// Store latest measurements
float accelX = 0;
float accelY = 0;
float accelZ = 0;

float gyroX = 0;
float gyroY = 0;
float gyroZ = 0;

float quatR = 0;
float quatI = 0;
float quatJ = 0;
float quatK = 0;


void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println("BNO085 test");

    Wire.begin(SDA_PIN, SCL_PIN);

    if (!bno08x.begin_I2C(BNO085_ADDR, &Wire))
    {
        Serial.println("Failed to find BNO085!");
        while (1)
        {
            delay(10);
        }
    }

    Serial.println("BNO085 found!");

    bno08x.enableReport(SH2_ROTATION_VECTOR);
    bno08x.enableReport(SH2_ACCELEROMETER);
    bno08x.enableReport(SH2_GYROSCOPE_CALIBRATED);

    Serial.println("Reports enabled!");
    Serial.println();
}


void loop()
{
    // Continuously read incoming BNO085 data
    if (bno08x.wasReset())
    {
        Serial.println("BNO085 was reset!");

        bno08x.enableReport(SH2_ROTATION_VECTOR);
        bno08x.enableReport(SH2_ACCELEROMETER);
        bno08x.enableReport(SH2_GYROSCOPE_CALIBRATED);
    }

    if (bno08x.getSensorEvent(&sensorValue))
    {
        switch (sensorValue.sensorId)
        {
            case SH2_ROTATION_VECTOR:
                quatR = sensorValue.un.rotationVector.real;
                quatI = sensorValue.un.rotationVector.i;
                quatJ = sensorValue.un.rotationVector.j;
                quatK = sensorValue.un.rotationVector.k;
                break;

            case SH2_ACCELEROMETER:
                accelX = sensorValue.un.accelerometer.x;
                accelY = sensorValue.un.accelerometer.y;
                accelZ = sensorValue.un.accelerometer.z;
                break;

            case SH2_GYROSCOPE_CALIBRATED:
                gyroX = sensorValue.un.gyroscope.x;
                gyroY = sensorValue.un.gyroscope.y;
                gyroZ = sensorValue.un.gyroscope.z;
                break;
        }
    }


    // Only print every 500 ms
    if (millis() - lastPrint >= PRINT_INTERVAL)
    {
        lastPrint = millis();

        Serial.println("-----------------------------");

        Serial.print("Acceleration: ");
        Serial.print("X=");
        Serial.print(accelX, 2);
        Serial.print("  Y=");
        Serial.print(accelY, 2);
        Serial.print("  Z=");
        Serial.println(accelZ, 2);

        Serial.print("Gyroscope:    ");
        Serial.print("X=");
        Serial.print(gyroX, 2);
        Serial.print("  Y=");
        Serial.print(gyroY, 2);
        Serial.print("  Z=");
        Serial.println(gyroZ, 2);

        Serial.print("Quaternion:   ");
        Serial.print("R=");
        Serial.print(quatR, 3);
        Serial.print("  I=");
        Serial.print(quatI, 3);
        Serial.print("  J=");
        Serial.print(quatJ, 3);
        Serial.print("  K=");
        Serial.println(quatK, 3);
    }
}