#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27,16,2);
 
void setup() {
  lcd.begin();  
}
 
void loop() { 
  lcd.setCursor(0,0); 
  lcd.print("luisdieguez.com");
  lcd.setCursor(0,1);  
  lcd.print("1602 LCD");
  delay(100);  
  lcd.clear(); 
}