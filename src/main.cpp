#include <Arduino.h>
#include <TFT_eSPI.h>

#include "display/display_provider.h"

auto tft = new TFT_eSPI;
auto display = new DisplayProvider;

void setup() {
    Serial.begin(115200);
    tft->init();
    tft->setRotation(0);
}

void loop() {}