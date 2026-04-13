//
// Created by iridescent on 27.04.22.
//
#include <AUI/Util/kAUI.h>
#include <AUI/Util/UIBuildingHelpers.h>
#include <AUI/View/AButton.h>
#include <fstream>
#include <eeg_data_flow/serial/SerialPort.hpp>
#include <AUI/View/ATabView.h>
#include <iostream>
#include "mainWindow.h"
#include "fft/fft_spectrum.h"

MainWindow::MainWindow() : AWindow("EEG project", 600_dp, 400_dp), dataFlow(256), mThread([&] {
    // Set to true to use serial port, false to read from file (for testing)
    constexpr bool USE_SERIAL_PORT = false;
    constexpr const char* SERIAL_DEVICE = "/dev/ttyACM0";
    constexpr const char* DATA_FILE = "/home/iridescent/Projects/eeg_proj/res/data.txt";
    
    std::string readData;
    int i = 0;
    getSpectrogram();
    
    if (USE_SERIAL_PORT) {
        // Serial port configuration for EEG data acquisition
        try {
            CppLinuxSerial::SerialPort serialPort(SERIAL_DEVICE, 
                                                  CppLinuxSerial::BaudRate::B_9600,
                                                  CppLinuxSerial::NumDataBits::EIGHT,
                                                  CppLinuxSerial::Parity::NONE,
                                                  CppLinuxSerial::NumStopBits::ONE);
            serialPort.SetTimeout(100); // 100ms timeout to allow checking for stop condition
            serialPort.Open();
            
            std::string buffer;
            while (!mStopThread) {
                serialPort.Read(readData);
                if (readData.empty()) continue;
                
                buffer += readData;
                
                // Process complete lines (assuming newline-delimited data)
                size_t newlinePos;
                while ((newlinePos = buffer.find('\n')) != std::string::npos) {
                    std::string line = buffer.substr(0, newlinePos);
                    buffer.erase(0, newlinePos + 1);
                    
                    // Remove carriage return if present
                    if (!line.empty() && line.back() == '\r') {
                        line.pop_back();
                    }
                    
                    if (line.empty()) continue;
                    
                    try {
                        float value = std::stof(line);
                        i++;
                        ui_thread{
                            dataFlow.update({i, value});
                            rawSignal->setData(dataFlow.getData());
                        };
                    } catch (const std::exception& e) {
                        // Skip invalid data
                        std::cerr << "Invalid data: " << line << std::endl;
                    }
                }
            }
            serialPort.Close();
        } catch (const CppLinuxSerial::Exception& e) {
            std::cerr << "Serial port error: " << e.what() << std::endl;
        }
    } else {
        // File-based reading for testing without hardware
        std::ifstream fis(DATA_FILE);
        if (!fis.is_open()) {
            std::cerr << "Could not open data file: " << DATA_FILE << std::endl;
            return;
        }
        
        while (fis >> readData && !mStopThread) {
            i++;
            try {
                float value = std::stof(readData);
                ui_thread{
                    dataFlow.update({i, value});
                    rawSignal->setData(dataFlow.getData());
                };
            } catch (const std::exception& e) {
                std::cerr << "Invalid data: " << readData << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
})
{
    _<ATabView> tabView;
    addView(tabView = _new<ATabView>() let {
        it->addTab(Vertical{
                recordButton = _new<AButton>("Record").connect(&AButton::clicked,this, [&] {
                    dataFlow.setRecordMode();
                    recordButton->setText(dataFlow.getRecordMode() ? "Stop recording" : "Record");
                }),
                rawSignal = _new<AGraphView>(),
                Centered{_new<ALabel>("EEG spectrum")},
                fftSpectrum = _new<AGraphView>(),
                _new<ALabel>("Frequency ranges"),
                histogram = _new<AHistogramView>(4),
        } let { it->setExpanding(); }, "Recording");
        it->setExpanding();
        it->addTab(Vertical{
                _new<ALabel>("Henlo")
        } let { it->setExpanding(); }, "Spectrum");
    });
    setContents(
            Vertical {tabView}

    );
}

void MainWindow::getSpectrogram() {
    sThread = std::thread([&]{
        fft_spectrum* f = new fft_spectrum(dataFlow.getYData().size());

        while (!mStopThread) {
            f->updateData(&dataFlow.getYData()[0]);
            ui_threadX[data = std::move(f->getSpectrum()), this]{
                fftSpectrum->setData(data);
                histogram->setData(data);
            };
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        delete f;
    });
}
MainWindow::~MainWindow() noexcept {
    mStopThread = true;
    if (sThread.joinable()) sThread.join();
    if (mThread.joinable()) mThread.join();
}


