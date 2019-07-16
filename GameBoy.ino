#include "GameBoy.h"

LedControl lc=LedControl(12,11,10);

unsigned long delaytime=100;
bool display[8][16];
void setup() {
  lc.shutdown(false);
  lc.setIntensity(0);
  lc.clearDisplay();
  lc.testMatrix(100);  
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  for(int x=0;x<8;x++){
      for(int y=0;y<16;y++){
          display[x][y]=0;
      }
  }
}
void memDisplay(short int x,short int y){
    display[x][y]=true;
}
  
void loop() {
}
