/***********************************************************************
 * Project      :     Example_CardInfo
 * Description  :     This example shows how use the utility libraries on which the'
                      SD library is based in order to get info about your SD card.
                      Very useful for testing a card when you're not sure whether its working or not.
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

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

void setup()
{
    Serial.begin(115200);

    int _error_cnt = 0;

    Serial.printf("*** tiny32 Example_CardInfo project ***\r\n");
    mcu.library_version();
    mcu.buzzer_beep(1);

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

  // print the type of card
  Serial.println();
  Serial.print("Card type:         ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
      mcu.buzzer_beep(3);
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    mcu.buzzer_beep(3);
    while (1);
  }

  Serial.print("Clusters:          ");
  Serial.println(volume.clusterCount());
  Serial.print("Blocks x Cluster:  ");
  Serial.println(volume.blocksPerCluster());

  Serial.print("Total Blocks:      ");
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println();

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("Volume type is:    FAT");
  Serial.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
  Serial.print("Volume size (Kb):  ");
  Serial.println(volumesize);
  Serial.print("Volume size (Mb):  ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Gb):  ");
  Serial.println((float)volumesize / 1024.0);

  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
  mcu.buzzer_beep(2);

}

void loop()
{
}
