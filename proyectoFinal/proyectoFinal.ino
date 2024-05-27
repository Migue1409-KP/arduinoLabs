#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const byte ROWS = 4; // Define el número de filas del teclado matricial
const byte COLS = 4; // Define el número de columnas del teclado matricial

char keys[rowsCount][columsCount] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '#','0','*', 'D' }
};

const byte rowPins[rowsCount] = { 7, 5, 4, 6 };
const byte columnPins[columsCount] = { 11, 10, 9, 8 };
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);

// Define la contraseña
char password[] = "1234";

LiquidCrystal_I2C lcd(0x27,16,2);

//pines sensor de distancia
const int EchoPin = 13;
const int TriggerPin = 12;

//pines sensor de luz
const int sensorLuz = 14;

//pine para el led
const int led = 3;

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

void setup() {
  Serial.begin(9600);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(sensorLuz, INPUT);
  pinMode(led, OUTPUT);
  lcd.init();
  lcd.backlight();
}

void loop() {
  int cmCursor = ping(TriggerPin, EchoPin);
  lcd.setCursor(0, 0);
  lcd.print("Ingrese contraseña: ");
  char key = keypad.getKey(); // Obtiene la tecla presionada

  if(cmCusor < 15 && digitalRead(sensorLuz) == HIGH){
    digitalWrite(led, HIGH);
  }
  
  if (key) { // Verifica si se ha presionado una tecla
    inputPassword += key; // Agrega la tecla presionada a la contraseña ingresada
    
    lcd.setCursor(inputPassword.length() - 1, 1); // Establece la posición del cursor en la pantalla LED
    lcd.print("*"); // Muestra un asterisco en la posición del cursor
    
    if (inputPassword.length() == 4) { // Verifica si se han ingresado 4 dígitos
      if (inputPassword == password) { // Compara la contraseña ingresada con la contraseña almacenada
        lcd.clear(); // Limpia la pantalla LED
        lcd.setCursor(0, 0); // Establece la posición del cursor en la pantalla LED
        lcd.print("Acceso concedido"); // Muestra "Acceso concedido" en la pantalla LED
      } else {
        lcd.clear(); // Limpia la pantalla LED
        lcd.setCursor(0, 0); // Establece la posición del cursor en la pantalla LED
        lcd.print("Acceso denegado"); // Muestra "Acceso denegado" en la pantalla LED
      }
      delay(2000); // Espera 2 segundos
      inputPassword = ""; // Restablece la contraseña ingresada
      lcd.clear(); // Limpia la pantalla LED
      lcd.print("Ingrese clave:"); // Muestra un mensaje inicial en la pantalla LED
    }
  }
}
