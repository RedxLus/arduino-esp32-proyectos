const int sensorPin = A0; // Pin analógico donde está conectado el sensor
int valorSensor = 0;      // Variable vacía inicializada como 0

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Lee el valor analógico del sensor
  valorSensor = analogRead(sensorPin);

  // Muestra el valor en el Monitor Serial
  Serial.print("Valor del sensor: ");
  Serial.println(valorSensor);

  // Espera 1 segundo antes de la siguiente lectura
  delay(1000);
}
