//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"



#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
const int M1=25;
const int M2=26;
const int M3=27;
const int M4=33;




String message = "";
char incomingChar;
void forward(){
  digitalWrite(M1,HIGH);
    digitalWrite(M2,LOW);
    digitalWrite(M3,HIGH);
    digitalWrite(M4,LOW);
}

void backward(){
   digitalWrite(M1,LOW);
    digitalWrite(M2,HIGH);
    digitalWrite(M3,LOW);
    digitalWrite(M4,HIGH);
}
void left(){
  digitalWrite(M1,LOW);
    digitalWrite(M2,HIGH);
    digitalWrite(M3,HIGH);
    digitalWrite(M4,LOW);
}
void right(){
  digitalWrite(M1,HIGH);
    digitalWrite(M2,LOW);
    digitalWrite(M3,LOW);
    digitalWrite(M4,HIGH);
}
void stopped(){
  digitalWrite(M1,LOW);
    digitalWrite(M2,LOW);
    digitalWrite(M3,LOW);
    digitalWrite(M4,LOW);
}
void setup() {
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin("king"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
unsigned long currentMillis = millis();
  
  if (SerialBT.available()){
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n'){
      message += String(incomingChar);
    }
    else{
      message = "";
    }
    Serial.write(incomingChar);
  }
  
  if(message == "forward"){
     digitalWrite(M1,HIGH);
    digitalWrite(M2,LOW);
    digitalWrite(M3,HIGH);
    digitalWrite(M4,LOW);
    SerialBT.println("forward");
  }
  if (message =="left"){
    digitalWrite(M1,LOW);
    digitalWrite(M2,HIGH);
    digitalWrite(M3,HIGH);
    digitalWrite(M4,LOW);
    SerialBT.println("left");
  }
  if(message == "right"){
     digitalWrite(M1,HIGH);
    digitalWrite(M2,LOW);
    digitalWrite(M3,LOW);
    digitalWrite(M4,HIGH);
    SerialBT.println("right");
   
  }
  if(message == "back"){
     digitalWrite(M1,LOW);
    digitalWrite(M2,HIGH);
    digitalWrite(M3,LOW);
    digitalWrite(M4,HIGH);
    SerialBT.println("back");
   
  }
  if (message =="stop"){
    digitalWrite(M1,LOW);
    digitalWrite(M2,LOW);
    digitalWrite(M3,LOW);
    digitalWrite(M4,LOW);
    SerialBT.println("stop");
  }
 
  
  

if (message =="dance"){
    forward();
    delay(1000);
    right();
    delay(700);
    forward();
    delay(1000);
    right();
    delay(700);
    forward();
    delay(1000);
    left();
    delay(2000);
    stopped();
delay (1000);

      backward();
    delay(1000);
    right();
    delay(700);
    backward();
    delay(1000);
    right();
    delay(700);
    backward();
    delay(1000);
    left();
    delay(2000);
    stopped();
  }

  delay(20);
}
