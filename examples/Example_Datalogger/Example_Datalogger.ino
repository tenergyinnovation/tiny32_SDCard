/***********************************************************************
 * Project      :     Example_Datalogger
 * Description  :     This example shows how to log data from three analog sensors
                      to an SD card using the SD library.
 * Hardware     :     tiny32_v3
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     04/07/2022
 * Revision     :     1.0
 * Rev1.0       :     Origital
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     admin@innovation.co.th
 * TEL          :     +66 82-308-3299
 ***********************************************************************/
#include <Arduino.h>
#include <tiny32_v3.h>
#include <SPI.h>
#include <SD.h>

tiny32_v3 mcu;

const int chipSelect = 5;

boolean sdcard_flag = 0;

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

void setup()
{
  Serial.begin(115200);

  int _error_cnt = 0;

  Serial.printf("*** tiny32 Example_Datalogger project ***\r\n");
  mcu.library_version();

 /************ SD card Initial *************/
  Serial.print("Info: Initializing SD card...");
  do
  {
    sdcard_flag = SD.begin(chipSelect);
    _error_cnt++;
    Serial.printf("# ");
    vTaskDelay(1000);
  } while (!sdcard_flag && (_error_cnt < 5));

  if (!sdcard_flag)
  {
    Serial.println("--> failed\r\n");
    Serial.println("\r\nError: !!initialization failed. Things to check: --> fail");
    Serial.println("1. is a card inserted?");
    Serial.println("2. is your wiring correct?");
    Serial.println("3. did you change the chipSelect pin to match your shield or module?");
    Serial.println("Note: press reset or reopen this serial monitor after fixing your issue!");
    mcu.buzzer_beep(4);
    while(1);
  }
  else
  {
    Serial.println("--> passed");
    mcu.buzzer_beep(1);
    vTaskDelay(1000);
  }
  Serial.println("card initialized.");

  mcu.buzzer_beep(2);
}

void loop()
{

  String _dataString = "";
  int _sensor_value;

  for (int i = 0; i < 10; i++)
  {
    _sensor_value = analogRead(33); // Analog read from PIN33 ;
    _dataString += String(_sensor_value);
    if (i < 9)
    _dataString += ",";
    vTaskDelay(100);
  }

  

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile)
  {
    dataFile.println(_dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(_dataString);
  }
  // if the file isn't open, pop up an error:
  else
  {
    Serial.println("error opening datalog.txt");
  }
}
