//
// Created by iridescent on 14.05.22.
//

#ifndef EEG_PROJ_AHISTOGRAMVIEW_H
#define EEG_PROJ_AHISTOGRAMVIEW_H
#include "AUI/View/AView.h"
#include "AUI/ASS/ASS.h"

class API_AUI_VIEWS AHistogramView : public AView {
public:
    AHistogramView(unsigned short columnCount);
    void setData(std::vector<glm::vec2> data);
    void render() override;
    std::vector<float> getColumnHeights();

private:
    std::vector<AColor> colors;
    unsigned int indent = 1;
    unsigned short columnCount;
    std::vector<float> columnHeights;
    void renderLegend();
};



#endif //EEG_PROJ_AHISTOGRAMVIEW_H
