# PRÁCTICA 3A : GENERACIÓN DE UNA PAGINA WEB

## APARTADO 1

#### CÓDIGO

```ruby

#include <WiFi.h>
#include <WebServer.h>

// SSID & Password
const char* ssid = "MIWIFI_2G_2jcE";  // Enter your SSID here
const char* password = "9GLX7t3u";  //Enter your Password here

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

void handle_root(void);

void setup() {
 Serial.begin(115200);
 Serial.println("Try Connecting to ");
 Serial.println(ssid);

 // Connect to your wi-fi modem
 WiFi.begin(ssid, password);

 // Check wi-fi is connected to wi-fi network
 while (WiFi.status() != WL_CONNECTED) {
 delay(1000);
 Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected successfully");
 Serial.print("Got IP: ");
 Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

 server.on("/", handle_root);

 server.begin();
 Serial.println("HTTP server started");
 delay(100); 
}

void loop() {
 server.handleClient();
}

// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>My Primera Pagina con ESP32 - Station Mode &#128522;</h1>\
</body>\
</html>";

// Handle root url (/)
void handle_root() {
 server.send(200, "text/html", HTML);
}
```

#### FUNCIONAMIENTO

Al principio hacemos *include* de dos librerías, la primera `#include <WiFi.h&gt;` sirve para permitir que nuestra placa se conecte a internet, y la segunda librería `#include <WebServer.h&gt;` es para hacer un servidor web.

A continuación en una *char* ponemos el SSID de nuestro WiFi y en otra la contraseña de este.

```ruby
const char* ssid = "MIWIFI_2G_2jcE";
const char* password = "9GLX7t3u";
```

Dentro del `void setup()` primero imprimimos por pantalla:
Try Connecting to:
MIWIFI_2G_2jcE

Lo hacemos utilizando el siguiente código:

```ruby
Serial.println("Try Connecting to ");
Serial.println(ssid);
```

Despues conectamos el mòdem WiFi a la placa con:

```ruby
WiFi.begin(ssid, password);
```

Una vez hecho esto debemos comprobar si el WiFi está conectado a la red WiFi, lo hacemos con el código:

```ruby
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.print(".");
}
```

Este bucle lo comprueba y si está conectado imprime un punto por pantalla.

A continuación imprimimos por pantalla que el WiFi se ha conectado correctamente y también imprimimos la IP del ESP32.

```ruby
Serial.println("");
Serial.println("WiFi connected successfully");
Serial.print("Got IP: ");
Serial.println(WiFi.localIP());
```

Y para finalizar el `void setup()` empezamos el servidor HTTP con:

```ruby
server.begin();
Serial.println("HTTP server started");
delay(100);
```

En el Loop, debemos llamar a la función `handleClient()` que se encarga de recibir las peticiones de los clientes y lanzar las funciones de callback asociadas en el ruteo.

```ruby
void loop() {
server.handleClient();
}
```

Ya casi para finalizar el programa creamos una string de nombre HTML que son los contenidos de tipo HTML que se van a mostrar en el servidor web, en nuestro caso se mostrara: My Primera Pagina con ESP32 - Station Mode 😊.

```ruby
String HTML = "<!DOCTYPE html&gt;\
<html&gt;\
<body&gt;\
<h1&gt;My Primera Pagina con ESP32 - Station Mode &#128522;</h1&gt;\
body&gt;\
html&gt;";
```

Y para finalizar, creamos la función `void handle_root()` que se ha llamado anteriormente dentro del `void setup()`. Dentro de esta función utilizamos la función send, la cual tiene tres parámetros: el primero es el código de respuesta (200, 301, 303, 404...), el segundo es el tipo de contenido HTTP (text/plain, text/html, text/json, image/png...) y el último el contenido del cuerpo de la respuesta, que en nuestro caso es el string HTML.

```ruby
void handle_root() {
server.send(200, "text/html", HTML);
}
```

#### SALIDA POR EL TERMINAL

![terminal](https://i.ibb.co/bKHjG1d/terminal.png)

#### VISUALIZACIÓN DE LA CONEXIÓN A LA PAGINA WEB CON UN NAVEGADOR

![pagina_web](https://i.ibb.co/0F5NWJm/pagina-web.png)

## APARTADO 2 

![pagina_web_1](https://i.ibb.co/jyJp0TM/pagina-web-2-1.png)
![pagina_web_2](https://i.ibb.co/zsVMKzW/pagina-web-2-2.png)
![pagina_web_3](https://i.ibb.co/d7nMscq/pagina-web-2-3.png)
![pagina_web_4](https://i.ibb.co/GTGScM5/pagina-web-2-4.png)
![pagina_web_5](https://i.ibb.co/8bq53FS/pagina-web-2-5.png)