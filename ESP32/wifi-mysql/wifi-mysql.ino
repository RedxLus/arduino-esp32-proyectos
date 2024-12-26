#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

#include <Wire.h>
#include <Adafruit_Sensor.h>

// Añada sus credenciales de red
const char* ssid     = "";
const char* password = "";

// Añada su dominio o dirección IP con path.
// http://192.168.1.35/web-esp/api.php
// http://ejemplo.es/api.php
const char* serverName = "";

// Si cambia el valor de apiKeyValue, el archivo PHP /api.php también debe tener la misma clave
const String apiKeyValue = "mNpsDHYQjaDmTzknzPc";

// Sensor YL-69 
const int sensorPin = A0;  
int valorSensor = 0;       
int porcentajeHumedad = 0; 
const String sensorName = "YL-69";

// Sensor YL-69 - calibración
const int valorSeco = 1023;  
const int valorHumedo = 320;

void setup() {
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);
  Serial.println("Conectando");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado a red WiFi con dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Ejecutar solo si el WIFI esta conectado
  if(WiFi.status() == WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    // Leer el valor analógico del sensor YL-69. Calcular el %. Limitar el % de 0 a 100. Mostrar por Serial
    valorSensor = analogRead(sensorPin);
    porcentajeHumedad = map(valorSensor, valorSeco, valorHumedo, 0, 100);
    porcentajeHumedad = constrain(porcentajeHumedad, 0, 100);

    Serial.print("Humedad del suelo: ");
    Serial.print(porcentajeHumedad);
    Serial.println("%");

    // Iniciar conexión. Especificar header. Formar la petición y mostrarla por Serial
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName
                           + "&value1=" + String(porcentajeHumedad);
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    // Enviar la petición HTTP POST
    int httpResponseCode = http.POST(httpRequestData);
        
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Cerrar conexión
    http.end();
  } else {
    Serial.println("WiFi no conectado.");
  }
  // Envia una petición cada segundo
  delay(1000);  
}