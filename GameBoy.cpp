#include "GameBoy.h"
#define OP_NOOP   0
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15


LedControl::LedControl(int dataPin, int clkPin, int csPin) {
    SPI_MOSI=dataPin;
    SPI_CLK=clkPin;
    SPI_CS=csPin;
    pinMode(SPI_MOSI,OUTPUT);
    pinMode(SPI_CLK,OUTPUT);
    pinMode(SPI_CS,OUTPUT);
    digitalWrite(SPI_CS,HIGH);
    SPI_MOSI=dataPin;
    for(int i=0;i<64;i++) 
        status[i]=0x00;
    for(int i=0;i<maxDevices;i++) {
        spiTransfer(i,OP_DISPLAYTEST,0);
        spiTransfer(i,OP_DECODEMODE,0);
        clearDisplay();
        shutdown(true);
    }
}
void LedControl::shutdown(bool b) {
   
    if(b){
        spiTransfer(addr, OP_SHUTDOWN,0);
        spiTransfer(addr-1, OP_SHUTDOWN,0);
        }
    else{
        spiTransfer(addr, OP_SHUTDOWN,1);
        spiTransfer(addr-1, OP_SHUTDOWN,1);
        }
}

void LedControl::setIntensity(int intensity) {
    if(intensity>=0 && intensity<16)	
        spiTransfer(addr, OP_INTENSITY,intensity);
        spiTransfer(addr-1, OP_INTENSITY,intensity);
}
void LedControl::clearDisplay() {
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
void LedControl::setLed(int row, int column, boolean state) {
    if(column>=8){
        column=column-8;
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
void LedControl::spiTransfer(int addr, volatile byte opcode, volatile byte data) {
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
void LedControl::testMatrix(short int delaytime){
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