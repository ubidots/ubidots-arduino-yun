  /*
Copyright (c) 2013-2016 Ubidots.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Made by Mateo Velez - Metavix for Ubidots Inc
Modified by Maria Hernandez
*/

#include "UbidotsYUN.h"
#include <Process.h>
/**
 * Constructor.
 */
Ubidots::Ubidots(char* token, char* server) {
    _token = token;
    _server = server;
    _deviceName = "YUN";
    _deviceLabel = "YUN";
    val = (Value *)malloc(MAX_VALUES*sizeof(Value));
}

/**
 * This function set a new device label assigned by the user
 * @arg deviceLabel the device label desired
 */
void Ubidots::setDeviceLabel(char *deviceLabel) {
    _deviceLabel = deviceLabel;
}

/**
 * This function set a device name
 * @arg deviceName the device name to set
 */
void Ubidots::setDeviceName(char *deviceName) {
    _deviceName =  deviceName;
}

/**
 * This function start the YUN device
 */
void Ubidots::init() {
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    Bridge.begin();
    digitalWrite(13, HIGH);
}

/**
 * This function is to get value from the Ubidots API
 * @arg deviceLabel the device label where your variable is located
 * @arg variableLabel the variable label where you will get the data
 * @return num the data that you get from the Ubidots API
 */
float Ubidots::getValue(char* deviceLabel, char* variableLabel) {
    const char* url = "http://things.ubidots.com/api/v1.6/devices";
    Process _client;
    float num;
    char request[400];
    char c[400];
    int i = 0;
    int timeout = 0;
    sprintf(request, "curl -X GET %s/%s/%s/lv?token=%s -vvv", url, deviceLabel, variableLabel, _token);
    _client.runShellCommand(request);
    while (!_client.available() && timeout < 10000) {
        timeout++;
        delay(1);
    }
    while (_client.available() && i < 400) {
        c[i] = _client.read();
        i++;
    }
    c[i] = '\0';
    i = 0;
    num = atof(c);
    Serial.flush();
    return num;
}

/**
 * This function is to save data to the YUN cache
 * @arg id the name of your variable
 * @arg value the value to save
 * @arg ctext[OPTIONAL] the context to save
 * @arg timestamp_val[OPTIONAL] the timestamp to save
 */
void Ubidots::add(char *id, float value, char *ctext, long unsigned timestamp_val) {
    (val+_currentValue)->idName = id;
    (val+_currentValue)->idValue = value;
    (val+_currentValue)->context = ctext;
    (val+_currentValue)->timestamp_val = timestamp_val;
    _currentValue++;
    if (_currentValue > MAX_VALUES) {
        Serial.println(F("You are sending more than 5 consecutives variables, you just could send 5 variables!"));
        _currentValue = MAX_VALUES;
    }
}
/**
 * This function is to send all data saved in add function
 */
void Ubidots::sendAll() {
    Process _client;
    int i;
    int timeout = 0;
    char str_value[10];
    char buffer[400];
    sprintf(buffer, "echo \"");
    if (_deviceName == "YUN") {
        sprintf(buffer, "%s%s/%s|POST|%s|%s=>", buffer, USER_AGENT, VERSION, _token, _deviceLabel);
    } else {
        sprintf(buffer, "%s%s/%s|POST|%s|%s:%s=>", buffer, USER_AGENT, VERSION, _token, _deviceLabel, _deviceName);
    }
    for (i = 0; i < _currentValue; ) {
        dtostrf((val + i)->idValue, 4, 2, str_value);
        sprintf(buffer, "%s%s:%s", buffer, (val + i)->idName, str_value);
        if ((val + i)->context != NULL) {
            sprintf(buffer, "%s\\$%s", buffer, (val + i)->context);
        }
        if ((val + i)->timestamp_val != NULL) {
            sprintf(buffer, "%s\@%lu%s", buffer, (val + i)->timestamp_val, "000");
        }
        i++;
        if (i < _currentValue) {
            sprintf(buffer, "%s,", buffer);
        }
    }
    sprintf(buffer, "%s|end\" | nc %s %s", buffer, _server, PORT);
    Serial.println(buffer);
    _client.runShellCommand(buffer);
    while (_client.running() && timeout < 10000) {
        timeout++;
        delay(1);
    }
    Serial.flush();
    _currentValue = 0;
}

// Old functions of the library
bool Ubidots::saveValue(String id, float value) {
    Process _client;
    int timeout = 0;
    String TOKEN = _token;
    String url;
    String token;
    String data;
    String headers;
    String all;
    url = "http://things.ubidots.com/api/v1.6/variables/"+id;
    url += "/values";
    token = " \"X-Auth-Token: "+TOKEN;
    token += "\" ";
    data = "\'{\"value\":" + String(value, 5);
    data += "}\' ";
    headers = "curl -i --header \"Accept: application/json; indent=4\" --header \"Content-Type: application/json\" --header"+token;
    headers += "-X POST -d ";
    all = headers + data;
    all += url;
    Serial.println("[WARNING] This method is -Deprecated-");
    _client.runShellCommand(all);

    while (!_client.available() && timeout > 10000) {
        timeout++;
        delay(1);
    }
    while (_client.available()) {
        char c = _client.read();
    }
    Serial.flush();
}

/**
 * This function set a data source tag
 * @arg tag the tag to set
 */
void Ubidots::setDataSourceTag(char *tag) {
    return setDeviceLabel(tag);
}

/**
 * This function set a data source name
 * @arg name the name to set
 */
void Ubidots::setDataSourceName(char *name) {
    return setDeviceName(name);
}
