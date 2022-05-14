//
// Created by iridescent on 04.05.22.
//

#include <iostream>
#include <valarray>
#include <glm/vec2.hpp>
#include "fft_spectrum.h"


fft_spectrum::fft_spectrum(int input_size) {
    this->input_size = input_size;
    this->output_size = (input_size/2 +1);
    output_buffer = static_cast<fftw_complex*>(fftw_malloc(output_size * sizeof(fftw_complex)));
    input_buffer = static_cast<double*>(fftw_malloc(input_size * sizeof(double)));

}

void fft_spectrum::updateData(double * data) {
    input_buffer = data;
    plan = fftw_plan_dft_r2c_1d(input_size,
                                input_buffer,
                                output_buffer,
                                flags);
    fftw_execute(plan);
}


std::vector<glm::vec2> fft_spectrum::getSpectrum() {
    std::vector<glm::vec2> res(output_size, {0,0});
    for (int i = 0; i < output_size; i++) {
        res[i][0] = i;
        res[i][1] = std::sqrt(output_buffer[i][0]*output_buffer[i][0]+ output_buffer[i][1]*output_buffer[i][1]);
    }
    return res;
}


fft_spectrum::~fft_spectrum() {
    fftw_free(input_buffer);
    fftw_free(output_buffer);
    fftw_destroy_plan(plan);
}

unsigned int fft_spectrum::get_output_size() {
    return output_size;
}