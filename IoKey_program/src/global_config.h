#ifndef Global_Config_h
#define Global_Config_h
#include <stdint.h>


#define DEVICE_ID 1
#define TIME_TO_SLEEP_SECONDS 3600


const uint8_t lorawan_dev_eui[8] = {0x22, 0x32, 0x33, 0x00, 0x00, 0x88, 0x88, 0x02};
const uint8_t lorawan_app_eui[8] = {0x45, 0x43, 0x4f, 0x4c, 0x45, 0x49, 0x4f, 0x45};
const uint8_t lorawan_app_key[16] = {0xCE, 0x23, 0x76, 0x27, 0x24, 0x82, 0x78, 0x8C, 0x69, 0x23, 0xED, 0x59, 0x78, 0xDF, 0xF4, 0x5C};

#define SENSOR_ADDRESS_TOP 0x20
#define SENSOR_ADDRESS_MIDDLE 0x30
#define SENSOR_ADDRESS_BOTTOM 0x40

#define LORAWAN_JOIN_TIMEOUT_S 10
#define LORAWAN_FRAME_LENGTH 8
#define DEEP_SLEEP_WAKEUP_PIN GPIO_NUM_7

#define I2C_CLOCK_SPEED 100000
#define BAUD_RATE 115200

#define BLE_SERVER_NAME String(DEVICE_ID)

// void gigascan()
// {
//     Wire.begin();

//     Serial.begin(BAUD_RATE);
//     while (!Serial)
//         delay(10);
//     Serial.println("\nI2C Scanner");
//     byte error, address;
//     int nDevices;
//     for (address = 1; address < 127; address++)
//     {
//         // The i2c_scanner uses the return value of
//         // the Write.endTransmisstion to see if
//         // a device did acknowledge to the address.
//         Wire.beginTransmission(address);
//         error = Wire.endTransmission();

//         if (error == 0)
//         {
//             Serial.print("I2C device found at address 0x");
//             if (address < 16)
//                 Serial.print("0");
//             Serial.print(address, HEX);
//             Serial.println("  !");

//             nDevices++;
//         }
//         else if (error == 4)
//         {
//             Serial.print("Unknown error at address 0x");
//             if (address < 16)
//                 Serial.print("0");
//             Serial.println(address, HEX);
//         }
//     }
//     if (nDevices == 0)
//         Serial.println("No I2C devices found\n");
//     else
//         Serial.println("done\n");

//     delay(5000); // wait 5 seconds for next scan
// }

#endif // Global_Config_h
