//
// Created by iridescent on 04.05.22.
//

#ifndef EEG_PROJ_FFT_SPECTRUM_H
#define EEG_PROJ_FFT_SPECTRUM_H

#include <vector>
#include "fftw3.h"


class fft_spectrum {
public:
    fft_spectrum(unsigned int input_size);
    ~fft_spectrum();
    std::vector<glm::vec2> update();
    void setData(double * data);
private:
    unsigned int input_size;
    unsigned int output_size;
    fftw_complex* input_buffer;
    fftw_complex* output_buffer;
    int flags = FFTW_ESTIMATE;
    fftw_plan plan;
};


#endif //EEG_PROJ_FFT_SPECTRUM_H
