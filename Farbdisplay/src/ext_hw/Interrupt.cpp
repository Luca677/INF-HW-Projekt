#include "interrupt.h"

volatile bool interruptFlag = false;

// ISR (Interrupt Service Routine)
void touchInterrupt() {
    interruptFlag = true;
}

void interruptInit() {
    pinMode(PA0, INPUT_PULLUP);

    attachInterrupt(
        digitalPinToInterrupt(PA0),
        touchInterrupt,
        FALLING
    );
}
