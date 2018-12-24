int in = 3;
int out = 4;

void setup() {
  pinMode(in,INPUT);
  pinMode(out,OUTPUT);
}

void loop() {
  digitalWrite(out,digitalRead(in));  
}