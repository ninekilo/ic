//
// Created by eunsoop on 26. 3. 28..
//
#include "display/view/sport_view.h"

#define VERTICAL_CENTER (TFT_HEIGHT / 2)
#define HORIZONTAL_CENTER (TFT_WIDTH / 2)

// SportIndicatorView IMPLEMENTATION STARTS ----

void drawGear(TFT_eSPI* tft, const int8_t gear) {
    tft->setTextDatum(TC_DATUM);
    tft->setTextFont(4);
    tft->setTextSize(5);
    if (gear == 0) {
        tft->drawString("N", HORIZONTAL_CENTER, 35);
    } else {
        tft->drawString(String(gear), HORIZONTAL_CENTER, 45);
    }
    tft->setTextFont(1);
}

void drawSpeed(TFT_eSPI* tft, const int8_t speed) {
    tft->setTextDatum(BC_DATUM);
    tft->setTextSize(4);
    tft->drawString(String(speed), HORIZONTAL_CENTER, 193);
}

void drawRPM(TFT_eSPI* tft, const int16_t rpm) {
    tft->setTextDatum(TL_DATUM);
    tft->setTextSize(2);

    // format 0000
    char rpmStr[5];
    snprintf(rpmStr, sizeof(rpmStr), "%04d", rpm);

    tft->drawString(String(rpmStr), 8, 7);
}

void drawColon(TFT_eSPI* tft, const int x, const int y) {
    tft->fillRect(x - 1, y + 10, 2, 2, TFT_WHITE);
    tft->fillRect(x - 1, y + 4, 2, 2, TFT_WHITE);
}

void drawTime(TFT_eSPI* tft, const int32_t time) {
    tft->setTextDatum(TR_DATUM);
    tft->setTextSize(2);

    // register space to save formatted values
    char hundredths[3];
    char seconds[3];
    char minutes[3];

    // format time to "hh:mm:ss.hh"
    snprintf(hundredths, sizeof(hundredths), "%02d", time % 100);
    snprintf(seconds, sizeof(hundredths), "%02d", (time / 100) % 60);
    snprintf(minutes, sizeof(hundredths), "%02d", (time / 6000) % 60);

    // draw separately due to (colon | dot)'s spacing.
    tft->drawString(String(minutes), TFT_WIDTH - 64, 7);
    drawColon(tft, TFT_WIDTH - 63, 7);
    tft->drawString(String(seconds), TFT_WIDTH - 36, 7);
    tft->fillRect(TFT_WIDTH - 36, 18, 2, 2, TFT_WHITE);
    tft->drawString(String(hundredths), TFT_WIDTH - 8, 7);
}

void SportIndicatorView::init(TFT_eSPI* tft) {
    tft->setTextColor(TFT_WHITE);

    tft->setTextDatum(TL_DATUM);
    tft->setTextSize(1);
    tft->drawString("rpm", 58, 15);

    tft->setTextDatum(TC_DATUM);
    tft->setTextSize(3);
    tft->drawString("Gear", HORIZONTAL_CENTER, 7);

    tft->setTextDatum(BC_DATUM);
    tft->setTextSize(2);
    tft->drawString("km/h", HORIZONTAL_CENTER, 215);

    // Draw initial values
    drawGear(tft, this->gear);
    drawSpeed(tft, this->speed);
    drawRPM(tft, this->rpm);
    drawTime(tft, this->time);
}

void SportIndicatorView::paint(TFT_eSPI* tft) {
    drawGear(tft, this->gear);
    drawSpeed(tft, this->speed);
    drawRPM(tft, this->rpm);
    drawTime(tft, this->time);
}

bool SportIndicatorView::needUpdate() {
    return false;
}

// SportIndicatorView IMPLEMENTATION ENDS ----

// ---------------------------------------------------
//    From here, widget views will be implemented.
// ---------------------------------------------------
#define WIDGET_CENTER 114

GForceWidget::GForceWidget() = default;

void drawGForce(TFT_eSPI* tft, const float_t lat, const float_t lng) {
    char latStr[6];
    char lngStr[6];

    sprintf(latStr, "%.2f", lat);
    sprintf(lngStr, "%.2f", lng);

    latStr[4] = 'g';
    lngStr[4] = 'g';
    latStr[5] = '\0';
    lngStr[5] = '\0';

    tft->setTextSize(3);
    tft->drawString(latStr, HORIZONTAL_CENTER + 40, WIDGET_CENTER - 30);
    tft->drawString(lngStr, HORIZONTAL_CENTER + 40, WIDGET_CENTER + 70);
}

// G Force Implementation
void GForceWidget::init(TFT_eSPI *tft) {
    tft->setTextDatum(TL_DATUM);
    tft->setTextSize(3);
    tft->drawString("G-Force", 15, 7);

    tft->drawSmoothCircle(HORIZONTAL_CENTER - 70, WIDGET_CENTER + 18, 80, TFT_WHITE, TFT_BLACK);
    tft->drawSmoothCircle(HORIZONTAL_CENTER - 70, WIDGET_CENTER + 18, 60, TFT_WHITE, TFT_DARKGREY);
    tft->drawSmoothCircle(HORIZONTAL_CENTER - 70, WIDGET_CENTER + 18, 40, TFT_WHITE, TFT_DARKGREY);
    tft->drawSmoothCircle(HORIZONTAL_CENTER - 70, WIDGET_CENTER + 18, 20, TFT_WHITE, TFT_DARKGREY);

    tft->setTextSize(2);
    tft->drawString("Lat.", HORIZONTAL_CENTER + 40, WIDGET_CENTER - 60);
    tft->drawString("Long.", HORIZONTAL_CENTER + 40, WIDGET_CENTER + 40);

    drawGForce(tft, this->lat, this->lng);
}

void GForceWidget::paint(TFT_eSPI *tft) {}

bool GForceWidget::needUpdate() {
    return false;
}

void GForceWidget::setGForce(float_t lat, float_t lng) {
    this->lat = lat;
    this->lng = lng;
}