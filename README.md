**DESCRIPCIÓN**

En este repo tenemos el código para la ESP32 en visual studio usando platformio, el cual corresponde a la carpeta llamada "Iot".
Abajo de este encontramos la carpeta correspondiente al código que va en la Raspberry Pi 4 donde se encuentra tanto el cliente coap con el que se comunica con la ESP32 mediante la dirección IP (En este se debe agragar la dirección IP que aparece al correr el monitor serial en el código de la carpeta anteriormente mencionada), también se encuentra el main donde se encuentra la interfaz que se implementa con kivy.

**INSTRUCCIONES**

**Respecto a las carpetas y archivos que se deben ejecutar**

Primero se debe clonar o descargar las carpetas del repositorio, por un lado en una máquina se tendrá el código de la ESP32 ya sea en Visual Studio o en arduinoIDE, en otra máquina se tendrá la raspberry corriendo y allí subiremos el código correspondiente a la Raspberry Pi.

Es **necesario** tener en cuenta que en el código de la ESP32 se debe coincidir donde se define el PIN de entrada el pin donde se está conectando a la Raspberry Pi, para nuestro caso fue el 21.

**Para correr el programa se deben seguir los siguientes pasos:**

**[1]** En la Raspberry Pi abrir una terminal y entrar a la carpeta del proyecto, en este caso "Oficina_Inteligente_RaspberryPi"

**[2]** Ejecutar el comando python3 main.py

Al seguir los pasos se abrirá la interfaz de kivy donde se pueden encender las diferentes luces que están conectadas, en este caso, enciende diferentes colores del led, ya sea rojo, azul o verde, además puede variar su intensidad haciendo que iluminen más o menos.

Añadido a esto se tiene la funcionalidad que provee el sensor de proximidad, el cual hace que cuando detecta un objeto a una distancia de entre 0cm y 30cm se enciende la luz roja, entre 30cm y 60cm se enciende la luz azul, entre 60cm y 100cm y más de 100cm o 1m se mantiene apagada, simulando la ausencia de personas en una habitación.
