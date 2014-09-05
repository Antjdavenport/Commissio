//WiFly Shield
//Mega pin 53 to shield pin 10
//Mega pin 51 to shield pin 11
//Mega pin 50 to shield pin 12
//Mega pin 52 to shield pin 13

#include "WiFly.h"
#include "Credentials.h"
//#include "Animations.h"
//#include "Tracker.h"
#include <PubSubClient.h>
#include <SPI.h>

//char* name = "MEGA1";
char* name = "MEGA1";
int animation;

//LED MATRIX
int NEG[6] = { 14, 15, 16, 17, 18 };
int POS[16] = { 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 45, 44};

int limbo;
int delaytime;

//KeyPhrase
byte LEDon[3] = "on";
byte LEDoff[4] = "off";

byte LED0[5] = "LED0";
byte LED1[5] = "LED1";
byte LED2[5] = "LED2";
byte LED3[5] = "LED3";
byte LED4[5] = "LED4";
byte LED5[5] = "LED5";
byte LED6[5] = "LED6";
byte LED7[5] = "LED7";
byte LED8[5] = "LED8";
byte LED9[5] = "LED9";
byte LED10[6] = "LED10";
byte LED11[6] = "LED11";
byte LED12[6] = "LED12";
byte LED13[6] = "LED13";
byte LED14[6] = "LED14";

int LED1t9 = 4;
int LED10t14 = 5;

byte zAxsis0[8] = "zAxsis0";
byte zAxsis1[8] = "zAxsis1";
byte zAxsis2[8] = "zAxsis2";
byte zAxsis3[8] = "zAxsis3";
byte zAxsis4[8] = "zAxsis4";
byte zAxsis5[8] = "zAxsis5";
byte zAxsis6[8] = "zAxsis6";
byte zAxsis7[8] = "zAxsis7";
byte zAxsis8[8] = "zAxsis8";
byte zAxsis9[8] = "zAxsis9";
byte zAxsis10[9] = "zAxsis10";
byte zAxsis11[9] = "zAxsis11";
byte zAxsis12[9] = "zAxsis12";
byte zAxsis13[9] = "zAxsis13";
byte zAxsis14[9] = "zAxsis14";

int zAxsis1t9 = 7;
int zAxsis10t14 = 8;

byte Data0[6] = "Data0";
byte Data1[6] = "Data1";
byte Data2[6] = "Data2";
byte Data3[6] = "Data3";
byte Data4[6] = "Data4";
byte Data5[6] = "Data5";
byte Data6[6] = "Data6";
byte Data7[6] = "Data7";
byte Data8[6] = "Data8";
byte Data9[6] = "Data9";
byte Data10[7] = "Data10";
byte Data11[7] = "Data11";
byte Data12[7] = "Data12";
byte Data13[7] = "Data13";
byte Data14[7] = "Data14";

int Data1t9 = 5;
int Data10t14 = 6;

byte idleData[12] = "UserTrusted";
byte alert[6] = "Alert";

char* Track;

//Broker IP
//DomAirport
byte ip[] = { 192, 168, 1, 2 };

WiFlyClient wifi;
PubSubClient cl(ip, 1883, callback, wifi);
void callback(char* topic, byte* payload, unsigned int length) {
    if ((length == 11) & (memcmp(payload, idleData, 11) ==0)){
      limbo = 0;
    }else if ((length == zAxsis1t9) & (memcmp(payload, Data0, zAxsis1t9) ==0)){
      DataTrack(0);
    }else if ((length == Data1t9) & (memcmp(payload, Data1, Data1t9) ==0)){
      DataTrack(1);
    }else if ((length == Data1t9) & (memcmp(payload, Data2, Data1t9) ==0)){
      DataTrack(2);
    }else if ((length == Data1t9) & (memcmp(payload, Data3, Data1t9) ==0)){
      DataTrack(3);
    }else if ((length == Data1t9) & (memcmp(payload, Data4, Data1t9) ==0)){
      DataTrack(4);
    }else if ((length == Data1t9) & (memcmp(payload, Data5, Data1t9) ==0)){
      DataTrack(5);
    }else if ((length == Data1t9) & (memcmp(payload, Data6, Data1t9) ==0)){
      DataTrack(6);
    }else if ((length == Data1t9) & (memcmp(payload, Data7, Data1t9) ==0)){
      DataTrack(7);
    }else if ((length == Data1t9) & (memcmp(payload, Data8, Data1t9) ==0)){
      DataTrack(8);
    }else if ((length == Data1t9) & (memcmp(payload, Data9, Data1t9) ==0)){
      DataTrack(9);
    }else if ((length == Data10t14) & (memcmp(payload, Data10, Data10t14) ==0)){
      DataTrack(10);
    }else if ((length == Data10t14) & (memcmp(payload, Data11, Data10t14) ==0)){
      DataTrack(11);
    }else if ((length == Data10t14) & (memcmp(payload, Data12, Data10t14) ==0)){
      DataTrack(12);
    }else if ((length == Data10t14) & (memcmp(payload, Data13, Data10t14) ==0)){
      DataTrack(13);
    }else if ((length == Data10t14) & (memcmp(payload, Data14, Data10t14) ==0)){
      DataTrack(14);
    }
    else if (name == "MEGA2"){
    if ((length == zAxsis1t9) & (memcmp(payload, zAxsis0, zAxsis1t9) ==0)){
      LEDTrack(0);
    }else if ((length == zAxsis1t9) & (memcmp(payload, zAxsis1, zAxsis1t9) ==0)){
      LEDTrack(1);
    }else if ((length == zAxsis1t9) & (memcmp(payload, zAxsis2, zAxsis1t9) ==0)){
      LEDTrack(2);
    }else if ((length == zAxsis1t9) & (memcmp(payload, zAxsis3, zAxsis1t9) ==0)){
      LEDTrack(3);
    }else if ((length == zAxsis1t9) & (memcmp(payload, zAxsis4, zAxsis1t9) ==0)){
      LEDTrack(4);
    }else if ((length == zAxsis1t9) & (memcmp(payload, zAxsis5, zAxsis1t9) ==0)){
      LEDTrack(5);
    }else if ((length == zAxsis1t9) & (memcmp(payload, zAxsis6, zAxsis1t9) ==0)){
      LEDTrack(6);
    }else if ((length == zAxsis1t9) & (memcmp(payload, zAxsis7, zAxsis1t9) ==0)){
      LEDTrack(7);
    }else if ((length == zAxsis1t9) & (memcmp(payload, zAxsis8, zAxsis1t9) ==0)){
      LEDTrack(8);
    }else if ((length == zAxsis1t9) & (memcmp(payload, zAxsis9, zAxsis1t9) ==0)){
      LEDTrack(9);
    }else if ((length == zAxsis10t14) & (memcmp(payload, zAxsis10, zAxsis10t14) ==0)){
      LEDTrack(10);
    }else if ((length == zAxsis10t14) & (memcmp(payload, zAxsis11, zAxsis10t14) ==0)){
      LEDTrack(11);
    }else if ((length == zAxsis10t14) & (memcmp(payload, zAxsis12, zAxsis10t14) ==0)){
      LEDTrack(12);
    }else if ((length == zAxsis10t14) & (memcmp(payload, zAxsis13, zAxsis10t14) ==0)){
      LEDTrack(13);
    }else if ((length == zAxsis10t14) & (memcmp(payload, zAxsis14, zAxsis10t14) ==0)){
      LEDTrack(14);
    }
  }else if (name == "MEGA1"){
    if ((length == LED1t9) & (memcmp(payload, LED0, LED1t9) ==0)){
      LEDTrack(0);
    }else if ((length == LED1t9) & (memcmp(payload, LED1, LED1t9) ==0)){
      LEDTrack(1);
    }else if ((length == LED1t9) & (memcmp(payload, LED2, LED1t9) ==0)){
      LEDTrack(2);
    }else if ((length == LED1t9) & (memcmp(payload, LED3, LED1t9) ==0)){
      LEDTrack(3);
    }else if ((length == LED1t9) & (memcmp(payload, LED4, LED1t9) ==0)){
      LEDTrack(4);
    }else if ((length == LED1t9) & (memcmp(payload, LED5, LED1t9) ==0)){
      LEDTrack(5);
    }else if ((length == LED1t9) & (memcmp(payload, LED6, LED1t9) ==0)){
      LEDTrack(6);
    }else if ((length == LED1t9) & (memcmp(payload, LED7, LED1t9) ==0)){
      LEDTrack(7);
    }else if ((length == LED1t9) & (memcmp(payload, LED8, LED1t9) ==0)){
      LEDTrack(8);
    }else if ((length == LED1t9) & (memcmp(payload, LED9, LED1t9) ==0)){
      LEDTrack(9);
    }else if ((length == LED10t14) & (memcmp(payload, LED10, LED10t14) ==0)){
      LEDTrack(10);
    }else if ((length == LED10t14) & (memcmp(payload, LED11, LED10t14) ==0)){
      LEDTrack(11);
    }else if ((length == LED10t14) & (memcmp(payload, LED12, LED10t14) ==0)){
      LEDTrack(12);
    }else if ((length == LED10t14) & (memcmp(payload, LED13, LED10t14) ==0)){
      LEDTrack(13);
    }else if ((length == LED10t14) & (memcmp(payload, LED14, LED10t14) ==0)){
      LEDTrack(14);
    }
  }
}

void setup(){
//  delaytime = 2;
//  animation = 0;
  limbo = 0;

  //Setup LED Pins
  for (int i=0; i < 6; i++) {
    pinMode(NEG[i], OUTPUT);
  }
  for (int i=0; i < 16; i++) {
    pinMode(POS[i], OUTPUT);
  }
  
  digitalWrite(NEG[0], HIGH);
  digitalWrite(NEG[1], LOW);
  digitalWrite(NEG[2], LOW);
  digitalWrite(NEG[3], LOW);
  digitalWrite(NEG[4], HIGH);
  digitalWrite(POS[5], HIGH);
  digitalWrite(POS[6], HIGH);
  digitalWrite(POS[7], HIGH);
  digitalWrite(POS[8], HIGH);
  digitalWrite(POS[9], HIGH); 

  WiFly.begin();  
  if (!WiFly.join(ssid, passphrase)) {
    while (1) {
        int wait = 5;
        digitalWrite(NEG[0], HIGH);
        digitalWrite(NEG[1], HIGH);
        digitalWrite(NEG[2], HIGH);
        digitalWrite(NEG[3], HIGH);
        digitalWrite(NEG[4], HIGH);
        digitalWrite(POS[5], LOW);
        digitalWrite(POS[6], LOW);
        digitalWrite(POS[7], LOW);
        digitalWrite(POS[8], LOW);
        digitalWrite(POS[9], LOW);
        
        delay(wait);
        
        digitalWrite(NEG[0], HIGH);
        digitalWrite(NEG[1], LOW);
        digitalWrite(NEG[2], LOW);
        digitalWrite(NEG[3], LOW);
        digitalWrite(NEG[4], HIGH);
        digitalWrite(POS[6], HIGH);
        digitalWrite(POS[7], LOW);
        digitalWrite(POS[8], LOW);
        
        delay(wait);
        
        digitalWrite(NEG[0], HIGH);
        digitalWrite(NEG[1], LOW);
        digitalWrite(NEG[2], HIGH);
        digitalWrite(NEG[3], LOW);
        digitalWrite(NEG[4], HIGH);
        digitalWrite(POS[6], LOW);
        digitalWrite(POS[7], HIGH);
        digitalWrite(POS[8], LOW);
        
        delay(wait);
        
        digitalWrite(NEG[0], HIGH);
        digitalWrite(NEG[1], LOW);
        digitalWrite(NEG[2], LOW);
        digitalWrite(NEG[3], LOW);
        digitalWrite(NEG[4], HIGH);
        digitalWrite(POS[6], LOW);
        digitalWrite(POS[7], LOW);
        digitalWrite(POS[8], HIGH);
        
        delay(wait);
    }
  }
  
  for (int i=0; i < 6; i++) {
    digitalWrite(NEG[i], HIGH);
  }for (int i=0; i<16; i++){
    digitalWrite(POS[i], HIGH);
  }for (int i=5; i>-1; i--){
    digitalWrite(NEG[i], LOW);
    delay(200);
  }for (int i=0; i<16; i++){
    digitalWrite(POS[i], LOW);
  }for (int i=0; i < 6; i++) {
    digitalWrite(NEG[i], HIGH);
  }

  cl.connect(name);
  cl.subscribe("#");
  if (name=="MEGA1"){
    cl.publish(name, "MEGA1 Awaiting Orders");
  }else if (name=="MEGA2"){
    cl.publish(name, "MEGA2 Awaiting Orders");
  }

  for (int i=0; i<6; i++) {
    digitalWrite(NEG[i], LOW);
  }for (int i=0; i<16; i++) {
    digitalWrite(POS[i], HIGH);
    delay(100);
  }for (int i=0; i<16; i++) {
    digitalWrite(POS[i], LOW);
    delay(100);
  }for (int i=0; i<6; i++) {
    digitalWrite(NEG[i], HIGH);
  }
}

void loop() {
  cl.loop();
 
  /*if (limbo == 0){
    for (int i=0; i<6; i++){
      digitalWrite(NEG[i], HIGH);
    }
    for (int i=0; i<16; i++){
      digitalWrite(POS[i], LOW);
    }
  
    digitalWrite(NEG[0], LOW);
    digitalWrite(POS[0], HIGH);
    digitalWrite(POS[2], HIGH);
    
    delay(delaytime);
    
    digitalWrite(NEG[0], HIGH);
    digitalWrite(NEG[1], LOW);
    digitalWrite(POS[1], HIGH);
    digitalWrite(POS[0], LOW);
    digitalWrite(POS[2], LOW);
    
    delay(delaytime);
    
    digitalWrite(NEG[1], HIGH);
    digitalWrite(NEG[2], LOW);
    digitalWrite(POS[0], HIGH);
    digitalWrite(POS[1], LOW);
    digitalWrite(POS[2], HIGH);
    
    delay(delaytime);
    
    digitalWrite(NEG[2], HIGH);
    digitalWrite(NEG[3], LOW);
    digitalWrite(POS[1], HIGH);
    digitalWrite(POS[0], LOW);
    digitalWrite(POS[2], LOW);
    
    delay(delaytime);
    
    digitalWrite(NEG[3], HIGH);
    digitalWrite(NEG[4], LOW);
    digitalWrite(POS[0], HIGH);
    digitalWrite(POS[1], LOW);
    digitalWrite(POS[2], HIGH);
    
    delay(delaytime);
    
    digitalWrite(NEG[4], HIGH);
    digitalWrite(POS[0], LOW);
    digitalWrite(POS[1], LOW);
    digitalWrite(POS[2], LOW);
  }*/
}

void LEDTrack(int LED){
  /*if (limbo == 0){
    for (int a=0; a<100; a++){
     for (int i=0; i<6; i++){
    digitalWrite(NEG[i], LOW);
  }
  for (int i=0; i<16; i++){
    digitalWrite(POS[i], LOW);
  }
  delay(10);
  for (int i=0; i<16; i++){
    digitalWrite(POS[i], HIGH);
  }
  delay(10);
    }
  limbo = 1;
  }else if (limbo ==1){
    */for (int i=0; i<6; i++){
      digitalWrite(NEG[i], LOW);
    }
    for (int i=0; i<16; i++){
      digitalWrite(POS[i], LOW);
    }
    digitalWrite(POS[LED], HIGH);
  //}
}

void DataTrack(int LED){
  for (int i=0; i<6; i++){
    digitalWrite(NEG[i], LOW);
  }
  for (int i=0; i<16; i++){
    digitalWrite(POS[i], LOW);
  }
  digitalWrite(POS[LED], HIGH);
}
