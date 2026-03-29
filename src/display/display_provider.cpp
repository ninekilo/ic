//
// Created by eunsoop on 3/16/2026.
//
#include "display/display_provider.h"

NKVerticalSplitView::NKVerticalSplitView(View* top, View* bottom) {
    this->top = top;
    this->bottom = bottom;
}

void NKVerticalSplitView::init(TFT_eSPI* tft) {
    tft->setViewport(0, 0, TFT_WIDTH, tft->height());
    tft->fillScreen(TFT_BLACK);

    // Drawing splitter
    tft->fillRectHGradient(28, 228, 91, 2, TFT_BLACK, 0x3333); // 70% of first half
    tft->fillRectHGradient(119, 228, 39, 2, 0x3333, 0xBBBB); // remaining 30% of first half
    tft->fillRect(158, 228, 4, 2, 0xBBBB);
    tft->fillRectHGradient(162, 228, 39, 2, 0xBBBB, 0x3333); // 30% of second half
    tft->fillRectHGradient(201, 228, 92, 2, 0x3333, TFT_BLACK); // remaining 70% of second half

    // Drawing driving info
    tft->setViewport(0, 0, tft->width(), 227);
    this->top->init(tft);

    // Drawing detailed info
    tft->setViewport(0, 231, tft->width(), 228);
    this->bottom->init(tft);

    tft->setViewport(0, 0, tft->width(), tft->height());
}

void NKVerticalSplitView::loop(TFT_eSPI* tft) {
    if (this->top && this->top->needUpdate()) {
        tft->setViewport(0, 0, tft->width(), 228);
        this->top->paint(tft);
    }

    if (this->bottom && this->bottom->needUpdate()) {
        tft->setViewport(0, 230, tft->width(), tft->height());
        this->bottom->paint(tft);
    }
}

// TODO: impl NKStackableView