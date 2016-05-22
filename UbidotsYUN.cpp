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
Modified by Kosme - Hormiga Azul
*/

#include "UbidotsYUN.h"
#include <Process.h>
/**
 * Constructor.
 */
Ubidots::Ubidots(char* token){
    _token = token;
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
void Ubidots::init(){

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
float Ubidots::parseValue(char *body){
  String raw;
  char *pch;
  float num;
  char reply[25];
  uint8_t bodyPosinit = 0;
  uint8_t bodyPosend = 0;
  pch = strstr(body,"\"value\":");
  raw = String(pch);
  bodyPosinit = 9 + raw.indexOf("\"value\":");
  bodyPosend = raw.indexOf(", \"timestamp\"");
  raw.substring(bodyPosinit,bodyPosend).toCharArray(reply, 25);
  Serial.println(reply);
  num = atof(reply);
  return num;
}
/**
 * This function is to get value from the Ubidots API
 * @arg id the id where you will get the data
 * @return num the data that you get from the Ubidots API
 */
float Ubidots::getValue(String id){
    Process _client;
    float num;
    char c[400];
    int i = 0;
    String TOKEN = _token;
    String token;
    String headers;
    String url;
    url = "http://things.ubidots.com/api/v1.6/variables/"+id;
    url += "/values?page_size=1";
    token = " \"X-Auth-Token: "+TOKEN;
    token += "\" ";
    headers = "curl --header \"Accept: application/json\" --header"+token;
    headers += "-X GET ";
    /*Serial.println(token);
    Serial.println(url);
    Serial.println(all);*/
    _client.runShellCommand(headers + url);
    url = "";
    while(!_client.available());
    while (_client.available()&& i<400) {
        c[i] = _client.read();
        i++;
        //Serial.print(c);
    }
    c[i] = '\0';
    while (_client.available()) {
        _client.read();
        //Serial.print(c);
    }
    //Serial.println(url);
    i = 0;
    num = parseValue(c);
    Serial.flush();
    return num;

}
/**
 * This function is to save data to the YUN cache
 * @arg id the id of your variable
 * @arg value the value to save
 * @arg ctext the context to save
 */
void Ubidots::add(char *id, float value, char *ctext) {
    (val+currentValue)->idName = id;
    (val+currentValue)->idValue = value;
    (val+currentValue)->context = ctext;
    currentValue++;
    if(currentValue > MAX_VALUES) {
        currentValue = MAX_VALUES;
    }
}
/**
 * This function is to send all data saved in add function
 */
void Ubidots::sendAll() {
    Process _client;
    int i;
    char buffer[500];
    for(i=0;i<currentValue;i++)
    {
      sprintf(buffer,"curl -X POST -H \"Content-Type: application/json\" -d ");
      sprintf(buffer, "'%s{\"value\": \"%f\", \"context\": {%s}}'", buffer, (val + i)->idValue, (val + i)->context);
      sprintf(buffer,"%s http://things.ubidots.com/api/v1.6/variables/%s/?token=%s", buffer,(val+i)->idName, _token);
      SerialUSB.println(buffer);
      _client.runShellCommand(buffer);
      while (_client.running());
      Serial.flush();
      sprintf(buffer,"");//Limpiar buffer
    }
    currentValue = 0;
}
