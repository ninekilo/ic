//
// Created by eunsoop on 26. 3. 28..
//

#ifndef CLUSTER_SPORT_DISPLAY_PROVIDER_H
#define CLUSTER_SPORT_DISPLAY_PROVIDER_H
#include "display/display_provider.h"

class SportIndicatorView : public View {
    int8_t gear = 0;
    int8_t speed = 0;
    int16_t rpm = 0;
    int32_t time = 0; // Millisecond * 10 (hundredths of seconds)
public:
    void init(TFT_eSPI *tft) final;
    void paint(TFT_eSPI *tft) final;
    bool needUpdate() final;

    ~SportIndicatorView() override = default;
};

// Widgets
class GForceWidget : public View {
    float_t lat = 0;
    float_t lng = 0;
public:
    GForceWidget();

    void init(TFT_eSPI *tft) final;
    void paint(TFT_eSPI *tft) final;
    bool needUpdate() final;

    void setGForce(float_t lat, float_t lng);

    ~GForceWidget() override = default;
};

#endif //CLUSTER_SPORT_DISPLAY_PROVIDER_H
