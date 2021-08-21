// SimpleRx - the slave or the receiver

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   7
#define CSN_PIN  8

const byte slaveAddress[][5] = {{'R', 'x', 'A', 'A', 'A'}, {'R', 'x', 'A', 'A', 'B'},
  {'R', 'x', 'A', 'A', 'C'}, {'R', 'x', 'A', 'A', 'D'}
};

RF24 radio(CE_PIN, CSN_PIN);

char dataReceived[10]; // this must match dataToSend in the TX
bool newData = false;

//===========

void setup() {

  Serial.begin(9600);

  Serial.println("SimpleRx Starting");
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, slaveAddress[1]);
  radio.enableDynamicPayloads() ;
  radio.setAutoAck(false);
  radio.startListening();
}

//=============

void loop() {
  getData();
  showData();
}

//==============

void getData() {
  if ( radio.available() ) {
    radio.read( &dataReceived, sizeof(dataReceived) );
    newData = true;
  }
}

void showData() {
  if (newData == true) {
    Serial.print("Data received ");
    Serial.println(dataReceived);
    newData = false;
  }
}
