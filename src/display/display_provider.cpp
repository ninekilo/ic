//
// Created by eunsoop on 3/16/2026.
//
#include "display/display_provider.h"

void drawSplitter(TFT_eSPI* tft, const int16_t y) {
    tft->fillRectHGradient(28, y, 91, 2, TFT_BLACK, 0x3333); // 70% of first half
    tft->fillRectHGradient(119, y, 39, 2, 0x3333, 0xBBBB); // remaining 30% of first half
    tft->fillRect(158, y, 4, 2, 0xBBBB);
    tft->fillRectHGradient(162, y, 39, 2, 0xBBBB, 0x3333); // 30% of second half
    tft->fillRectHGradient(201, y, 92, 2, 0x3333, TFT_BLACK); // remaining 70% of second half
}

NKVerticalSplitView::NKVerticalSplitView(View* top, View* bottom) {
    this->top = top;
    this->bottom = bottom;
}

void NKVerticalSplitView::init(TFT_eSPI* tft) {
    tft->setViewport(0, 0, TFT_WIDTH, TFT_HEIGHT);
    tft->fillScreen(TFT_BLACK);

    drawSplitter(tft, 228);

    // Drawing driving info
    tft->setViewport(0, 0, TFT_WIDTH, 227);
    this->top->init(tft);

    // Drawing detailed info
    tft->setViewport(0, 230, TFT_WIDTH, 250);
    this->bottom->init(tft);

    tft->setViewport(0, 0, TFT_WIDTH, TFT_HEIGHT);
}

void NKVerticalSplitView::loop(TFT_eSPI* tft) {
    if (this->top && this->top->needUpdate()) {
        tft->setViewport(0, 0, TFT_WIDTH, 228);
        this->top->paint(tft);
    }

    if (this->bottom && this->bottom->needUpdate()) {
        tft->setViewport(0, 230, TFT_WIDTH, 250);
        this->bottom->paint(tft);
    }
}

void drawIndexIndicator(TFT_eSPI* painter, const int8_t size, const int8_t index) {
    // Draw splitter to separate current view and index indicator
    painter->setViewport(0, 0, TFT_WIDTH, TFT_HEIGHT);
    drawSplitter(painter, 458);

    // Set viewport to the area for index indicator
    painter->setViewport(0, 460, TFT_WIDTH, 20);

    const int start = (TFT_WIDTH - (14 * size)) / 2; // Center the indicators

    // Draw indicator
    for (int8_t i = 0; i < size; i++) {
        painter->fillRect(start + (i * 14), 8, 4, 4, (i == index ? TFT_WHITE : TFT_LIGHTGREY));
    }
}

NKStackableView::NKStackableView(View **views, const int8_t size) {
    this->views = views;
    this->size = size;
}

void NKStackableView::setIndex(const int8_t idx) {
    if (idx < 0 || idx >= this->size) return;
    this->index = idx;
    this->idxChange = true;
}

void NKStackableView::init(TFT_eSPI* painter) {
    // NKStackable uses a viewport to manage the area for each view and current index indicator. Therefore, dimension need to be saved.
    this->dimension[0] = static_cast<int16_t>(painter->getViewportY());
    this->dimension[1] = static_cast<int16_t>(painter->getViewportHeight());

    painter->setViewport(0, this->dimension[0], TFT_WIDTH, 227);
    this->views[this->index]->init(painter);

    painter->setViewport(0, this->dimension[0], TFT_WIDTH, this->dimension[1]);
    drawIndexIndicator(painter, this->size, this->index);
}

void NKStackableView::paint(TFT_eSPI* painter) {
    // Set viewport to the area for painting current view
    painter->setViewport(0, this->dimension[0], TFT_WIDTH, 227);

    if (this->idxChange) {
        this->views[this->index]->init(painter);
        this->idxChange = false;

        painter->setViewport(0, this->dimension[0], TFT_WIDTH, this->dimension[1]);
        drawIndexIndicator(painter, this->size, this->index);
    }else {
        this->views[this->index]->paint(painter);
        painter->setViewport(0, this->dimension[0], TFT_WIDTH, this->dimension[1]);
    }
}

bool NKStackableView::needUpdate() {
    return this->views[this->index]->needUpdate();
}