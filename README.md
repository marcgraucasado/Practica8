# PR8-MarcGrau

## PRACTICA 8: Buses de comunicación IV

## Objetivo: 

El objetivo de esta práctica es comprender el funcionamiento de la comunicación serie asíncrona UART (Universal Asynchronous Receiver-Transmitter) en el microcontrolador ESP32. Esta comunicación es fundamental para muchos sistemas embebidos, permitiendo intercambiar datos entre diferentes dispositivos sin necesidad de sincronización de reloj.

## Introducción Teórica:

La nomenclatura UART se refiere a módulos que permiten la comunicación serie asíncrona, es decir, sin una señal de reloj externa. Esta comunicación es full-duplex, lo que significa que permite la transmisión y recepción de datos simultáneamente. Por otro lado, USART (Universal Synchronous Asynchronous Receiver-Transmitter) es similar a UART, pero incluye soporte para comunicaciones síncronas, como las que utilizan los buses I2C y SPI.


### Características principales del UART: 

- Comunicación asíncrona (sin señal de reloj).

- Full-duplex (transmisión y recepción simultánea).

- Configurable en términos de velocidad (baudios), bits de datos, bits de parada y paridad.

- Uso de señales TxD (Transmitter) y RxD (Receiver) para transmisión y recepción de datos respectivamente.
  

### Proceso de Comunicación UART:

1. Inicio de transmisión: Se envía un bit de inicio para alertar al receptor del inicio de una nueva trama de datos.

2. Transmisión de datos: Los bits de datos (usualmente 8) se envían uno a uno.

3. Bit de paridad (opcional): Puede incluirse para la detección de errores.

4. Bits de parada: Uno o dos bits para indicar el final de la trama.

5. Sincronización: El receptor usa su propio reloj interno, sincronizado al bit de inicio, para muestrear los bits entrantes.
   

### Niveles de Comunicación UART:

Existen varios estándares para definir los niveles de voltaje de las señales UART:

- RS232: Utiliza voltajes típicos de ±12V para representar los niveles lógicos.

- TTL: Utiliza 0V para el nivel bajo y 3.3V o 5V para el nivel alto, como en el ESP32.

- RS485 y RS422: Usan diferencias de voltaje para mejorar la resistencia al ruido en largas distancias.

### Control de Flujo:

- Hardware: Utiliza señales como RTS (Request to Send) y CTS (Clear to Send) para coordinar la transmisión de datos.

- Software: Implementa bytes especiales como ACK/NACK para confirmar la recepción correcta de paquetes.

### Descripción del Código (Ejercicio Práctico 1):

El código que se desarrollará en esta práctica consiste en crear un bucle de comunicación en el que los datos enviados a través del puerto serie principal del ESP32 (UART0) sean redirigidos a UART2, y viceversa. Esto permite visualizar en la consola los datos recibidos y enviados sin necesidad de hardware adicional.

```cpp
#include <HardwareSerial.h>

HardwareSerial uart2(2);

void setup() {
    Serial.begin(115200);  // Configura UART0 para depuración
    uart2.begin(9600, SERIAL_8N1, 16, 17);  // Configura UART2 en los pines GPIO16 (RX) y GPIO17 (TX)
    Serial.println("Comunicacion UART2 iniciada");
}

void loop() {
    // Redirige datos de UART0 a UART2
    if (Serial.available()) {
        uart2.write(Serial.read());
    }
    // Redirige datos de UART2 a UART0
    if (uart2.available()) {
        Serial.write(uart2.read());
    }
}
```

### Entradas y Salidas Esperadas:

- Entrada: Texto introducido a través del terminal UART0 (puerto serie principal del ESP32).

- Salida: El texto enviado a UART0 se reenvía a UART2 y viceversa, permitiendo la comunicación bidireccional.

### Conclusión:

Esta práctica permite comprender los conceptos básicos de la comunicación UART, su configuración y uso en el ESP32. El uso de múltiples puertos serie es esencial para proyectos que requieren la integración de módulos GPS, GSM o cualquier otro dispositivo serial. Este conocimiento es fundamental para avanzar en aplicaciones más complejas que involucren múltiples dispositivos.



