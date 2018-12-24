#include "Charliplexing.h"      //initializes the LoL Sheild library
#include "Font.h"

// Images

const byte tw[126] PROGMEM = {
   0, 1, 0, 0, 0, 0, 0, 5, 7, 6, 2, 2, 0, 0, 
   0, 4, 5, 0, 0, 0, 3, 7, 7, 7, 7, 3, 0, 0, 
   0, 3, 7, 7, 4, 2, 5, 7, 7, 7, 7, 0, 0, 0, 
   0, 3, 7, 7, 7, 7, 7, 7, 7, 7, 6, 0, 0, 0, 
   0, 1, 7, 7, 7, 7, 7, 7, 7, 7, 4, 0, 0, 0, 
   0, 0, 4, 7, 7, 7, 7, 7, 7, 7, 1, 0, 0, 0, 
   0, 0, 1, 6, 7, 7, 7, 7, 7, 4, 0, 0, 0, 0, 
   0, 0, 0, 3, 7, 7, 7, 7, 4, 0, 0, 0, 0, 0, 
   0, 2, 5, 7, 7, 7, 5, 2, 0, 0, 0, 0, 0, 0};
   
const byte wa[126] PROGMEM = {
   0, 0, 0, 0, 1, 7, 7, 7, 1, 0, 0, 0, 0, 0, 
   0, 0, 0, 6, 7, 7, 7, 7, 7, 6, 0, 0, 0, 0, 
   0, 0, 2, 7, 0, 3, 7, 7, 7, 7, 2, 0, 0, 0, 
   0, 0, 7, 7, 0, 0, 7, 7, 7, 7, 7, 0, 0, 0, 
   0, 0, 7, 7, 0, 0, 7, 7, 7, 7, 7, 0, 0, 0, 
   0, 0, 7, 7, 7, 0, 0, 1, 0, 7, 7, 0, 0, 0, 
   0, 0, 1, 7, 7, 7, 1, 0, 0, 7, 1, 0, 0, 0, 
   0, 0, 3, 7, 7, 7, 7, 7, 7, 4, 0, 0, 0, 0, 
   0, 0, 7, 3, 1, 7, 7, 7, 1, 0, 0, 0, 0, 0};

const byte hangouts[126] PROGMEM = {
   0, 0, 0, 0, 3, 6, 7, 6, 3, 0, 0, 0, 0, 0, 
   0, 0, 0, 4, 7, 7, 7, 7, 7, 4, 0, 0, 0, 0, 
   0, 0, 0, 7, 6, 5, 7, 5, 6, 7, 0, 0, 0, 0, 
   0, 0, 2, 7, 3, 0, 5, 0, 3, 7, 2, 0, 0, 0, 
   0, 0, 2, 7, 6, 2, 6, 3, 3, 7, 2, 0, 0, 0, 
   0, 0, 0, 7, 7, 4, 7, 5, 7, 7, 0, 0, 0, 0, 
   0, 0, 0, 2, 7, 7, 7, 7, 7, 4, 0, 0, 0, 0, 
   0, 0, 0, 0, 1, 4, 6, 7, 5, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0};

const byte mail[126] PROGMEM = {
   3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 
   0, 0, 5, 7, 7, 7, 7, 7, 7, 7, 7, 5, 0, 0, 
   0, 0, 0, 2, 7, 7, 7, 7, 7, 7, 2, 0, 0, 0, 
   0, 0, 0, 0, 0, 4, 7, 7, 4, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 2, 6, 6, 1, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 4, 4, 0, 0, 5, 4, 0, 0, 0, 0, 
   0, 0, 1, 5, 2, 0, 0, 0, 0, 2, 5, 1, 0, 0, 
   0, 3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 4, 0, 
   5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 5};

const byte skype[126] PROGMEM = {
   0, 0, 0, 5, 7, 7, 5, 5, 4, 1, 0, 0, 0, 0, 
   0, 0, 6, 7, 7, 7, 6, 6, 7, 7, 3, 0, 0, 0, 
   0, 0, 7, 7, 7, 0, 1, 1, 0, 6, 7, 1, 0, 0, 
   0, 0, 6, 7, 5, 0, 6, 7, 5, 7, 7, 5, 0, 0, 
   0, 0, 6, 7, 7, 3, 0, 0, 1, 6, 7, 6, 0, 0, 
   0, 0, 5, 7, 6, 4, 7, 7, 1, 3, 7, 6, 0, 0, 
   0, 0, 1, 7, 6, 0, 2, 2, 0, 5, 7, 7, 0, 0, 
   0, 0, 0, 3, 7, 7, 6, 6, 7, 7, 7, 6, 0, 0, 
   0, 0, 0, 0, 1, 4, 5, 5, 7, 7, 5, 0, 0, 0};   
   
const byte gplus[126] PROGMEM = {
   0, 0, 6, 6, 7, 7, 5, 0, 0, 0, 0, 0, 0, 0, 
   0, 3, 7, 0, 0, 7, 4, 0, 0, 0, 0, 0, 0, 0, 
   0, 5, 7, 0, 0, 7, 4, 0, 0, 0, 7, 0, 0, 0, 
   0, 0, 7, 7, 3, 7, 0, 0, 0, 0, 7, 0, 0, 0, 
   0, 0, 0, 1, 7, 2, 0, 0, 7, 7, 7, 7, 7, 0, 
   0, 0, 4, 5, 7, 7, 3, 0, 0, 0, 7, 0, 0, 0, 
   0, 7, 4, 0, 0, 5, 7, 0, 0, 0, 7, 0, 0, 0, 
   0, 7, 2, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 
   0, 5, 7, 7, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0};
  
const byte ingress[126] PROGMEM = {
   0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 6, 4, 1, 2, 4, 6, 0, 0, 0, 0, 
   0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 
   0, 0, 0, 6, 7, 7, 5, 6, 7, 7, 6, 0, 0, 0, 
   0, 0, 0, 6, 0, 7, 7, 7, 7, 0, 6, 0, 0, 0, 
   0, 0, 0, 6, 3, 3, 6, 6, 3, 3, 7, 0, 0, 0, 
   0, 0, 0, 7, 1, 0, 7, 7, 0, 1, 7, 0, 0, 0, 
   0, 0, 0, 0, 6, 4, 0, 0, 4, 7, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0};

const byte phone[126] PROGMEM = {
   0, 0, 0, 3, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 7, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 7, 7, 3, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 6, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 5, 7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 2, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 5, 7, 2, 1, 4, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 6, 7, 7, 5, 6, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 5, 7, 6, 2, 0, 0, 0, 0};

const byte q[126] PROGMEM = {
   0, 0, 0, 0, 1, 6, 7, 7, 5, 1, 0, 0, 0, 0, 
   0, 0, 0, 1, 7, 6, 3, 3, 6, 7, 1, 0, 0, 0, 
   0, 0, 0, 5, 7, 0, 0, 0, 0, 7, 5, 0, 0, 0, 
   0, 0, 0, 7, 4, 0, 0, 0, 0, 5, 7, 0, 0, 0, 
   0, 0, 0, 7, 4, 0, 0, 0, 0, 4, 7, 0, 0, 0, 
   0, 0, 0, 7, 5, 0, 0, 0, 0, 5, 7, 0, 0, 0, 
   0, 0, 0, 5, 7, 0, 0, 4, 7, 7, 5, 0, 0, 0, 
   0, 0, 0, 1, 7, 6, 3, 3, 7, 7, 2, 0, 0, 0, 
   0, 0, 0, 0, 1, 5, 7, 7, 5, 4, 5, 0, 0, 0};

const byte sat[126] PROGMEM = {
   0, 4, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   3, 7, 7, 7, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   4, 7, 7, 7, 7, 4, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 3, 6, 7, 3, 3, 5, 2, 0, 0, 0, 0, 0, 
   0, 0, 0, 2, 5, 4, 7, 7, 7, 0, 0, 0, 0, 0, 
   0, 0, 0, 4, 3, 4, 6, 7, 4, 2, 5, 2, 0, 0, 
   0, 0, 0, 0, 5, 5, 3, 3, 5, 6, 7, 7, 6, 3, 
   0, 0, 0, 0, 0, 3, 4, 2, 2, 2, 5, 7, 7, 6, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6, 1};

const byte sms[126] PROGMEM = {
   0, 0, 6, 7, 7, 7, 7, 7, 7, 7, 6, 0, 0, 0, 
   0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 
   0, 0, 7, 7, 7, 3, 7, 3, 7, 7, 7, 0, 0, 0, 
   0, 0, 7, 7, 6, 7, 7, 7, 6, 7, 7, 0, 0, 0, 
   0, 0, 7, 7, 4, 0, 0, 0, 2, 7, 7, 0, 0, 0, 
   0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 
   0, 0, 5, 6, 7, 7, 7, 6, 6, 6, 5, 0, 0, 0, 
   0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
   
const byte fb[126] PROGMEM = {
   0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 
   0, 0, 7, 7, 7, 7, 7, 6, 2, 5, 7, 0, 0, 0, 
   0, 0, 7, 7, 7, 7, 7, 0, 0, 5, 7, 0, 0, 0, 
   0, 0, 7, 7, 7, 7, 7, 0, 7, 7, 7, 0, 0, 0, 
   0, 0, 7, 7, 7, 6, 0, 0, 0, 4, 7, 0, 0, 0, 
   0, 0, 7, 7, 7, 7, 2, 0, 2, 7, 7, 0, 0, 0, 
   0, 0, 7, 7, 7, 7, 7, 0, 7, 7, 7, 0, 0, 0, 
   0, 0, 7, 7, 7, 7, 7, 0, 7, 7, 7, 0, 0, 0, 
   0, 0, 7, 7, 7, 7, 7, 0, 7, 7, 7, 0, 0, 0};

const int count = 12;
const byte *images[] = {fb,gplus,hangouts,ingress,mail,phone,q,sat,skype,tw,wa,sms};
int state[count];
int last = -1;

const int DISABLED = 0;
const int FADEIN = 1;
const int ENABLED = 2;
const int FADEOUT = 3;

// time
int seconds = 0;
int minutes = 0;
int hours = 0;
long lasttick = 0;
long remaining = 0;
boolean isclockset = false;

const int CM_OFF = 0;
const int CM_ON = 1;
const int CM_FAINT = 2;
// day night dependent
const int CM_ONOFF = 3;
const int CM_ONFAINT = 4;
const int CM_FAINTOFF = 5;

boolean clockvisible = false;
int clockmode = CM_OFF;

// TEXT
char text[200] = "HELLO WORLD!";
int textcounter = 0;

void setup() {
  scrolltext();
  
  LedSign::Init(GRAYSCALE | DOUBLE_BUFFER);
  for (int i = 0; i < count; i++) state[i] = DISABLED;
  
  /*LedSign::Clear(7);
  LedSign::Flip(true);
  delay(200);
  LedSign::Clear();
  LedSign::Flip(true);
  delay(100); */
  last = -1;
  
  lasttick = millis();
  
  Serial.begin(9600);  
}

int printc(char c, int x, int y) {
   switch (c) {
     case ':': 
       LedSign::Set(x,y + 4,1);
       LedSign::Set(x,y + 7,1);       
       return 2;
     case '-': 
       LedSign::Set(x,y + 4,1);
       LedSign::Set(x + 1,y + 4,1);       
       LedSign::Set(x + 2,y + 4,1);       
       LedSign::Set(x + 3,y + 4,1);       
       return 5;
     case '_': 
       LedSign::Set(x,y + 8,1);
       LedSign::Set(x + 1,y + 8,1);       
       LedSign::Set(x + 2,y + 8,1);       
       LedSign::Set(x + 3,y + 8,1);       
       return 5;
     case '/': 
       LedSign::Set(x + 4,y + 0,1);
       LedSign::Set(x + 4,y + 1,1);
       LedSign::Set(x + 3,y + 2,1);       
       LedSign::Set(x + 3,y + 3,1);       
       LedSign::Set(x + 2,y + 4,1);       
       LedSign::Set(x + 2,y + 5,1);       
       LedSign::Set(x + 1,y + 6,1);       
       LedSign::Set(x + 1,y + 7,1);      
       return 5;
     case '.': 
       LedSign::Set(x,y + 7,1);           
       return 2;
     case ',': 
       LedSign::Set(x,y + 7,1);
       LedSign::Set(x,y + 8,1);
       return 5;
     default: return Font::Draw(c, x, y);
   } 
}

void scrolltext() {
   int startx = 14;
   int cpos = 0;
   LedSign::Init();
   
   while (cpos <= strlen(text)) {
     int x = startx;
     int p = cpos;
     LedSign::Clear();
     while (x < 14 && p <= strlen(text)) {
       
       x += printc(text[p], x, 0);
       p++;
       if (x < 0) {
         startx = x;
         cpos = p;
       }
     }
     startx--;
     delay(40);
     if (x < 0) break;
   }
   LedSign::Init(GRAYSCALE | DOUBLE_BUFFER);
   LedSign::Clear();
   LedSign::Flip(true);
}

void wait(int t) {
  delay(t);
}


boolean checkserial() {
   while (Serial.available() > 0) {
     byte startbyte = Serial.read();
     delay(30);
     
     if (startbyte == 'a') { // demo 'a'
        for (int i = 0; i < count; i++)
          if (state[i] != ENABLED)
            state[i] = FADEIN;
     }
     if (startbyte == 'b') { // disable all 'a'
        for (int i = 0; i < count; i++) {
          if (state[i] == FADEIN)
            state[i] = DISABLED;
          if (state[i] == ENABLED)
            state[i] = FADEOUT;
        }
     }
     if (startbyte == 's') { // startbyte: 's'
       if (!Serial.available()) return false;
       byte address = Serial.read() - 97;
       if (!Serial.available()) return false;
       byte newstate = Serial.read();
              
       if (address >= 0 && address < count) {
          if (newstate == 48) // '0'
            state[address] = (state[address] == ENABLED ? FADEOUT : DISABLED);            
          if (newstate == 49) // '1'
            state[address] = (state[address] == ENABLED ? ENABLED : FADEIN);
          return true;
          }
       }
     
     if (startbyte == 'h') {
       if (!Serial.available()) return false;
       hours = Serial.read() - 97;
       isclockset = true;
     }
     
     if (startbyte == 'm') {
       if (!Serial.available()) return false;
       minutes = Serial.read() - 97;
       isclockset = true;
     }
     
     if (startbyte == 'i') {
       if (!Serial.available()) return false;
       seconds = Serial.read() - 97;
       isclockset = true;
     }
     
     if (startbyte == 'c') {
       if (!Serial.available()) return false;
       clockmode = Serial.read() - 97;
     }
     
     if (startbyte == 't') {
       int p = 0;
       byte c;
       delay(100);
       while (p < 199 && Serial.available() && (c = Serial.read()) != '\n')
         text[p++] = toupper(c);
       text[p] = 0;
       textcounter = 1;
     }
     
     if (startbyte == 'u') {
       if (!Serial.available()) return false;
       textcounter = Serial.read() - 97;
     }
     
   }
   return false;
}

void tickclock() {
   remaining += millis() - lasttick;
   lasttick = millis();
   seconds += remaining / 1000;
   remaining %= 1000;
   while (seconds >= 60) {
     minutes++;
     seconds -= 60;
   }
   while (minutes >= 60) {
     hours++;
     minutes -= 60;
   }
   hours %= 24;
}

void showclock(float brightness) {
   LedSign::Clear();
   
   for (int i = 0; i < 5; i++) {
      LedSign::Set(12-i*2,0,(hours & 1 << i) != 0 ? ceil(brightness * 7.0) : round(brightness * 0.0));
      LedSign::Set(12-i*2,1,(hours & 1 << i) != 0 ? ceil(brightness * 7.0) : round(brightness * 1.0));
   }
   
   for (int i = 0; i < 6; i++) {
      LedSign::Set(12-i*2,3,(minutes & 1 << i) != 0 ? ceil(brightness * 7.0) : round(brightness * 0.0));
      LedSign::Set(12-i*2,4,(minutes & 1 << i) != 0 ? ceil(brightness * 7.0) : round(brightness * 1.0));
      
      LedSign::Set(12-i*2,6,(seconds & 1 << i) != 0 ? ceil(brightness * 7.0) : round(brightness * 0.0));
      LedSign::Set(12-i*2,7,(seconds & 1 << i) != 0 ? ceil(brightness * 7.0) : round(brightness * 1.0));
   }
   
   LedSign::Flip(true);
}

void animateclock(boolean visibility, int duration) {
   int frame = 20;
   for (int i = 0; i <= duration / frame; i++) {
     float progress = 1.0 * i * frame / duration;
     showclock(visibility ? progress : 1.0 - progress);
     delay(frame);
  }
   clockvisible = visibility;
}

void loop() {
   tickclock();
   checkserial();
  
   boolean anynotification = false;
   for (int i = 0; i < count; i++)
     if (state[i] != DISABLED)
       anynotification = true;
   
   boolean day = hours > 8;
   int cm = clockmode;
   if (clockmode == CM_ONOFF) cm = (day ? CM_ON : CM_OFF);
   if (clockmode == CM_FAINTOFF) cm = (day ? CM_FAINT : CM_OFF);
   if (clockmode == CM_ONFAINT) cm = (day ? CM_ON : CM_FAINT);
   if (textcounter > 0) cm = CM_OFF;
   
   if (clockvisible != (!anynotification && isclockset && cm != CM_OFF))
     animateclock((!anynotification && isclockset && cm != CM_OFF),400);
   
   if (anynotification) {  
     const int swaptime = 200;
     const int viewtime = 1000;
     for (int i = 0; i < count; i++) {
      checkserial();
      switch (state[i]) {
          case FADEIN: {
            if (last != -1) {
              swapout(images[last],swaptime);
              // delay(50);
            }
            animate(images[i],300);
            wait(viewtime);
            state[i]++;
            last = i;
            break;
          }
          case ENABLED: {
            if (last != -1)
              swap(images[last],images[i],swaptime);
            else swapin(images[i],swaptime);
            wait(viewtime);
            last = i;
            break;
          }
          case FADEOUT: {
            if (last != -1)
              swap(images[last],images[i],swaptime); 
            else swapin(images[i],swaptime);
            //wait(viewtime);
            fadeout(images[i],200);
            last = -1;
            state[i]++;
            break;
          }
       }
       if (state[i] > FADEOUT) state[i] = DISABLED;
     }
   }
   else {
     if (isclockset && cm != CM_OFF)
       showclock(cm == CM_ON ? 1.0 : 0.125); 
   }
   
   if (textcounter > 0) {
      if (clockvisible) animateclock(false,400);
      if (last != -1) swapout(images[last],200);
      scrolltext();
      textcounter--;
      last = -1;
   }
}

void demo() {
  for (int i = 0; i < count; i++) {
    swap(images[i],images[(i+1)%count],400);
    delay(400);
  } 
}

void animate(const byte *image, int duration) {
   int frame = 20;
   for (int i = 0; i <= duration / frame; i++) {
     float progress = 1.0 * i * frame / duration;
     // Easing
     progress = 1.0 - pow(1.0 - progress,3.0);
     applyimage(image,progress,0,0,1.0);
     LedSign::Flip(true);
     delay(frame);
  }
}

void fadeout(const byte *image,int duration) {
   int frame = 20;
   for (int i = 0; i <= duration / frame; i++) {
     float progress = 1.0 * i * frame / duration;
     applyimage(image,1.0,0,0,1.0-progress);
     LedSign::Flip(true);    
     delay(frame);
  }
}

void swap(const byte *imgold, const byte *imgnew, int duration) {
   if (imgold == imgnew) return;
   int frame = 20;
   for (int i = 0; i <= duration / frame; i++) {
     float progress = 1.0 * i * frame / duration;
     // Easing
     progress = sin(progress * 3.14159 -0.5*3.14159)*0.5 + 0.5;
     applyimage(imgold,1.0,-round(14.0 * progress),0,1.0);
     applyimage(imgnew,1.0,-round(14.0 * progress)+14,0,1.0);
     LedSign::Flip(true);
     delay(frame);
  }
}

void swapout(const byte *imgold, int duration) {
   int frame = 20;
   for (int i = 0; i <= duration / frame; i++) {
     float progress = 1.0 * i * frame / duration;
     // Easing
     progress = sin(progress * 3.14159 -0.5*3.14159)*0.5 + 0.5;
     LedSign::Clear();
     applyimage(imgold,1.0,-round(14.0 * progress),0,1.0);
     LedSign::Flip(true);
     delay(frame);
  }
}

void swapin(const byte *imgold, int duration) {
   int frame = 20;
   for (int i = 0; i <= duration / frame; i++) {
     float progress = 1.0 * i * frame / duration;
     // Easing
     progress = sin(progress * 3.14159 -0.5*3.14159)*0.5 + 0.5;
     LedSign::Clear();
     applyimage(imgold,1.0,-round(14.0 * progress)+14,0,1.0);
     LedSign::Flip(true);
     delay(frame);
  }
}

void applyimage(const byte* image) {
    applyimage(image,1.0,0,0,1.0);
    /*for (int x = 0; x < 14; x++)
      for (int y = 0; y < 9; y++) {
         LedSign::Set(x,y,image[14 * y + x]);
      }*/
    LedSign::Flip(true);
}

void applyimage(const byte* image, float zoom, int xoffset, int yoffset, float brightness) {
    for (int x = 0; x < 14; x++)
      for (int y = 0; y < 9; y++) {
         int pixelx = x;
         int pixely = y;
         if (zoom != 1.0 || xoffset != 0 || yoffset != 0) {
            pixelx = -xoffset + floor(x / zoom);
            pixely = -yoffset + floor(y / zoom);
         }
         int p = 14 * pixely + pixelx;
         if (pixely < 9 && pixelx < 14 && pixely >= 0 && pixelx >= 0) {
           if (brightness != 1.0)
             LedSign::Set(x,y,ceil(pgm_read_byte_near(image + p) * brightness));
             else LedSign::Set(x,y,pgm_read_byte_near(image + p));
         }
         else if (xoffset == 0 && yoffset == 0) LedSign::Set(x,y,0);
      }
}


