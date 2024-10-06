#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "your_SSID";         // Your WiFi network name
const char* password = "your_PASSWORD"; // Your WiFi password

// Create an instance of the WiFiServer class on port 80
WiFiServer server(80);

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);
,  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  
  // Print ESP32 Local IP Address
  Serial.println("Connected to WiFi");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());
  
  // Start the server
  server.begin();
}

void loop() {
  // Listen for incoming clients
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("New Client Connected");

    // Wait until the client sends some data
    while (!client.available()) {
      delay(1);
    }

    // Read the first line of the client's request
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
    
    // Send the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();  // End of HTTP header
    client.println("<!DOCTYPE html><html>");
    client.println("<head><title>ESP32 Web Server</title></head>");
    client.println("<body><h1>Hello World!</h1></body>");
    client.println("</html>");
    
    // Close the connection
    client.stop();
    Serial.println("Client Disconnected");
  }
}
