#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>

#define PIN            D4
#define NUMPIXELS      64

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int snakeSize = 4;
int snakeX[snakeSize] = {0, 0, 0, 0};
int snakeY[snakeSize] = {0, 1, 2, 3};
int foodX, foodY;
int dirX = 1, dirY = 0;

bool gameRunning = true;

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
  gameRunning = true;
  spawnFood();
  server.send(200, "text/plain", "Snake game started.");
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

  if (gameRunning) {
    snakeGameAnimation();
    delay(200);
  }
}

void spawnFood() {
  foodX = random(8);
  foodY = random(8);
}

void snakeGameAnimation() {
  moveSnake();
  if (checkCollision()) {
    gameRunning = false;  // Game over
  }
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    spawnFood();
    growSnake();
  }
  displaySnake();
}

bool checkCollision() {
  // Check if the snake hits itself
  for (int i = 1; i < snakeSize; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      return true;  // Collision with itself
    }
  }

  return false;  // No collision
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

void growSnake() {
  int lastSegmentIndex = snakeSize - 1;

  int newSegmentX = snakeX[lastSegmentIndex] - dirX;
  int newSegmentY = snakeY[lastSegmentIndex] - dirY;

  snakeX[lastSegmentIndex + 1] = newSegmentX;
  snakeY[lastSegmentIndex + 1] = newSegmentY;

  snakeSize++;
}

void displaySnake() {
  strip.clear();

  for (int i = 0; i < snakeSize; i++) {
    strip.setPixelColor(snakeX[i] + snakeY[i] * 8, strip.Color(0, 255, 0));  // Green
  }

  strip.setPixelColor(foodX + foodY * 8, strip.Color(255, 0, 0));  // Red

  strip.show();
}
