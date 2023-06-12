#include <Tone32.h>
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
//const int    
const int outPin[3] = {25, 26, 27};
// The ESP32 has 16 channels which can generate 16 independent waveforms // We'll just choose PWM channel 0 here 
const int  outChannel[3]= {0, 1, 2};
int freq[3];
int dur[3];
char cmd[100];
int cmdIndex;

void debug(String st) {
  SerialBT.print("debug " + st + "\n");
}

void exeCmd() {
  
 if(cmd[0]=='a' && cmd[1]==' ') {
    freq[0]= atoi(cmd+2);
    tone(outPin[0], freq[0], dur[0], 
    outChannel[0]);
 // noTone(outPin[0],outChannel[0]);
    debug((String)"Freq1 = "+freq[0]+"Hz");
  }
if(cmd[0]=='b' && cmd[1]==' ') {
    freq[1]= atoi(cmd+2);
    tone(outPin[1], freq[1], dur[1], 
    outChannel[1]);
 // noTone(outPin[0],outChannel[0]);
    debug((String)"Freq2 = "+freq[1]+"Hz");
  }  
if(cmd[0]=='c' && cmd[1]==' ') {
    freq[2]= atoi(cmd+2);
    tone(outPin[2], freq[2], dur[2], 
    outChannel[2]);
 // noTone(outPin[0],outChannel[0]);
    debug((String)"Freq3 = "+freq[2]+"Hz");
  } 
  
  if(cmd[0]=='d' && cmd[1]==' ') {
    dur[0]= atoi(cmd+2);    
    debug((String)"Dur1 = "+dur[0]+" ms");
  }   
  
  
  if(cmd[0]=='e' && cmd[1]==' ') {
    dur[1]= atoi(cmd+2);    
    debug((String)"Dur2 = "+dur[1]+" ms");
  }   
  
   if(cmd[0]=='f' && cmd[1]==' ') {
    dur[2]= atoi(cmd+2);    
    debug((String)"Dur3 = "+dur[2]+" ms");
  }   
  
 if(cmd[0]=='g' && cmd[1]==' ') {
 noTone(outPin[0],outChannel[0]);
}  
if(cmd[0]=='h' && cmd[1]==' ') {
 noTone(outPin[1],outChannel[1]);
}  
 if(cmd[0]=='i' && cmd[1]==' ') {
 noTone(outPin[2],outChannel[2]);
}
}
void setup() {
 for(int i=0; i<3; i++){
  ledcAttachPin(outPin[i], outChannel[i]); 
 }
 Serial.begin(115200);
 SerialBT.begin("ESP32"); //Bluetooth device name
 Serial.println("The device started, now you can pair it with bluetooth!");// Bluetooth default baud is 115200
  cmdIndex = 0;
}
void loop() {  
   if(SerialBT.available()) {    
    char c = (char)SerialBT.read();    
    if(c=='\n') {
      cmd[cmdIndex] = 0;
      exeCmd();  // execute the command
      cmdIndex = 0; // reset the cmdIndex
    } else {      
      cmd[cmdIndex] = c;
      if(cmdIndex<99) cmdIndex++;
    }
  }
}