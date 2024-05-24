#include <Keypad.h>
 
const byte rowsCount = 4;
const byte columsCount = 4;
 
char keys[rowsCount][columsCount] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '#','0','*', 'D' }
};

const byte rowPins[rowsCount] = { 7, 5, 4, 6 };
const byte columnPins[columsCount] = { 11, 10, 9, 8 };
const int motor1 = 12;
const int motor2 = 2;
int motorst1 = HIGH;
int motorst2 = HIGH;
 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);
 
void setup() {
  Serial.begin(9600);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, HIGH);
}
 
void loop() {
  char key = keypad.getKey();
 
  if (key) {
    Serial.println(key);
    switch(key){
      case '1':
        motorst1 = LOW;
        digitalWrite(motor1, motorst1);
      break;
      case '2':
        motorst1 = HIGH;
        digitalWrite(motor1, motorst1);
      break;
      case '4':
        motorst2 = LOW;
        digitalWrite(motor2, motorst2);
      break;
      case '5':
        motorst2 = HIGH;
        digitalWrite(motor2, motorst2);
      break;
    }
  }
}