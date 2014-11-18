Ubidots-Arduino YÚN
===================

Ubidots-Arduino-YUN is an Arduino library for interacting with Ubidots through its API.

The Arduino Yún is a microcontroller board based on the ATmega32u4 and the Atheros AR9331. The Atheros processor supports a Linux distribution based on OpenWrt named OpenWrt-Yun. The board has built-in Ethernet and WiFi support, a USB-A port, micro-SD card slot, 20 digital input/output pins, a 16 MHz crystal oscillator, and a micro USB connection.

Components
----------

*  Arduino Yún:

.. figure:: https://github.com/ubidots/ubidots-arduino-yun/blob/master/pictures/YUN.jpg
    :name: arduino-yún
    :align: center
    :alt: arduino-yún

* 2 Lua files, those files are to get a token and post and get a value of your variable. 

   * `Post Lua file <https://github.com/ubidots/ubidots-arduino-yun/blob/master/Content/ubidots_post.lua?>`_
   * `Get Lua file <https://github.com/ubidots/ubidots-arduino-yun/blob/master/Content/ubidots_get.lua?>`_


Install the Library
-------------------

1. `Download the library as a ZIP file <https://github.com/ubidots/ubidots-arduino-yun/raw/master/Content/UbidotsArduinoYUN.zip?raw=true>`_

2. Open the Arduino IDE and go to "Sketch" --> "Import Library" --> "Add Library".

3. Select the downloaded ZIP file



Add the LUA files to Arduino YÚN
--------------------------------


1. Connect your YÚN to the power supply.

2. Check there will be an unsecure wifi network start with Arduino Yun or Dragino - xxxxxxxxxxxx show in wifi connection.

.. figure:: https://github.com/ubidots/ubidots-dragino/blob/master/Content/yun_wifi.png
    :name: yun-wifi
    :align: center
    :alt: yun-wifi

3. Connect to this network and so we can enter 192.168.240.1 into the broswer and see the configure page of ms14. The default pass is "arduino".

.. figure:: https://github.com/ubidots/ubidots-dragino/blob/master/Content/yun_pass.jpg
    :name: yun-pass
    :align: center
    :alt: yun-pass

4. Once you are connected press "system".

.. figure:: https://github.com/ubidots/ubidots-dragino/blob/master/Content/yun_system.jpg
    :name: yun-system
    :align: center
    :alt: yun-system

5. Connect YÚN to your SSID and press "configure & restart". This may take several minutes.

.. figure:: https://github.com/ubidots/ubidots-dragino/blob/master/Content/yun_config.jpg
    :name: yun-config
    :align: center
    :alt: yun-config

6. Now you can see in the port tab of the Arduino IDE (1.5.7) the dragino with the IP. Takes note of this IP.

.. figure:: https://github.com/ubidots/ubidots-dragino/blob/master/Content/yun_ip.jpg
    :name: yun-ip
    :align: center
    :alt: yun-ip

7. Open WinSCP and place the IP that scored before, use SCP protocol, User: root and pass: arduino.

.. figure:: https://github.com/ubidots/ubidots-dragino/blob/master/Content/yun_winscp.jpg
    :name: winscp
    :align: center
    :alt: winscp

8. Now add the lua files in the root directory. 

.. figure:: https://github.com/ubidots/ubidots-dragino/blob/master/Content/yun_root.jpg
    :name: yun-root
    :align: center
    :alt: yun-root


A Quick example
----------------
Here's a quick example of how to use the library, with the serial terminal of Arduino:


.. code-block:: cpp

	/*
	Simple example for Arduino YÚN
	This sketch connects to Ubidots (http://www.ubidots.com) using an Arduino YÚN Hardware
	
	Components:
	  * Arduino YÚN Hardware
	  * LUA files of Ubidots
	
	Created 5 Aug 2014
	by Mateo Vélez
	
	This code is in the public domain.
	
	*/
	#include <ubidots_arduinoYUN.h>
	#include <Process.h>
	
	
	String token = "7lIgBfuGWCh56j1ucunhfnYrMPLJh1";                    //your Ubidots token
	String idvari = "546b83dd7625421b7c01ac75";                                   //this is de ID of the variaable that do you want to know
	Ubidots ubiclient(token);                                                     //initializes the Ubidots library 
	
	void setup() {
	  // start serial port:
	  Bridge.begin();                                                            //initializes the bridge library
	  Console.begin();                                                           //initializes the console                     
	  Console.println("Ubidots client");                                          
	}
	
	void loop() {
	  int value = 2014;                                                          //an arbitrary value to be sent to Ubidots
	  ubiclient.save_value(idvari,String(value));                                //the function to save value in your variable 
	
	  Console.println("Reading last value...");  
	  String incomingValue;                                                      
	  incomingValue = ubiclient.get_value(idvari);                               //reads value from the Ubidots variable
	  Console.println(incomingValue);
	}


Explanation of the functions of the library
-------------------------------------------

Ubidots ubiclient():
````````````````````
.. code-block:: cpp

    Ubidots ubiclient(token);

=======  ========  =================================
Type     Argument  Description
=======  ========  =================================
String   token     Your Ubidots token
=======  ========  =================================

Initializes a Ubidots client. This is most likely to be the first Ubidots library function to call.

save_value()
````````````````````
.. code-block:: cpp

    boolean = ubiclient.save_value(idvari, String(incomingByte), ctext)
=======  ============  ===================================
Type     Argument      Description
=======  ============  ===================================
String   idvari        ID of the variable to save
String   incomingByte  The value of the sensor
=======  ============  ====================================

Saves a a value to Ubidots. Returns true upon success. Returns false upon error.


get_value()
```````````
.. code-block:: cpp

    readvalue = ubiclient.get_value(idvari);

==================  ===========  =============================================
Type                Argument     Description
==================  ===========  =============================================
String              idvari       ID of the variable that you want make request 
==================  ===========  =============================================

Gets a value from Ubidots. Returns a String containing the last value of the variable.
