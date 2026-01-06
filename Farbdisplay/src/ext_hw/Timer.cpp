#include "Timer.h"

// Pointer Deklaration für den HardwareTimer
HardwareTimer* timer = nullptr;

// Timer Interrupt Service Routine
void timerIsr() {
    digitalWrite(PA1, HIGH);
}

void timerInit() {
    pinMode(PA1, OUTPUT);
    // TIM2 HardwareTimer Objekt erstellen
    timer = new HardwareTimer(TIM2);

    // 80 MHz / 8000 = 10 kHz → Overflow 100 = 10 ms
    timer->setPrescaleFactor(8000);
    timer->setOverflow(100);

    timer->attachInterrupt(timerIsr); // Interrupt anhängen
    timer->resume();   // Timer starten
}
