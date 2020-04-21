# ESP8266 controlado con Alexa
Con este tutorial podrás encender un LED con Alexa, usando Arduino como IDE, el LED puede ser sustituido por un relay para encender un foco de tu casa o cualquier otra cosa, queda a tu imaginación.

## Comenzando 🚀
A continuación se recomiendan el uso de las siguientes versiones, han sido probadas en Windows, Linux, Mac OS, usar alguna versión diferente podría no funcionar correctamente. Si te funciona con otras versiones comentalas para ayudar a los demás.

### Pre-requisitos 📋
Con las siguientes versiones funciona el archivo.ino
```
Arduino 1.8.7
ESP8266 2.6.0
fauxmoESP *
ESP Async *
* usar las versiones de este Git

Placa Nodemcu, Wemos o arduino con ESP8266
Led 5mm
Resistencia 220-300 ohm
```
### Instalación 🔧

El codigo se encuentra en la carpeta Ejemplo1
Configura tu circuito en tu placa usando el LED y la resistencia. Dependiendo en que pin lo conectes lo configuras en tu archivo .ino. Puedes guiarte con las siguiente imagen.

<p align="center">
<img src="/images/diagrama.png" alt="serial"/>
</p>

```
#define PIN_DEVICE         D0
#define ID_DEVICE          "Led Rojo"
```
***Nota*** Puedes modificar el pin y el nombre a tu gusto, recuerda que ID_DEVICE será el nombre como aparecera en la app de Alexa.

Configura el archivo credentials.h con la configuracion de tu router. Ejemplo:

```
#define WIFI_SSID "TP-Link_F521"
#define WIFI_PASS "56854214"
```
## Ejecutando las pruebas ⚙️

Con esas configuraciones el archivo deberia compilar y subirse correctamente, verifica que usas la velocidad de 115200 y la tarjeta correcta. Al abrir el Serial deberias ver que se conecta a tu red WiFi.

<p align="center">
<img src="/images/serial.png" alt="serial"/>
</p>

Ahora abres la app de Alexa y agregas un nuevo dispositivo. Seleccionas de tipo ***Otro***
<p align="center">
<img src="/images/otro.jpeg" alt="otro" width="300"/>
</p>

Esperas en lo que detecta el dispositivo.

<p align="center">
<img src="/images/espera.jpeg" alt="espera" width="300"/>
</p>

Si fue correcto te aparecerá que fue encontrado, con el nombre que le pusiste anteriormente.

<p align="center">
<img src="/images/detectado.jpeg" alt="detectado" width="300"/>
</p>

Ahora puedes decirle a Alexa:

_Alexa, enciende Led Rojo_

<p align="center">
<img src="/images/on.jpeg" alt="on" width="500"/>
</p>

_Alexa, apaga Led Rojo_
<p align="center">
<img src="/images/off.jpeg" alt="off" width="500"/>
</p>

## Contenido adicional 🛠️
Puedes agregar más pines
```
#define PIN_ROJO         D0
#define ID_ROJO          "Led Rojo"
#define PIN_AZUL         D1
#define ID_AZUL          "Led Azul"
#define PIN_VERDE         D2
#define ID_VERDE          "Led Verde"
```
Recuerda agregarlos los pines de salida en el Setup y agregarlos en la parte de Añadir dispositivos virtuales
```
// Añadir dispositivos virtuales
   fauxmo.addDevice(ID_ROJO);
   fauxmo.addDevice(ID_AZUL);
   fauxmo.addDevice(ID_VERDE);
```

Y agregas un if para cada dispositivo
```
if (strcmp(device_name, ID_ROJO)==0) {
    digitalWrite(PIN_ROJO, state ? HIGH : LOW);
} 

if (strcmp(device_name, ID_AZUL)==0) {
    digitalWrite(PIN_AZUL, state ? HIGH : LOW);
}

 if (strcmp(device_name, ID_VERDE)==0) {
    digitalWrite(PIN_VERDE, state ? HIGH : LOW);
}
```
No hay limite en tu creatividad puedes usar este ejemplo como base para alguna idea genial que se te ocurra.
Saludos

## Autores ✒️

* **Jaime Rodríguez** - *Trabajo Inicial* - [Bad Code](https://github.com/rpjosejaime)

## Expresiones de Gratitud 🎁

* Comenta a otros sobre este proyecto 📢
* Da las gracias públicamente 🤓.
* etc.

---
⌨️ con ❤️ por [Jaime Rodríguez](https://github.com/rpjosejaime) 😊
