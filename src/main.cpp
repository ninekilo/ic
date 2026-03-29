#include <Arduino.h>
#include <TFT_eSPI.h>

#include "display/display_provider.h"
#include "display/view/sport_view.h"

auto tft = new TFT_eSPI;
DisplayProvider* display = nullptr;

void setup() {
    Serial.begin(115200);
    tft->init();
    tft->setRotation(0);
    tft->fillScreen(TFT_BLACK);

    display = new NKVerticalSplitView(
        new SportIndicatorView(),
        new SportIndicatorView()
    );

    display->init(tft);
}

void loop() {
    if (display) display->loop(tft);
}