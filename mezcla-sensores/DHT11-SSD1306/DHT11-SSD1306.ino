#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Configuración del OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Configuración del DHT
#define DHTPIN 2      // Pin digital conectado al sensor DHT
#define DHTTYPE DHT11 // Tipo de sensor: DHT11 o DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  // Inicia el OLED y detiene el programa si falla
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("No se pudo iniciar el OLED"));
    for (;;); 
  }
  display.clearDisplay();
  display.display();

  // Inicia el sensor DHT
  dht.begin();
  Serial.println(F("DHT iniciado"));

  // Muestra un mensaje inicial en el OLED
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(F("Inicializando..."));
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  // Lee la temperatura y humedad
  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();

  // Verifica si la lectura es válida
  if (isnan(temperatura) || isnan(humedad)) {
    Serial.println(F("Error al leer del sensor DHT"));
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("Error al leer DHT"));
    display.display();
    delay(2000);
    return;
  }

  // Muestra los datos en el Serial
  Serial.print(F("Temperatura: "));
  Serial.print(temperatura);
  Serial.println(F(" °C"));

  Serial.print(F("Humedad: "));
  Serial.print(humedad);
  Serial.println(F(" %"));

  // Muestra los datos en el OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.print(F("Sensor: DHT"));
  display.println(DHTTYPE); 

  display.setCursor(0, 20);
  display.print(F("Temp: "));
  display.print(temperatura);
  display.println(F(" C"));

  display.setCursor(0, 40);
  display.print(F("Humedad: "));
  display.print(humedad);
  display.println(F(" %"));

  display.display();

  delay(2000); // Actualiza cada 2 segundos
}
