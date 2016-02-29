#ifndef _UbidotsYUN_H_
#define _UbidotsYUN_H_

#include <Process.h>

class Ubidots {
   public:
      Ubidots(char* token);
      void init();
      bool saveValue(String id, float value);
      float getValue(String id);
      void add(String id, float value);
      //bool send2variables(String id, float value, String id2, float value2);

   private:
      char* _token;
      float parseValue(char *body);
};

#endif