Ubidots-Arduino YÚN
===================

Ubidots-Arduino-YUN is an Arduino library for interacting with Ubidots through its API.

The Arduino Yún is a microcontroller board based on the ATmega32u4 and the Atheros AR9331. The Atheros processor supports a Linux distribution based on OpenWrt named OpenWrt-Yun. The board has built-in Ethernet and WiFi support, a USB-A port, micro-SD card slot, 20 digital input/output pins, a 16 MHz crystal oscillator, and a micro USB connection.

Components
----------

*  Arduino Yún:

.. figure:: /_static/devices/YUN.jpg
    :name: arduino-yún
    :align: center
    :alt: arduino-yún

* Lua files. Download `here <http://app.ubidots.com/accounts/signin/>`_


Install the Library
-------------------

1. Download the library as a ZIP file `here <http://app.ubidots.com/accounts/signin/>`_

2. Open the Arduino IDE and go to "Sketch" --> "Import Library" --> "Add Library".

3. Select the downloaded ZIP file



Add the LUA files to Arduino YÚN
--------------------------------

1. Connect your dragino to the power supply.

2. Check there will be an unsecure wifi network start with Arduino Yun - xxxxxxxxxxxx show in wifi connection.

.. figure:: /_static/devices/yun_wifi.png
    :name: arduino-yún-wifi
    :align: center
    :alt: arduino-yún-wifi

3. Connect to this network and so we can enter 192.168.240.1 into the broswer and see the configure page of ms14. The default pass is "arduino".

.. figure:: /_static/devices/yun_pass.jpg
    :name: arduino-yún-pass
    :align: center
    :alt: arduino-yún-pass

4. Once you are connected press "system".

.. figure:: /_static/devices/yun_system.jpg
    :name: arduino-yún-system
    :align: center
    :alt: arduino-yún-system

5. Connect dragino to your SSID and press "configure & restart". This may take several minutes.

.. figure:: /_static/devices/yun_config.jpg
    :name: arduino-yún-config
    :align: center
    :alt: arduino-yún-config

6. Now you can see in the port tab of the Arduino IDE (1.5.7) the dragino with the IP. Takes note of this IP.

.. figure:: /_static/devices/yun_ip.jpg
    :name: arduino-yún-ip
    :align: center
    :alt: arduino-yún-ip

7. Open WinSCP and place the IP that scored before, use SCP protocol, User: root and pass: arduino.

.. figure:: /_static/devices/yun_winscp.jpg
    :name: winscp
    :align: center
    :alt: winscp

8. Now add the lua files in the root directory. 

.. figure:: /_static/devices/yun_root.jpg
    :name: yún-root
    :align: center
    :alt: yún-root


Preparing your Ubidots Account
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
In your Ubidots account, create a Data source called "Arduino Yún" and then a variable called "My variable":

1. As a `logged in user <http://app.ubidots.com/accounts/signin/>`_
   navigate to the "Sources" tab.

.. figure:: /_static/devices/sources.png
    :name: Sources Tab - Ubidots
    :scale: 60%
    :align: center
    :alt: Sources Tab - Ubidots

2. Create a data source called "Arduino Yún" by clicking
   on the orange button located in the upper right corner of the screen:

.. figure:: /_static/devices/new-source.png
    :name: New Data Source
    :scale: 60%
    :align: center
    :alt: New Data Source

3. Click on the created Data Source and then on "Add New Variable":

.. figure:: /_static/devices/yun_newvar.png
    :name: New Variable
    :scale: 60%
    :align: center
    :alt: New Variable

4. Take note of the variable's ID to which you want to send data. We'll need it later to include in our core:

.. figure:: /_static/devices/yun-id.png
    :name: Variable ID
    :scale: 60%
    :align: center
    :alt: Variable ID

5. Create a token under "My Profile" tab. We'll need it later for our code:

.. figure:: /_static/devices/electricimp_token.png
    :name: Token creation
    :scale: 60%
    :align: center
    :alt: Token creation

A Quick example
----------------
Here's a quick example of how to use the library, with the serial terminal of Arduino:


.. code-block:: cpp

	  /*
	  Simple example to Dragino

	  This sketch connects to Ubidots (http://www.ubidots.com) using an Dragino Hardware

	  Is a simple example to explain the functions of the Dragino library


	  Components:
	  * Dragino Hardware
	  * LUA files of Ubidots

	  Created 5 Aug 2014
	  by Mateo Vélez

	  This code is in the public domain.

	  */
		#include <ubidots_dragino.h>
		#include <Process.h>


		String api = "5ca9b10038e49e0492c6794f9043f0918ddcbd26";                    //your API key
		String idvari = "53baaf3c76254244e1c8e408";                                 //this is de ID of the variaable that do you want to know
		Ubidots ubiclient(api);                                                     //initializes the Ubidots library 

		void setup() {
		  // start serial port:
		  Bridge.begin();                                                           //initializes the bridge library
		  Console.begin();                                                          //initializes the console

		  while (!Console);                                                         //wait for Network Serial to open
		  Console.println("Ubidots client");                                        
		  ubiclient.ubitoken(api);                                                  //get the token to the communication with Ubidots
		  delay(20);
		  
		}

		void loop() {
		 
		  int incomingByte = 678;                                                   //a random value for post it to Ubidots
		  String idvari2= "53baaf3c76254244e1c8e408";                               //the ID of the variable that do you want to post
		  String valor;                                                             //a random variable to save the value after that you ask to the Ubidots API
		  valor = ubiclient.get_value(idvari);                                      //the function to get the value of your variable, return the value
		  Console.print(valor);
		  ubiclient.save_value(idvari2,String(incomingByte));                       //the function to save value in your variable
		  
		}


Explanation of the functions of the library
-------------------------------------------

Ubidots ubiclient():
````````````````````
.. code-block:: cpp

    Ubidots ubiclient(api);

=======  ========  =================================
Type     Argument  Description
=======  ========  =================================
String   api       Your API key for the Ubidots API
=======  ========  =================================

Initialize a Ubidots client. This is most likely to be the first Ubidots library function to call.

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

Save a value to Ubidots. Returns true upon success. Returns false upon error.


get_value()
```````````
.. code-block:: cpp

    readvalue = ubiclient.get_value(idvari);

==================  ===========  =============================================
Type                Argument     Description
==================  ===========  =============================================
String              idvari       ID of the variable that you want make request 
==================  ===========  =============================================

Get value from Ubidots. Returns a String containing the last value of the variable.

ubitoken();
``````````` 

.. code-block:: cpp

    boolean = ubiclient.ubitoken(api);  

==================  ===========  =============================================
Type                Argument     Description
==================  ===========  =============================================
String              api          Your API key for the Ubidots API
==================  ===========  =============================================