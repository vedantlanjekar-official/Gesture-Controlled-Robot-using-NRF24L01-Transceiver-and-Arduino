//Arduino Gesture Control Robot
//Reciver Circuit 
//Created BY DIY Builder
//You need to install the required libraries before uploading the code.
//To install the libraries first download the library from here https://github.com/nRF24/RF24 then go to sketch > include Library > ADD .ZIP File > Select the downloaded
// libary's Zip file and you're done now. You can upload the the sketch now.
// For more details you can contact me here www.instagram.com/diy.builder


#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

int ENA = 3;
int ENB = 9;
int MotorA1 = 4;
int MotorA2 = 5;
int MotorB1 = 6;
int MotorB2 = 7;

RF24 radio(8, 10);

const byte address[6] = "00001";

struct data {
  int xAxis;
  int yAxis;

};
data receive_data;



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
radio.begin();
radio.openReadingPipe(0,address);
radio.setPALevel(RF24_PA_MIN);
radio.setDataRate(RF24_250KBPS);
radio.startListening();
pinMode(ENA, OUTPUT);
pinMode(ENB, OUTPUT);
pinMode(MotorA1, OUTPUT);
pinMode(MotorA2, OUTPUT);
pinMode(MotorB1, OUTPUT);
pinMode(MotorB2, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly
 while(radio.available()) {
    radio.read(&receive_data, sizeof(data));
 if(receive_data.yAxis > 400) {
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, HIGH);
  digitalWrite(MotorB1, HIGH);
  digitalWrite(MotorB2, LOW);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  
}else if(receive_data.yAxis < 320) {
  digitalWrite(MotorA1, HIGH);
  digitalWrite(MotorA2, LOW);
  digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, HIGH);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
} else if(receive_data.xAxis < 320){
  digitalWrite(MotorA1, HIGH);
  digitalWrite(MotorA2, LOW);
  digitalWrite(MotorB1, HIGH);
  digitalWrite(MotorB2, LOW);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}else if(receive_data.xAxis > 400){
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, HIGH);
  digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, HIGH);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}else {
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, LOW);
  digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  }
 }
}
