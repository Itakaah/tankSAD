//Sender
#include <SPI.h>
#include <LoRa.h>

#define NUM_JOY 2
#define MIN_VAL 0
#define MAX_VAL 1023
//Parameters
const int joyPinX [2] = {A0, A1};
const int joyPinY [2] = {A2, A3};
const int joyOffset  = 0;

int joyValX [NUM_JOY] = {0,0};
int joyValY [NUM_JOY] = {0,0};

int value[4] = {0,0,0,0};

int counter = 0;
int i = 0;
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUM_JOY; i++) {
    pinMode(joyPinX[i], INPUT);
    pinMode(joyPinY[i], INPUT);
  }

  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  readJoystick();
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
    for (i = 0; i < 4; i++) {

  LoRa.beginPacket();
  LoRa.print(i);
  LoRa.print(value[i]);
  LoRa.endPacket();
  Serial.print("sent: ");
  Serial.println(value[i]);
  counter++;

  Serial.println(i);
  delay(100);
}
  delay(500);
}


void readJoystick( ) { /* function readJoystick */
  ////Test routine for Joystick
  for (int i = 0; i < NUM_JOY; i++) {
    joyValX[i] = analogRead(joyPinX[i]);
    joyValY[i] = analogRead(joyPinY[i]);
    value[i] = joyValX[i];
    value[i+2] = joyValY[i];
    //Serial.print(F("joyX")); Serial.print(i); Serial.print(F(" : ")); Serial.println(joyValX[i]);
    //Serial.print(F("joyY")); Serial.print(i); Serial.print(F(" : ")); Serial.println(joyValY[i]);

  }
}
