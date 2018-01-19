#include <Wire.h>
#include <SparkFunSX1509.h>

SX1509 ledExpander;

const uint8_t BAUD_RATE = 9600;


void setup(){
  Serial.begin(BAUD_RATE);

  if(!ledExpander.begin(0x3F)){
    Serial.println("Problem starting the SX1509!");
  } else {
    Serial.println("SX1509 connected!");
  }
}

void loop(){

}