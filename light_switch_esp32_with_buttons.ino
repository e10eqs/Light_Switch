// Load Wi-Fi library
#include <WiFi.h>
#include <ESP32_Servo.h>


//using doit esp32 devkit v1


// Replace with your network credentials
const char* ssid     = "SJAB";  // SJAB
const char* password = "Bucky1994!"; //Bucky1994!

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output25State = "off";
String output26State = "off";
String output27State = "off";

// Define servopins
int servopin1 = 25;
int servopin2 = 26;
int servopin3 = 27;

//define positions
int minpos = 0;
int npos = 90;
int maxpos = 180;

Servo servo1;
Servo servo2;
Servo servo3;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  servo1.attach(servopin1);
  servo2.attach(servopin2);
  servo3.attach(servopin3);
  // Set servo to initial position
  servo1.write(npos);
  servo2.write(npos);
  servo3.write(npos);
 

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
 WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected

      
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
              // turns the GPIOs on and off
              if (header.indexOf("GET /25/on") >= 0) 
              {
              servo3.attach(servopin3);
              Serial.println("GPIO 25 on");
              output25State = "on";
              servo3.write(maxpos);
              delay(500);
              servo3.write(npos);
              delay(500);
              servo3.detach();
              } 
              else if (header.indexOf("GET /25/off") >= 0)
              {
              servo3.attach(servopin3);
              Serial.println("GPIO 25 off");
              output25State = "off";
              servo3.write(minpos);
              delay(500);
              servo3.write(npos);
              delay(500);
              servo3.detach();
              }
              
              else if (header.indexOf("GET /26/on") >= 0) 
              {
              servo1.attach(servopin1);
              Serial.println("GPIO 26 on");
              output26State = "on";
              servo1.write(maxpos);
              delay(500);
              servo1.write(npos);
              delay(500);
              servo1.detach();
              } 
              else if (header.indexOf("GET /26/off") >= 0) 
              {
              servo1.attach(servopin1);
              Serial.println("GPIO 26 off");
              output26State = "off";
              servo1.write(minpos); 
              delay(500);
              servo1.write(npos);
              delay(500);
              servo1.detach();
              }
              
              else if (header.indexOf("GET /27/on") >= 0)
              {
              servo2.attach(servopin2);
              Serial.println("GPIO 27 on");
              output27State = "on";
              servo2.write(maxpos);
              delay(500);
              servo2.write(npos);
              delay(500);
              servo2.detach();
              } 
              else if (header.indexOf("GET /27/off") >= 0) 
              {
              servo2.attach(servopin2);
              Serial.println("GPIO 27 off");
              output27State = "off";
              servo2.write(minpos);
              delay(500);
              servo2.write(npos);
              delay(500);
              servo2.detach();
              }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #444444;}</style></head>");
           
            // Web Page Heading
            client.println("<body><h1>Anna's Light Switches</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 25  
            client.println("<p> Light Switch 1 " + output25State + "</p>");
            // If the output25State is off, it displays the ON button      
            if(output25State=="off")
            {
            client.println("<p><a href=\"/25/on\"><button class=\"button\">ON</button></a></p>");
            }
            else if(output25State=="on")
            {
            client.println("<p><a href=\"/25/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
               
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p> Light Switch 2 " + output26State + "</p>");
            // If the output26State is off, it displays the ON button       
            if(output26State=="off")
            {
            client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            }
            else if(output26State=="on")
            {
            client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
             // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p> Light Switch 3 " + output27State + "</p>");
            // If the output27State is off, it displays the ON button       
            if(output27State=="off")
            {
            client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            }
            else if(output27State=="on")
            {
            client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } 
          
          else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
