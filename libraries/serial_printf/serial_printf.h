
// Arduino serial printf
// @ 2020-2024 Alexandr Belogolovsky ab2014box@gmail.com

#ifndef __SOFTSERIAL_PRINTF_H_
#define __SOFTSERIAL_PRINTF_H_

#include <Arduino.h>

//#define PF_SERIAL_OUTPUT_DISABLE /* Uncomment this line to disable print to console */

//#define PF_SOFTSERIAL_DEFAULT /* Uncomment this line to use softserial by default */

#ifndef PF_SERIAL_PRINTF_LIMIT
 #define PF_SERIAL_PRINTF_LIMIT 80
#endif

#ifndef SERIAL_RX_PIN
 #define SERIAL_RX_PIN 8
#endif

#ifndef SERIAL_TX_PIN
 #define SERIAL_TX_PIN 9
#endif

#ifndef PF_SERIAL_PORT_SPEED_BAUD_DEFAULT
 #define PF_SERIAL_PORT_SPEED_BAUD_DEFAULT 9600
#endif

extern Stream * pfSerial;

void uninitPf(void);

void initPfConsoleStdSerial(void);

void initPfConsoleStdSerial(long speed);

void initPfConsoleHwSerial(HardwareSerial * hwSerial);

void initPfConsoleHwSerial(HardwareSerial * hwSerial, long speed);

void initPfConsoleSoftSerial(long speed, uint8_t rx_pin, uint8_t tx_pin);

/** Printf analogue for SoftwareSerial port */
void pf(const char *fmt, ...);
void pf(const String sfmt, ...);
void pf(const __FlashStringHelper *fsfmt, ...);

#endif //__SOFTSERIAL_PRINTF_H_
