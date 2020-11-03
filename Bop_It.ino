//declare pins
int microphonePin;
int buttonPin;
int joystickPin;
int scoreboardPin;

//declare variables
int newGame;
int score = 0;
int currInstruction;

void setup() {
  pinMode(microphonePin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(joystickPin, INPUT);
  pinMode(scoreboardPin, OUTPUT);
}

void loop() {
  //check for new game request
  if (readInputButton() == 1) newGame = 1;
  
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
      score = 0;
      newGame = 0;
    }
    
    //display score to user
    displayScore();
  }
  
  //display losing score
  displayScore();
}

int fetchInstruction() {
  return random(1,4);
}

void playInstruction(int instruction) {
  //play tone for each instruction
}

int readInputMicrophone() {
  return digitalRead(microphonePin);
}

int readInputButton() {
  return digitalRead(buttonPin);
}

int readInputJoystick() {
  return digitalRead(joystickPin);
}

void displayScore() {
  //displays score on seven seg display
}
