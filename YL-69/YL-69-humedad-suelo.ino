const int sensorPin = A0;  // Pin analógico donde está conectado el sensor
int valorSensor = 0;       // Variable vacía inicializada como 0
int porcentajeHumedad = 0; // Variable vacía inicializada como 0

// Valores obtenidos durante la calibración
const int valorSeco = 1023;  
const int valorHumedo = 320;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  // Leer el valor analógico del sensor YL-69
  valorSensor = analogRead(sensorPin);

  // Calcular el %
  porcentajeHumedad = map(valorSensor, valorSeco, valorHumedo, 0, 100);

  // Limitar el % entre 0 y 100 para evitar valores fuera de rango
  porcentajeHumedad = constrain(porcentajeHumedad, 0, 100);

  // Mostrar el porcentaje de humedad en el Monitor Serial
  Serial.print("Humedad del suelo: ");
  Serial.print(porcentajeHumedad);
  Serial.println("%");

  // Esperar 1 segundo antes de la siguiente lectura
  delay(1000);
}
