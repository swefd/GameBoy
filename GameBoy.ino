#include "GameBoy.h"

LedControl lc=LedControl(12,11,10);
byte position=5;
byte gameis=0;
int x_cube,y_cube;
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
void testCube(){
    x=1;
    for(y=0;y<16;y++){
        lc.drowDisplay();
        if(digitalRead(5)||digitalRead(6)) {
            lc.clearDisplay();
            x=x+lc.moveX(x,y,1);
            lc.drowPoint(x,y);
            lc.drowPoint(x,y+1);
            lc.drowPoint(x+1,y);
            lc.drowPoint(x+1,y+1);
            lc.drowDisplay();
        }
        if(lc.chekCollision(x,y+2)||lc.chekCollision(x+1,y+2)) {
            lc.memDisplay(x,y);
            lc.memDisplay(x,y+1);
            lc.memDisplay(x+1,y);
            lc.memDisplay(x+1,y+1);
            return;
        }
            lc.drowPoint(x,y);
            lc.drowPoint(x,y+1);
            lc.drowPoint(x+1,y);
            lc.drowPoint(x+1,y+1);
            lc.fullLine();
            delay(100);

    }
}
void Cube(int x, int y){
byte cordX[]={x,x+1,x,x+1};
byte cordY[]={y,y,y+1,y+1};
    
    for(int i=0;i<4;i++){
        lc.setLed(abs(cordX[i]-7),cordY[i],1);
    }
    
}

void tetrisBlock(int x){
int timedel=100;
x=abs(x-7);
for(int y=0;y<16;y++){
    if(digitalRead(5))x=x-lc.moveX(x,y,1);
    if(digitalRead(6))x=x-lc.moveX(x-1,y,1);
    
    lc.clearDisplay();
    lc.drowDisplay();
    if(lc.isFree(x,y+2)||lc.isFree(x+1,y+2)){
        lc.setLed(x,y,1);
        lc.setLed(x,y+1,1);
        lc.setLed(x+1,y,1);
        lc.setLed(x+1,y+1,1);
    }
    else {
        x=abs(x-7);
        lc.memDisplay(x,y);
        lc.memDisplay(x,y+1);
        lc.memDisplay(x+1,y);
        lc.memDisplay(x+1,y+1);
    } 
    delay(timedel); 
}
/*
int y=0;
int x=random(-1,8);
byte cordX[]={x,x+1,x,x+1};
byte cordY[]={y,y,y+1,y+1};
int timedel=100;
    for(y;y<16;y++){
        
        x=x+lc.moveX(x,y,1);
        if(lc.isFree(x,y+2)||lc.isFree(x+1,y+2)){
            lc.clearDisplay();
            for(int i=0;i<4;i++){
                lc.setLed(abs(cordX[i]-7),cordY[i],1);
            }
            delay(timedel);
        }
        else {
            for(int i=0;i<4;i++){
                lc.memDisplay(abs(cordX[i]-7),cordY[i]);
            }
        }  
    }
*/
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
 //bootloader();
}

  
void loop() {
testCube();
delay(10);
/*
if(gameis==1){
for(;;){
gonka();
}
} 

if(gameis==2){
for(;;){
lc.drowDisplay();
testFoo();
}
}
*/
}
