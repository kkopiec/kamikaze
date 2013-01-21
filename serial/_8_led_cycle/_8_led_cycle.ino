//setting up array of leds

int dleds[8] ={2,3,4,5,6,7,8,9};
long c = 0 ;
long g = 0;;
char buffer[] = {0,0,0,0,
                 0,0,0,0};
long prev_milis = 0;
long interval = 100;
void setup(){
  c = 0;    
 for (int i = 0; i<8;i++){
  pinMode(dleds[i], OUTPUT);
 } 
 Serial.begin(9600);
}

void loop(){
  unsigned long cur_milis = millis();
 
  if(cur_milis - prev_milis > interval) {
    // save the last time you blinked the LED
    prev_milis = cur_milis;  

    displayNumber((unsigned char)buffer[c%8]);
    c++;
  } else {
      if(Serial.available()){
       buffer[g%8]=Serial.read();
       g++;
       
      }  
  }
}

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



