# Arduino YÚN 

Ubidots-Arduino-YUN is an Arduino library for interacting with Ubidots through its API.

The Arduino Yún is a microcontroller board based on the ATmega32u4 and the Atheros AR9331. The Atheros processor supports a Linux distribution based on OpenWrt named OpenWrt-Yun. The board has built-in Ethernet and WiFi support, a USB-A port, micro-SD card slot, 20 digital input/output pins, a 16 MHz crystal oscillator, and a micro USB connection.

## Requiremets

* [Arduino YÚN](https://www.arduino.cc/en/Main/ArduinoBoardYun)
* [Arduino IDE 1.6.5 or higher](https://www.arduino.cc/en/Main/Software)
* [Ubidots Arduino YÚN library](https://github.com/ubidots/ubidots-arduino-yun/archive/master.zip)

## Setup

1. Connect your Arduino Yún to the power supply.
2. Check for an unsecure wifi network starting with “Arduino Yun”
3. Connect to this network and enter 192.168.240.1 into a web broswer to see the configuration page of the Arduino Yún. The default password is “arduino”
4. Once you’re connected click on “system”
5. Specify the Wireless Parameters of your Wi-Fi connection, then press “configure & restart”. This may take several minutes.
6. Download the UbidotsYUN library [here](https://github.com/ubidots/Ubidots-CC3000/archive/master.zip)
7. Go to the Arduino IDE, click on **Sketch -> Include Library -> Add .ZIP Library**
8. Select the .ZIP file of Ubidots_FONA and then "Accept" or "Choose"
9. Do the same to add the Adafruit_FONA library.
10. Close the Arduino IDE and open it again.

<aside class="alert">
Use the Arduino 1.6.5 version or newer with the Arduino YÚN.
</aside>
<aside class="warning">
Make sure your Arduino is powered by a 1 amp or higher rated external power supply when using with the CC3000! Powering an Arduino + CC3000 from a computer/laptop USB port will lead to unstable behavior and lockups because the USB port can't supply enough power!
</aside>
    
## Send one value to Ubidots

To send a value to Ubidots, go to **Sketch -> Examples -> UbidotsYUN library** and select the "saveValue" example. Set your Ubidots personal **TOKEn**

```c++
#include <UbidotsYUN.h>
#define TOKEN "YOUR_TOKEN_HERE"


Ubidots client(TOKEN);

void setup() {
  client.init();
  Serial.begin(9600);

}

void loop() {
  float value = analogRead(A0);
  client.add("Variable_Name", value);
  client.sendAll(); 
}

```


## Get one value from Ubidots

To get the last value of a variable from Ubidots, go to **Sketch -> Examples -> UbidotsYUN library** and select the "getValue" example. 
Put your Ubidots token and variable ID where indicated, as well as the WiFi settings.
Upload the code, open the Serial monitor to check the results. If no response is seen, try unplugging your Arduino and then plugging it again. Make sure the baud rate of the Serial monitor is set to the same one specified in your code.

```c++
#include <UbidotsYUN.h>
#define TOKEN "YOUR_TOKEN_HERE"
#define ID "YOUR_ID_HERE"

Ubidots client(TOKEN);

void setup() {
  client.init();
  Serial.begin(9600);
}

void loop() {
  float value = client.getValue(ID);
}

```


## Send multiple values to Ubidots

To send multiple values you can use our example in our library or copy the next code and do not forget to change set there your **TOKEN**

```c
#include <UbidotsYUN.h>
#define TOKEN "YOUR_TOKEN_HERE"


Ubidots client(TOKEN);

void setup() {
  client.init();
  Serial.begin(9600);

}

void loop() {
  float value = analogRead(A0);
  float value1 = analogRead(A1);
  float value2 = analogRead(A2);
  client.add("Variable_Name", value);
  client.add("Variable_Name_2", value1);
  client.add("Variable_Name_3", value2);
  client.sendAll(); 
}

```