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
*/

#include "UbidotsYUN.h"
#include <Process.h>
/**
 * Constructor.
 */
Ubidots::Ubidots(char* token, char* server) {
    _token = token;
    _server = server;
    _dsName = "YUN";
    _dsTag = "YUN";
    val = (Value *)malloc(MAX_VALUES*sizeof(Value));
}
/** 
 * This function set a data source tag
 * @arg tag the tag to set
 */
void Ubidots::setDataSourceTag(char *tag) {
    _dsTag = tag;
}
/** 
 * This function set a data source name
 * @arg name the name to set
 */
void Ubidots::setDataSourceName(char *name) {
    _dsName = name;
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
 * @arg id the id where you will get the data
 * @return num the data that you get from the Ubidots API
 */
float Ubidots::parseValue(char *body) {
    String raw;
    char *pch;
    float num;
    char reply[25];
    uint8_t bodyPosinit = 0;
    uint8_t bodyPosend = 0;
    pch = strstr(body, "\"value\":");
    raw = String(pch);
    bodyPosinit = 9 + raw.indexOf("\"value\":");
    bodyPosend = raw.indexOf(", \"timestamp\"");
    raw.substring(bodyPosinit, bodyPosend).toCharArray(reply, 25);
    Serial.println(reply);
    num = atof(reply);
    return num;
}
/** 
 * This function is to get value from the Ubidots API
 * @arg id the id where you will get the data
 * @return num the data that you get from the Ubidots API
 */
float Ubidots::getValue(String id) {
    Process _client;
    float num;
    char c[400];
    int i = 0;
    int timeout = 0;
    String TOKEN = _token;
    String token;
    String headers;
    String url;
    url = "http://things.ubidots.com/api/v1.6/variables/"+id;
    url += "/values?page_size=1";
    token = " \"X-Auth-Token: "+TOKEN;
    token += "\" ";
    headers = "curl --header \"Accept: application/json; indent=4\" --header" + token;
    headers += "-X GET ";
    /*Serial.println(token);
    Serial.println(url);
    Serial.println(all);*/
    _client.runShellCommand(headers + url);
    url = "";
    while (!_client.available() && timeout < 10000) {
        timeout++;
        delay(1);
    }
    while (_client.available() && i < 400) {
        c[i] = _client.read();
        i++;
    }
    c[i] = '\0';
    while (_client.available()) {
        _client.read();
    }
    i = 0;
    num = parseValue(c);
    Serial.flush();
    return num;
}
/** 
 * This function is to save data to the YUN cache
 * @arg id the name of your variable
 * @arg value the value to save
 * @arg ctext the context to save
 */
void Ubidots::add(char *id, float value, char *ctext) {
    (val+currentValue)->idName = id;
    (val+currentValue)->idValue = value;
    (val+currentValue)->context = ctext;
    currentValue++;
    if (currentValue > MAX_VALUES) {
        currentValue = MAX_VALUES;
    }
}
/** 
 * This function is to send all data saved in add function
 */
void Ubidots::sendAll() {
    Process _client;
    int i;
    int timeout = 0;
    String value;
    char buffer[400];
    sprintf(buffer, "(sleep 1\necho \"");
    if (_dsName == "YUN") {
        sprintf(buffer, "%s%s%s|POST|%s|%s=>", buffer, USER_AGENT, VERSION, _token, _dsTag);
    } else {
        sprintf(buffer, "%s%s%s|POST|%s|%s:%s=>", buffer, USER_AGENT, VERSION, _token, _dsTag, _dsName);
    }
    for (i = 0; i < currentValue; ) {
        value = String((val + i)->idValue, 2);
        sprintf(buffer, "%s%s:%s", buffer, (val + i)->idName, value.c_str());
        if ((val + i)->context != NULL) {
            sprintf(buffer, "%s\\$%s", buffer, (val + i)->context);
        }
        i++;
        if (i < currentValue) {
            sprintf(buffer, "%s,", buffer);
        }
    }
    sprintf(buffer, "%s|end\") | telnet %s %s", buffer, _server, PORT);
    SerialUSB.println(buffer);
    _client.runShellCommand(buffer);
    while (_client.running() && timeout < 10000) {
        timeout++;
        delay(1);
    }
    Serial.flush();
    currentValue = 0;
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
    /*Serial.println(token);
    Serial.println(url);
    Serial.println(data);
    Serial.println(all);*/
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
