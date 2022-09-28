# tiny32_SDCard
Example code tiny32 interface with SD card via SPI bus

*********************************************************************


##### Library need to clone from github ####
1. git clone https://github.com/tenergyinnovation/tiny32_v3.git

2. git clone https://github.com/arduino-libraries/SD.git
   - comment file "Sd2PinMap.h" at line 527 => //#error Architecture or board not supported. 


#### Hardware configuration ####
*** SPI pin between tiny32 to SD card ****

MISO --> 19

MOSI --> 23

SCK  --> 18

CS   --> 5 



#### Hardware Link ####
https://www.allnewstep.com/product/557/%E0%B9%82%E0%B8%A1%E0%B8%94%E0%B8%B9%E0%B8%A5%E0%B8%9A%E0%B8%B1%E0%B8%99%E0%B8%97%E0%B8%B6%E0%B8%81%E0%B8%82%E0%B9%89%E0%B8%AD%E0%B8%A1%E0%B8%B9%E0%B8%A5%E0%B8%A5%E0%B8%87-micro-sd-card-micro-sd-card-module-micro-sd-card-module

https://randomnerdtutorials.com/esp32-microsd-card-arduino/

https://microcontrollerslab.com/microsd-card-esp32-arduino-ide/
