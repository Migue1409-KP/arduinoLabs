#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const byte rowsCount = 4;
const byte columsCount = 4;
 
char keys[rowsCount][columsCount] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '*','0','#', 'D' }
};

const byte rowPins[rowsCount] = { 7, 6, 5, 4 };
const byte columnPins[columsCount] = { 11, 10, 9, 8 };
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);

// Define la contraseña
char password[] = "1472";

LiquidCrystal_I2C lcd(0x27,16,2);

//pines sensor de distancia
const int EchoPin = 3;
const int TriggerPin = 2;

//motor
int M1_Izq = 13; //Direccion
int M1_Derecha = 12; //Direccion

//pines sensor de luz
const int fotocelda = A0;

//pine para el led
const int led = A1;

String inputPassword = ""; // Variable para almacenar la contraseña ingresada por el usuario

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

void girar(int direccion)
{
  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direccion == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }
    digitalWrite(M1_Izq, inPin1);
    digitalWrite(M1_Derecha, inPin2);
}

void stop(){
    digitalWrite(M1_Izq, LOW);
    digitalWrite(M1_Derecha, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(M1_Izq, OUTPUT);
  pinMode(M1_Derecha, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  stop();
  lcd.init();
  lcd.backlight();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Ingrese contraseña: ");
  char key = keypad.getKey(); // Obtiene la tecla presionada
  int cm = ping(TriggerPin, EchoPin);
  int luz = analogRead(fotocelda);
  if(cm < 15 && luz < 150){
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW );
  }
  
  if (key) { // Verifica si se ha presionado una tecla
    inputPassword += key; // Agrega la tecla presionada a la contraseña ingresada
    
    lcd.setCursor(inputPassword.length() - 1, 1); // Establece la posición del cursor en la pantalla LED
    lcd.print("*"); // Muestra un asterisco en la posición del cursor
    Serial.println(inputPassword);
    
    if (inputPassword.length() == 4) { // Verifica si se han ingresado 4 dígitos
      if (inputPassword == password) { // Compara la contraseña ingresada con la contraseña almacenada
        lcd.clear(); // Limpia la pantalla LED
        lcd.setCursor(0, 0); // Establece la posición del cursor en la pantalla LED
        lcd.print("Acceso concedido"); // Muestra "Acceso concedido" en la pantalla LED
        Serial.println("Acceso concedido");
        girar(2);
        delay(35000);
        stop();
        delay(5000);
        girar(1);
        delay(35000);
        stop();
      } else {
        lcd.clear(); // Limpia la pantalla LED
        lcd.setCursor(0, 0); // Establece la posición del cursor en la pantalla LED
        lcd.print("Acceso denegado"); // Muestra "Acceso denegado" en la pantalla LED
        Serial.println("Acceso denegado");
        delay(2000); // Espera 2 segundos
      }
      inputPassword = ""; // Restablece la contraseña ingresada
      lcd.clear(); // Limpia la pantalla LED
    }
  }
}