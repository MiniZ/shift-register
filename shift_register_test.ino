
#include <avr/pgmspace.h>
int datapin0=11;
int datapin1=10;
int datapin2=9;
int shiftpin=12;
int showpin=8;

prog_uint8_t digits[8][3] = { 
{B00000111, B01111101, B11001110},
{B00001000, B10010010, B00101001},
{B00001000, B00010010, B00101001},
{B00000110, B00010010, B00101001},
{B00000001, B00010010, B00101110},
{B00000000, B10010010, B00101000},
{B00001000, B10010010, B00101000},
{B00000111, B00010001, B11001000},
};

void setup() {                

  DDRC = B00000111;
  PORTC = B00000000;
  pinMode(datapin0,OUTPUT);
  pinMode(datapin1,OUTPUT);
  pinMode(datapin2,OUTPUT);
  pinMode(showpin,OUTPUT);
  pinMode(shiftpin,OUTPUT);
  digitalWrite(datapin0,LOW);
  digitalWrite(datapin1,LOW);
  digitalWrite(datapin2,LOW);
  digitalWrite(showpin,LOW);
  digitalWrite(shiftpin,LOW);
}
void doJob(boolean state, prog_uint8_t grid[8][3]){
 for(byte i=0; i<8; i++){
   digitalWrite(showpin,LOW);
    byte val0 = grid[i][0];
    byte val1 = grid[i][1];
    byte val2 = grid[i][2];
    for(int i=0; i<8; i++) {
      	digitalWrite(datapin0, !!(val2 & (1 << 7-i)));
     	digitalWrite(datapin1, !!(val1 & (1 << 7-i)));
        digitalWrite(datapin2, !!(val0 & (1 << 7-i)));
	digitalWrite(shiftpin, HIGH);
	digitalWrite(shiftpin, LOW);		
    }
  digitalWrite(showpin,state);
  PORTC=i;
    
   
 } 
}

void gadachocheba() {
  int mda[8][3] = {0};
  for (int i = 0 ; i < 8; i++ ){
    for (int j = 0; j < 3; j++) {
      byte x = digits[i][j];
      digits[i][j] = x/2;
      if(x%2 == 1){
        mda[i][(j+1)%3] = 1;
      }
    }
  }
   for (int i = 0 ; i < 8; i++ ){
      for (int j = 0; j < 3; j++) {
        if(mda[i][j] == 1) {
          digits[i][j] += 128;
        }
      }
   }
}
  

void loop() {
  for(int i=0; i<100;i++){
    doJob(HIGH,digits);
  }
  gadachocheba();
}
