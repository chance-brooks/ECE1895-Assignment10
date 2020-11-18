//declare pins
const int microphonePin = PC0;
const int buttonPin = PC1;
const int joystickPin1 = PC2;
const int joystickPin2 = PC3;

const int buzzer;
const int LED1;
const int LED2; 
const int LED3;
const int sr_dataPin = PD0;
const int sr_clockPin = PD1;
const int sr_latchPin = PD2;

//declare variables
int newGame;
int score;
int currInstruction;

void setup() {
  Serial.begin(9600);
  pinMode(microphonePin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(joystickPin1, INPUT);
  pinMode(joystickPin2, INPUT);
  
  pinMode(buzzer, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(sr_dataPin, OUTPUT);
  pinMode(sr_clockPin, OUTPUT);
  pinMode(sr_latchPin, OUTPUT);
  digitalWrite(sr_latchPin, HIGH);
  score = 0;
  newGame = 0;
}

void loop() {
  //check for new game request
  if (readInputButton() == 1) {
    newGame = 1;
    score = 0; //set score to 0 on new game
    displayScore();
  }
  
  //start new game
  while (newGame == 1) {
    //get new command
    currInstruction = fetchInstruction();
    playInstruction(currInstruction);
    
    //check for correct input
    if (currInstruction==1 && readInputMicrophone()==1) score++;
    else if (currInstruction==2 && readInputButton()==1) score++;
    else if (currInstruction==3 && readInputJoystick()==1) score++;
    else {
      newGame = 0;
      //play sound or LEDs to indicate loss. Keep score same. Will reset on new game so last score keeps displayed after loss
    }
    
    //display score to user
    displayScore();
  }
  
}

int fetchInstruction() {
  return random(1,4);
}

void playInstruction(int instruction) {
  //play tone and light LED based on instruction
  if (instruction == 1) {
    digitalWrite(LED1, HIGH);
    tone(buzzer, 500);
    delay(1000);
    noTone(buzzer);
    digitalWrite(LED1, LOW);
  }
  else if (instruction == 2) {
    digitalWrite(LED2, HIGH);
    tone(buzzer, 1000);
    delay(1000);
    noTone(buzzer);
    digitalWrite(LED2, LOW);
  }
  else if (instruction == 3) {
    digitalWrite(LED3, HIGH);
    tone(buzzer, 1500);
    delay(1000);
    noTone(buzzer);
    digitalWrite(LED3, LOW);
  }
}

int readInputMicrophone() {
  return digitalRead(microphonePin);
}

int readInputButton() {
  if (analogRead(buttonPin) != 0)
    return 1;
  return 0;
}

int readInputJoystick() {
  if (analogRead(joystickPin1) != 0 || analogRead(joystickPin2) != 0)
    return 1;
  return 0;
}

void displayScore() {
  if((score > 99)||(score < 0))
  {
    Serial.println("Score is out of bounds.");
  }
  byte tensByte = num2seg(score/10);
  byte onesByte = num2seg(score%10);
  digitalWrite(sr_latchPin, LOW);
  shiftOut(sr_dataPin, sr_clockPin, LSBFIRST, onesByte);
  shiftOut(sr_dataPin, sr_clockPin, LSBFIRST, tensByte);
  digitalWrite(sr_latchPin, HIGH);
}

byte num2seg(int n) {
  byte out;
  switch(n) {
    case 0:
      Serial.println((String)"Displaying "+n+"...");
      out = B00000011;
      break;
    case 1:
      Serial.println((String)"Displaying "+n+"...");
      out = B10011111;
      break;
    case 2:
      Serial.println((String)"Displaying "+n+"...");
      out = B00100101;
      break;
    case 3:
      Serial.println((String)"Displaying "+n+"...");
      out = B00001101;
      break;
    case 4:
      Serial.println((String)"Displaying "+n+"...");
      out = B10011001;
      break;
    case 5:
      Serial.println((String)"Displaying "+n+"...");
      out = B01001001;
      break;
    case 6:
      Serial.println((String)"Displaying "+n+"...");
      out = B01000001;
      break;
    case 7:
      Serial.println((String)"Displaying "+n+"...");
      out = B00011111;
      break;
    case 8:
      Serial.println((String)"Displaying "+n+"...");
      out = B00000001;
      break;
    case 9:
      Serial.println((String)"Displaying "+n+"...");
      out = B00001001;
      break;
    default:
      Serial.println("Error: Out of bounds. Displaying Error...");
      out = B10010011;
      break;
  }
  return out;
}
