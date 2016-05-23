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

#ifndef _UbidotsYUN_H_
#define _UbidotsYUN_H_


#define SERVER "translate.ubidots.com"
#define PORT "9010"
#define MAX_VALUES 5
#define USER_AGENT "YUN"
#define VERSION "/1.0"



#include <Process.h>


typedef struct Value {
    char  *idName;
    char  *context;
    float idValue;
} Value;

class Ubidots {
   public:
      Ubidots(char* token);
      void init();
      float getValue(String id);
      void add(char* id, float value, char* ctext = NULL);
      void setDataSourceTag(char *tag);
      void setDataSourceName(char *name);
      void sendAll();
   private:
      char* _token;
      char* _dsName;
      char*_dsTag;
      uint8_t currentValue;
      float parseValue(char *body);
      Value * val;
};

#endif
