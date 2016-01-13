byte zigZagBells[][8] =  {
  {7,15,127,62,28,44,4,0},
  {224,240,254,124,56,52,32,0},
  {7,15,127,62,28,44,4,0},
  {224,240,254,124,56,52,32,0}
};

byte zoomBells[][8] =  {
  {24,60,126,126,126,126,255,24},
  {0,8,28,28,28,62,8,0},
  {0,0,24,24,60,16,0,0},
  {0,0,0,16,16,0,0,0}
};

byte bells[][8] = {
  {0,16,56,56,56,124,56,0},
  {0,6,16,106,60,12,4,0},
  {0,16,56,56,56,124,56,0},
  {0,6,16,106,60,12,4,0}
};

byte windmill[][8] ={
  {1,2,4,8,16,32,64,0},
  {8,8,8,8,8,8,8,0},
  {64,32,16,8,4,2,1,0},
  {0,0,0,127,0,0,0,0}
};

byte hourglass[][8] ={
  {255,126,60,24,36,66,129,255},
  {129,126,60,24,36,66,255,255},
  {129,66,60,24,36,126,255,255},
  {129,66,36,24,60,126,255,255}
};

byte vanja[][8] = {
  {124,66,66,124,66,66,66,124},
  {24,36,66,66,126,66,66,66},
  {132,132,132,254,133,133,133,134},
  {24,36,66,66,126,66,66,66}
};

byte vera[][8] {
  {124,66,66,124,66,66,66,124},
  {126,64,64,126,64,64,64,126},
  {124,66,66,66,124,64,64,64},
  {24,36,66,66,126,66,66,66}
};

byte relja[][8] = {
  {124,66,66,66,124,64,64,64},
  {126,64,64,126,64,64,64,126},
  {48,72,132,134,133,133,133,134},
  {24,36,66,66,126,66,66,66}

};

byte savo[][8] = {
  {24,36,64,64,64,64,36,24},
  {24,36,66,66,126,66,66,66},
  {124,66,66,124,66,66,66,124},
  {24,36,66,66,66,66,36,24}
};

byte urosh[][8] {
  {66,66,66,62,2,2,66,60},
  {124,66,66,66,124,64,64,64},
  {24,36,66,66,66,66,36,24},
  {65,65,65,65,73,73,73,127}
};

byte milosh[][8] {
  {66,102,90,66,66,66,66,66},
  {66,70,74,74,82,82,98,66},
  {24,36,66,66,66,66,66,66},
  {24,36,66,66,66,66,36,24},
  {65,65,65,65,73,73,73,127}
};

byte ognjen[][8] = {
  {24,36,66,66,66,66,36,24},
  {126,66,64,64,64,64,64,64},
  {132,132,132,254,133,133,133,134},
  {126,64,64,126,64,64,64,126},
  {66,66,66,126,66,66,66,66}
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
  {30,18,34,34,66,255,129},
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

byte TDD[][8] = {
  {127,8,8,8,8,8,8,8},
  {120,68,66,66,66,66,68,120},
  {120,68,66,66,66,66,68,120},
};

byte TDDSigns[][8] = {
  {129,66,36,24,24,36,66,129},
  {0,1,2,2,132,72,40,16},
  {0,1,2,2,132,72,40,16}
};

void chiledrenNames(){
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

void playTDD() {
  scrollSceneEndDelay(3,TDD,3,3500);
  delay(1000);
  maxOne(1,TDDSigns[0]);
  maxOne(2,TDDSigns[1]);
  maxOne(3,TDDSigns[2]);
  delay(2000);
  clearScreen(1);
  delay(750);
  clearScreen(2);
  delay(750);
  clearScreen(3);
  delay(1500);

}
