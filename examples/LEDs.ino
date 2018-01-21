#include <Wire.h>
#include <SparkFunSX1509.h>

SX1509 ledExpander;

const uint8_t LED_EXPANDER_ADDRESS = 0x3F;

const int BAUD_RATE = 9600;

const uint8_t GND_LED_PINS[4] = {12, 8, 4, 0};
const uint8_t RED_LED_PINS[4] = {13, 9, 5, 1};
const uint8_t GRN_LED_PINS[4] = {14, 10, 6, 2};
const uint8_t BLUE_LED_PINS[4] = {15, 11, 7, 3};

uint8_t colors[4][4][3] = {
  {{0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}},
  {{0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}},
  {{0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}},
  {{0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}}
};

void setLEDColor(uint8_t row, uint8_t col, byte red, byte green, byte blue){
  colors[row][col][0] = red;
  colors[row][col][0] = green;
  colors[row][col][0] = blue;
}

void renderLED(uint8_t row, uint8_t col, uint8_t color[]){
  // write all LED GNDs HIGH
  ledExpander.digitalWrite(GND_LED_PINS[0], 1);
  ledExpander.digitalWrite(GND_LED_PINS[1], 1);
  ledExpander.digitalWrite(GND_LED_PINS[2], 1);
  ledExpander.digitalWrite(GND_LED_PINS[3], 1);
  // set row we're working with LOW
  ledExpander.digitalWrite(GND_LED_PINS[row], 0);
  //write the color to the correct column
  ledExpander.analogWrite(RED_LED_PINS[col], 0xFF - color[0]);
  ledExpander.analogWrite(GRN_LED_PINS[col], 0xFF - color[1]);
  ledExpander.analogWrite(BLUE_LED_PINS[col], 0xFF - color[2]);
}

void renderAll(){
  for(uint8_t row = 0; row < 4; row++){
    for(uint8_t col = 0; col < 4; col++){
      renderLED(row, col, colors[row][col]);
    }
  }
}

void setup(){
  Serial.begin(BAUD_RATE);

  if(!ledExpander.begin(LED_EXPANDER_ADDRESS)){
    Serial.println("Problem starting the SX1509!");
  } else {
    Serial.println("SX1509 connected!");
  }

  ledExpander.pinMode(RED_LED_PINS[0], ANALOG_OUTPUT);
  ledExpander.pinMode(RED_LED_PINS[1], ANALOG_OUTPUT);
  ledExpander.pinMode(RED_LED_PINS[2], ANALOG_OUTPUT);
  ledExpander.pinMode(GRN_LED_PINS[0], ANALOG_OUTPUT);
  ledExpander.pinMode(GRN_LED_PINS[1], ANALOG_OUTPUT);
  ledExpander.pinMode(GRN_LED_PINS[2], ANALOG_OUTPUT);
  ledExpander.pinMode(BLUE_LED_PINS[0], ANALOG_OUTPUT);
  ledExpander.pinMode(BLUE_LED_PINS[1], ANALOG_OUTPUT);
  ledExpander.pinMode(BLUE_LED_PINS[2], ANALOG_OUTPUT);
  ledExpander.pinMode(GND_LED_PINS[0], OUTPUT);
  ledExpander.pinMode(GND_LED_PINS[1], OUTPUT);
  ledExpander.pinMode(GND_LED_PINS[2], OUTPUT);
  ledExpander.pinMode(GND_LED_PINS[3], OUTPUT);

  setLEDColor(0, 0, 0xFF, 0xFF, 0xFF);
  setLEDColor(0, 1, 0xFF, 0x00, 0x00);
  setLEDColor(0, 2, 0x00, 0xFF, 0x00);
  setLEDColor(0, 3, 0x00, 0x00, 0xFF);
  setLEDColor(1, 0, 0xFF, 0xFF, 0xFF);
  setLEDColor(1, 1, 0xFF, 0x00, 0x00);
  setLEDColor(1, 2, 0x00, 0xFF, 0x00);
  setLEDColor(1, 3, 0x00, 0x00, 0xFF);
  setLEDColor(2, 0, 0xFF, 0xFF, 0xFF);
  setLEDColor(2, 1, 0xFF, 0x00, 0x00);
  setLEDColor(2, 2, 0x00, 0xFF, 0x00);
  setLEDColor(2, 3, 0x00, 0x00, 0xFF);
  setLEDColor(3, 0, 0xFF, 0xFF, 0xFF);
  setLEDColor(3, 1, 0xFF, 0x00, 0x00);
  setLEDColor(3, 2, 0x00, 0xFF, 0x00);
  setLEDColor(3, 3, 0x00, 0x00, 0xFF);
}

void loop(){
  renderAll();
}