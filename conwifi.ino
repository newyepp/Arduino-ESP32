#include <WiFi.h>
 
const char* ssid     = "New";
const char* password = "09102887321";
 
WiFiServer server(80);
 
void setup()
{
  Serial.begin(115200);
 
  pinMode(2, OUTPUT);      // set the LED pin mode
  pinMode(27, OUTPUT);      // set the LED pin mode
  pinMode(25, OUTPUT);      // set the LED pin mode
  pinMode(32, OUTPUT);      // set the LED pin mode
 
  delay(10);
 
  // We start by connecting to a WiFi network
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.begin();
 
}
 
int value = 0;
 
void loop() {
  WiFiClient client = server.available();   // listen for incoming clients
 
  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character
 
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
 
            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/2H\">here</a> to turn the LED on pin 2 on.<br>");
            client.print("Click <a href=\"/2L\">here</a> to turn the LED on pin 2 off.<br>");
            client.print("<br>");
 
            client.print("Click <a href=\"/27H\">here</a> to turn the LED on pin 27 on.<br>");
            client.print("Click <a href=\"/27L\">here</a> to turn the LED on pin 27 off.<br>");
            client.print("<br>");
 
            client.print("Click <a href=\"/25H\">here</a> to turn the LED on pin 25 on.<br>");
            client.print("Click <a href=\"/25L\">here</a> to turn the LED on pin 25 off.<br>");
            client.print("<br>");
 
            client.print("Click <a href=\"/32H\">here</a> to turn the LED on pin 32 on.<br>");
            client.print("Click <a href=\"/32L\">here</a> to turn the LED on pin 32 off.<br>");
            client.print("<br>");
 
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
 
        // Check to see if the client request was "GET /xH" or "GET /xL":
        if (currentLine.endsWith("GET /2H")) {
          digitalWrite(2, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /2L")) {
          digitalWrite(2, LOW);                // GET /L turns the LED off
        }
 
        if (currentLine.endsWith("GET /27H")) {
          digitalWrite(27, HIGH);               // GET /H turns the LED on
        }
 
        if (currentLine.endsWith("GET /27L")) {
          digitalWrite(27, LOW);                // GET /L turns the LED off
        }
 
        if (currentLine.endsWith("GET /25H")) {
          digitalWrite(25, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /25L")) {
          digitalWrite(25, LOW);                // GET /L turns the LED off
        }
 
        if (currentLine.endsWith("GET /32H")) {
          digitalWrite(32, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /32L")) {
          digitalWrite(32, LOW);                // GET /L turns the LED off
        }
 
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
