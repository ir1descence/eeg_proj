//
// Created by iridescent on 27.04.22.
//

#ifndef AUI_APP_AGRAPHVIEW_H
#define AUI_APP_AGRAPHVIEW_H

#endif //AUI_APP_AGRAPHVIEW_H

#include "AUI/View/AView.h"
#include "eeg_data_flow/dataFlow.h"

class API_AUI_VIEWS AGraphView: public AView{
public:
    AGraphView();
    void render() override;
    void setData(std::vector<glm::vec2> data);
    void renderCoordinatesY();
    void renderCoordinatesX();
private:
    AVector<glm::vec2> data;
    int pointsNum;
    double delta = 1;
    double maxY = 0;
    double minY = 0;
    double maxX = 0;
    double minX = 0;
};