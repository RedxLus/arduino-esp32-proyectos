#include "TFT.h"
#include "SPI.h"

#define cs 10 // pin para conexión CS
#define dc 9 // pin para conexión A0
#define rst 8 // pin para conexión reset

TFT screen = TFT(cs, dc, rst);

void setup() {
  screen.begin();

  // color de la pantalla ( r , g , b )
  screen.background(255, 255, 255);
  screen.stroke(200, 100, 0);

  // dibujar círculos
  screen.fill(255, 255, 255);
  screen.circle(60, 50, 21);  
  screen.circle(60, 50, 20);
  screen.circle(100, 50, 21);
  screen.circle(100, 50, 20);
  delay(500);

  // dibujar rectángulos
  screen.fill(200, 100, 0);
  screen.rect(99, 40, 4, 20);
  screen.rect(91, 48, 20, 4);
  screen.rect(51, 48, 20, 4);
  delay(500);

  // color del texto en pantalla ( r , g , b )
  screen.stroke(0, 0, 0);
  screen.setTextSize(2);
 
  // salida de texto
  screen.text("ARDUINO", 40, 85);
  delay(500);
}

void loop() {
 
}