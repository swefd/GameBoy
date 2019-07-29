#include "GameBoy.h"

LedControl lc=LedControl(12,11,10);

unsigned long delaytime=100;
int x,y;
void testFoo(){
    x=1;
    for(y=0;y<16;y++){
        lc.drowDisplay();
        Serial.println(lc.chekCollision(x,y+1));
        if(digitalRead(5)) {
            x=x+1;
            delay(10);
        }
        if(digitalRead(6)) {
            x=x-1;
            delay(10);
        }
        if(lc.chekCollision(x,y+1)) {
            lc.memDisplay(x,y);
            Serial.println("Get");
            return;
        }
        lc.drowPoint(x,y);
        delay(1);
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
  //lc.display[0][0]=1;
}

  
void loop() {
 // lc.drowDisplay();
  testFoo();
}
