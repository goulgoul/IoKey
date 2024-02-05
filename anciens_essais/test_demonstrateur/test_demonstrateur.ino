#include <I2CSoilMoistureSensor.h>
#include <Wire.h>
#include <esp_sleep.h>

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  30        /* Time ESP32 will go to sleep (in seconds) */
#define BUTTON_PIN_BITMASK 0x200000000 // 2^33 in hex
#define dry 210
#define wet 510



RTC_DATA_ATTR int bootCount = 0;

//I2CSoilMoistureSensor sensor;

I2CSoilMoistureSensor topSensor(0x20);
I2CSoilMoistureSensor middleSensor(0x21);
I2CSoilMoistureSensor bottomSensor(0x22);

/*
Method to print the reason by which ESP32
has been awaken from sleep
*/

void Sleep(){
 
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("\nSetup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
  " Seconds");
  Serial.println("Going to sleep..");
  esp_deep_sleep_start();
  
}


void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO");break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}



void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  topSensor.begin();
  middleSensor.begin();
  bottomSensor.begin();

  Serial.begin(115200);
  //sensor.begin();
  delay(1000); // give some time to boot up
  print_wakeup_reason();
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  pinMode(6,OUTPUT);
  pinMode(7,INPUT_PULLUP);

  //Serial.print("I2C Soil Moisture Sensor Address: ");
  //Serial.println(sensor.getAddress(),HEX);
  //Serial.print("Sensor Firmware version: ");
  //Serial.println(sensor.getVersion(),HEX);

  Serial.println("Top Sensor");
  Serial.print("Address: ");
  Serial.println(topSensor.getAddress(),HEX);
  Serial.print("Firmware version: ");
  Serial.println(topSensor.getVersion(),HEX);
  Serial.println();
  Serial.println();

  Serial.println("Middle Sensor");
  Serial.print("Address: ");
  Serial.println(middleSensor.getAddress(),HEX);
  Serial.print("Firmware version: ");
  Serial.println(middleSensor.getVersion(),HEX);
  Serial.println();
  Serial.println();

  Serial.println("Bottom Sensor");
  Serial.print("Address: ");
  Serial.println(middleSensor.getAddress(),HEX);
  Serial.print("Firmware version: ");
  Serial.println(bottomSensor.getVersion(),HEX);
  Serial.println();
  Serial.println();
  
  //while(sensor.isBusy()) delay(50);
  
  //int value = sensor.getCapacitance();
  //int pre = map(value, dry, wet, 0, 100);
  //Serial.print("Humidity: ");

  //Serial.print(pre);
  //Serial.print("% ");
  while (topSensor.isBusy()) delay(50);
  unsigned int topCapacitance = topSensor.getCapacitance();
  int pre = map(topCapacitance, dry, wet, 0, 100);
  Serial.print("Soil Capacitance_top: ");
  //Serial.print("top = ");
  Serial.print(pre);
  Serial.print("% ");
  int topTemperature = topSensor.getTemperature();
  Serial.print(", Temperature_top: ");
  //Serial.print("top = "); 
  Serial.print(topTemperature/(float)10);
  topSensor.sleep();

  while (middleSensor.isBusy()) delay(50);
  unsigned int middleCapacitance = middleSensor.getCapacitance();
  int sec= map(middleCapacitance, dry, wet, 0, 100);
  Serial.print("\nSoil Capacitance_middle: ");
  //Serial.print("middle = ");
  Serial.print(sec);
  Serial.print("% ");
  int middleTemperature = middleSensor.getTemperature();
  Serial.print(", Temperature_middle: ");
  //Serial.print("middle = "); 
  Serial.print(middleTemperature/(float)10);
  topSensor.sleep();

  while (bottomSensor.isBusy()) delay(50);
  unsigned int bottomCapacitance = bottomSensor.getCapacitance();
  int bot= map(bottomCapacitance, dry, wet, 0, 100);
  Serial.print("\nSoil Capacitance_bottom: ");
  //Serial.print("middle = ");
  Serial.print(bot);
  Serial.print("% ");
  int bottomTemperature = bottomSensor.getTemperature();
  Serial.print(", Temperature_bottom: ");
  //Serial.print("middle = "); 
  Serial.print(bottomTemperature/(float)10);
  topSensor.sleep();


  //Serial.print("soil moisture Capacitance: ");
  //Serial.print(sensor.getCapacitance()); 
  //Serial.print(", Temperature: ");
  //Serial.print(sensor.getTemperature()/(float)10);
  //sensor.sleep();
  for (int i = 0; i < 5; i++) {
    digitalWrite(6, HIGH);
    delay(500);
    digitalWrite(6, LOW);
    delay(500);
  }
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_7,1 );
  Sleep();
  Serial.flush(); 
  
  


  //Sleep();
 
  Serial.println();

  



  
}

void loop() {
  // put your main code here, to run repeatedly:
  

}