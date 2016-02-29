#include "UbidotsYUN.h"
#include <Process.h>
/**
 * Constructor.
 */
Ubidots::Ubidots(char* token){ 
    _token = token;
}
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
    headers = "curl --header \"Accept: application/json; indent=4\" --header"+token;
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

bool Ubidots::saveValue(String id, float value){
    Process _client;
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
    data = "\'{\"value\":"+String(value,5);
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
    while(!_client.available());
    while (_client.available()) {
        char c = _client.read();
        //Serial.print(c);
    }
    Serial.flush();   
}
