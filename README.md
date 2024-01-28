
Arduino serial printf
=====================

@ 2020-2024 Alexandr Belogolovsky ab2014box@gmail.com

Use pf("...%...", ...) instead of combination:
  sprintf(buffer, "...%...", ...);
  Serial.print(buffer);

Can use for standard Serial, hardware serials Serial1...Serial3 and SoftSerial

Init examples:
  initPfConsoleStdSerial(115200); // use standard Serial
  initPfConsoleHwSerial(&Serial1, 9600); // use HardwareSerial
  initPfSoftSerialConsole(9600, RXpin, TXpin); // use SoftwareSerial
