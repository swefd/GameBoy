#include "GameBoy.h"
#define OP_NOOP   0
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15
#define UP             1
#define DOWN           2
#define LEFT           3
#define RIGHT          4

GameBoy::GameBoy() {
    SPI_MOSI=12;
    SPI_CLK=11;
    SPI_CS=10;
    pinMode(SPI_MOSI,OUTPUT);
    pinMode(SPI_CLK,OUTPUT);
    pinMode(SPI_CS,OUTPUT);
    digitalWrite(SPI_CS,HIGH);
    //SPI_MOSI=dataPin;
    for(int i=0;i<64;i++) status[i]=0x00;
    for(int i=0;i<maxDevices;i++) {
        spiTransfer(i,OP_DISPLAYTEST,0);
        spiTransfer(i, OP_SCANLIMIT,7);
        spiTransfer(i,OP_DECODEMODE,0);
        clearDisplay();
        shutdown(true);
    }
}
void GameBoy::shutdown(bool b) {
   
    if(b){
        spiTransfer(addr, OP_SHUTDOWN,0);
        spiTransfer(addr-1, OP_SHUTDOWN,0);
        }
    else{
        spiTransfer(addr, OP_SHUTDOWN,1);
        spiTransfer(addr-1, OP_SHUTDOWN,1);
        }
}

void GameBoy::setIntensity(int intensity) {
    if(intensity>=0 && intensity<16)	
        spiTransfer(addr, OP_INTENSITY,intensity);
        spiTransfer(addr-1, OP_INTENSITY,intensity);
}
void GameBoy::clearDisplay() {
    short int offset1;
    short int offset2;
    offset1=addr*8;
    offset2=(addr-1)*8;
    for(int i=0;i<8;i++) {
        status[offset1+i]=0;
        spiTransfer(addr, i+1,status[offset1+i]);
    }
    for(int i=0;i<8;i++) {
    status[offset2+i]=0;
    spiTransfer((addr-1), i+1,status[offset2+i]);
    }
    
}
void GameBoy::setLed(int row, int column, boolean state) {
    if(column>=8){
        column=abs(column-8);
    int offset;
    byte val=0x00;
    
    offset=(addr-1)*8;
    val=B10000000 >> column;
    if(state)
        status[offset+row]=status[offset+row]|val;
    else {
        val=~val;
        status[offset+row]=status[offset+row]&val;
    }
        spiTransfer(addr-1, row+1,status[offset+row]);
    }
    else{
    int offset;
    byte val=0x00;
    if(addr<0 || addr>=maxDevices)
        return;
        offset=addr*8;
    val=B10000000 >> column;
    if(state)
        status[offset+row]=status[offset+row]|val;
    else {
        val=~val;
        status[offset+row]=status[offset+row]&val;
    }
        spiTransfer(addr, row+1,status[offset+row]);
    }
    
}
void GameBoy::spiTransfer(int addr, volatile byte opcode, volatile byte data) {
    //Create an array with the data to shift out
    int offset=addr*2;
    int maxbytes=maxDevices*2;

    for(int i=0;i<maxbytes;i++)
        spidata[i]=(byte)0;
    //put our device data into the array
    spidata[offset+1]=opcode;
    spidata[offset]=data;
    //enable the line 
    digitalWrite(SPI_CS,LOW);
    //Now shift out the data 
    for(int i=maxbytes;i>0;i--)
        shiftOut(SPI_MOSI,SPI_CLK,MSBFIRST,spidata[i-1]);
    //latch the data onto the display
    digitalWrite(SPI_CS,HIGH);
}    
void GameBoy::testMatrix(short int delaytime){
for(int x=0;x<8;x++){
    for(int y=0;y<16;y++){
        setLed(x,y,true);
        delay(delaytime);
    }
} 
delay(1000);
clearDisplay();
delay(100);
for(int y1=0;y1<16;y1++){
    for(int x1=0;x1<8;x1++){
        setLed(x1,y1,true);
        delay(delaytime);
    }
}
clearDisplay();       
}

void GameBoy::memDisplay(short int x,short int y){
    x=abs(x-7);
    display[x][y]=true;
}
void GameBoy::drawPoint(int x,int y){
    x=abs(x-7);

    if(x<8&&x>-1&&y>0&&y<16){
        setLed(x,y,1);
    }
    else return;
}
void GameBoy::wipePoint(int x,int y){
    x=abs(x-7);
    if(x<8&&x>0&&y>0&&y<16){
        setLed(x,y,0);
        display[x][y]=0;
    }
    else return;
}
bool GameBoy::chekCollision(int x, int y){
    x=abs(x-7);
    if(display[x][y]==1||x>7||x<0||y>15||y<0) return true;
    else return false;

}
void GameBoy::drawDisplay(){
      for(int x=0;x<8;x++){
      for(int y=0;y<16;y++){
          setLed(abs(x-7),y,display[abs(x-7)][y]);
      }
  }
}
bool GameBoy::chekState(int x,int y){
        if(display[x][y]==1) return true;
        else false;
} 
bool GameBoy::isFree(int x,int y){
    x=abs(x-7);
    if(display[x][y]==1||x<0||x>7||y<0||y>15) return false;
    else return true;
}      
int GameBoy::moveX(int start_x, int start_y,int left_x,int right_x, int move_var ){
    start_x=abs(start_x-7);
    if(digitalRead(5)){
        if(display[start_x-move_var-right_x][start_y]==1||start_x-move_var-right_x<0) return 0;
        else return move_var;
    }
    else if(digitalRead(6)){
        if(display[start_x+move_var+left_x][start_y]==1||start_x+move_var+left_x>7) return 0;
        else return -move_var;
    }
    else return 0;
}
void GameBoy::clearLine(byte num_line){
    for(int x=0;x<8;x++) {
        display[abs(x-7)][num_line]=false;
        setLed(abs(x-7),num_line,0);
    }
}        
void GameBoy::fullLine(){
    for(int y=15;y>-1;y--){
        byte count=0;
        for(int x=0;x<8;x++){
            if(display[abs(x-7)][y]==true){
                count++;
            }
            if(count==8) {
                clearLine(y);
                for(y;y>0;y=y-1){  
                    for(int x=0;x<8;x++){
                        display[abs(x-7)][y]=display[abs(x-7)][y-1];
                    }
                    clearLine(y-1);
                }    
            }
        }
    }
}
int GameBoy::getKey(){
    pinMode(A1,INPUT);
    pinMode(2,INPUT);
    pinMode(3,INPUT);
    int keyCode=0;
    int a=analogRead(A1);
    if(a>190&&a<213) keyCode=5; // Right
    delay(10);
    if(a>240&&a<270) keyCode=6; //Down
    delay(10);
    if(a>300&&a<370) keyCode=3;//Up
    delay(10);
    if(a>400&&a<520) keyCode=4;//Left
    delay(10);
    if(digitalRead(2))keyCode=1;//KEY1
    delay(10);
    if(digitalRead(3))keyCode=2;//KEY2
    return keyCode;
}
