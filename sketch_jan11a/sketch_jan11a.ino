int dataPin = 12;
int enablePin = 11;
int latchPin = 10;
int clockPin = 9;

int sensorPin[] = {13, 8, 7, 6, 5, 4, 3, 2};
int sensorPinLen = sizeof(sensorPin)/sizeof(sensorPin[0]);

#define number_of_74hc595s 3
#define numOfRegisterPins number_of_74hc595s * 8
#define numRGBLeds 8

boolean registers[numOfRegisterPins];

int redPin[]   = {0, 3, 6, 9, 12, 15, 18, 21};
int greenPin[] = {1, 4, 7, 10, 13, 16, 19, 22};
int bluePin[]  = {2, 5, 8, 11, 14, 17, 20, 23};
int array[8];
String output = "";

void setup() {
  Serial.begin(9600);

  pinMode(dataPin,  OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  for (int i = 0; i<sensorPinLen; i++){
    pinMode(sensorPin[i], INPUT);
  }

  digitalWrite(enablePin, LOW);
  for (int i = numOfRegisterPins - 1; i >=  0; i--) {
    registers[i] = LOW;   
  }
  ledOff(0); 
}

void loop() {
  if(Serial.available()){
    for(int i = 0; i < 8; i++){
      array[i] = Serial.parseInt();
    }
  }
  
  for(int i=0; i<8; i++){
    if(array[i] == 1){
      Red(i);
    } else if(array[i] == 2){
      Green(i);
    } else if(array[i] == 3){
      Blue(i);
    } else if(array[i] == 0) {
      Default(i);
    }
  }
  //effect_1(1);//effect_X(how many time you want to repeat the effect.)
  //ledOff(0);  //ledOff(leds off time )
  for(int i=0; i<sensorPinLen; i++){
    output += String(digitalRead(sensorPin[i]));
  }
  
  Serial.println(output);
  output = "";
  delay(1000);
}
//////////////////////////////////////////////////////EFFECT 1
void effect_1(int repeatEffect) {
  for (int i = 1; i <= repeatEffect; i++) {
    Red(7);
    brigtness();
    ledOff(0);

    
  }
}
//////////////////////Functions/////////////////////
void brigtnessNodelay() {
  for (int i = 255; i >= 0; i--) {
    analogWrite(enablePin, i);
  }
}
void brigtness() {
  for (int i = 255; i >= 0; i--) {
    analogWrite(enablePin, i);
    delay(5);
  }
}

void ledOff(int clearSpeed) {
  for (int i = 0; i <= 35; i++) {
    registersWrite(i, HIGH);
    delay(clearSpeed);
  }
}
void ledOffR(int clearSpeed) {
  for (int i = 35; i >= 0; i--) {
    registersWrite(i, HIGH);
    delay(clearSpeed);
  }
}

void turnOutputsOn() {
  digitalWrite(enablePin, LOW);
}
void turnOutputsOff() {
  digitalWrite(enablePin, HIGH);
}

void registersWrite(int index, int value) {
  digitalWrite(enablePin, LOW);
  digitalWrite(latchPin, LOW);
  for (int i = numOfRegisterPins - 1; i >=  0; i--) {
    digitalWrite(clockPin, LOW);
    int val = registers[i];
    digitalWrite(dataPin, val);
    digitalWrite(clockPin, HIGH);
  }
  digitalWrite(latchPin, HIGH);
  registers[index] = value;
}

void Red(int num) {
    registersWrite(redPin[num], LOW);
    registersWrite(bluePin[num], HIGH);
    registersWrite(greenPin[num], HIGH);
}

void Green(int num) {
    registersWrite(redPin[num], HIGH);
    registersWrite(bluePin[num], HIGH);
    registersWrite(greenPin[num], LOW);
}

void Blue(int num) {
    registersWrite(redPin[num], HIGH);
    registersWrite(bluePin[num], LOW);
    registersWrite(greenPin[num], HIGH);
}

void Default(int num) {
    registersWrite(redPin[num], HIGH);
    registersWrite(bluePin[num], HIGH);
    registersWrite(greenPin[num], HIGH);
}
