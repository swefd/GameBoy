#include "GameBoy.h"

LedControl lc=LedControl(12,11,10);

unsigned long delaytime=100;
int x,y;
void testFoo(){
    x=1;
    lc.point(x,0);
    for(y=0;y<16;y++){
        if(y==15) lc.point(x,15,x,0);
        else lc.point(x,y,x,y+1);
        delay(100);
        if(!lc.chekCollision(x,y)){
            lc.memDisplay(x,y);
            return;
        }
    }
    lc.drowDisplay();
}
void setup() {
  lc.shutdown(false);
  lc.setIntensity(0);
  lc.clearDisplay();
  //lc.testMatrix(100);  
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  for(int x=0;x<8;x++){
      for(int y=0;y<16;y++){
          lc.display[x][y]=0;
      }
  }
  //lc.display[2][15]=1;
}

  
void loop() {
  //lc.drowDisplay();
  testFoo();
}
