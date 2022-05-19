//
// Created by iridescent on 14.05.22.
//

#include <numeric>
#include "AHistogramView.h"


AHistogramView::AHistogramView(unsigned short columnCount) : columnHeights(columnCount, 0),
colors(columnCount){
    this->columnCount = columnCount;
    setExpanding();
}

void AHistogramView::setData(std::vector<glm::vec2> data) {
    double sum = 0;
    for (auto& c : columnHeights) {
        c = 0;
    }
    for (int i = 1; i <= 3; i++) {
        columnHeights[0] += data[i][1];
    }
    for (int i = 4; i <= 8; i++) {
        columnHeights[1] += data[i][1];
    }
    for (int i = 9; i <= 12; i++) {
        columnHeights[2] += data[i][1];
    }
    for (int i = 12; i <= 30; i++) {
        columnHeights[3] += data[i][1];
    }
//    for (int i = 31; i <= 100; i++) {
//        columnHeights[4] += data[i][1];
//    }
    for (auto& c : columnHeights) {
        sum += c;
    }
    for (auto& c : columnHeights) {
        c /= sum;
    }
}

std::vector<float> AHistogramView::getColumnHeights() {
    return columnHeights;
}

void AHistogramView::render() {
    unsigned int viewHeingh = getSize()[1];
    indent = 5;
    int columnLength = (getSize()[0] - columnCount * indent - 0.25 * getSize()[0]) / columnCount;
    colors = {0x48D1CC_rgb, 0xFF7F50_rgb, 0x9932CC_rgb, 0xDAA520_rgb};
    AView::render();
    Render::line(ASolidBrush{0x002020_rgb}, {0,viewHeingh}, {getSize()[0],viewHeingh});
    Render::line(ASolidBrush{0x002020_rgb}, {0,0}, {0,getSize()[1]});
    for (int i = 0; i < columnCount; i++) {
        Render::rect(ASolidBrush{colors[i]},
                     {indent + (indent + columnLength) * i, viewHeingh * ( 1 - columnHeights[i])},
                     {columnLength, viewHeingh * columnHeights[i] - 1});
        //std::cout << i << " " << indent + (indent + columnLength) * i << " " << viewHeingh * ( 1 - columnHeights[i]) << std::endl;
        //std::cout << i << " " << (indent + columnLength) * (i + 1) << " " << viewHeingh << std::endl;
    }
    renderLegend();
    //Render::lines(ASolidBrush{0x000000_rgb}, data);
}

void AHistogramView::renderLegend() {
    Render::rect(ASolidBrush{0x0020202_rgb},
                 {getSize()[0] - 0.25 * getSize()[0] + indent, 1},
                 {0.25 * getSize()[0] - indent, getSize()[1] - 1});
    Render::rect(ASolidBrush{0xffffff_rgb},
                 {getSize()[0] - 0.25 * getSize()[0] + indent + 1, 2},
                 {0.25 * getSize()[0] - indent - 2, getSize()[1] - 3});
    for (int i = 0; i < columnCount; i++) {

        Render::rect(ASolidBrush{0xffffff_rgb},
                     {getSize()[0] - 0.25 * getSize()[0] + indent + 1, 2},
                     {0.25 * getSize()[0] - indent - 2, getSize()[1] - 3});
    }
}