 t # SBP-Embedded
This is the embedded systems repository for the Solar Bench PRoject

## Guide
We will be using the Arduino IDE to help develop the software needed to control the ESP-32 microcontroller. The Arduino IDE is user-friendly,
well-documented, and is great for beginners.

### Steps
1) Visit the [Arduino website](https://www.arduino.cc/en/software) to install the latest version of the Arduino IDE.  
2) After getting the latest version of the Arduino IDE, follow [this tutorial](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/) as it provides an in-depth guide to adding the ESP32 board as a recognized board to the Arduino IDE (You may skip the installation test step, but ensure that the example sketches can be found).
3) Now you need to add all the necessary libraries to compile the program. Go to Sketch -> Include Library -> Manage Libraries and add the following libraries:  
    - Google Cloud IoT Core JWT  
    - PubSubClient  
    - MQTT 
    - Vector 
4) Go to Tools -> Board -> ESP32 Arduino. Select any ESP32 board.
5) Verify that the sketch compiles without errors. (Sketch -> Verify)

## Config Support
The following links are useful to help configure the Arduino Environment  
[Espressif Arduino Core Documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/index.html)  
[Example Tutorial](https://www.instructables.com/How-to-Add-WiFi-Control-to-Any-Project-ESP32-Begin/)  

## ESP Programming Help Commands  
[Link 1](https://www.esp32.com/viewtopic.php?t=4061)
[Link 2](https://githubmemory.com/repo/espressif/esptool/issues/662)
1) sudo python esptool.py write_flash_status --non-volatile 0
2) sudo python esptool.py --chip auto --port /dev/cu.usbserial-0001 --baud 115200 --before default_reset --after hard_reset write_flash -u --flash_mode dio --flash_freq 40m --flash_size 4MB 0x0 factory/factory_WROOM-32.bin
3) sudo python esptool.py --chip auto --port /dev/cu.usbserial-0001 --baud 115200 --before default_reset --after hard_reset write_flash -u --flash_mode dio --flash_freq 40m --flash_size 4MB 0x0 factory/factory_WROVER-32.bin
4) sudo python esptool.py erase_flash
5) sudo python esptool.py read_flash_status 
6) sudo python esptool.py flash_id


## Useful tutorials  
[Intro to ESP32](https://www.electronicshub.org/getting-started-with-esp32/)  
[EEPROM for ESP32](https://randomnerdtutorials.com/esp32-flash-memory/)  
[Install Google Cloud](https://geekflare.com/gcloud-installation-guide/)  
[Install Google Cloud Help](https://stackoverflow.com/questions/31037279/gcloud-command-not-found-while-installing-google-cloud-sdk)
[Google Cloud Platform for ESP32 1](https://www.youtube.com/watch?v=lRX8O1tzkpA)
[Google Cloud Platform for ESP32 2](http://nilhcem.com/iot/cloud-iot-core-with-the-esp32-and-arduino)  
[ESP32 Multithreading 1](https://randomnerdtutorials.com/esp32-dual-core-arduino-ide/)  
[ESP32 Multithreading 2](https://www.instructables.com/ESP32-With-Arduino-IDE-Multi-Core-Programming/)
