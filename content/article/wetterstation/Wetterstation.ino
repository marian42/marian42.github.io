#include <Time.h>        //http://www.arduino.cc/playground/Code/Time
#include <SD.h>
#include <EEPROM.h>

// DCF timing
#define pindcf 3
#define pindcfenable 4

// ILC communication
#define pintrigger 8//3; // F5
#define pindata 6 //2; // E4
#define pinclock 7 // 4; // E3

// SD card
#define pincs 10
boolean sdenabled = true;

// BT
String line;
#define pinbt 2
boolean btenabled = true;
long lastping = 0;
#define addr_btenabled 42
#define eepromcheck 43

char commandbuffer[50];

// weather data
long data[6];
#define datalength 6

// system
int counter = 0;
int vin;
int vcc;
int v33;
#define pinbutton 9
#define pinerror A0

// timing
long next_ilc = 0;
int intervall = 4;
long next_time = 0;

// pin setup
void setupio() {
  pinMode(pintrigger,OUTPUT);
  pinMode(pindata,INPUT);
  pinMode(pinclock,OUTPUT);
  digitalWrite(pinclock,LOW);
  digitalWrite(pintrigger,LOW);
  pinMode(pincs,OUTPUT);
  pinMode(pindcf,INPUT);
  pinMode(pindcfenable,OUTPUT);
  digitalWrite(pindcfenable,HIGH);
  pinMode(pinbt,OUTPUT);
  pinMode(pinbutton,INPUT);
  pinMode(pinerror,OUTPUT);
  digitalWrite(pinerror,LOW);
}

// setup bt
void sendsetup() {
  btenabled = EEPROM.read(addr_btenabled) == 1;
  if (EEPROM.read(eepromcheck) != eepromcheck) btenabled = true;
  digitalWrite(pinbt,!btenabled);
  
  log("Booting...");
  send("time","(notime)");
  send("saving","(initializing...)");
  senddata();
  /*send("registerevent","Aktualisieren");
  send("registerevent","DCF");
  send("registerevent","Disconnect");
  send("requestint","intervall");  
  send("intervall",String(intervall)); */  
}

// Manage bt

void checkserial() {
  int p = 0;
  
  if (Serial.available()) {
    while(Serial.available() && p < 49) {
       commandbuffer[p++] = Serial.read();
       }
    commandbuffer[p++]='\0';
  }
  
  if(p>0) {
     line = line + (char*)commandbuffer;
     String message = "";
     for (int i = 0; i < line.length(); i++)
       if (line.charAt(i) == '\n') {
          //receiveline(message); 
          Serial.print("mirror:" + message);
          message = "";
       }
       else message = message + line.charAt(i);
     line = message;
  }
}

void receiveline(String message) {
  lastping = millis();
  if (message == "ping") return;
  if (message == "requestsetup") { sendsetup(); return; }
  
  if (message == "event:Aktualisieren") {
    refresh();
    return; 
  }  
  if (message == "event:DCF") {
    getdcf();
    return; 
  }
  if (message == "event:Disconnect") {
    log("Offline");
    btenabled = false;
    digitalWrite(pinbt,!btenabled);
    return; 
  }
  
  String name = "";
  String value = "";
  
  int p = 0;
  while (p < message.length() && message.charAt(p) != ':') { name = name + message.charAt(p++); }
  p++;
  while (p < message.length()) { value = value + message.charAt(p++); }
  
  if (name == "mirror") {
    Serial.print(value + "\n");
    return;
  }

  if (name == "intervall") {
    int v = value.toInt();
    if (v == 0) return;
    intervall = v;
    return;
  }
}

// status
void log(String s) {
  if (!btenabled) return;  
  Serial.print("Status:" + s + "\n");
}

// send values
void send(String name, String value) {
  if (!btenabled) return;
  Serial.print(name + ":" + value + "\n");
}

// setup sd
void setupsd() {
  if (!sdenabled) return;
  log("Initializing SD card...");  
  if (!SD.begin(pincs)) {
    log("Card failed, or not present");    
    sdenabled = false;    
    digitalWrite(pinerror,HIGH);
  }
  else log("SD ready."); 
}

// retrieve data
void getdata() {
  int length = 6;
  //long data[length];
  
  // request data
  log("Requesting data...");
  digitalWrite(pintrigger,LOW);
  delay(1);
  digitalWrite(pintrigger,HIGH);
  delay(1);
  
  // wait until ilc is ready
  delay(10);
  while(digitalRead(pindata)) delay(1);
  
  log("Receiving data...");
  // Receive
  for (int i = 0; i < length; i++) {
    long l = 0;
    for (long mask = 0x01; mask; mask <<= 1) {
      digitalWrite(pinclock,HIGH);
      delay(1);
  
      //while (millis() < next) delay(1);
      if (digitalRead(pindata))
        l = (l | mask);
      digitalWrite(pinclock,LOW);
      delay(1);
      //next += intervall;
    }
    data[i] = l;
  }  
  digitalWrite(pintrigger,HIGH);
  
  if (data[0] == 0) digitalWrite(pinerror,HIGH);
}

void sendvalue(String name, long value) {
  Serial.print(name);
  Serial.print(":");
  Serial.print((value / 100));
  Serial.print(".");
  if (abs(value) % 100 < 10) Serial.print("0");
  Serial.print(abs(value) % 100);
  Serial.print("\n");
}

void senddata() {
  log("Sending...");
  sendvalue("Temperatur",data[0]);
  sendvalue("Regen",data[1]);
  sendvalue("Wind",data[2]);
  sendvalue("Licht",data[3]);
  sendvalue("Druck",data[4]);
  sendvalue("Feuchtigkeit",data[5]);
}

// save data to sd
void savedata() {
  if (!sdenabled) return;
  log("Saving to SD...");  
  send("saving","Saving...");
  
  char filename[14];
  sprintf(filename,"%d-%02d-%02d.TXT",year() % 100, month(), day());
  
  File dataFile = SD.open(filename, FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    // time
    dataFile.print(String(now())); dataFile.print(" ");
    
    // data
    for (int i = 0; i < datalength; i++) {
      long v = data[i];
      dataFile.print(v / 100);
      dataFile.print(".");
      if (abs(v % 100) < 10) dataFile.print("0");
      dataFile.print(abs(v % 100));
      dataFile.print(" ");
    }
    
    // voltage
    dataFile.print(vin); dataFile.print(" ");
    dataFile.print(vcc); dataFile.print(" ");
    dataFile.print(v33);
    
    dataFile.println();
    dataFile.close();
    log("Done saving.");
    send("saving","successful");
  }  
  // if the file isn't open, pop up an error:
  else {
    log("Error while saving data.");    
    send("saving","failed");
    digitalWrite(pinerror,HIGH);
  }
}

// Battery
long readVcc() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  return result;
}

void checkbattery() {
   vcc = readVcc();
   int a5 = analogRead(A5);
   vin = vcc / 512.0 * a5;
   
   String bs = "No battery";
   if (vin > 7200) bs = "Full";
   else if (vin > 6000) bs = "OK";
   else if (vin > 5000) bs = "Almost empty";
   else if (vin > 1000) bs = "Empty";
   if (vin < 6000 && vin > 1000) digitalWrite(pinerror, HIGH);
   
   v33 = analogRead(A4) / 1024.0 * vcc;
   
   send("Battery",bs);
   send("Vin",String(vin));
   send("Vcc",String(vcc));   
   send("3.3V",String(v33));
 }

void getdcf() {
  digitalWrite(pindcfenable,LOW);
  log("Receiving DCF time...");
  
  // Check for BT connection
  /*if (btenabled) {
    long n = millis();
    if (lastping < n - 10000) {
      Serial.print("ping\n");
      while (lastping < n - 10000 && millis() < n + 1000);// checkserial();
      if (lastping > n - 10000) digitalWrite(pinbt,LOW);
    }
  } */
  
  // Find start
  send("time","Receiving...");
  
  int up = 0;
  int down = 0;
  
  while (!digitalRead(pindcf));
  long last = millis();
  
  int c = 59;
  while (down < 1300) {
    if (digitalRead(pinbutton)) {
      digitalWrite(pindcfenable,HIGH); 
      return;   
    }
    while(digitalRead(pindcf)) delay(2);
    up = millis() - last;
    last = millis();
    while(millis() - last < 50);
    //Serial.print("time:(");
    //Serial.print(c--);
    //Serial.print(") Searching start...\n");
    //send("time","(" + String(c--) + ") Searching start...");
    
    while(!digitalRead(pindcf)) delay(2);
    down = millis() - last;
    last = millis();
    while(millis() - last < 90);
  }
  
  // Reading data
  boolean data[59];
  int p = 0;
  
  while (p < 60) {    
    if (digitalRead(pinbutton)) {
      digitalWrite(pindcfenable,HIGH); 
      return;   
    }
    while(digitalRead(pindcf));
    up = millis() - last;
    last = millis();
    data[p] = up > 120;
    //send("time",String(p) + " / 60 (" + String(p * 100 / 59) + "%)");
    p++;
    
    // do stuff
    // ...    
    while(millis() - last < 50);
    
    while(!digitalRead(pindcf));
    down = millis() - last;
    last = millis();
    while(millis() - last < 90);
  }
  
  digitalWrite(pindcfenable,HIGH);  
  digitalWrite(pinbt,!btenabled);
  
  // Analyzing data
  setTime((data[34] ? 20 : 0) + (data[33] ? 10 : 0) + (data[32] ? 8 : 0) + (data[31] ? 4 : 0) + (data[30] ? 2 : 0) + (data[29] ? 1 : 0),  // Hour
          (data[27] ? 40 : 0) + (data[26] ? 20 : 0) + (data[25] ? 10 : 0) + (data[24] ? 8 : 0) + (data[23] ? 4 : 0) + (data[22] ? 2 : 0) + (data[21] ? 1 : 0),  // Minute
          0,  // Sec
          (data[41] ? 20 : 0) + (data[40] ? 10 : 0) + (data[39] ? 8 : 0) + (data[38] ? 4 : 0) + (data[37] ? 2 : 0) + (data[36] ? 1 : 0), // Day
          (data[49] ? 10 : 0) + (data[48] ? 8 : 0) + (data[47] ? 4 : 0) + (data[46] ? 2 : 0) + (data[45] ? 1 : 0), // Month
          2000 + (data[57] ? 80 : 0) + (data[56] ? 40 : 0) + (data[55] ? 20 : 0) + (data[54] ? 10 : 0) + (data[53] ? 8 : 0) + (data[52] ? 4 : 0) + (data[51] ? 2 : 0) + (data[50] ? 1 : 0)); // Year
  if (year() != 2013) digitalWrite(pinerror,HIGH);
}

void sendtime() {
  Serial.print("time:");
  if (hour() < 10) Serial.print("0");
  Serial.print(hour());
  Serial.print(":");
  if (minute() < 10) Serial.print("0");
  Serial.print(minute());
  Serial.print(":");
  if (second() < 10) Serial.print("0");
  Serial.print(second());
  Serial.print(" ");
  if (day() < 10) Serial.print("0");
  Serial.print(day());
  Serial.print(".");
  if (month() < 10) Serial.print("0");
  Serial.print(month());
  Serial.print(".");
  Serial.print(year());
  Serial.print("\n");
}

void setup() {
  setupio();
  
  Serial.begin(9600); 
  sendsetup();
  
  setupsd();
  refresh();
  getdcf();
}

void refresh() {
  getdata();
  senddata();
  checkbattery();
  if (sdenabled)
    savedata();
  counter++;
  send("counter",String(counter));
  log("Ready");
}

void loop() {    
  if (millis() > next_ilc) {
    next_ilc = millis() + intervall * 1000;
    
    refresh();    
  }
 
  if (millis() > next_time) {
    next_time = millis() + 1000; 
    sendtime(); 
  }
  
  if (digitalRead(pinbutton)) {
    if (btenabled) {
      log("Offline");
      delay(100);
    }
    btenabled = !btenabled;
    digitalWrite(pinbt,!btenabled);
    EEPROM.write(addr_btenabled,(btenabled ? 1 : 0));
    EEPROM.write(eepromcheck,eepromcheck);
    while (digitalRead(pinbutton));
    delay(100);
  }
  
  //checkserial();
}

