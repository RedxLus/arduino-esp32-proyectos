// Descargar librería: "Rtc by Makuna"

#include <ThreeWire.h>  
#include <RtcDS1302.h>

ThreeWire myWire(3,4,2); // DAT, SCLK, RST
RtcDS1302<ThreeWire> Rtc(myWire);

void setup () 
{
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
}

void loop () 
{
    RtcDateTime now = Rtc.GetDateTime();

    printDateTime(now);
    Serial.println();

    if (!now.IsValid())
    {
        // Causas comunes:
        //    1) La batería del dispositivo está baja o incluso falta y la alimentación fue desconectada.
        Serial.println("¡El RTC perdió confianza en la fecha y hora!");
    }

    delay(5000); // cinco segundos
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
}
