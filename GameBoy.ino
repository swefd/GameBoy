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
void drowPoint(short int x,short int y){
    lc.clearDisplay();
    drowDisplay();
    lc.setLed(x,y,true);
    memDisplay(x,y);
}
bool chekPoint(short int x,short int y){
    bool state=false;
    if(display[x][y]==1) state=true;
    return state;
}
void drowDisplay(){
    for(int y=0;y<16;y++){
        for(int x=0;x<8;x++){
             lc.setLed(x,y,display[x][y]);
        }
    }
}
void movePoint(int x_start,int y_start,int x_finish,int y_finish){
    if(!chekPoint(x_finish,y_finish)) {
       memDisplay[x_start][y_start]=0;
       //memDisplay[x_finish][y_finish]=true;
        drowPoint(x_finish,y_finish);
    }
    else if(chekPoint(x_finish,y_finish)||x_finish>8||x_finish<0||y_finish>16||y_finish<0) {
        drowPoint(x_start,y_start);
    }
    
}
void loop() {
    
}
