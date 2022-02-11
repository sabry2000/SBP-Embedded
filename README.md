# SBP-Embedded
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
4) Go to Tools -> Board -> ESP32 Arduino. Select any ESP32 board.
5) Verify that the sketch compiles without errors. (Sketch -> Verify)

## Config Support
The following links are useful to help configure the Arduino Environment  
[Espressif Arduino Core Documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/index.html)  
[Example Tutorial](https://www.instructables.com/How-to-Add-WiFi-Control-to-Any-Project-ESP32-Begin/)  

