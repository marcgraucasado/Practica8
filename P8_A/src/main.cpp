#include <Arduino.h>
#define RXD1 16
#define TXD1 17
 
void setup() {
  Serial.begin(9600);               // Iniciem la comunicació per USB
  while (!Serial);                    // Esperem que el monitor sèrie estigui llest
 
  Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1); // Configurem la UART1 amb els pins corresponents
  Serial.println("Bucle UART amb ESP32-S3 iniciat"); // Mostrem un missatge de confirmació
}
 
void loop() {
  static String inputString = ""; // Utilitzem una cadena per desar els caràcters que escrivim
 
  // Llegim els caràcters que introduïm pel monitor sèrie
  if (Serial.available()) {
    char incomingByte = Serial.read(); // Llegim un byte
    if (incomingByte == '\n' || incomingByte == '\r') { 
      // Quan rebem un salt de línia, processem l’entrada
      if (inputString.length() > 0) {
        // Enviem el que hem escrit a través de la UART1
        Serial1.write(inputString.c_str()); 
        Serial.println("Enviat a UART1: " + inputString); // Mostrem el que hem enviat
        inputString = ""; // Esborrem la cadena per començar de nou
      }
    } else {
      // Si no és un salt de línia, afegim el caràcter a la cadena
      inputString += incomingByte;
    }
  }
 
  // Llegim les dades que arriben per UART1 i les mostrem pel monitor sèrie
  if (Serial1.available()) {
    char receivedByte = Serial1.read(); // Llegim un byte des de UART1
    Serial.write(receivedByte);         // El mostrem pel monitor sèrie
  }
}