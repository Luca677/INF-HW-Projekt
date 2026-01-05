#include "Timer.h"

// Wir benutzen TIM2
HardwareTimer* timer = nullptr;

// Diese Funktion wird vom Timer-Interrupt aufgerufen
void timerIsr() {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void timerInit() {
    pinMode(LED_BUILTIN, OUTPUT);

    // TIM2 existiert auf dem Nucleo L152RE
    timer = new HardwareTimer(TIM2);

    // 80 MHz / 8000 = 10 kHz → Overflow 100 = 10 ms
    timer->setPrescaleFactor(8000);
    timer->setOverflow(100);

    timer->attachInterrupt(timerIsr);
    timer->resume();   // Timer starten
}
