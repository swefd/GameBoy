#include "GameBoy.h"

LedControl lc=LedControl(12,11,10);
byte position=5;
byte gameis=0;
bool isChoos=false;  
unsigned long delaytime=100;
int x,y;
void testFoo(){
    x=1;
    for(y=0;y<16;y++){
        lc.drowDisplay();    
        if(digitalRead(5)||digitalRead(6)) x=x+lc.moveX(x,y,1);
        if(lc.chekCollision(x,y+1)) {
            lc.memDisplay(x,y);
            return;
        }
        lc.drowPoint(x,y);
        lc.fullLine();
        delay(100);
    }
    
}

void bigPixel(int x, int y){
    lc.setLed(x,y,1);
    lc.setLed(x,y+1,1);
    lc.setLed(x+1,y,1);
    lc.setLed(x+1,y+1,1);
}

void bootloader(){  
    gameis=0;
    for(;;){
    if(digitalRead(5)) gameis=1;
    delay(10);
    if(digitalRead(6)) gameis=2;
    delay(10);
    if(gameis==1){
    lc.clearDisplay();
    bigPixel(3,1);
    bigPixel(3,3);
    bigPixel(1,3);
    bigPixel(5,3);
    bigPixel(3,5);
    bigPixel(1,7);
    bigPixel(5,7);
    delay(100);   
    }
    if(gameis==2){
    lc.clearDisplay();
    bigPixel(3,1);
    bigPixel(1,1);
    bigPixel(5,1);
    bigPixel(3,3);
    delay(100);
    }
    if(digitalRead(5)&&digitalRead(6)) return;
    }
}
void createLine(int y){
    if(y>15) y=abs(y-15);
    lc.setLed(0,y,1);
    lc.setLed(0,y+1,1);
    lc.setLed(0,y+2,1);
    lc.setLed(7,y,1);
    lc.setLed(7,y+1,1);
    lc.setLed(7,y+2,1);
    
}
void deletLine(int y){
    if(y>15) y=abs(y-15);
    lc.setLed(0,y,0);
    lc.setLed(0,y+1,0);
    lc.setLed(0,y+2,0);
    lc.setLed(7,y,0);
    lc.setLed(7,y+1,0);
    lc.setLed(7,y+2,0);
}
void creatCar(int x,int y){
    lc.setLed(x,y,1);
    lc.setLed(x,y-1,1);
    lc.setLed(x-1,y-1,1);
    lc.setLed(x+1,y-1,1);
    lc.setLed(x,y-2,1);
    lc.setLed(x-1,y-3,1);
    lc.setLed(x+1,y-3,1);
}
void deletCar(int x,int y){
    lc.setLed(x,y,0);
    lc.setLed(x,y-1,0);
    lc.setLed(x-1,y-1,0);
    lc.setLed(x+1,y-1,0);
    lc.setLed(x,y-2,0);
    lc.setLed(x-1,y-3,0);
    lc.setLed(x+1,y-3,0);  
}
void creatMyCar(int position){
    lc.setLed(position,12,1);
    lc.setLed(position,13,1);
    lc.setLed(position-1,13,1);
    lc.setLed(position+1,13,1);
    lc.setLed(position,14,1);
    lc.setLed(position-1,15,1);
    lc.setLed(position+1,15,1);
}
void deletMyCar(int position){
    lc.setLed(position,12,0);
    lc.setLed(position,13,0);
    lc.setLed(position-1,13,0);
    lc.setLed(position+1,13,0);
    lc.setLed(position,14,0);
    lc.setLed(position-1,15,0);
    lc.setLed(position+1,15,0);
}
void gonka(){
    byte x_car_bot=random(0,10);
    if(x_car_bot>5) x_car_bot=2;
    else x_car_bot=5;
    for(int y=0;y<16;y++){
    createLine(y);
    createLine(y+5);
    createLine(y+10);
    creatCar(x_car_bot,y+3);
    creatMyCar(position);
    if(digitalRead(5)){
        deletMyCar(position);
        position=2;
        creatMyCar(position);
    }
    if(digitalRead(6)){
        deletMyCar(position);
        position=5;
        creatMyCar(position); 
    }
    delay(10);
    deletCar(x_car_bot,y+3);
    deletLine(y-1);
    deletLine(y+4);
    deletLine(y+9);
    }
}
void setup() {
  lc.shutdown(false);
  lc.setIntensity(0);
  lc.clearDisplay();
  //lc.testMatrix(100);  
  pinMode(5,INPUT);
  pinMode(6,INPUT);
 Serial.begin(9600);
 lc.display[0][0]=1;
   for(int x=0;x<8;x++){
      for(int y=0;y<16;y++){
          lc.display[x][y]=0;
      }
  }
  bootloader();
}

  
void loop() {
if(gameis==1) gonka();
if(gameis==2){
lc.drowDisplay();
testFoo();
}
}
