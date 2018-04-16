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
