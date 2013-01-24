//setting up array of leds
#include "Tlc5940.h"
int dleds[8] ={2,3,4,5,6,7,8,9};
long c = 0 ;
long g = 0;;
int layers[] = {30,31,32,33,34,35,36,37};
int numLayers = 8;

unsigned char frame [8*8] ={0};

unsigned char buffer[] = {0,0,0,0,0,0,0,0};
long prev_milis = 0;
long interval = 100;
void setup(){
  Tlc.init();
  c = 0;    
 for (int i = 0; i<8;i++){
  pinMode(dleds[i], OUTPUT);
 } 
 for (int i = 0; i<numLayers;i++){
  pinMode(layers[i], OUTPUT);

 } 
 //digitalWrite(6,HIGH);
 //digitalWrite(7,HIGH);
 Serial.begin(115200);
}

void loop(){
 
if(Serial.available()){
       //buffer[g%8]=
       buffer[g%8]=(unsigned char)Serial.read();
       //Serial.println(buffer[g%8], DEC);
       g++;
       
      }  else 
      for (int i =0; i < numLayers;i++){
        switchLayer(i);
       switch (i%numLayers){
         case 1:
          TlcDisplay((unsigned short)buffer[1] <<8| (unsigned short)buffer[0] );
          break;
         case 0:
          TlcDisplay((unsigned short)buffer[3] <<8| (unsigned short)buffer[2] );
        break;
       }  
      //delay();
    //displayNumber((unsigned char)buffer[c%8]);
      }
}

void TlcDisplay()
{ 
  
  
    for( int j =0 ; j<8;j++)
    {
      switchLayer(j);
    for( int i =0; i<8;i++)
    {
      
    }
    }
    
  
  
//  Tlc.clear();
//  for(int i = 0; i<=64;i++)
//  {
//    
//   
//    if((in&(1<<i))>0)Tlc.set(i, 4095); 
//    
//  }
  Tlc.update();
    //delay(1);
}
//testing function
void displayNumber(unsigned char in){
  int d;
  for (d = 0 ; d < 8 ; d++){
   if ( (in & 1) == 1) {
    digitalWrite(dleds[d], HIGH);
   } else {
     digitalWrite(dleds[d], LOW);
   } 
    in = in >> 1; 
  }
}

void switchLayer(int lnum){
  for (int i = 0; i < numLayers; i++){
    digitalWrite(layers[i],LOW);
  }
  digitalWrite(layers[lnum], HIGH);
}
