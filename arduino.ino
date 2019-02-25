const int analogCPin = A1, analogVoltPin = A2;
float volt=0, voltage, arus;
float avgacs;
unsigned int x=0;
float nilaiacs=0.0, samples=0.0, ratacs=0.0, nilaiacsf=0.0, Ptot=0.0;



/** RF24Mesh_Example.ino by TMRh20

   This example sketch shows how to manually configure a node via RF24Mesh, and send data to the
*/


#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
#include <EEPROM.h>


/**** Configure the nrf24l01 CE and CS pins ****/
RF24 radio(7, 8);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

#define nodeID 1 //gunakan 2 untuk beban


uint32_t displayTimer = 0;

struct payload_t {
  unsigned long ms;
  unsigned long counter;
}; 

void setup() {
  Serial.begin(9600);
  mesh.setNodeID(nodeID);
  mesh.loadDHCP();
  mesh.begin(76,RF24_250KBPS);
}



void loop() {
  mesh.update();
  mesh.checkConnection();
  voltage = analogRead(analogVoltPin);
volt =(voltage*25/1023);

float nilaiacs=0.0, samples=0.0, ratacs=0.0, nilaiacsf=0.0;
  for (int x = 0; x < 150; x++) {
    nilaiacs = analogRead(analogCPin);
    samples = samples + nilaiacs;
  }
  avgacs=samples/150.0;
  arus = (((avgacs*(5.0 / 1024.0))-2.475 )/0.100);

if (arus > 0.02){
  arus=arus;
}
else{
  (arus=0);} 
  Ptot = 13.2 * 100;
  mesh.update();
uint32_t dt = volt * 100 *arus;

Ptot = uint32_t(Ptot);

Serial.print(volt);
Serial.println("volt");
Serial.print(arus);
Serial.println("ampere");

     (mesh.write(&dt, 'M', sizeof(dt)));    
delay(1000);
}

