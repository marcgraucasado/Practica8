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

### Funciones Principales del Objeto Serial

A continuación, se describen las funciones principales de la clase Serial, con ejemplos de uso:

- if(Serial): Comprueba si el puerto serie está listo para usar.
```cpp
if (Serial) {
    Serial.println("El puerto serie está listo.");
}
```
- available(): Devuelve el número de bytes disponibles para leer desde el puerto serie.
```cpp
int bytesDisponibles = Serial.available();
Serial.print("Bytes disponibles: ");
Serial.println(bytesDisponibles);
```
- availableForWrite(): Devuelve el número de bytes libres en el buffer de transmisión.
```cpp
int espacioLibre = Serial.availableForWrite();
Serial.print("Espacio libre en buffer: ");
Serial.println(espacioLibre);
```
- begin(): Inicia la comunicación serie especificando la velocidad en baudios.
```cpp
Serial.begin(115200);
```
- end(): Detiene la comunicación serie.
```cpp
Serial.end();
```
- find(): Busca una cadena específica en el flujo de datos de entrada.
```cpp
if (Serial.find("OK")) {
    Serial.println("Cadena 'OK' encontrada.");
}
```  
- findUntil(): Busca una cadena específica hasta que se alcance otra cadena de finalización.
```cpp
if (Serial.findUntil("OK", "ERROR")) {
    Serial.println("Encontrado 'OK' antes de 'ERROR'.");
}
```
- flush(): Espera a que se envíen todos los datos en el buffer de salida.
```cpp
Serial.flush();
Serial.println("Buffer de salida vacío.");
```
- parseFloat(): Lee el siguiente número de punto flotante del flujo de datos de entrada.
```cpp
float numero = Serial.parseFloat();
Serial.print("Número flotante recibido: ");
Serial.println(numero);
```
- parseInt(): Lee el siguiente número entero del flujo de datos de entrada.
```cpp
int numero = Serial.parseInt();
Serial.print("Número entero recibido: ");
Serial.println(numero);
```
- peek(): Devuelve el siguiente byte en el buffer de entrada sin eliminarlo.
```cpp
int siguienteByte = Serial.peek();
Serial.print("Siguiente byte en buffer: ");
Serial.println(siguienteByte);
```
- print(): Envía datos al puerto serie sin un salto de línea final.
```cpp
Serial.print("Hola, ");
Serial.print("mundo!");
```

- println(): Envía datos al puerto serie con un salto de línea final.
```cpp
Serial.println("¡Hola mundo!");
```
- read(): Lee el siguiente byte disponible del puerto serie.
```cpp
int byteRecibido = Serial.read();
Serial.print("Byte recibido: ");
Serial.println(byteRecibido);
```
- readBytes(): Lee bytes del puerto serie en un buffer.
```cpp
char buffer[20];
int bytesLeidos = Serial.readBytes(buffer, sizeof(buffer));
Serial.print("Bytes leídos: ");
Serial.println(bytesLeidos);
```
- readBytesUntil(): Lee bytes del puerto serie en un buffer hasta que se alcance un carácter de terminación.
```cpp
char buffer[20];
int bytesLeidos = Serial.readBytesUntil('\n', buffer, sizeof(buffer));
Serial.print("Bytes leídos hasta nueva línea: ");
Serial.println(bytesLeidos);
```
- readString(): Lee todos los caracteres disponibles y los devuelve como una cadena.
```cpp
String mensaje = Serial.readString();
Serial.print("Mensaje recibido: ");
Serial.println(mensaje);
```
- readStringUntil(): Lee caracteres hasta que se alcance un carácter de terminación y los devuelve como una cadena.
```cpp
String mensaje = Serial.readStringUntil('\n');
Serial.print("Mensaje hasta nueva línea: ");
Serial.println(mensaje);
```
- setTimeout(): Establece el tiempo máximo de espera para operaciones de lectura.
```cpp
Serial.setTimeout(5000);  // 5 segundos
```
- write(): Envía un byte o una serie de bytes al puerto serie.
```cpp
Serial.write("Mensaje enviado");
```
- serialEvent(): Función de interrupción que se llama cuando hay datos disponibles para leer.
```cpp
  void serialEvent() {
    while (Serial.available()) {
        char c = Serial.read();
        Serial.print("Dato recibido en evento: ");
        Serial.println(c);
    }
}
```

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

### Ejercicio Práctico 2: Módulo GPS

Este ejercicio consiste en conectar un módulo GPS al ESP32 para recibir datos de posición, velocidad y hora actual. El módulo GPS se comunicará con el ESP32 a través del puerto UART2.

Código para el Módulo GPS:
```cpp
#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial softSerial(4, 3);  // RX, TX

void setup() {
    Serial.begin(115200);
    softSerial.begin(9600);
    Serial.println("Esperando datos del GPS...");
}

void loop() {
    while (softSerial.available()) {
        char c = softSerial.read();
        if (gps.encode(c)) {
            float lat, lon;
            unsigned long age;
            gps.f_get_position(&lat, &lon, &age);
            Serial.print("Latitud: ");
            Serial.println(lat, 6);
            Serial.print("Longitud: ");
            Serial.println(lon, 6);
            Serial.print("Satélites: ");
            Serial.println(gps.satellites());
            Serial.print("Precisión HDOP: ");
            Serial.println(gps.hdop());
            Serial.println();
        }
    }
}
```

### Salida esperada:

- Latitud y longitud en coordenadas decimales.

- Número de satélites conectados.

- Precisión del posicionamiento.

### Ejercicio Práctico 3: Módulo GPRS/GSM

Este ejercicio consiste en conectar un módulo GPRS/GSM al ESP32 para enviar datos a través de la red móvil. El módulo se conectará usando UART2 y requerirá configuración adicional para manejar comandos AT.

Código para el Módulo GPRS/GSM:
```cpp
#include <TinyGsmClient.h>

#define TINY_GSM_MODEM_SIM800

TinyGsm modem(Serial2);

void setup() {
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, 16, 17);
    Serial.println("Inicializando el módem...");
    if (!modem.restart()) {
        Serial.println("Error al reiniciar el módem.");
        while (true);
    }
    Serial.println("Módem inicializado correctamente.");
    Serial.println(modem.getModemInfo());
}

void loop() {
    // Aquí se pueden enviar comandos AT para conectarse a una red
}
```

### Salida Esperada

- Información del módem.

- Confirmación de reinicio exitoso.

### Conclusión:

Esta práctica permite comprender los conceptos básicos de la comunicación UART, su configuración y uso en el ESP32. El uso de múltiples puertos serie es esencial para proyectos que requieren la integración de módulos GPS, GSM o cualquier otro dispositivo serial. Este conocimiento es fundamental para avanzar en aplicaciones más complejas que involucren múltiples dispositivos.



