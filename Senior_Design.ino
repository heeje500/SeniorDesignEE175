#include <Bounce.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <ILI9341_t3.h>
#include <font_Arial.h> // from ILI9341_t3

#include "runawaysamples.h"
#include "drums.h" 
#include "beam.h"
#include "power.h"
#include "easy.h" 
#include "drums2.h" 

AudioPlayMemory          playMem8;       
AudioPlayMemory          playMem10;      
AudioPlayMemory          playMem13;      
AudioPlayMemory          playMem9;       
AudioPlayMemory          playMem11;      
AudioPlayMemory          playMem12;      
AudioPlayMemory          playMem14;      
AudioPlayMemory          playMem5;       
AudioPlaySdWav           playSdWav1;     
AudioPlayMemory          playMem15;      
AudioPlayMemory          playMem1;       
AudioPlayMemory          playMem2;       
AudioPlayMemory          playMem3;       
AudioPlayMemory          playMem6;       
AudioPlayMemory          playMem4;       
AudioPlayMemory          playMem7;       
AudioPlaySdRaw           playSdRaw1;     
AudioMixer4              sound13_16;         
AudioMixer4              sound9_12;         
AudioMixer4              sound5_8;         
AudioMixer4              SDsounds_Rec;         
AudioMixer4              sound1_4;        
AudioMixer4              allSounds;        
AudioFilterStateVariable filter1;        
AudioInputI2S            i2s2;           
AudioMixer4              mixerLow;      
AudioMixer4              mixerMid;       
AudioMixer4              mixerHigh;     
AudioAnalyzePeak         peak1;          
AudioRecordQueue         queue1;         
AudioMixer4              filterMix;        
AudioEffectDelay         delay1;         
AudioEffectFreeverb      freeverb1;      
AudioMixer4              delayMix;         
AudioMixer4              reverbMix;        
AudioAnalyzePeak         peak2;         
AudioOutputI2S           headphones;     
AudioConnection          C1(playMem8, 0, sound5_8, 3);
AudioConnection          C2(playMem10, 0, sound9_12, 1);
AudioConnection          C3(playMem13, 0, sound13_16, 0);
AudioConnection          C4(playMem9, 0, sound9_12, 0);
AudioConnection          C5(playMem11, 0, sound9_12, 2);
AudioConnection          C6(playMem12, 0, sound9_12, 3);
AudioConnection          C7(playMem14, 0, sound13_16, 1);
AudioConnection          C8(playMem5, 0, sound5_8, 0);
AudioConnection          C9(playSdWav1, 0, SDsounds_Rec, 0);
AudioConnection          C10(playSdWav1, 1, SDsounds_Rec, 1);
AudioConnection          C11(playMem15, 0, sound13_16, 2);
AudioConnection          C12(playMem1, 0, sound1_4, 0);
AudioConnection          C13(playMem2, 0, sound1_4, 1);
AudioConnection          C14(playMem3, 0, sound1_4, 2);
AudioConnection          C15(playMem6, 0, sound5_8, 1);
AudioConnection          C16(playMem4, 0, sound1_4, 3);
AudioConnection          C17(playMem7, 0, sound5_8, 2);
AudioConnection          C18(playSdRaw1, 0, SDsounds_Rec, 2);
AudioConnection          C19(sound13_16, 0, allSounds, 3);
AudioConnection          C20(sound9_12, 0, allSounds, 2);
AudioConnection          C21(sound5_8, 0, allSounds, 1);
AudioConnection          C22(SDsounds_Rec, 0, sound13_16, 3);
AudioConnection          C23(sound1_4, 0, allSounds, 0);
AudioConnection          C24(allSounds, 0, filter1, 0);
AudioConnection          C25(filter1, 0, mixerLow, 0);
AudioConnection          C26(filter1, 1, mixerMid, 0);
AudioConnection          C27(filter1, 2, mixerHigh, 0);
AudioConnection          C28(i2s2, 0, queue1, 0);
AudioConnection          C29(i2s2, 0, peak1, 0);
AudioConnection          C30(mixerLow, 0, filterMix, 0);
AudioConnection          C31(mixerMid, 0, filterMix, 1);
AudioConnection          C32(mixerHigh, 0, filterMix, 2);
AudioConnection          C33(filterMix, 0, reverbMix, 1);
AudioConnection          C34(filterMix, freeverb1);
AudioConnection          C35(filterMix, delay1);
AudioConnection          C36(filterMix, 0, delayMix, 0);
AudioConnection          C37(delay1, 0, delayMix, 1);
AudioConnection          C38(delay1, 1, delayMix, 2);
AudioConnection          C39(delay1, 2, delayMix, 3);
AudioConnection          C40(freeverb1, 0, reverbMix, 0);
AudioConnection          C41(delayMix, 0, reverbMix, 2);
AudioConnection          C42(reverbMix, 0, headphones, 0);
AudioConnection          C43(reverbMix, 0, headphones, 1);
AudioConnection          C44(reverbMix, peak2); 
AudioControlSGTL5000     sgtl5000_1;     

//LCD DISPLAY
#define TFT_DC      9
#define TFT_CS      36
#define TFT_RST    255  //connect to 3.3V
#define TFT_MOSI    11
#define TFT_SCLK    13
#define TFT_MISO    12
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);

AudioControlSGTL5000 audioShield;

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11
#define SDCARD_SCK_PIN   14

//PROGMEM
Bounce a1 = Bounce(0, 5);
Bounce a2 = Bounce(1, 5);  
Bounce a3 = Bounce(2, 5);
Bounce a4 = Bounce(3, 5);
Bounce b1 = Bounce(4, 5);
Bounce b2 = Bounce(5, 5);
Bounce b3 = Bounce(33, 5);
Bounce b4 = Bounce(34, 5);
Bounce c1 = Bounce(35, 5);

Bounce c2 = Bounce(25, 5);
Bounce c3 = Bounce(37, 5);
Bounce c4 = Bounce(38, 5);
Bounce d1 = Bounce(40, 5);
Bounce d2 = Bounce(41, 5);
Bounce d3 = Bounce(24, 5);

//WAV
Bounce d4 = Bounce(29, 5);

//the i experiment
Bounce button10 = Bounce(28, 5);
Bounce button11 = Bounce(27, 5);

//delay ON
Bounce delayON = Bounce(26, 5);

//stop 
Bounce button12 = Bounce(39, 5);

Bounce buttonRecord = Bounce(30, 8);
Bounce buttonStop = Bounce(31, 8);
Bounce buttonPlay = Bounce(32, 8);

const int myInput = AUDIO_INPUT_MIC;
int mode = 0; 
File frec; 

int i = 0;  //i iteration 

//LED DISPLAY Initations

void setup() {
  Serial.begin(9600);
  AudioMemory(800);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  
  sound1_4.gain(0, 0.4);
  sound1_4.gain(1, 0.4);
  sound1_4.gain(2, 0.4);
  sound1_4.gain(3, 0.4);

  sound5_8.gain(0, 0.4);
  sound5_8.gain(1, 0.4);
  sound5_8.gain(2, 0.4);
  sound5_8.gain(3, 0.4);

  sound9_12.gain(0, 0.4);
  sound9_12.gain(1, 0.4);
  sound9_12.gain(2, 0.4);
  sound9_12.gain(3, 0.4);

  allSounds.gain(0, 0.4);
  allSounds.gain(1, 0.4);
  allSounds.gain(2, 0.4);
  allSounds.gain(3, 0.4);

  sound13_16.gain(0, 0.4);
  sound13_16.gain(1, 0.4);
  sound13_16.gain(2, 0.4);
  sound13_16.gain(3, 0.4);

  SDsounds_Rec.gain(0, 0.4);
  SDsounds_Rec.gain(1, 0.4);
  SDsound_Rec.gain(2, 0.4);
  SDsound_Rec.gain(3, 0.4);

  //delay channel 
  reverbMix.gain(3, 0.5);          
  delay1.disable(0);            
  delay1.disable(1);            
  delay1.disable(2);            
  delay1.disable(3);            
  delay1.disable(4);            
  delay1.disable(5);            
  delay1.disable(6);            
  delay1.disable(7);            

  AudioInterrupts();
  
 //Buttons
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);
  pinMode(35, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(37, INPUT_PULLUP);
  pinMode(38, INPUT_PULLUP);
  pinMode(40, INPUT_PULLUP);
  pinMode(41, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);

  //stop
  pinMode(39, INPUT_PULLUP);

  //I
  pinMode(28, INPUT_PULLUP);
  //decremnet
  pinMode(27, INPUT_PULLUP);
  
//Record, play, and stop
  pinMode(30, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);

  //turn on delay 
  pinMode(26, INPUT_PULLUP);

  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_RED);
  tft.setFont(Arial_24);
  tft.setCursor(5, 8);
  tft.println("HBGM");


  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.micGain(40);
  sgtl5000_1.lineInLevel(2,2);

  //Initalize SD Card
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);

  if (!(SD.begin(SDCARD_CS_PIN))) {
    while(1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
}



elapsedMillis msecs;

void loop() {
  //volume
  int knob = analogRead(A1);
  float vol = (float)knob / 1023.0;
  audioShield.volume(vol);

  int v = map(knob, 0, 1023, 0, 100);

  if (msecs > 15) {
    if (v > 0) {
      msecs = 0;
      float rightNumber = v;

      // draw the verticle bars
      tft.setTextColor(ILI9341_WHITE);
      tft.setFont(Arial_14);
      tft.setCursor(127, 160);
      tft.print("Volume");
      tft.setTextColor(ILI9341_BLUE);
      int height = rightNumber;
      tft.fillRect(100, 280 - height, 120, height, ILI9341_BLUE);
      tft.fillRect(100, 280 - 100, 120, 101 - height, ILI9341_BLACK);
     
      tft.setFont(Arial_14);
      tft.fillRect(130, 284, 40, 16, ILI9341_BLACK);
      tft.setCursor(130, 284);
      tft.print(rightNumber);
    }

  }
  
  //filters
  int knobL = analogRead(A0);
  float volL = (float)knobL / 1023.0;
  mixerLow.gain(0, volL);
  mixerLow.gain(1, volL);

  int l = map(knobL, 0, 1023, 0, 100);
  
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_14);
  tft.setCursor(100, 50);
  tft.print("Lowpass:");

  tft.setTextColor(ILI9341_GREEN);
  
  if(0 < l && l < 5){
    tft.fillRect(190, 50, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 50);
    tft.print("0%");
  }
  if(5 < l && l < 10){
    tft.fillRect(190, 50, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 50);
    tft.print("10%");
  }
  if(10 < l && l < 20){
    tft.fillRect(190, 50, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 50);
    tft.print("20%");
  }
  if(20 < l && l < 30){
    tft.fillRect(190, 50, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 50);
    tft.print("30%");
  }
  if(30 < l && l < 40){
    tft.fillRect(190, 50, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 50);
    tft.print("40%");
  }
  if(40 < l && l < 50){
    tft.fillRect(190, 50, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 50);
    tft.print("50%");
  }
  if(50 < l && l < 60){
    tft.fillRect(190, 50, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 50);
    tft.print("60%");
  }
  if(60 < l && l < 70){
    tft.fillRect(190, 50, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 50);
    tft.print("70%");
  }
  if(70 < l && l < 80){
    tft.fillRect(190, 50, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 50);
    tft.print("80%");
  }
  if(80 < l && l < 90){
    tft.fillRect(190, 50, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 50);
    tft.print("90%");
  }
  if(90 < l && l < 100){
    tft.fillRect(190, 50, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 50);
    tft.print("100%");
  }

  int knobH = analogRead(A3);
  float volH = (float)knobH / 1023.0;
  mixerHigh.gain(0, volH);
  mixerHigh.gain(1, volH);

  int h = map(knobH, 0, 1023, 0, 100);

  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_14);
  tft.setCursor(100, 70);
  tft.print("Highpass:");

  tft.setTextColor(ILI9341_GREEN);

  if(0 < h && h < 5){
    tft.fillRect(190, 70, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 70);
    tft.print("0%");
  }
  if(5 < h && h < 10){
    tft.fillRect(190, 70, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 70);
    tft.print("10%");
  }
  if(10 < h && h < 20){
    tft.fillRect(190, 70, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 70);
    tft.print("20%");
  }
  if(20 < h && h < 30){
    tft.fillRect(190, 70, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 70);
    tft.print("30%");
  }
  if(30 < h && h < 40){
    tft.fillRect(190, 70, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 70);
    tft.print("40%");
  }
  if(40 < h && h < 50){
    tft.fillRect(190, 70, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 70);
    tft.print("50%");
  }
  if(50 < h && h < 60){
    tft.fillRect(190, 70, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 70);
    tft.print("60%");
  }
  if(60 < h && h < 70){
    tft.fillRect(190, 70, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 70);
    tft.print("70%");
  }
  if(70 < h && h < 80){
    tft.fillRect(190, 70, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 70);
    tft.print("80%");
  }
  if(80 < h && h < 90){
    tft.fillRect(190, 70, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 70);
    tft.print("90%");
  }
  if(90 < h && h < 100){
    tft.fillRect(190, 70, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 70);
    tft.print("100%");
  }
  

  int knobV = analogRead(A8);
  float freeV = (float)analogRead(A8) / 1023.0;
        mixer6.gain(0, freeV);
        mixer6.gain(1, 1.0 - freeV);

  int r = map(knobV, 0, 1023, 0, 100);

  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_14);
  tft.setCursor(100, 90);
  tft.print("Reverb:");

  tft.setTextColor(ILI9341_GREEN);

  if(0 < r && r < 5){
    tft.fillRect(190, 90, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 90);
    tft.print("0%");
  }
  if(5 < r && r < 10){
    tft.fillRect(190, 90, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 90);
    tft.print("10%");
  }
  if(10 < r && r < 20){
    tft.fillRect(190, 90, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 90);
    tft.print("20%");
  }
  if(20 < r && r < 30){
    tft.fillRect(190, 90, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 90);
    tft.print("30%");
  }
  if(30 < r && r < 40){
    tft.fillRect(190, 90, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 90);
    tft.print("40%");
  }
  if(40 < r && r < 50){
    tft.fillRect(190, 90, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 90);
    tft.print("50%");
  }
  if(50 < r && r < 60){
    tft.fillRect(190, 90, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 90);
    tft.print("60%");
  }
  if(60 < r && r < 70){
    tft.fillRect(190, 90, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 90);
    tft.print("70%");
  }
  if(70 < r && r < 80){
    tft.fillRect(190, 90, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 90);
    tft.print("80%");
  }
  if(80 < r && r < 90){
    tft.fillRect(190, 90, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 90);
    tft.print("90%");
  }
  if(90 < r && r < 100){
    tft.fillRect(190, 90, 50, 16, ILI9341_BLACK);
    tft.setCursor(190, 90);
    tft.print("100%");
  }

  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(Arial_14);
  tft.setCursor(100, 110);
  tft.print("Delay:");

  // Update all the button objects
  a1.update();
  a2.update();
  a3.update();
  a4.update();
  b1.update();
  b2.update();
  b3.update();
  b4.update();
  c1.update();
  c2.update();
  c3.update();
  c4.update();
  d1.update();
  d2.update();
  d3.update();
  d4.update();
    
  button10.update();
  button11.update();
  button12.update();
  

  delayON.update();


  if(delayON.fallingEdge()) {
    tft.fillRect(160, 110, 50, 16, ILI9341_BLACK);
    tft.setTextColor(ILI9341_GREEN);
    tft.print(" ON");
  }

  else{
    tft.fillRect(160, 110, 50, 16, ILI9341_BLACK);
    tft.setTextColor(ILI9341_RED);
    tft.print(" OFF");
  }
  
if (button10.fallingEdge()) {
    i++; 
  }

if (button11.fallingEdge()) {
    i--;
}


 if (i == 0) {
  if (a1.fallingEdge()) {
    playMem1.play(AudioSampleRunaway1stkey);
  }
  
  if (a2.fallingEdge()) {
    playMem2.play(AudioSampleRunaway2ndkey);
  }
  if (a3.fallingEdge()) {
    playMem3.play(AudioSampleR3rdkeywav);
  }
  if (a4.fallingEdge()) {
    playMem4.play(AudioSampleRunaway4th);
  }
  if (b1.fallingEdge()) {
    playMem5.play(AudioSampleRunaway5th);
  }
  if (b2.fallingEdge()) {
    playMem6.play(AudioSampleRunaway6th);
  }
  if (b3.fallingEdge()) {
    playMem7.play(AudioSampleRunaway7th);
  }
  if (b4.fallingEdge()) {
    playMem8.play(AudioSampleRunawaylastkey);
  }
  if (c1.fallingEdge()) {
    playMem9.play(AudioSampleWho);
  }

  if (c2.fallingEdge()) {
    playMem10.play(AudioSampleBeemC12);
  }

  if (c3.fallingEdge()) {
    playMem11.play(AudioSamplePowera1);
    
  }

  if (c4.fallingEdge()) {
    playMem12.play(AudioSamplePowera2);  
  }

  if (d1.fallingEdge()) {
    playMem13.play(AudioSamplePowera3);
  }

  if (d2.fallingEdge()) {
    playMem14.play(AudioSamplePowerd1);
  }

  if (d3.fallingEdge()) {
    playMem15.play(AudioSampleLucid4);
    
  }
  if (d4.fallingEdge()) {
    playSdWav1.play("RUN1.WAV");
  }

}
  
  if (i == 1) { 

     if (a1.fallingEdge()) {
      playMem1.play(AudioSampleC1);
     }

    if (a2.fallingEdge()) {
      playMem2.play(AudioSampleK1);
    }

    if(a3.fallingEdge()) {
       playMem3.play(AudioSampleS1);
    }

    if (a4.fallingEdge()) {
    playMem4.play(AudioSampleO1);
    }
    
  if (b1.fallingEdge()) {
    playMem5.play(AudioSampleK1);
  }
  if (b2.fallingEdge()) {
    playMem6.play(AudioSampleH1);
  }

  if (b3.fallingEdge()) {
    playMem7.play(AudioSampleDream);
  }
  if (b4.fallingEdge()) {
    playMem8.play(AudioSampleInst2);
  } 
  
    if (c1.fallingEdge()) {
    playMem9.play(AudioSampleWho);
  }

  if (c2.fallingEdge()) {
    playMem10.play(AudioSampleH808);
  }
  
  if (c3.fallingEdge()) {
    playMem11.play(AudioSampleHclap);
  }
  if (c4.fallingEdge()) {
    playMem12.play(AudioSampleHhi);
  }
  
  if (d1.fallingEdge()) {
    playMem13.play(AudioSampleHkick);
  }
  if (d2.fallingEdge()) {
    playMem14.play(AudioSampleRkick);
  }
  if (d3.fallingEdge()) {
    playMem15.play(AudioSampleRunaway6th);
  }
    if (d4.fallingEdge()) {
    playSdWav1.play("RUN1.WAV");
  }
}

if (i == 2) {
  if (a1.fallingEdge()) {
    playMem1.play(AudioSampleBeemK12w);
  }
  
  if (a2.fallingEdge()) {
    playMem2.play(AudioSampleBeemK2);
  }
  if (a3.fallingEdge()) {
    playMem3.play(AudioSampleBeemS12w);
  }
  if (a4.fallingEdge()) {
    playMem4.play(AudioSampleBeemS2);
  }
  if (b1.fallingEdge()) {
    playMem5.play(AudioSampleBeemS3);
  }
  if (b2.fallingEdge()) {
    playMem6.play(AudioSampleBeemS4);
  }
  if (b3.fallingEdge()) {
    playMem7.play(AudioSampleBeemS5);
  }
  if (b4.fallingEdge()) {
    playMem8.play(AudioSampleBeemS6);
  }
  if (c1.fallingEdge()) {
    playMem9.play(AudioSampleBeemT1);
  }
  if (d4.fallingEdge()) {
    playSdWav1.play("RUN1.WAV");
  }

  if (c2.fallingEdge()) {
    playMem10.play(AudioSampleBeemC12);
  }
  
  if (c3.fallingEdge()) {
    playMem11.play(AudioSamplePowera1);
  }
  if (c4.fallingEdge()) {
    playMem12.play(AudioSamplePowera2);
  }
  if (d1.fallingEdge()) {
    playMem13.play(AudioSamplePowera3);
  }
  if (d2.fallingEdge()) {
    playMem14.play(AudioSamplePowerd1);
  }
  if (d3.fallingEdge()) {
    playMem15.play(AudioSampleRunaway6th);
  }
  
}

if (i==3) {
  if (a1.fallingEdge()) {
    playMem1.play(AudioSampleE808);
  }
  
  if (a2.fallingEdge()) {
    playMem2.play(AudioSampleE8082);
  }
  if (a3.fallingEdge()) {
    playMem3.play(AudioSampleEasy);
  }
  if (a4.fallingEdge()) {
    playMem4.play(AudioSampleEkick);
  }
  if (b1.fallingEdge()) {
    playMem5.play(AudioSampleEs1);
  }
  if (b2.fallingEdge()) {
    playMem6.play(AudioSampleEs2);
  }
  if (b3.fallingEdge()) {
    playMem7.play(AudioSampleEs3);
  }
  if (b4.fallingEdge()) {
    playMem8.play(AudioSampleEs4);
  }
  if (c1.fallingEdge()) {
    playMem9.play(AudioSampleEs5);
  }
  if (d4.fallingEdge()) {
    playSdWav1.play("RUN1.WAV");
  }

  if (c2.fallingEdge()) {
    playMem10.play(AudioSampleEs6);
  }
  
  if (c3.fallingEdge()) {
    playMem11.play(AudioSampleEsnare);
  }
  if (c4.fallingEdge()) {
    playMem12.play(AudioSampleHe);
  }
  if (d1.fallingEdge()) {
    playMem13.play(AudioSampleMy);
  }
  if (d2.fallingEdge()) {
    playMem14.play(AudioSamplePowerd1);
  }
  if (d3.fallingEdge()) {
    playMem15.play(AudioSampleRunaway6th);
  }
  
}

if (i == 4) {
  if (a1.fallingEdge()) {
    playMem1.play(AudioSampleCut1);
  }
  
  if (a2.fallingEdge()) {
    playMem2.play(AudioSampleCut2);
  }
  if (a3.fallingEdge()) {
    playMem3.play(AudioSampleCut3);
  }
  if (a4.fallingEdge()) {
    playMem4.play(AudioSampleH808);
  }
  if (b1.fallingEdge()) {
    playMem5.play(AudioSampleHclap);
  }
  if (b2.fallingEdge()) {
    playMem6.play(AudioSampleHhi);
  }
  if (b3.fallingEdge()) {
    playMem7.play(AudioSampleHkick);
  }
  if (b4.fallingEdge()) {
    playMem8.play(AudioSampleRkick);
  }
  if (c1.fallingEdge()) {
    playMem9.play(AudioSampleEs5);
  }
  if (d4.fallingEdge()) {
    playSdWav1.play("RUN1.WAV");
  }

  if (c2.fallingEdge()) {
    playMem10.play(AudioSampleLucid1);
  }
  
  if (c3.fallingEdge()) {
    playMem11.play(AudioSampleLucid2);
  }
  if (c4.fallingEdge()) {
    playMem12.play(AudioSampleLucid3);
  }
  if (d1.fallingEdge()) {
    playMem13.play(AudioSampleLucid4);
  }
  if (d2.fallingEdge()) {
    playMem14.play(AudioSampleLucid5);
  }
  if (d3.fallingEdge()) {
    playMem15.play(AudioSampleRunaway6th);
  }

  
}

  if (button12.fallingEdge()) {
    stopMusic(); 
  }

  if (delayON.fallingEdge()) {
    delay1.delay(0, 500);         
    delay1.delay(1, 400);
    delay1.delay(2, 300);
  }
  if (delayON.risingEdge()) {
    delay1.disable(0);               
    delay1.disable(1);            
    delay1.disable(2);
  }
  
  buttonRecord.update();
  buttonStop.update();
  buttonPlay.update();
  
  // Respond to button presses
 // 0 = stopped, 1 = recording, 2 = playing
  if (buttonRecord.fallingEdge()) {
    Serial.println("Record Button Press");
    if (mode == 2) stopPlaying();
    if (mode == 0) startRecording();

  }
  
  if (buttonStop.fallingEdge()) {
    Serial.println("Stop Button Press");
    if (mode == 1) stopRecording();
    if (mode == 2) stopPlaying(); 
  }
  
  if (buttonPlay.fallingEdge()) {
    Serial.println("Play Button Pressed");
    if (mode == 1) stopRecording(); 
    if (mode == 0) startPlaying();
  }

  if (mode == 1) {
    continueRecording();
  }
  if (mode == 2) {
    continuePlaying();
  }

  if (msecs > 15) {
    if (peak2.available()) {
      msecs = 0;
      float leftNumber = peak2.read();
      

      // draw the verticle bars
      tft.setTextColor(ILI9341_WHITE);
      tft.setFont(Arial_14);
      tft.setCursor(15, 50);
      tft.print("Peak");
      tft.setTextColor(ILI9341_GREEN);
      int height = leftNumber * 210;
      tft.fillRect(15, 280 - height, 40, height, ILI9341_GREEN);
      tft.fillRect(15, 300 - 225, 40, 210 - height, ILI9341_BLACK);
      tft.setFont(Arial_14);
      tft.fillRect(15, 284, 40, 16, ILI9341_BLACK);
      tft.setCursor(15, 284);
      tft.print(leftNumber);
    }

}

}


//-------------------------------------------------------//
void startRecording() {
  Serial.println("startRecording");
  if (SD.exists("RECORD.RAW")) {
    SD.remove("RECORD.RAW");
  }
  frec = SD.open("RECORD.RAW", FILE_WRITE);
  if (frec) {
    queue1.begin();
    mode = 1;
  }
}

void continueRecording() {
  if (queue1.available() >= 2) {
    byte buffer[512];
    memcpy(buffer, queue1.readBuffer(), 256);
    queue1.freeBuffer();
    memcpy(buffer+256, queue1.readBuffer(), 256);
    queue1.freeBuffer();
    frec.write(buffer, 512);
  }
}

void stopRecording() {
  Serial.println("stopRecording");
  queue1.end();
  if (mode == 1) {
    while (queue1.available() > 0) {
      frec.write((byte*)queue1.readBuffer(), 256);
      queue1.freeBuffer();
    }
    frec.close();
  }
  mode = 0;
}

void startPlaying() {
  Serial.println("startPlaying");
  playSdRaw1.play("RECORD.RAW");
  mode = 2;
}

void continuePlaying() {
  if (!playSdRaw1.isPlaying()) {
    playSdRaw1.stop();
    mode = 0;
  }
}

void stopPlaying() {
  Serial.println("stopPlaying");
  if (mode == 2) playSdRaw1.stop();
  mode = 0;
}

void stopMusic() {
  
 
  if (playMem1.isPlaying()) {
    playMem1.stop();
  }
  
  else if (playMem2.isPlaying()){
    playMem2.stop();
  }
  else if (playMem3.isPlaying()) {
    playMem3.stop();
  }
  else if (playMem4.isPlaying()) {
    playMem4.stop();
  }
  else if (playMem5.isPlaying()) {
    playMem5.stop();
  }
  else if (playMem6.isPlaying()) {
    playMem6.stop();
  }
  else if (playMem7.isPlaying()) {
    playMem7.stop();
  }
  else if (playMem8.isPlaying()) {
    playMem8.stop();
  }
  else if (playMem9.isPlaying()) {
    playMem9.stop();
  }
  else if (playSdWav1.isPlaying()) {
    playSdWav1.stop();
  }

}
