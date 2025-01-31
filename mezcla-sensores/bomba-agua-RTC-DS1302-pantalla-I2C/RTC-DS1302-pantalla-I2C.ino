// Descargar librería: https://github.com/lafvintech/Super-Starter-Kit-for-ESP32-S3-WROOM/blob/main/C/Libraries/LiquidCrystal_I2C-1.1.2.zip
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define SDA 5                    // Definir pines SDA
#define SCL 4                    // Definir pines SCL
LiquidCrystal_I2C lcd(0x27,16,2);

// Descargar librería: "Rtc by Makuna"
#include <ThreeWire.h>  
#include <RtcDS1302.h>

ThreeWire myWire(14,13,12); // DAT, SCLK, RST
RtcDS1302<ThreeWire> Rtc(myWire);

// Configuración de la pump
#define pump1 7      // Pin digital para controlar la bomba de agua

void setup() {
  Wire.begin(SDA, SCL);           
  if (!i2CAddrTest(0x27)) {
      lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }
  lcd.init();                     
  lcd.backlight();                
  lcd.setCursor(0,0);             
  lcd.print("hello, world!");     

    Serial.begin(9600);

    Serial.print("Compilado en: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);

    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();

    if (!Rtc.IsDateTimeValid()) 
    {
        // Causas comunes:
        //    1) Es la primera vez que se ejecuta y el dispositivo aún no estaba funcionando.
        //    2) La batería del dispositivo está baja o incluso falta.

        Serial.println("¡El RTC perdió confianza en la fecha y hora!");
        Rtc.SetDateTime(compiled);
    }

    if (Rtc.GetIsWriteProtected())
    {
        Serial.println("El RTC estaba protegido contra escritura, habilitando escritura ahora");
        Rtc.SetIsWriteProtected(false);
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("El RTC no estaba funcionando activamente, iniciándolo ahora");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) 
    {
        Serial.println("¡El RTC es más antiguo que la hora de compilación! (Actualizando fecha y hora)");
        Rtc.SetDateTime(compiled);
    }
    else if (now > compiled) 
    {
        Serial.println("El RTC es más reciente que la hora de compilación. (Esto es esperado)");
    }
    else if (now == compiled) 
    {
        Serial.println("¡El RTC es igual a la hora de compilación! (No esperado, pero todo está bien)");
    }

  // Configuración del pin de la pump
  delay(1000);
  pinMode(pump1, OUTPUT);
  digitalWrite(pump1, HIGH); // La bomba empieza desactivada
}

void loop() {
    RtcDateTime now = Rtc.GetDateTime();
    printDateTime(now);

    if (!now.IsValid()) {
        // Causas comunes:
        //    1) La batería del dispositivo está baja o incluso falta y la alimentación fue desconectada.
        lcd.setCursor(0, 1);  // Mover el cursor a fila 1, columna 0
        lcd.print("RTC sin confianza!");
    } else {
        lcd.setCursor(0, 1);  // Mover el cursor a fila 1, columna 0
        lcd.print("Hora: ");
        lcd.print(now.Hour());
        lcd.print(":");
        lcd.print(now.Minute());
        lcd.print(":");
        lcd.print(now.Second());
    }

    // Activar y desactivar la bomba cada minuto
    if (now.Minute() % 2 == 0) {
        digitalWrite(pump1, LOW); // Activa la bomba
    } else {
        digitalWrite(pump1, HIGH); // Desactiva la bomba
    }

    delay(1000);
}

bool i2CAddrTest(uint8_t addr) {
    Wire.beginTransmission(addr);
    return (Wire.endTransmission() == 0);
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt) {
    char datestring[20];

    snprintf_P(datestring, 
                countof(datestring),
                PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
                dt.Month(),
                dt.Day(),
                dt.Year(),
                dt.Hour(),
                dt.Minute(),
                dt.Second());
    
    lcd.setCursor(0, 0);  // Mover el cursor a fila 0, columna 0
    lcd.print("                ");  // Limpiar la línea
    lcd.setCursor(0, 0);  // Volver a la posición inicial
    lcd.print(datestring); // Mostrar la fecha y hora en la LCD
}
