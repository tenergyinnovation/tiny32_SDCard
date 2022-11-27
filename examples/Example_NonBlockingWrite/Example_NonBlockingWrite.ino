/***********************************************************************
 * Project      :     Example_NonBlockingWrite
 * Description  :     This example demonstrates how to perform non-blocking writes
 *                    to a file on a SD card. The file will contain the current millis()
 *                    value every 10ms. If the SD card is busy, the data will be buffered
 *                    in order to not block the sketch.
 *
 *                    NOTE: myFile.availableForWrite() will automatically sync the
 *                          file contents as needed. You may lose some unsynced data
 *                          still if myFile.sync() or myFile.close() is not called.
 * 
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

// File object to represent file
File txtFile;

// string to buffer output
String buffer;

const int chipSelect = 5;
const char filename[] = "demo.txt";
boolean sdcard_flag = 0;

unsigned long lastMillis = 0;

void setup()
{
  Serial.begin(115200);

  int _error_cnt = 0;

  Serial.printf("*** tiny32 Example_NonBlockingWrite project ***\r\n");
  mcu.library_version();
  mcu.buzzer_beep(1);
  vTaskDelay(1000);

  // reserve 1kB for String used as a buffer
  buffer.reserve(1024);

  // set LED pin to output, used to blink when writing
  pinMode(LED_BUILTIN, OUTPUT);

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

  
  // If you want to start from an empty file,
  // uncomment the next line:
  // SD.remove(filename);

  // try to open the file for writing
  txtFile = SD.open(filename, FILE_WRITE);
  if (!txtFile) {
    Serial.print("error opening ");
    Serial.println(filename);
    while (1);
  }

  // add some new lines to start
  txtFile.println();
  txtFile.println("Hello World!");

  mcu.buzzer_beep(2);
}

void loop()
{
  // check if it's been over 10 ms since the last line added
  unsigned long now = millis();
  if ((now - lastMillis) >= 10) {
    // add a new line to the buffer
    buffer += "Hello ";
    buffer += now;
    buffer += "\r\n";

    lastMillis = now;
  }

  // check if the SD card is available to write data without blocking
  // and if the buffered data is enough for the full chunk size
  unsigned int chunkSize = txtFile.availableForWrite();
  if (chunkSize && buffer.length() >= chunkSize) {
    // write to file and blink LED
    digitalWrite(LED_BUILTIN, HIGH);
    txtFile.write(buffer.c_str(), chunkSize);
    digitalWrite(LED_BUILTIN, LOW);

    // remove written data from buffer
    buffer.remove(0, chunkSize);
  }
}



