//
// Created by eunsoop on 3/16/2026.
//
#include "display/display_provider.h"

NKVerticalSplitView::NKVerticalSplitView(View* top, View* bottom) {
    this->top = top;
    this->bottom = bottom;
}

void NKVerticalSplitView::init(TFT_eSPI *tft) {
    tft->setWindow(0, 0, tft->width(), tft->height());
    tft->fillScreen(TFT_BLACK);

    // Drawing splitter
    tft->setWindow(28, 228, 291, 230);
    tft->fillRectHGradient(0, 0, 91, 2, TFT_BLACK, 0x3333); // 70% of first half
    tft->fillRectHGradient(91, 0, 39, 2, 0x3333, 0xBBBB); // remaining 30% of first half
    tft->fillRect(132, 0, 1, 2, 0xBBBB);
    tft->fillRectHGradient(133, 0, 39, 2, 0xBBBB, 0x3333); // 30% of second half
    tft->fillRectHGradient(172, 0, 91, 2, 0x3333, TFT_BLACK); // remaining 70% of second half

    // Drawing driving info
    tft->setWindow(0, 0, tft->width(), 228);
    this->top->init(tft);

    // Drawing detailed info
    tft->setWindow(0, 230, tft->width(), tft->height());
    this->bottom->init(tft);

    tft->setWindow(0, 0, tft->width(), tft->height());
}

void NKVerticalSplitView::loop(TFT_eSPI *tft) {
    if (this->top && this->top->needUpdate()) {
        tft->setWindow(0, 0, tft->width(), 228);
        this->top->paint(tft);
    }

    if (this->bottom && this->bottom->needUpdate()) {
        tft->setWindow(0, 230, tft->width(), tft->height());
        this->bottom->paint(tft);
    }
}

// TODO: impl NKStackableView