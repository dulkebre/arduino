byte xDirection = 1;
byte xSpeed = 1;
byte yDirection = 1;
byte ySpeed = 1;
byte x = 3;
byte y = 5;

byte background[8] =  {0,0,0,15,0,0,16,16};

void playFrame() {
  clearScreen(1);
  // Collision detection
  byte newX = x + xDirection*xSpeed;
  byte newY = y + yDirection*ySpeed;
  if (newX > 8 || newX < 1) {
    xDirection = xDirection * -1;
  } else if ((background[x-1]&(1<<newY))!=0) {
    yDirection = yDirection * -1;  
  }
  if (newY > 7 || newY < 0) {
    yDirection = yDirection * -1;
  } else if ((background[newX-1]&(1<<y))!=0) {
    xDirection = xDirection * -1;  
  }
 
  // Calculate new coordinates
  x = x + xDirection*xSpeed;
  y = y + yDirection*ySpeed;
  // Draw
  maxOne(1,background);
  maxSingle(x,(1<<y) + background[x-1]);
}
