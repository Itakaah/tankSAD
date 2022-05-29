//Sender
#include <SPI.h>
#include <LoRa.h>

#define NUM_JOY 2 // nombre de valeurs rendues sur un joystick
#define MIN_VAL 0 // valeur minimale du joystick
#define MAX_VAL 1023 // valeur maximale du joystick
//Parameters
const int joyPinX [2] = {A0, A1};
const int joyPinY [2] = {A2, A3};
const int joyOffset  = 0;

int joyValX [NUM_JOY] = {0,0};
int joyValY [NUM_JOY] = {0,0};

int value[4] = {0,0,0,0}; // valeurs envoyés par la manette au tank

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
    for (i = 0; i < 4; i++) { // on envoi un packet a la fois donc on envoi toutes les données nécessaires en 4 temps

  LoRa.beginPacket();
  LoRa.print(i); // on precede la valeur par un chiffre indiquant a quelle valeur elle correspond
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


void readJoystick( ) { //lis la valur des joystick et les rangent dans leur place respectives
  for (int i = 0; i < NUM_JOY; i++) {
    joyValX[i] = analogRead(joyPinX[i]);
    joyValY[i] = analogRead(joyPinY[i]);
    value[i] = joyValX[i];
    value[i+2] = joyValY[i];
    //Serial.print(F("joyX")); Serial.print(i); Serial.print(F(" : ")); Serial.println(joyValX[i]);
    //Serial.print(F("joyY")); Serial.print(i); Serial.print(F(" : ")); Serial.println(joyValY[i]);

  }
}
