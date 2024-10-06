
# ESP32 Web Server

This project sets up a simple web server on an ESP32 microcontroller using the WiFi library. When connected to a Wi-Fi network, the ESP32 listens for incoming client requests and serves a basic HTML page.

## Features
- Connects to a specified Wi-Fi network.
- Serves a simple HTML page displaying "Hello World!".
- Displays the ESP32's local IP address in the Serial Monitor.

## Requirements
- ESP32 Development Board
- Arduino IDE with ESP32 board support installed
- WiFi library (included with the ESP32 board support)

## Code Overview

### Wi-Fi Credentials
Make sure to replace the following variables with your own Wi-Fi network credentials:
```cpp
const char* ssid = "your_SSID";         // Your WiFi network name
const char* password = "your_PASSWORD"; // Your WiFi password
```

### Key Components

1. **WiFi Setup**:
   - Connects to the specified Wi-Fi network.
   - Prints the connection status and local IP address to the Serial Monitor.

2. **Server Initialization**:
   - Creates an instance of the `WiFiServer` class to listen for incoming connections on port 80.

3. **Client Handling**:
   - Waits for a client to connect.
   - Reads the client's HTTP request.
   - Sends back an HTML response with "Hello World!".
   - Closes the client connection after responding.

### Code Explanation

```cpp
#include <WiFi.h> // Include the WiFi library

// Replace with your network credentials
const char* ssid = "your_SSID";         // Your WiFi network name
const char* password = "your_PASSWORD"; // Your WiFi password

WiFiServer server(80); // Create a WiFiServer instance on port 80

void setup() {
  Serial.begin(115200); // Start Serial Monitor
  WiFi.begin(ssid, password); // Connect to Wi-Fi
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

  server.begin(); // Start the server
}

void loop() {
  WiFiClient client = server.available(); // Listen for incoming clients
  
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
    client.println(); // End of HTTP header
    client.println("<!DOCTYPE html><html>");
    client.println("<head><title>ESP32 Web Server</title></head>");
    client.println("<body><h1>Hello World!</h1></body>");
    client.println("</html>");
    
    client.stop(); // Close the connection
    Serial.println("Client Disconnected");
  }
}
```

### How to Use

1. Open the Arduino IDE and create a new sketch.
2. Copy and paste the code into the sketch.
3. Replace `your_SSID` and `your_PASSWORD` with your actual Wi-Fi credentials.
4. Upload the code to your ESP32.
5. Open the Serial Monitor (set to 115200 baud rate) to view the connection status and the ESP32's IP address.
6. Connect to the ESP32's IP address using a web browser to see the "Hello World!" message.

### Troubleshooting
- Ensure your Wi-Fi credentials are correct.
- Verify that the ESP32 is powered and connected properly.
- Check that the Serial Monitor is set to the correct baud rate (115200).
