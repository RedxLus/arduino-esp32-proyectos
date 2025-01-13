#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_MOSI 35
#define TFT_CLK 36
#define TFT_CS 15
#define TFT_DC 4
#define TFT_RST 5

Adafruit_ST7735 screen = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);

int logoX = 0, logoY = 0;  
int velocityX = 2, velocityY = 2; 

void setup() {
  screen.initR(INITR_BLACKTAB);
  screen.fillScreen(ST77XX_WHITE); 
}

void loop() {

  screen.fillScreen(ST77XX_WHITE);

  logoX += velocityX;
  logoY += velocityY;

  if (logoX <= 0 || logoX + 50 >= screen.width()) velocityX = -velocityX;
  if (logoY <= 0 || logoY + 50 >= screen.height()) velocityY = -velocityY;

  drawESP32Logo(logoX, logoY);

  delay(30);
}

void drawESP32Logo(int x, int y) {
  screen.fillCircle(x + 25, y + 25, 20, ST77XX_BLACK);
  screen.fillCircle(x + 25, y + 25, 18, ST77XX_WHITE);
  screen.fillRect(x + 15, y + 22, 20, 2, ST77XX_BLACK);
  screen.fillRect(x + 15, y + 27, 20, 2, ST77XX_BLACK);
  screen.fillRect(x + 22, y + 5, 6, 10, ST77XX_BLACK);
  screen.setTextColor(ST77XX_BLACK);
  screen.setTextSize(1);
  screen.setCursor(x + 10, y + 40);
  screen.print("ESP32");
}
