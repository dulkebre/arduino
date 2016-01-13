/* code for max 7219 from maxim, 
 reduced and optimised for using more than one 7219 in a row,
 ______________________________________
 
 Code History:
 --------------
 
 The original code was written for the Wiring board by:
 * Nicholas Zambetti and Dave Mellis /Interaction Design Institute Ivrea /Dec 2004
 * http://www.potemkin.org/uploads/Wiring/MAX7219.txt
 
 First modification by:
 * Marcus Hannerstig/  K3, malmÃ¶ hÃ¶gskola /2006
 * http://www.xlab.se | http://arduino.berlios.de
 
 This version is by:
 * tomek ness /FH-Potsdam / Feb 2007
 * http://design.fh-potsdam.de/ 
 
 * @acknowledgements: eric f. 
 
 -----------------------------------
 
 General notes: 
 
 -if you are only using one max7219, then use the function maxSingle to control
 the little guy ---maxSingle(register (1-8), collum (0-255))
 
 -if you are using more than one max7219, and they all should work the same, 
 then use the function maxAll ---maxAll(register (1-8), collum (0-255))
 
 -if you are using more than one max7219 and just want to change something
 at one little guy, then use the function maxOne
 ---maxOne(Max you want to control (1== the first one), register (1-8), 
 column (0-255))
 
 During initiation, be sure to send every part to every max7219 and then
 upload it.
 For example, if you have five max7219's, you have to send the scanLimit 5 times
 before you load it-- otherwise not every max7219 will get the data. the
 function maxInUse keeps track of this, just tell it how many max7219 you are
 using.
 */

int dataIn = 2;
int load = 3;
int clock = 4;

int maxInUse = 3;    //change this variable to set how many MAX7219's you'll use

int e = 0;           // just a variable

// define max7219 registers
byte max7219_reg_noop        = 0x00;
byte max7219_reg_digit0      = 0x01;
byte max7219_reg_digit1      = 0x02;
byte max7219_reg_digit2      = 0x03;
byte max7219_reg_digit3      = 0x04;
byte max7219_reg_digit4      = 0x05;
byte max7219_reg_digit5      = 0x06;
byte max7219_reg_digit6      = 0x07;
byte max7219_reg_digit7      = 0x08;
byte max7219_reg_decodeMode  = 0x09;
byte max7219_reg_intensity   = 0x0a;
byte max7219_reg_scanLimit   = 0x0b;
byte max7219_reg_shutdown    = 0x0c;
byte max7219_reg_displayTest = 0x0f;

byte zigZagBells[][8] =  {
  {
    7,15,127,62,28,44,4,0}
  ,
  {
    224,240,254,124,56,52,32,0}
  ,
  {
    7,15,127,62,28,44,4,0}
  ,
  {
    224,240,254,124,56,52,32,0}
};

byte zoomBells[][8] =  {
  {
    24,60,126,126,126,126,255,24}
  ,
  {
    0,8,28,28,28,62,8,0}
  ,
  {
    0,0,24,24,60,16,0,0}
  ,
  {
    0,0,0,16,16,0,0,0}
};

byte bells[][8] = {
  {
    0,16,56,56,56,124,56,0}
  ,
  {
    0,6,16,106,60,12,4,0}
  ,
  {
    0,16,56,56,56,124,56,0}
  ,
  {
    0,6,16,106,60,12,4,0}
};

byte windmill[][8] ={
  {
    1,2,4,8,16,32,64,0}
  ,
  {
    8,8,8,8,8,8,8,0}
  ,
  {
    64,32,16,8,4,2,1,0}
  ,
  {
    0,0,0,127,0,0,0,0}
};

byte hourglass[][8] ={
  {
    255,126,60,24,36,66,129,255}
  ,
  {
    129,126,60,24,36,66,255,255}
  ,
  {
    129,66,60,24,36,126,255,255}
  ,
  {
    129,66,36,24,60,126,255,255}
};

byte vanja[][8] = {
  {
    124,66,66,124,66,66,66,124}
  ,
  {
    24,36,66,66,126,66,66,66}
  ,
  {
    132,132,132,254,133,133,133,134}
  ,
  {
    24,36,66,66,126,66,66,66}
};

byte vera[][8] {
  {
    124,66,66,124,66,66,66,124}
  ,
  {
    126,64,64,126,64,64,64,126}
  ,
  {
    124,66,66,66,124,64,64,64}
  ,
  {
    24,36,66,66,126,66,66,66
}
};

byte relja[][8] = {
  {
    124,66,66,66,124,64,64,64}
  ,
  {
    126,64,64,126,64,64,64,126}
  ,
  {
    48,72,132,134,133,133,133,134}
  ,
  {
    24,36,66,66,126,66,66,66}

};

byte savo[][8] = {
  {
    24,36,64,64,64,64,36,24}
  ,
  {
    24,36,66,66,126,66,66,66}
  ,
  {
    124,66,66,124,66,66,66,124}
  ,
  {
    24,36,66,66,66,66,36,24}
};

byte urosh[][8] {
  {
    66,66,66,62,2,2,66,60}
  ,
  {
    124,66,66,66,124,64,64,64}
  ,
  {
    24,36,66,66,66,66,36,24}
  ,
  {
    65,65,65,65,73,73,73,127}
};

byte milosh[][8] {
  {
    66,102,90,66,66,66,66,66}
  ,
  {
    66,70,74,74,82,82,98,66}
  ,
  {
    24,36,66,66,66,66,66,66}
  ,
  {
    24,36,66,66,66,66,36,24}
  ,
  {
    65,65,65,65,73,73,73,127}
};

byte ognjen[][8] = {
  {
    24,36,66,66,66,66,36,24}
  ,
  {
    126,66,64,64,64,64,64,64}
  ,
  {
    132,132,132,254,133,133,133,134}
  ,
  {
    126,64,64,126,64,64,64,126}
  ,
  {
    66,66,66,126,66,66,66,66}
};

byte tara[][8] {
{127,8,8,8,8,8,8,8},
{24,36,66,66,126,66,66,66},
{124,66,66,66,124,64,64,64},
{24,36,66,66,126,66,66,66}
};

byte tea[][8] {
{127,8,8,8,8,8,8,8},
{126,64,64,126,64,64,64,126},
{24,36,66,66,126,66,66,66}
};

byte srna[][8] {
{24,36,64,64,64,64,36,24},
{124,66,66,66,124,64,64,64},
{66,66,66,126,66,66,66,66},
{24,36,66,66,126,66,66,66}
};

byte andrej[][8] = {
{24,36,66,66,126,66,66,66},
{66,66,66,126,66,66,66,66},
{30,18,34,34,66,255,1e29},
{124,66,66,66,124,64,64,64},
{126,64,64,126,64,64,64,126},
{2,2,2,2,2,66,36,24}
};

byte mila[][8] = {
{66,102,90,66,66,66,66,66},
{66,70,74,74,82,82,98,66},
{24,36,66,66,66,66,66,66},
{24,36,66,66,126,66,66,66}
};

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


void setup () {

  pinMode(dataIn, OUTPUT);
  pinMode(clock,  OUTPUT);
  pinMode(load,   OUTPUT);

  digitalWrite(13, HIGH);  

  //initiation of the max 7219
  maxAll(max7219_reg_scanLimit, 0x07);      
  maxAll(max7219_reg_decodeMode, 0x00);  // using an led matrix (not digits)
  maxAll(max7219_reg_shutdown, 0x01);    // not in shutdown mode
  maxAll(max7219_reg_displayTest, 0x00); // no display test
  for (e=1; e<=8; e++) {    // empty registers, turn all LEDs off 
    maxAll(e,0);
}
  maxAll(max7219_reg_intensity, 0x00 & 0x0f);    // the first 0x0f is the value you can set
  // range: 0x00 to 0x0f
}  

void loop () {
  scrollScene(3,vanja,4);
  scrollScene(3,vera,4);
  play3Sceens(windmill,zoomBells,hourglass);
  scrollScene(3,relja,4);
  scrollScene(3,savo,4);
  play3Sceens(zigZagBells,windmill,zoomBells);
  scrollScene(3,srna,4);
  scrollScene(3,urosh,4);
  scrollScene(3,tara,4);
  play3Sceens(hourglass,zigZagBells,windmill);
  scrollScene(3,ognjen,5);
  scrollScene(3,tea,3);
  play3Sceens(windmill,zoomBells,hourglass);
  scrollScene(3,milosh,5);
  scrollScene(3,andrej,6);
  scrollScene(3,mila,4);
  play3Sceens(hourglass,zigZagBells,windmill);
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

void maxOne(byte maxNr, byte col[]) {
  int c;
  for (c=0;c<8;c++){
    maxOne(maxNr,c+1,col[c]); 
}
}































