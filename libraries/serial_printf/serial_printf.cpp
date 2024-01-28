
// Arduino serial printf
// @ 2020-2024 Alexandr Belogolovsky ab2014box@gmail.com

#include <Arduino.h>
#include <SoftwareSerial.h>

#include <stdarg.h>

#include "serial_printf.h"

//static
Stream * pfSerial = NULL;

static char buf[PF_SERIAL_PRINTF_LIMIT];

// uninit for change console
void uninitPf(void)
{
    pfSerial = NULL;
}

// Call this when standard Serial already started outside here
void initPfConsoleStdSerial(void)
{
    if (pfSerial == NULL) {
  #ifndef PF_SERIAL_OUTPUT_DISABLE
        pfSerial = &Serial;
  #endif
    }
}

void initPfConsoleStdSerial(long speed)
{
    if (pfSerial == NULL) {
  #ifndef PF_SERIAL_OUTPUT_DISABLE
        pfSerial = &Serial;
        Serial.begin(speed);
  #endif
    }
}

// Call this when hardware Serial already started outside here
void initPfConsoleHwSerial(HardwareSerial * hwSerial)
{
    if (pfSerial == NULL) {
  #ifndef PF_SERIAL_OUTPUT_DISABLE
        pfSerial = hwSerial;
  #endif
    }
}

void initPfConsoleHwSerial(HardwareSerial * hwSerial, long speed)
{
    if (pfSerial == NULL) {
  #ifndef PF_SERIAL_OUTPUT_DISABLE
        pfSerial = hwSerial;
        hwSerial->begin(speed);
  #endif
    }
}

void initPfConsoleSoftSerial(long speed, uint8_t rx_pin, uint8_t tx_pin)
{
    if (pfSerial == NULL) {
  #ifndef PF_SERIAL_OUTPUT_DISABLE
        SoftwareSerial * s = new SoftwareSerial(rx_pin, tx_pin);
        pfSerial = s;
        s->begin(speed);
  #endif
    }
} 

// Default init when not init before first call pf()
static void initPfDefault(void)
{
  #ifdef PF_SOFTSERIAL_DEFAULT
    initPfConsoleSoftSerial(PF_SERIAL_PORT_SPEED_BAUD_DEFAULT, SERIAL_RX_PIN, SERIAL_TX_PIN);
  #else
    if (Serial.available()) { // standard Serial already started ounside here
        initPfConsoleStdSerial();
    } else {
        initPfConsoleStdSerial(PF_SERIAL_PORT_SPEED_BAUD_DEFAULT);
    }
  #endif
}

/** Printf analogue for SoftwareSerial port */
void pf(const char *fmt, ...)
{
  #ifndef PF_SERIAL_OUTPUT_DISABLE
    if (pfSerial == NULL) initPfDefault();

    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, PF_SERIAL_PRINTF_LIMIT, fmt, args);
    va_end (args);

    pfSerial->print(buf);
  #endif
}

void pf(const String sfmt, ...)
{
  #ifndef PF_SERIAL_OUTPUT_DISABLE
    char * fmt = sfmt.c_str();

    if (pfSerial == NULL) initPfDefault();

    va_list args;
    va_start(args, sfmt);
    vsnprintf(buf, PF_SERIAL_PRINTF_LIMIT, fmt, args);
    va_end (args);

    pfSerial->print(buf);
  #endif
}

void pf(const __FlashStringHelper *fsfmt, ...)
{
  #ifndef PF_SERIAL_OUTPUT_DISABLE
    static char fmt[PF_SERIAL_PRINTF_LIMIT];
    strcpy_P(fmt, (PGM_P)fsfmt);

    if (pfSerial == NULL) initPfDefault();

    va_list args;
    va_start(args, fsfmt);
    vsnprintf(buf, PF_SERIAL_PRINTF_LIMIT, fmt, args);
    va_end (args);

    pfSerial->print(buf);
  #endif
}
