# Arduino YÚN

Ubidots-Arduino-YUN is an Arduino library for interacting with Ubidots through its API.

The Arduino Yún is a microcontroller board based on the ATmega32u4 and the Atheros AR9331. The Atheros processor supports a Linux distribution based on OpenWrt named OpenWrt-Yun. The board has built-in Ethernet and WiFi support, a USB-A port, micro-SD card slot, 20 digital input/output pins, a 16 MHz crystal oscillator, and a micro USB connection.

**IMPORTANT NOTE**: During the tests of this sample library we noticed that due to the hardware architecture the library presents inconsistencies making a POST and a GET request inside the same code. If you find the solution to this inconsistency, we invite you to make the Pull Request for our review.

<aside class="warning">We upgrade the library to send values with name of a variable because the YUN library to run shell command in linux has small buffer to save a message.</aside>

## Requiremets

* [Arduino YÚN](https://www.arduino.cc/en/Main/ArduinoBoardYun)
* [Arduino IDE 1.6.5 or higher](https://www.arduino.cc/en/Main/Software)
* [Ubidots Arduino YÚN library](https://github.com/ubidots/ubidots-arduino-yun/archive/v2.0.0.zip)

## Setup

1. Connect your Arduino Yún to the power supply.
2. Check for an unsecure wifi network starting with “Arduino Yun”
3. Connect to this network and enter 192.168.240.1 into a web broswer to see the configuration page of the Arduino Yún. The default password is “arduino”
4. Once you’re connected click on “system”
5. Specify the Wireless Parameters of your Wi-Fi connection, then press “configure & restart”. This may take several minutes.
6. Download the UbidotsYUN library [here](https://github.com/ubidots/ubidots-arduino-yun/archive/v2.0.0.zip)
7. Go to the Arduino IDE, click on **Sketch -> Include Library -> Add .ZIP Library**
8. Select the .ZIP file of Ubidots_FONA and then "Accept" or "Choose"
9. Do the same to add the Adafruit_FONA library.
10. Close the Arduino IDE and open it again.

<aside class="alert">
Use the Arduino 1.6.5 version or newer with the Arduino YÚN.
</aside>

**Note:** The library will create a new Ubidots Device named **"YUN"**. If you desire to assign a different device name or label, you can add it the add in the `setup` of your code the following lines:

* To change the Device Name:

> client.setDeviceName("New_name");

* To change the Device label:

> client.setDeviceLabel("New_label");

## Send one value to Ubidots

To send a value to Ubidots, go to **Sketch -> Examples -> UbidotsYUN library** and select the "saveValue" example. Set your Ubidots personal **TOKEN**

```c++
// This example is to save a variable to the Ubidots API

/****************************************
 * Include Libraries
 ****************************************/
#include <UbidotsYUN.h>

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "YOUR_TOKEN_HERE"
#define VARIABLE_LABEL "temperature"  // Change for your variable label desired

Ubidots client(TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/

//Put here your auxiliar functions

/****************************************
 * Main Functions
 ****************************************/
void setup() {
  client.init();
  Serial.begin(9600);
}

void loop() {
  float value = analogRead(A0);
  client.add(VARIABLE_LABEL, value); // Change for your variable name
  client.sendAll();
  delay(1000);
}


```


## Get one value from Ubidots

To get the last value of a variable from Ubidots, go to **Sketch -> Examples -> UbidotsYUN library** and select the "getValue" example.
Put your Ubidots token, device label, and variable label where indicated.

```c++
// This example is to obtain a variable value from Ubidots

/****************************************
 * Include Libraries
 ****************************************/
#include <UbidotsYUN.h>

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "YOUR_TOKEN_HERE"
#define DEVICE_LABEL "yun" // Assign the device label where the variable desired is located
#define VARIABLE_LABEL "temperature" // Assign the variable label desired to obtain data

Ubidots client(TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/

//Put here your auxiliar functions

/****************************************
 * Main Functions
 ****************************************/
void setup() {
  client.init();
  Serial.begin(9600);
}

void loop() {
  float value = client.getValue(DEVICE_LABEL, VARIABLE_LABEL);
  Serial.print("the value obtained is: ");
  Serial.println(value);
  delay(5000);
}


```


## Send multiple values to Ubidots

To send multiple values you can use our example in our library or copy the next code and do not forget to change set there your **TOKEN**

```c++
// This example is to save multiple variables to the Ubidots API

/****************************************
 * Include Libraries
 ****************************************/
#include <UbidotsYUN.h>

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "YOUR_TOKEN_HERE"
#define VARIABLE_LABEL_1 "temperature"  // Change for your variable label desired
#define VARIABLE_LABEL_2 "humidity"  // Change for your variable label desired
#define VARIABLE_LABEL_3 "pressure"  // Change for your variable label desired

Ubidots client(TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/

//Put here your auxiliar functions

/****************************************
 * Main Functions
 ****************************************/
void setup() {
  client.init();
  Serial.begin(9600);
}

void loop() {
  float value_1 = analogRead(A0);
  float value_2 = analogRead(A1);
  float value_3 = analogRead(A2);
  client.add(VARIABLE_LABEL_1, value_1);
  client.add(VARIABLE_LABEL_2, value_2);
  client.add(VARIABLE_LABEL_3, value_3);
  client.sendAll();
  delay(1000);
}

```

The library allow you send just 5 variables per request. But don't worry for that, if you desire send more than 5 variables, refer to the example below. Don't forget assign your Ubidots TOKEN, and the variables labels where is indicated:

```c++
// This example is to save multiple variables to the Ubidots API

/****************************************
 * Include Libraries
 ****************************************/
#include <UbidotsYUN.h>

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "YOUR_TOKEN_HERE"
#define VARIABLE_LABEL_1 "temperature-1"  // Change for your variable label desired
#define VARIABLE_LABEL_2 "humidity-1"  // Change for your variable label desired
#define VARIABLE_LABEL_3 "pressure-1"  // Change for your variable label desired
#define VARIABLE_LABEL_4 "temperature-2"  // Change for your variable label desired
#define VARIABLE_LABEL_5 "humidity-2"  // Change for your variable label desired
#define VARIABLE_LABEL_6 "pressure-2"  // Change for your variable label desired
#define VARIABLE_LABEL_7 "distance"  // Change for your variable label desired

Ubidots client(TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/

//Put here your auxiliar functions

/****************************************
 * Main Functions
 ****************************************/
void setup() {
  client.init();
  Serial.begin(9600);
}

void loop() {
  float value = analogRead(A0);

  client.add(VARIABLE_LABEL_1, value);
  client.add(VARIABLE_LABEL_2, value);
  client.add(VARIABLE_LABEL_3, value);
  client.add(VARIABLE_LABEL_4, value);
  client.sendAll();
  client.add(VARIABLE_LABEL_5, value);
  client.add(VARIABLE_LABEL_6, value);
  client.add(VARIABLE_LABEL_7, value);
  client.sendAll();
  delay(1000);
}
```
