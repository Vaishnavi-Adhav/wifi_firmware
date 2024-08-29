#include "WiFi.h"
#include "HTTPClient.h"

// Replace with your network credentials
const char* ssid = "Sanavi Forever";       // Your Wi-Fi SSID
const char* password = "Vaish@123";   // Your Wi-Fi password

void setup() {
  Serial.begin(115200);
  
  // Set WiFi to station mode and disconnect from any previous connections
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Scanning for Wi-Fi networks...");

  // Start scanning for available Wi-Fi networks
  int n = WiFi.scanNetworks();
  Serial.println("Scan done");
  if (n == 0) {
    Serial.println("No networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    bool found = false;
    
    // Check if "random" is in the list of scanned networks
    for (int i = 0; i < n; ++i) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      delay(10);
      
      if (WiFi.SSID(i) == ssid) {
        found = true;
      }
    }
    
    if (found) {
      Serial.println("Network 'Sanavi Forever' found. Connecting...");
      WiFi.begin(ssid, password);

      // Wait until the ESP32 is connected to the Wi-Fi network
      while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
      }

      Serial.println();
      Serial.println("Connected to Wi-Fi");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());

      // Check if we can connect to an external site (e.g., Google)
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin("http://www.apple.com");
        int httpCode = http.GET();
        if (httpCode > 0) {
          Serial.println("HTTP GET request successful. Internet connection is working. Connected to Apple");
        } else {
          Serial.println("HTTP GET request failed. Check your internet connection.");
        }
        http.end();
      }
    } else {
      Serial.println("Network 'Sanavi Forever' not found. Cannot connect.");
    }
  }
}

void loop() {
  // Nothing to do here
}
