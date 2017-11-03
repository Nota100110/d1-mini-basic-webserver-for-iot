#include <ESP8266WiFi.h>
 
const char* ssid = "********";
const char* password = "********";
 
int ledPin = D4;
int ledPin1 = D6;
int ledPin2 = D0;
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
 
  pinMode(ledPin, OUTPUT); /*configuring pins to behave as input or output*/
  digitalWrite(ledPin, LOW);

  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, LOW);

  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, LOW);
 
  // Connect to WiFi network
  Serial.println(); /*Literally just printing data to serial port*/ 
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password); /*Initializes the WiFi library's network settings and provides the current status.*/
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LED=OFF") != -1){
    digitalWrite(ledPin, LOW);
    value = LOW;
  }

  if (request.indexOf("/LED1=ON") != -1) {
    digitalWrite(ledPin1, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LED1=OFF") != -1){
    digitalWrite(ledPin1, LOW);
    value = LOW;
  }

   if (request.indexOf("/LED2=ON") != -1) {
    digitalWrite(ledPin2, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LED2=OFF") != -1){
    digitalWrite(ledPin2, LOW);
    value = LOW;
  }
 
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led is now: ");
 
  if(value == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }
  
  client.println("<br><br>");
  client.println("Click <a href=\"/LED=ON\">here</a> turn the LED 1 on d4 ON<br>");
  client.println("Click <a href=\"/LED=OFF\">here</a> turn the LED 1 on d4 OFF<br>");

  client.println("Click <a href=\"/LED1=ON\">here</a> turn the LED 2 on d6 ON<br>");
  client.println("Click <a href=\"/LED1=OFF\">here</a> turn the LED 2 on d6 OFF<br>");

  client.println("Click <a href=\"/LED2=ON\">here</a> turn the LED 3 on d0 ON<br>");
  client.println("Click <a href=\"/LED2=OFF\">here</a> turn the LED 3 on d0 OFF<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client is now disconnected");
  Serial.println("");
 
}
