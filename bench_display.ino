#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define BUTTON_PIN 0

const char* messages[] = {
  "   Gem &     Pollux",
  "1% better every day!",
  "Diamonds are made under pressure",
  "Mind over matter",
  "Keep moving forward",
  "Progress, not perfection",
  "Stay hungry, stay focused",
  "Small steps matter",
  "Discipline equals freedom",
  "Dream big. Start small",
  "Push through the dip",
  "Consistency is key",
  "Act with purpose",
  "Don't stop working",
  "Stay focused",
  "Think long-term",
  "Embrace the grind",
  "Show up daily",
  "Done is better than perfect",
  "Be relentless",
  "Success is earned",
  "Growth through struggle",
  "Be better, do better",
  "You can do it",
  "Results over excuses",
  "Fall. Rise. Repeat.",
  "Effort compounds",
  "Commit and adapt",
  "Your pace, your race",
  "Simplicity wins",
  "Earn it daily"
};


const int numMessages = sizeof(messages) / sizeof(messages[0]);

int lastButtonState = HIGH;
int messageIndex = 0;

void printWrapped(const char* msg, int16_t x, int16_t y, int16_t width) {
  display.setCursor(x, y);
  while (*msg) {
    int16_t x1, y1;
    uint16_t w, h;
    String word = "";
    while (*msg && *msg != ' ') word += *msg++;
    if (*msg == ' ') word += *msg++;
    display.getTextBounds(word.c_str(), display.getCursorX(), display.getCursorY(), &x1, &y1, &w, &h);
    if (display.getCursorX() + w > x + width) {
      display.setCursor(x, display.getCursorY() + 16);
      if (word.startsWith(" ")) word = word.substring(1);
    }
    display.print(word);
  }
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  printWrapped(messages[messageIndex], 0, 0, SCREEN_WIDTH);
  display.display();
}

void loop() {
  int currentButtonState = digitalRead(BUTTON_PIN);
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    messageIndex = (messageIndex + 1) % numMessages;
    display.clearDisplay();
    printWrapped(messages[messageIndex], 0, 0, SCREEN_WIDTH);
    display.display();
    delay(200);
  }
  lastButtonState = currentButtonState;
}
