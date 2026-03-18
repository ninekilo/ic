#include <Arduino.h>
#include <TFT_eSPI.h>
#include <display_provider.h>

auto tft = new TFT_eSPI;
DisplayProvider *displayProvider;

void setup() {
    Serial.begin(115200);
    tft->init();
    tft->setRotation(0);
    tft->fillScreen(TFT_YELLOW);
    displayProvider = new SportDisplayProvider;
    displayProvider->init(tft);
}

void loop() {
    displayProvider->loop(tft);
}