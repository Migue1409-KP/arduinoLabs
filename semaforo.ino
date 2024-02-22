// Definición de pines
const int rojoPin = 4;
const int verdePin = 5;
const int botonPin = 3;
// Constantes para los estados del semáforo
const int ESTADO_ROJO = 0;
const int ESTADO_AMARILLO = 1;
const int ESTADO_VERDE = 2;
int estadoAnterior = ESTADO_ROJO;

// Variables de estado
int estadoActual = ESTADO_ROJO;
bool botonPresionado = false;

void setup() {
  // Configurar pines como salida
  pinMode(rojoPin, OUTPUT);
  pinMode(verdePin, OUTPUT);
  
  // Configurar pin del botón como entrada, input_pullup invierte el high y low
  pinMode(botonPin, INPUT_PULLUP);

  // Apagar LEDs al inicio
  digitalWrite(rojoPin, LOW);
  digitalWrite(verdePin, LOW);
}

void loop() {
  // Leer estado del botón
  botonPresionado = digitalRead(botonPin) == LOW;

  // Encender/apagar LEDs según estado actual
  digitalWrite(rojoPin, estadoActual == ESTADO_ROJO || estadoActual == ESTADO_AMARILLO ? HIGH : LOW);
  digitalWrite(verdePin, estadoActual == ESTADO_VERDE || estadoActual == ESTADO_AMARILLO ? HIGH : LOW);

  // Actualizar estado del semáforo
  switch (estadoActual) {
    case ESTADO_ROJO:
      delay(4000);
      estadoAnterior = estadoActual;
      estadoActual = ESTADO_AMARILLO;
      break;
    case ESTADO_AMARILLO:
      delay(2000);
      if(estadoAnterior == ESTADO_ROJO){
        estadoAnterior = estadoActual;
        estadoActual = ESTADO_VERDE;
      } else {
        estadoAnterior = estadoActual;
        estadoActual = ESTADO_ROJO;
      }
      break;
    case ESTADO_VERDE:
      delay(4000);
      estadoAnterior = estadoActual;
      estadoActual = ESTADO_AMARILLO;
      break;
  }
}