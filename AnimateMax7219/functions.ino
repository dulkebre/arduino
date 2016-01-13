void putByte(byte data) {
  byte i = 8;
  byte mask;
  while(i > 0) {
    mask = 0x01 << (i - 1);      // get bitmask
    digitalWrite( clock, LOW);   // tick
    if (data & mask){            // choose bit
      digitalWrite(dataIn, HIGH);// send 1
}
    else{
      digitalWrite(dataIn, LOW); // send 0
}
    digitalWrite(clock, HIGH);   // tock
    --i;                         // move to lesser bit
}
}

void maxSingle( byte reg, byte col) {    
  //maxSingle is the "easy"  function to use for a single max7219

  digitalWrite(load, LOW);       // begin     
  putByte(reg);                  // specify register
  putByte(col);//((data & 0x01) * 256) + data >> 1); // put data   
  digitalWrite(load, LOW);       // and load da stuff
  digitalWrite(load,HIGH); 
}

void maxAll (byte reg, byte col) {    // initialize  all  MAX7219's in the system
  int c = 0;
  digitalWrite(load, LOW);  // begin     
  for ( c =1; c<= maxInUse; c++) {
    putByte(reg);  // specify register
    putByte(col);//((data & 0x01) * 256) + data >> 1); // put data
}
  digitalWrite(load, LOW);
  digitalWrite(load,HIGH);
}

void maxOne(byte maxNr, byte reg, byte col) {    
  //maxOne is for addressing different MAX7219's, 
  //while having a couple of them cascaded

  int c = 0;
  digitalWrite(load, LOW);  // begin     

  for ( c = maxInUse; c > maxNr; c--) {
    putByte(0);    // means no operation
    putByte(0);    // means no operation
}

  putByte(reg);  // specify register
  putByte(col);//((data & 0x01) * 256) + data >> 1); // put data 

  for ( c =maxNr-1; c >= 1; c--) {
    putByte(0);    // means no operation
    putByte(0);    // means no operation
}

  digitalWrite(load, LOW); // and load da stuff
  digitalWrite(load,HIGH); 
}

void play3Sceens(byte scene1[][8], byte scene2[][8], byte scene3 [][8]){
  int dly = 750;
  int s1 = 0;
  int s2 = 0;
  int s3 = 0;
  int sceneCount = 0;
  for (;sceneCount < 4; sceneCount++) {
    maxOne(1,scene1[sceneCount]);
    maxOne(2,scene2[sceneCount]);
    maxOne(3,scene3[sceneCount]);
    delay(dly);
  }
}

void scrollScene(int noDisplays, byte scene[][8], int length){
  int dly = 750;
  int s1 = 0;
  int s2 = 0;
  int s3 = 0;
  int sceneCount = 0;
  byte cls[] = {
    0,0,0,0,0,0,0,0};
  for (;sceneCount < length; sceneCount++) {
    if (sceneCount >= 0) {
      maxOne(3,scene[sceneCount - 0]);
  }
    if (sceneCount >= 1) {
      maxOne(2,scene[sceneCount - 1]);
  }
    if (sceneCount >= 2) {
      maxOne(1,scene[sceneCount - 2]);
  }
    delay(dly);
  } 
  maxOne(3,cls);
  maxOne(2,scene[length-1]);
  maxOne(1,scene[length-2]);
  delay(dly);

  maxOne(2,cls);
  maxOne(1,scene[length-1]);
  delay(dly);

  maxOne(1,cls);
  delay(dly); 
}

void scrollSceneEndDelay(int noDisplays, byte scene[][8], int length, int endDelay){
  int dly = 750;
  int s1 = 0;
  int s2 = 0;
  int s3 = 0;
  int sceneCount = 0;
  byte cls[] = {
    0,0,0,0,0,0,0,0};
  for (;sceneCount < length; sceneCount++) {
    if (sceneCount >= 0) {
      maxOne(3,scene[sceneCount - 0]);
    }
  
    if (sceneCount >= 1) {
        maxOne(2,scene[sceneCount - 1]);
    }
    if (sceneCount >= 2) {
        maxOne(1,scene[sceneCount - 2]);
    }
    delay(dly);
  } 
  delay(endDelay);
  maxOne(3,cls);
  maxOne(2,scene[length-1]);
  maxOne(1,scene[length-2]);
  delay(dly);

  maxOne(2,cls);
  maxOne(1,scene[length-1]);
  delay(dly);

  maxOne(1,cls);
  delay(dly); 
}

void maxOne(byte maxNr, byte col[]) {
  int c;
  for (c=0;c<8;c++){
    maxOne(maxNr,c+1,col[c]); 
  }
}

void clearScreen(int maxNr) {
  byte emptyScreen[] = {0,0,0,0,0,0,0,0};
  maxOne(maxNr, emptyScreen);
}
