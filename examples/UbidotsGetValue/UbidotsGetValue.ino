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
  /* Print value with 5 decimal points precision */
  //Serial.println(value, 5);
  delay(5000);
}
