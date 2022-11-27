/***********************************************************************
 * Project      :     Example_Files
 * Description  :     This example shows how print out the files in a
 *                    directory on a SD card
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
File root;

const int chipSelect = 5;
boolean sdcard_flag = 0;

void printDirectory(File dir, int numTabs);


void setup()
{
  Serial.begin(115200);

  int _error_cnt = 0;

  Serial.printf("*** tiny32 Example_listfiles project ***\r\n");
  mcu.library_version();
  mcu.buzzer_beep(1);
  vTaskDelay(1000);

  
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

  root = SD.open("/");

  printDirectory(root, 0);

  Serial.println("done!");

  mcu.buzzer_beep(2);
}

void loop()
{
}


void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
