// Descargar librería: https://github.com/lafvintech/Super-Starter-Kit-for-ESP32-S3-WROOM/blob/main/C/Libraries/LiquidCrystal_I2C-1.1.2.zip
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define SDA 14                    // Definir pines SDA
#define SCL 13                    // Definir pines SCL
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Wire.begin(SDA, SCL);          
  if (!i2CAddrTest(0x27)) {
      lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }
  lcd.init();                     // Inicialización del controlador de LCD
  lcd.backlight();                
  lcd.setCursor(0,0);             // Mueva el cursor a la fila 0, columna 0
  lcd.print("hello, world!");     // Se muestra un texto en esa posición
}

void loop() {
  lcd.setCursor(0,1);             // Mueva el cursor a la fila 1, columna 0
  lcd.print("Counter:");          // Se muestra un texto en esa posición
  lcd.print(millis() / 1000);
  delay(1000);
  }

  bool i2CAddrTest(uint8_t addr) {
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
      return true;
  }
  return false;
}