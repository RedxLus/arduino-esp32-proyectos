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

// Configuración del YL-69
const int sensorPin = A0;  // Pin analógico donde está conectado el sensor
int valorSensor = 0;       // Variable para la lectura analógica
int porcentajeHumedad = 0; // Variable para el porcentaje calculado
const int valorSeco = 1024;  // Valor en seco (aire)
const int valorHumedo = 600; // Valor en agua (máxima humedad)

// Configuración de la pump
#define pump1 D7      // Pin digital para controlar la bomba de agua


void setup() {
  Serial.begin(9600);

  // Inicia el OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("No se pudo iniciar el OLED"));
    for (;;); // Detén el programa si falla el OLED
  }
  display.clearDisplay();
  display.display();

  // Muestra un mensaje inicial en el OLED
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(F("Inicializando..."));
  display.display();
  delay(2000);
  display.clearDisplay();

  // Configuración del pin de la pump
  delay(1000);
  pinMode(pump1, OUTPUT);
  digitalWrite(pump1, HIGH); // La bomba empieza desactivada
}

void loop() {
  // Leer el valor analógico del sensor
  valorSensor = analogRead(sensorPin);

  // Mapear el rango calibrado al porcentaje de 0% a 100%
  porcentajeHumedad = map(valorSensor, valorSeco, valorHumedo, 0, 100);

  // Limitar el porcentaje entre 0 y 100 para evitar valores fuera de rango
  porcentajeHumedad = constrain(porcentajeHumedad, 0, 100);
 
  // Muestra el valor en el Monitor Serial
  Serial.print("Valor del sensor: ");
  Serial.println(valorSensor);

  // Mostrar el porcentaje de humedad en el Monitor Serial
  Serial.print("Humedad del suelo: ");
  Serial.print(porcentajeHumedad);
  Serial.println("%");

  // Muestra los datos en el OLED
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(F("Auto riego"));

  display.setCursor(0, 40);
  display.print(F("Humedad: "));
  display.print(porcentajeHumedad);
  display.println(F(" %"));

  display.display();

  // Activar la bomba si la humedad es menor al 20%
  if (porcentajeHumedad < 20) {
    Serial.println("Humedad baja. Activando bomba...");
    digitalWrite(pump1, LOW); // Bomba activada
  } else {
    Serial.println("Humedad adecuada. Desactivando bomba...");
    digitalWrite(pump1, HIGH); // Bomba desactivada
  }

  // Esperar 1 segundo antes de la siguiente lectura
  delay(1000);
}
