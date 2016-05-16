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
