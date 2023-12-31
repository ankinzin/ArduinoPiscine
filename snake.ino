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
  String html = "<!DOCTYPE html>"
                "<html>"
                "<head>"
                "<style>"
                "body { font-family: Arial, sans-serif; text-align: center; }"
                ".btn { display: inline-block; padding: 10px 20px; font-size: 18px; margin: 10px; cursor: pointer; border: none; border-radius: 5px; color: white; }"
                ".btn-left { background-color: #3498db; }"
                ".btn-right { background-color: #e74c3c; }"
                ".btn-up { background-color: #2ecc71; }"
                ".btn-down { background-color: #f39c12; }"
                "</style>"
                "</head>"
                "<body>"
                "<h1>ESP8266 Snake Game</h1>"
                "<a class='btn btn-left' href='/snake?dir=left'>Left</a>"
                "<a class='btn btn-right' href='/snake?dir=right'>Right</a><br>"
                "<a class='btn btn-up' href='/snake?dir=up'>Up</a>"
                "<a class='btn btn-down' href='/snake?dir=down'>Down</a>"
                "<p>Use arrow buttons to control the snake</p>"
                "</body>"
                "</html>";

  server.send(200, "text/html", html);
}

void handleSnakeGame() {
  String direction = server.arg("dir");
  if (direction == "left" && dirX != 1) {
    dirX = -1;
    dirY = 0;
  } else if (direction == "right" && dirX != -1) {
    dirX = 1;
    dirY = 0;
  } else if (direction == "up" && dirY != 1) {
    dirX = 0;
    dirY = -1;
  } else if (direction == "down" && dirY != -1) {
    dirX = 0;
    dirY = 1;
  }

  gameRunning = true;
  spawnFood();
  server.send(200, "snake", "Snake game started.");
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
  for (int i = 1; i < snakeSize; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      return true;  
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
  // Implement logic to increase the size of the snake
  // For example, add new segment to the end of the snake
}

void displaySnake() {
  strip.clear();

  for (int i = 0; i < snakeSize; i++) {
    strip.setPixelColor(snakeX[i] + snakeY[i] * 8, strip.Color(0, 255, 0));  // Green
  }

  strip.setPixelColor(foodX + foodY * 8, strip.Color(255, 0, 0));  // Red

  strip.show();
}
