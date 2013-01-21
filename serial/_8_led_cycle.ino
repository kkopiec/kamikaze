//setting up array of leds

int dleds[8] ={2,3,4,5,6,7,8,9};
unsigned char c ;

void setup(){
  c = 0;    
 for (int i = 0; i<8;i++){
  pinMode(dleds[i], OUTPUT);
 } 
 Serial.begin(9600);
}

void loop(){
 
   displayNumber(c);
 
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

void serialEvent(){
  
  if(Serial.available()){
    c = (unsigned char)Serial.read();
  }
}
        

