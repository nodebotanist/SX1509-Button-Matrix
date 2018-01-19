#include <Wire.h>
#include <SparkFunSX1509.h>

SX1509 ledExpander;

const uint8_t LED_EXPANDER_ADDRESS = 0x3F;

const int BAUD_RATE = 9600;

const uint8_t ROW_GND_PINS[4] = {12, 8, 4, 0};
const uint8_t COL1_RED = 1;
const uint8_t COL1_GREEN = 2;
const uint8_t COL1_BLUE = 3;

void setup(){
  Serial.begin(BAUD_RATE);

  if(!ledExpander.begin(LED_EXPANDER_ADDRESS)){
    Serial.println("Problem starting the SX1509!");
  } else {
    Serial.println("SX1509 connected!");
  }

  ledExpander.pinMode(COL1_RED, ANALOG_OUTPUT);
  ledExpander.pinMode(COL1_GREEN, ANALOG_OUTPUT);
  ledExpander.pinMode(COL1_BLUE, ANALOG_OUTPUT);
  ledExpander.pinMode(ROW_GND_PINS[0], OUTPUT);
  ledExpander.pinMode(ROW_GND_PINS[1], OUTPUT);
  ledExpander.pinMode(ROW_GND_PINS[2], OUTPUT);
  ledExpander.pinMode(ROW_GND_PINS[3], OUTPUT);

  ledExpander.digitalWrite(ROW_GND_PINS[0], 1);
  ledExpander.digitalWrite(ROW_GND_PINS[1], 1);
  ledExpander.digitalWrite(ROW_GND_PINS[2], 1);
  ledExpander.digitalWrite(ROW_GND_PINS[3], 1);


}

int row = 0;
void loop(){
  ledExpander.digitalWrite(ROW_GND_PINS[row], 0);
  ledExpander.analogWrite(COL1_RED, 0xFF - (row * 60));
  ledExpander.analogWrite(COL1_GREEN, 0xFF - (52 * (row + 1)));
  ledExpander.analogWrite(COL1_BLUE, 0xFF - (20 * (row + 1)));
  ledExpander.digitalWrite(ROW_GND_PINS[row], 1);
  row++;
  if(row > 3){
    row = 0;
  }
}