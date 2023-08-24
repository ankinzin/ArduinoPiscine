#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>

#define PIN            D4
#define NUMPIXELS      64

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

const int snakeSize = 4;
int snakeX[snakeSize] = {0, 0, 0, 0};
int snakeY[snakeSize] = {0, 1, 2, 3};
int foodX, foodY;
int dirX = 1, dirY = 0; 



#ifndef STASSID
#define STASSID "123456"
#define STAPSK "123456lol"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "Hello from ESP8266!");
}

void handleSnakeGame() {
  snakeGameAnimation();
  server.send(200, "text/plain", "Snake game animation started.");
}

void setup(void) {
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, LOW);
  Serial.begin(115200);

  strip.begin();
  strip.show();
  randomSeed(analogRead(0));
  spawnFood();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/snake", HTTP_GET, handleSnakeGame);

  server.begin();
}

void loop(void) {
  server.handleClient();
}

void spawnFood() {
  foodX = random(8);
  foodY = random(8);
}

void snakeGameAnimation() {
  for (int i = 0; i < 10; i++) {
    moveSnake();
    displaySnake();
    delay(200);
  }
}

void moveSnake() {
  int newHeadX = snakeX[0] + dirX;
  int newHeadY = snakeY[0] + dirY;

  for (int i = snakeSize - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  snakeX[0] = newHeadX;
  snakeY[0] = newHeadY;
}

void displaySnake() {
  strip.clear();

  for (int i = 0; i < snakeSize; i++) {
    strip.setPixelColor(snakeX[i] + snakeY[i] * 8, strip.Color(0, 255, 0));  // Green
  }

  strip.setPixelColor(foodX + foodY * 8, strip.Color(255, 0, 0));  // Red

  strip.show();
}
