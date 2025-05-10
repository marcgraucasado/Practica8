#include <TinyGPS++.h>
 
// Definim la instància del GPS i el port sèrie
TinyGPSPlus gps;
HardwareSerial mySerial(1);  // Utilitzem UART1 en l'ESP32 (podem usar també UART0 o UART2)
 
#define RX_PIN 16  // Pin RX per al GPS
#define TX_PIN 17  // Pin TX per al GPS
 
void setup()
{
 // Inicialitzem la comunicació amb el monitor sèrie
 Serial.begin(115200);
 while (!Serial);  // Esperem que el monitor sèrie estigui llest
 
 // Inicialitzem la comunicació sèrie amb el GPS
 mySerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
 
 Serial.println("Esperant coordenades del GPS...");
}
 
void loop()
{
 // Llegim les dades del GPS
 while (mySerial.available() > 0)
 {
   gps.encode(mySerial.read());  // Decodifiquem cada byte rebut del GPS
 
   if (gps.location.isUpdated())  // Si la ubicació s'ha actualitzat
   {
     // Mostrem la latitud i longitud en format decimal
     float latitude = gps.location.lat();
     float longitude = gps.location.lng();
 
     Serial.print("Latitud: ");
     Serial.print(latitude, 6);  // Mostrem la latitud amb 6 decimals
     Serial.print("  Longitud: ");
     Serial.print(longitude, 6);  // Mostrem la longitud amb 6 decimals
     Serial.println();
 
     // Opcional: també podem mostrar més dades, com el nombre de satèl·lits
     Serial.print("Satèl·lits: ");
     Serial.println(gps.satellites.value());
   }
 }
}