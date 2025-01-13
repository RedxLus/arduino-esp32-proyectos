#define pump1 D7      // Pin digital para controlar la bomba de agua

// Configuración del YL-69
const int sensorPin = A0;  // Pin analógico donde está conectado el sensor
int valorSensor = 0;       // Variable para la lectura analógica
int porcentajeHumedad = 0; // Variable para el porcentaje calculado
const int valorSeco = 1024;  // Valor en seco (aire)
const int valorHumedo = 600; // Valor en agua (máxima humedad)

void setup() {
  Serial.begin(9600); 
  delay(1000);
  pinMode(pump1, OUTPUT);
  digitalWrite(pump1, HIGH);
}

void loop() {
  // Leer el valor analógico del sensor
  valorSensor = analogRead(sensorPin);

  // Mapear el rango calibrado al porcentaje de 0% a 100%
  porcentajeHumedad = map(valorSensor, valorSeco, valorHumedo, 0, 100);

  // Limitar el porcentaje entre 0 y 100 para evitar valores fuera de rango
  porcentajeHumedad = constrain(porcentajeHumedad, 0, 100);

  // Mostrar el porcentaje de humedad en el Monitor Serial
  Serial.print("Humedad del suelo: ");
  Serial.print(porcentajeHumedad);
  Serial.println("%");

  // Activar la bomba si la humedad es menor al 20%
  if (porcentajeHumedad < 20) {
    Serial.println("Humedad baja. Activando bomba...");
    digitalWrite(pump1, LOW); // Bomba activada
  } else {
    Serial.println("Humedad adecuada. Desactivando bomba...");
    digitalWrite(pump1, HIGH); // Bomba desactivada
  }

  // Esperar 30 segundos antes de la siguiente lectura
  delay(30000);
}
