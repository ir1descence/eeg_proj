//
// Created by iridescent on 03.05.22.
//

#include <complex>
#include <valarray>

#ifndef EEG_PROJ_FFT_H
#define EEG_PROJ_FFT_H

#endif //EEG_PROJ_FFT_H
class fft_ {
public:
    typedef std::complex<double> Complex;
    typedef std::valarray<Complex> CArray;
    static void fft(CArray& x);
    static void ifft(CArray& x);
private:
    constexpr static double PI = 3.141592653589793238460;
};