#include <WiFi.h>
#include <WiFiUdp.h>
#include <coap-simple.h>

// WiFi credentials
const char* ssid = "WIFI-LIS";
const char* password = "";

// Pins
const int LED_PIN_GREEN = 2;  // Pin GPIO para el color verde del LED
const int LED_PIN_BLUE = 0;   // Pin GPIO para el color azul del LED
const int LED_PIN_RED = 15;    // Pin GPIO para el color rojo del LED
const int TRIG_PIN = 12;
const int ECHO_PIN = 14;

const unsigned int MAX_DIST = 23200;

WiFiUDP udp;
Coap coap(udp);

// Function prototypes
void callback_light(CoapPacket &packet, IPAddress ip, int port);
void handleDistance();
void setLEDIntensity(int pin, int intensity);

void setup() {
  Serial.begin(9600);

  // Set up pins
  pinMode(LED_PIN_GREEN, OUTPUT);
  pinMode(LED_PIN_BLUE, OUTPUT);
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Add CoAP server endpoint
  coap.server(callback_light, "light");

  // Start CoAP server/client
  coap.start();
}

void loop() {
  handleDistance();
  coap.loop();
  delay(600);  // Wait before next measurement
}

// CoAP server endpoint URL callback
void callback_light(CoapPacket &packet, IPAddress ip, int port) {
  Serial.println("[Light] Command received");

  // Get the command from the packet
  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = NULL;

  String message(p);

  // Parse message to control intensity
  int intensity;
  if (message.startsWith("red")) {
    intensity = message.substring(3).toInt();
    setLEDIntensity(LED_PIN_RED, intensity);
  } else if (message.startsWith("blue")) {
    intensity = message.substring(4).toInt();
    setLEDIntensity(LED_PIN_BLUE, intensity);
  } else if (message.startsWith("green")) {
    intensity = message.substring(5).toInt();
    setLEDIntensity(LED_PIN_GREEN, intensity);
  } else if (message.equals("off")) {
    setLEDIntensity(LED_PIN_RED, 0);
    setLEDIntensity(LED_PIN_BLUE, 0);
    setLEDIntensity(LED_PIN_GREEN, 0);
  }

  // Send response
  coap.sendResponse(ip, port, packet.messageid, "OK");
}

void handleDistance() {
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;

  // Trigger the sensor
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the pulse width
  while (digitalRead(ECHO_PIN) == 0);
  t1 = micros();
  while (digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  cm = pulse_width / 58.0;

  // Print the distance
  if (pulse_width > MAX_DIST) {
    Serial.println("Out of range");
  } else {
    Serial.print(cm);
    Serial.println(" cm");
  }

  // Control LEDs based on distance
  if (cm < 30) {
    setLEDIntensity(LED_PIN_RED, 255);
    setLEDIntensity(LED_PIN_BLUE, 0);
    setLEDIntensity(LED_PIN_GREEN, 0);
  } else if (cm >= 30 && cm < 60) {
    setLEDIntensity(LED_PIN_RED, 0);
    setLEDIntensity(LED_PIN_BLUE, 255);
    setLEDIntensity(LED_PIN_GREEN, 0);
  } else if (cm >= 60 && cm < 100) {
    setLEDIntensity(LED_PIN_RED, 0);
    setLEDIntensity(LED_PIN_BLUE, 0);
    setLEDIntensity(LED_PIN_GREEN, 255);
  } else {
    setLEDIntensity(LED_PIN_RED, 0);
    setLEDIntensity(LED_PIN_BLUE, 0);
    setLEDIntensity(LED_PIN_GREEN, 0);
  }
}

void setLEDIntensity(int pin, int intensity) {
  analogWrite(pin, intensity);
}