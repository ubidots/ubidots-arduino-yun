#include <UbidotsYUN.h>
#define TOKEN "YOUR_TOKEN_HERE"
#define ID1 "YOUR_ID_HERE"
#define ID2 "YOUR_ID_HERE"
#define ID3 "YOUR_ID_HERE"

Ubidots client(TOKEN);

void setup() {
  client.init();
  Serial.begin(9600);

}

void loop() {
  float value = analogRead(A0);
  float value1 = analogRead(A1);
  float value2 = analogRead(A2);
  client.add(ID1, value);
  client.add(ID2, value1,"\"Context_key\": \"Value\"");
  client.add(ID3, value2);
  client.sendAll();
}
