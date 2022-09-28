/***********************************************************************
 * Project      :     Example_DumpFile
 * Description  :     This example shows how to read a file from the SD card using the
                      SD library and send it over the serial port.
 * Hardware     :     tiny32_v3
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     04/07/2022
 * Revision     :     1.0
 * Rev1.0       :     Origital
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     admin@innovation.co.th
 * TEL          :     +66 82-380-3299
 ***********************************************************************/
#include <Arduino.h>
#include <tiny32_v3.h>
#include <SPI.h>
#include <SD.h>

tiny32_v3 mcu;

const int chipSelect = 5;

boolean sdcard_flag = 0;


void setup()
{
  Serial.begin(115200);

  int _error_cnt = 0;

  Serial.printf("*** tiny32 Example_DumpFile project ***\r\n");
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

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt");

  // if the file is available, write to it:
  if (dataFile) {
    Serial.println("\\r\nStart Dump file\r\n");
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    dataFile.close();
    Serial.println("\r\nDump file completed\r\n");
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }

  mcu.buzzer_beep(2);
}

void loop()
{
}
