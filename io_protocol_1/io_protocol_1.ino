//arduino 1.0.5-r2

#define NUM_PORTS 3
#define FIRST_PORT 0
#define PERIOD 50
#define BAUD 115200

#include "IOP.h"
#include "interval.h"

IOP iop;
Interval ticker(PERIOD);

int value[NUM_PORTS];

void setup(){
  Serial.begin(BAUD);
  iop.comment();
  iop.println("started");
}
void loop(){
  if (ticker.check()){
    iop.sendAnalog(FIRST_PORT,NUM_PORTS); 
  } 
}





