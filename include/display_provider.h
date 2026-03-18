//
// Created by eunsoop on 3/16/2026.
//

#ifndef DISPLAY_PROVIDER_H
#define DISPLAY_PROVIDER_H
#include "TFT_eSPI.h"

class View;
class ViewPainter;

class DisplayProvider {
public:
    virtual void init(TFT_eSPI* tft);
    virtual void loop(TFT_eSPI* tft);
    virtual ~DisplayProvider() = default;
};

class VerticalSplitView : public DisplayProvider {
public:
    VerticalSplitView(View* top, View* bottom);
    void init(TFT_eSPI* tft) override;
    void loop(TFT_eSPI* tft) override;
private:
    View* top = nullptr;
    View* bottom = nullptr;
};

class View {
public:
    void init(ViewPainter* painter);
    void paint(ViewPainter* painter);
};

class ViewPainter : public TFT_eSPI{
    void setWindow(int32_t x0, int32_t y0, int32_t x1, int32_t y1) override;
    virtual ~ViewPainter() = default;
};

#endif //DISPLAY_PROVIDER_H