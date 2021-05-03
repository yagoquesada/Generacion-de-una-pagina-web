/*
 ESP32 Web Server - STA Mode
 modified on 25 MAy 2019
 by Mohammadreza Akbari @ Electropeak
 https://electropeak.com/learn
*/

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
<h1>PRACTICA B INTERRUPCION POR TIMER</h1>\
<h2>CODIGO</h2>\
<p>#include <Arduino.h></p>\
<p></p>\
<p>volatile int interruptCounter;</p>\
<p>int totalInterruptCounter;</p>\
<p></p>\
<p>hw_timer_t * timer = NULL;</p>\
<p>portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;</p>\
<p></p>\
<p>void IRAM_ATTR onTimer() {</p>\
<p>     portENTER_CRITICAL_ISR(&timerMux);</p>\
<p>     interruptCounter++;</p>\
<p>     portEXIT_CRITICAL_ISR(&timerMux);</p>\
<p></p>\
<p>}</p>\
<p></p>\
<p>void setup() {</p>\
<p></p>\
<p>     Serial.begin(9600);</p>\
<p></p>\
<p>     timer = timerBegin(0, 80, true);</p>\
<p>     timerAttachInterrupt(timer, &onTimer, true);</p>\
<p>     timerAlarmWrite(timer, 1000000, true);</p>\
<p>     timerAlarmEnable(timer);</p>\
<p></p>\
<p>}</p>\
<p></p>\
<p>void loop() {</p>\
<p></p>\
<p>     if (interruptCounter > 0) {</p>\
<p></p>\
<p>     portENTER_CRITICAL(&timerMux);</p>\
<p>     interruptCounter--;</p>\
<p>     portEXIT_CRITICAL(&timerMux);</p>\
<p></p>\
<p>     totalInterruptCounter++;</p>\
<p></p>\
<p>     Serial.print(An interrupt as occurred. Total number: );</p>\
<p>     Serial.println(totalInterruptCounter);</p>\
<p></p>\
<p>}</p>\
<p>}</p>\
<h2>FUNCIONAMIENTO</h2>\
<p>Empezamos declarando el contador de interrupciones con **volatile**, lo que evitara que se elimine a causa de optimizaciones del compilador.</p>\
<p>```</p>\
<p>volatile int interruptCounter;</p>\
<p>```</p>\
<p></p>\
<p>Declaramos tambien un contador para ver cuantas interrupciones han ocurrido desde el principio del programa, este no requiere **volatile**, ya que solo vamos a usarlo en el *loop* principal (*main loop*).</p>\
<p>```</p>\
<p>int totalInterruptCounter;</p>\
<p>```</p>\
<p></p>\
<p>Para la configuracion del timer que haremos mas adelante, primero necesitaremos un puntero.</p>\
<p>```</p>\
<p>hw_timer_t * timer = NULL;</p>\
<p>```</p>\
<p></p>\
<p>Y la ultima variable que tenemos que declarar es del tipo `portMUX_TYPE`, esta la usaremos para la sincronización entre el *main loop* y la ISR.</p>\
<p>```</p>\
<p>portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;</p>\
<p>```</p>\
<p></p>\
<p>A continuacion vamos a declarar el siguiente **void**:</p>\
<p>```</p>\
<p>void setup() {</p>\
<p></p>\
<p>  Serial.begin(9600);</p>\
<p> </p>\
<p>  timer = timerBegin(0, 80, true);</p>\
<p>  timerAttachInterrupt(timer, &onTimer, true);</p>\
<p>  timerAlarmWrite(timer, 1000000, true);</p>\
<p>  timerAlarmEnable(timer);</p>\
<p> </p>\
<p>}</p>\
<p>```</p>\
<p></p>\
<p>Dentro de este tenemos la inicialización de nuestro timer llamando a la funcion `timerBegin`. Esta funcion recibe como entrada el numero del temporizador que queremos usar (en nuestro caso el 0), el valor del prescaler (en nuestro caso 80) e indicamos si el contador cuenta hacia adelante (*true*) o si lo hace hacia atras (*false*).</p>\
<p>```</p>\
<p>timer = timerBegin(0, 80, true);</p>\
<p>```</p>\
<p></p>\
<p>Ahora usaremos la funcion `timerAttachInterrupt`, esta recibe como entrada un puntero al temporizador, la direccion a la funcion `onTimer` que más tarde especificaremos y sirve para manejar la interrupcion y finalmente el valor *true* para especificar que la interrupcion es de tipo *edge*. </p>\
<p>```</p>\
<p>timerAttachInterrupt(timer, &onTimer, true);</p>\
<p>```</p>\
<p></p>\
<p>A continuacion usaremos la funcion `timerAlarmWrite`, esta tambien recibe como entrada tres valores: Como primera entrada recibe el puntero al temporizador, como segunda el valor del contador en el que se tiene que generar la interrupcion y finalmente un indicador de si el temporizador se ha de recargar automaticamente al generar la interrupcion.</p>\
<p>```</p>\
<p>timerAlarmWrite(timer, 1000000, true);</p>\
<p>```</p>\
<p></p>\
<p>Finalmente llamamos a la funcion `timerAlarmEnable`, en esta pasamos como entrada nuestra variable de temporizador.</p>\
<p>```</p>\
<p>timerAlarmEnable(timer);</p>\
<p>```</p>\
<p></p>\
<p>El *main loop* completo es el siguiente:</p>\
<p>```</p>\
<p>void loop() {</p>\
<p> </p>\
<p>  if (interruptCounter > 0) {</p>\
<p> </p>\
<p>    portENTER_CRITICAL(&timerMux);</p>\
<p>    interruptCounter--;</p>\
<p>    portEXIT_CRITICAL(&timerMux);</p>\
<p> </p>\
<p>    totalInterruptCounter++;</p>\
<p> </p>\
<p>    Serial.print(An interrupt as occurred. Total number: );</p>\
<p>    Serial.println(totalInterruptCounter);</p>\
<p> </p>\
<p>  }</p>\
<p>}</p>\
<p>```</p>\
<p></p>\
<p>Este programa basicamente consiste en incrementar el contador con el numero total de interrupciones (`totalInterruptCounter`) i imprimirlo al puerto serie.</p>\
<p></p>\
<p>Para acabar explicaremos como funciona la funcion ISR (*interrupt service routine*). Esta consistira en incrementar el contador de interrupciones que indicara al bucle principal que se ha producido una interrupcion. Esto se produce dentro de una sección critica, declarada con `portENTER_CRITICAL_ISR` y `portEXIT_CRITICAL_ISR`. El codigo completo del ISR queda:</p>\
<p>```</p>\
<p>void IRAM_ATTR onTimer() {</p>\
<p>  portENTER_CRITICAL_ISR(&timerMux);</p>\
<p>  interruptCounter++;</p>\
<p>  portEXIT_CRITICAL_ISR(&timerMux);</p>\
<p> </p>\
<p>}</p>\
<p>```</p>\
<p></p>\
<h2>IMPRESION SERIE</h2>\
<p></p>\
<p>Este programa va a imprimir por pantalla el numero de veces que hay una interrupcion. Por lo tanto imprimira algo como:</p>\
<p></p>\
<p>```</p>\
<p>An intrrupt as occurred. Total number: 1</p>\
<p>An intrrupt as occurred. Total number: 2</p>\
<p>An intrrupt as occurred. Total number: 3</p>\
<p>An intrrupt as occurred. Total number: 4</p>\
<p>An intrrupt as occurred. Total number: 5</p>\
<p>An intrrupt as occurred. Total number: 6</p>\
<p>An intrrupt as occurred. Total number: 7</p>\
<p>...</p>\
<p>```</p>\
<p></p>\
<p>Y asi indefinidamente hasta que no se pare manualmente.</p>\
</body>\
</html>";

// Handle root url (/)
void handle_root() {
 server.send(200, "text/html", HTML);
}