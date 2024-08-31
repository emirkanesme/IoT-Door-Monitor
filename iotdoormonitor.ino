#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>  // For ESP8266. Use <WiFi.h> for ESP32.

const char* ssid = "";      // Your WiFi SSID
const char* password = "";    // Your WiFi Password

const int RS = D2, EN = D3, d4 = D5, d5 = D6, d6 = D7, d7 = D8;
const int pinD0 = 16;  // GPIO 16 (D0)
const int pinD1 = 5;   // GPIO 5 (D1)
LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

IPAddress local_IP(192, 168, 1, 184);    // Choose a unique IP address in your network
IPAddress gateway(192, 168, 1, 1);       // Typically your router's IP address
IPAddress subnet(255, 255, 255, 0);      // Standard subnet mask

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.print("Connecting...");

  WiFi.config(local_IP, gateway, subnet);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi.");
  Serial.println(WiFi.localIP());  // Print the static IP address
  lcd.clear();
  lcd.print("WiFi Connected!");

  server.begin();
  Serial.println("Server started");
  lcd.setCursor(0, 1);
  lcd.print("Server Ready!");

  pinMode(pinD0, OUTPUT);
  pinMode(pinD1, OUTPUT);
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New client connected.");
    String currentLine = "";
    String request = "";
    String text = "";
    String status = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;  // Store the incoming data

        if (c == '\n') {
          if (currentLine.length() == 0) {
            // Extract text and status from URL
            int textStart = request.indexOf("text=") + 5;
            int textEnd = request.indexOf('&', textStart);
            if (textEnd == -1) textEnd = request.indexOf(' ', textStart);
            text = request.substring(textStart, textEnd);
            text.replace("+", " ");

            int statusStart = request.indexOf("status=") + 7;
            int statusEnd = request.indexOf(' ', statusStart);
            status = request.substring(statusStart, statusEnd);

            // Update LCD and GPIO pins
            lcd.clear();
            lcd.print(text);

            if (status == "available") {
              digitalWrite(pinD0, HIGH);
              digitalWrite(pinD1, LOW);
            } else if (status == "not_available") {
              digitalWrite(pinD0, LOW);
              digitalWrite(pinD1, HIGH);
            } else if (status == "none") {
              digitalWrite(pinD0, LOW);
              digitalWrite(pinD1, LOW);
            }

            // Send HTTP response with CSS
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<!DOCTYPE HTML><html>");
            client.print("<head>");
            client.print("<style>");
            client.print("body {");
            client.print("  font-family: Arial, sans-serif;");
            client.print("  text-align: center;");
            client.print("  background-color: #f4f4f4;");
            client.print("  margin: 0;");
            client.print("  padding: 0;");
            client.print("}");
            client.print("h1 {");
            client.print("  color: #333;");
            client.print("}");
            client.print("form {");
            client.print("  display: inline-block;");
            client.print("  background: #fff;");
            client.print("  padding: 20px;");
            client.print("  border-radius: 8px;");
            client.print("  box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);");
            client.print("}");
            client.print("input[type=\"text\"] {");
            client.print("  font-size: 18px;");
            client.print("  padding: 10px;");
            client.print("  width: 300px;");
            client.print("  border: 1px solid #ccc;");
            client.print("  border-radius: 4px;");
            client.print("}");
            client.print("input[type=\"submit\"] {");
            client.print("  font-size: 18px;");
            client.print("  padding: 10px 20px;");
            client.print("  background-color: #007BFF;");
            client.print("  color: white;");
            client.print("  border: none;");
            client.print("  border-radius: 4px;");
            client.print("  cursor: pointer;");
            client.print("}");
            client.print("input[type=\"submit\"]:hover {");
            client.print("  background-color: #0056b3;");
            client.print("}");
            client.print(".status-radio {");
            client.print("  margin: 0 10px;");
            client.print("}");
            client.print("</style>");
            client.print("</head>");
            client.print("<body>");
            client.print("<h1>LCD Controller</h1>");
            client.print("<form action='/' method='get'>");
            client.print("Text: <input type='text' name='text'><br><br>");
            client.print("Status: ");
            client.print("<label class=\"status-radio\">");
            client.print("<input type='radio' name='status' value='available'> Available ");
            client.print("</label>");
            client.print("<label class=\"status-radio\">");
            client.print("<input type='radio' name='status' value='not_available'> Not Available ");
            client.print("</label>");
            client.print("<label class=\"status-radio\">");
            client.print("<input type='radio' name='status' value='none'> None");
            client.print("</label><br><br>");
            client.print("<input type='submit' value='Send to LCD'>");
            client.print("</form>");
            client.print("</body>");
            client.print("</html>");
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c; // Store current line
        }
      }
    }
    client.stop(); // Close connection with client
    Serial.println("Client disconnected.");
  }
}
