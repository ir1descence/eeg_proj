//
// Created by iridescent on 27.04.22.
//

#include "AUI/Platform/AWindow.h"
#include "AUI/View/AButton.h"
#include "view/AGraphView.h"
#include "thread"

class MainWindow : public AWindow {
public:
    static std::pair<int, int> windowSize;
    MainWindow();
private:
    std::mutex m;
    std::thread mThread;
    std::thread sThread;
    _<AGraphView> rawSignal;
    _<AGraphView> fftSpectrum;
    _<AButton> recordButton;
    DataFlow dataFlow;
    //_<ALabel> test;

};
