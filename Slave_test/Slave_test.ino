byte x[5];
int i  = 0;
byte buf_read[10];

void setup() {
  Serial.begin(38400); // usb
  Serial1.begin(38400);//
}

void loop() {
  serialEventRead();
  delay(200);
  serialEventWrite();
  clearBuff();
}

void serialEventRead(){
  for (i = 0; i < 5; i++) {
    x[i] = Serial1.read();
  }
}


void serialEventWrite(){
  for(i=0;i<5;i++){
    Serial.write(x[i]);
    }
}

void clearBuff(){
  for(i=0;i<5;i++){
    x[i] = 0x00;
    }
}
