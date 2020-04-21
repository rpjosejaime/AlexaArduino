#include <Arduino.h>
#ifdef ESP32
    #include <WiFi.h>
#else
    #include <ESP8266WiFi.h>
#endif
#include "fauxmoESP.h"

// Edítalo de acuerdo a la configuración de tu router.

#include "credentials.h"

fauxmoESP fauxmo;

#define SERIAL_BAUDRATE     115200
#define PIN_DEVICE         D1
#define ID_DEVICE          "Led Rojo"

void wifiSetup() {

    // Set WIFI module to STA mode
    WiFi.mode(WIFI_STA);

    // Connect
    Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // Wait
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();
    
    // Connected!
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());

}

void setup() {

    // Init serial port and clean garbage
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println();
    Serial.println();

    // LEDs
    pinMode(PIN_DEVICE, OUTPUT);
    
    // Wifi
    wifiSetup();

    // De forma predeterminada, fauxmoESP crea su propio servidor web en el puerto definido
    // El puerto TCP debe ser 80 para dispositivos 3 gen. (el valor predeterminado es 1901)
    // Esto debe hacerse antes de la llamada a enable ()
    fauxmo.createServer(true); // not needed, this is the default value
    fauxmo.setPort(80); // This is required for gen3 devices

    // Tienes que llamar a enable (verdadero) una vez que tengas una conexión WiFi
    // Puedes habilitar o deshabilitar la biblioteca en cualquier momento
    // Si lo desactivas, evitarás que los dispositivos se descubran y se cambien.
    fauxmo.enable(true);

  
    // Puedes usar diferentes formas de invocar a alexa para modificar el estado de los dispositivos:
    // "Alexa, enciende el led jaime"
    // "Alexa, led jaime encendido"

    // Añadir dispositivos virtuales
    fauxmo.addDevice(ID_DEVICE);

    fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
        
        // Devolución de llamada cuando se recibe un comando de Alexa.
        // Puede usar device_id o device_name para elegir el elemento para realizar una acción en (relé, LED, ...)
        // State es un valor booleano (ON / OFF) y value un número de 0 a 255 (si dice "configurar la luz de la cocina al 50%", recibirá un 128 aquí).
        // Solo recuerda no demorarte mucho aquí, esto es una devolución de llamada, salir tan pronto como sea posible.
        // Si tiene que hacer algo más involucrado, establezca una marca y procésela en su bucle principal.        
        
        Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
        
        // La comprobación de device_id es más simple si está seguro del orden en que se cargan y no cambia.
        // De lo contrario, comparar el nombre de dispositivo es más seguro.

        if (strcmp(device_name, ID_DEVICE)== 0) {
            digitalWrite(PIN_DEVICE, state ? HIGH : LOW);
        }
   
    });

}

void loop() {
    // fauxmoESP usa un servidor TCP asíncrono pero un servidor UDP de sincronización
    // Por lo tanto, tenemos que sondear manualmente para paquetes UDP
    fauxmo.handle();

    // Este es un código de muestra para generar un montón libre cada 5 segundos
    // Esta es una forma barata de detectar fugas de memoria.
    static unsigned long last = millis();
    if (millis() - last > 5000) {
        last = millis();
        Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
    }
    
    // Si el estado de su dispositivo se cambia por cualquier otro medio (MQTT, botón físico, ...)
    // puede indicar a la biblioteca que informe el nuevo estado a Alexa en la próxima solicitud:
    // fauxmo.setState (ID_YELLOW, true, 255);

}
