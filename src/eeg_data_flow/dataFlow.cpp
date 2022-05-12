#include <future>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstring>
#include "dataFlow.h"

//
// Created by iridescent on 28.04.22.
//
void DataFlow::update(glm::vec2 d) {
    mutex.lock();
    data.push_back(d);
    data.erase(data.begin());
    mutex.unlock();
    dataChanged = true;
}
void DataFlow::setRecordMode() {
    recordMode = !recordMode;
    if (recordMode) record();
}
void DataFlow::record() {
    rThread = std::thread([&]{
        std::ofstream file;
        std::time_t result = std::time(nullptr);
        std::stringstream sstream;
        std::cout << "каво\n";
        sstream << std::put_time(std::localtime(&result), "%F_%T");
        std::cout << sstream.str() << "\n";
        file.open(sstream.str()+".txt", std::ios::out);
        std::cout << file.is_open() << std::endl;
        while (recordMode) {
            if (dataChanged) {
                mutex.lock();
                file << data[data.size()-1][1] << " ";
                mutex.unlock();
                dataChanged = false;
            }
        }
        file.close();
    });
}

DataFlow::DataFlow(unsigned int pointsNum) : data(pointsNum, {0,0}) {
}

DataFlow::~DataFlow() {
    if (recordMode) rThread.join();
    recordMode = false;
}


std::vector<glm::vec2> DataFlow::getData() {
    std::lock_guard<std::mutex> guard(mutex);
    return data;
}

std::vector<double> DataFlow::getYData() {
    std::lock_guard<std::mutex> guard(mutex);
    std::vector<double> yData;
    for (glm::vec2 point : data) {
        yData.push_back(point[1]);
    }
    return yData;
}

bool DataFlow::getRecordMode() {
    return recordMode;
}

