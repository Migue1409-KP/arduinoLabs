// Definición de pines
const int botonPin2 = 2;
const int botonPin = 3;
const int rojoPin = 4;
const int verdePin = 5;

// Constantes para los estados del semáforo
const int ESTADO_ROJO = 0;
const int ESTADO_AMARILLO = 1;
const int ESTADO_VERDE = 2;

// Variables de estado
int estadoAnterior = ESTADO_ROJO;
int estadoActual = ESTADO_ROJO;
bool botonPresionado = false;
int time = 4000;

void bottonAction() {
  botonPresionado = true;
}

void setup() {
  // Configurar pines como salida
  pinMode(rojoPin, OUTPUT);
  pinMode(verdePin, OUTPUT);

  // Configurar pin del botón como entrada, input_pullup invierte el high y low
  pinMode(botonPin, INPUT_PULLUP);
  pinMode(botonPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(botonPin),
                  bottonAction,
                  FALLING);

  attachInterrupt(digitalPinToInterrupt(botonPin2),
                  bottonAction,
                  FALLING);


  // Apagar LEDs al inicio
  digitalWrite(rojoPin, LOW);
  digitalWrite(verdePin, LOW);
}

void loop() {
  time = 4000;
  if(botonPresionado){
    if(estadoAnterior == ESTADO_ROJO){
      delay(time/2);
      estadoActual = ESTADO_AMARILLO;
      estadoAnterior = ESTADO_ROJO;
    } else{
      estadoActual = ESTADO_ROJO;
      estadoAnterior = ESTADO_AMARILLO;
      time = 10000;
    }
    botonPresionado = false;
  }

  // Encender/apagar LEDs según estado actual
  digitalWrite(rojoPin, estadoActual == ESTADO_ROJO || estadoActual == ESTADO_AMARILLO ? HIGH : LOW);
  digitalWrite(verdePin, estadoActual == ESTADO_VERDE || estadoActual == ESTADO_AMARILLO ? HIGH : LOW);

  // Actualizar estado del semáforo
  switch (estadoActual) {
    case ESTADO_ROJO:
      delay(time);
      estadoAnterior = estadoActual;
      estadoActual = ESTADO_AMARILLO;
      break;
    case ESTADO_AMARILLO:
      delay(time/2);
      estadoActual = estadoAnterior == ESTADO_ROJO ? ESTADO_VERDE : ESTADO_ROJO;
      estadoAnterior = ESTADO_AMARILLO;   
      break;
    case ESTADO_VERDE:
      delay(time);
      estadoAnterior = estadoActual;
      estadoActual = ESTADO_AMARILLO;
      break;
  }
}