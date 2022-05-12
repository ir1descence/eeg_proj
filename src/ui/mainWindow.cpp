//
// Created by iridescent on 27.04.22.
//
#include <AUI/Util/kAUI.h>
#include <AUI/Util/UIBuildingHelpers.h>
#include <AUI/View/AButton.h>
#include <fstream>
#include <eeg_data_flow/serial/SerialPort.hpp>
#include "mainWindow.h"
#include "fft/fft_spectrum.h"

MainWindow::MainWindow() : AWindow("EEG project", 600_dp, 400_dp), dataFlow(1024), mThread([&] {
    //std::ifstream serialRead("/dev/ttyACM0");
    /*CppLinuxSerial::SerialPort serialPort("", CppLinuxSerial::BaudRate::B_9600,
                                              CppLinuxSerial::NumDataBits::EIGHT,
                                              CppLinuxSerial::Parity::NONE,
                                              CppLinuxSerial::NumStopBits::ONE);
    // Use SerialPort serialPort("/dev/ttyACM0", 13000); instead if you want to provide a custom baud rate
    serialPort.SetTimeout(-1); // Block when reading until any data is received
    serialPort.Open();*/
    unsigned int count = 0;
    std::ifstream fis ("/home/iridescent/CLionProjects/eeg_proj/res/data.txt");
    // Read some data back (will block until at least 1 byte is received due to the SetTimeout(-1) call above)
    std::string readData;
    //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int i = 0;
    while (!fis.eof()) {
        //serialPort.Read(readData);
        //float readData;
        //char buf[255];
        //m.lock();
        fis >> readData;
        dataFlow.update({/*std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::steady_clock::now() - begin).count()*/i,std::stof(readData)});
        //m.unlock();
        i++;
        ui_thread{
            //std::cout << std::stof(readData) << std::endl;
            rawSignal->setData(dataFlow.getData());
        };

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}),
sThread([&]{
    fft_spectrum* f = new fft_spectrum(200);
    while (1) {
        //serialPort.Read(readData);
        //float readData;
        //char buf[255];
        f->setData(&dataFlow.getYData()[0]);
        ui_thread{

            //std::cout << std::stof(readData) << std::endl;
            fftSpectrum->setData(f->update());
        };
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
})
{
    setContents(
            Vertical{
                    recordButton = _new<AButton>("Record").connect(&AButton::clicked,
                                                                   this, [&] {
                        dataFlow.setRecordMode();
                        recordButton->setText(dataFlow.getRecordMode() ? "Stop recording" : "Record");
                    }),
                    rawSignal = _new<AGraphView>(200),
                    fftSpectrum = _new<AGraphView>(101),
                            }
            );
}
