#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);
const int EchoPin = 13;
const int TriggerPin = 12;


void setup() {
   Serial.begin(9600);
   pinMode(TriggerPin, OUTPUT);
   pinMode(EchoPin, INPUT);
   lcd.init();
   lcd.backlight();
}
 
//Aquí la muestra de las mediciones
void loop() {
   int cm = ping(TriggerPin, EchoPin);
   lcd.setCursor(0, 0);
   lcd.print("Distancia medida: ");
   lcd.setCursor(0, 1);
   lcd.print(cm);
   lcd.print("cm");
   delay(500);
}
 
//Cálculo para la distancia
int ping(int TriggerPin, int EchoPin) {
   long duration, distanceCm;
    
   digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(TriggerPin, LOW);
    
   duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
    
   distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
   return distanceCm;
}