//
// Created by iridescent on 28.04.22.
//

#include <AUI/Common/SharedPtrTypes.h>
#include <AUI/Common/AVector.h>
#include <glm/vec2.hpp>

#ifndef EEG_PROJ_DATAFLOW_H
#define EEG_PROJ_DATAFLOW_H

#endif //EEG_PROJ_DATAFLOW_H
class DataFlow {
public:
    DataFlow(unsigned int pointsNum);
    ~DataFlow();
    void update(glm::vec2 point);
    std::vector<double> getYData();
    std::vector<glm::vec2> getData();
    void record();
    void setRecordMode();
    bool getRecordMode();
    unsigned int getDataLength();
private:
    std::thread rThread;
    std::mutex mutex;
    bool dataChanged = false;
    bool recordMode = false;
    std::vector<glm::vec2> data;
};
