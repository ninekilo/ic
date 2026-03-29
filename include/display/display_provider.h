//
// Created by eunsoop on 3/16/2026.
//

#ifndef DISPLAY_PROVIDER_H
#define DISPLAY_PROVIDER_H
#include "TFT_eSPI.h"

class View;

class DisplayProvider {
public:
    virtual void init(TFT_eSPI* tft);
    virtual void loop(TFT_eSPI* tft);
    virtual ~DisplayProvider() = default;
};

/**
 * NKVerticalSplitView is a display provider that splits the screen into two parts: top and bottom.
 * The top part is for driving info, and the bottom part is for detailed info.
 * The splitter is drawn to visually separate the two parts.
 *
 * The area is not split exactly in half due to cluster design.
 */
class NKVerticalSplitView : public DisplayProvider {
public:
    NKVerticalSplitView(View* top, View* bottom);
    void init(TFT_eSPI* tft) override;
    void loop(TFT_eSPI* tft) override;
private:
    View* top = nullptr;
    View* bottom = nullptr;
};

class View {
public:
    virtual void init(TFT_eSPI* painter); // For drawing initial values
    virtual void paint(TFT_eSPI* painter); // For update values
    virtual bool needUpdate(); // For checking if update is needed
    virtual ~View() = default;
};

class NKStackableView : public View {
public:
    explicit NKStackableView(View** views, int8_t size);
    void setIndex(int8_t idx);
    void init(TFT_eSPI* painter) override;
    void paint(TFT_eSPI* painter) override;
    bool needUpdate() override;

    ~NKStackableView() override = default;
private:
    int16_t dimension[2] = {0,}; // y, height (X must be 0; Width must be TFT_WIDTH)
    View** views = nullptr;
    int8_t index = 0;
    bool idxChange = false;
    int8_t size = 0;
};

#endif //DISPLAY_PROVIDER_H