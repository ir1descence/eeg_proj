# EEG Signal Processing — Diploma Project

A desktop application for real-time acquisition, visualization, and analysis of electroencephalography (EEG) signals. The application reads raw EEG data from a hardware device over a serial port, performs signal processing (FFT and wavelet transform), and displays the results in an interactive GUI.

---

## Features

- **Real-time signal acquisition** via a serial port (UART) interface
- **Raw EEG waveform** visualization with dynamic graph rendering
- **FFT spectrum** analysis using the FFTW3 library
- **Histogram view** of signal amplitude distribution
- **Data recording** mode for saving EEG sessions to disk
- Cross-platform GUI built with the [AUI Framework](https://github.com/aui-framework/aui)

---

## Project Structure

```
eeg_proj/
├── src/
│   ├── main.cpp                  # Application entry point
│   ├── ui/
│   │   └── mainWindow.{h,cpp}    # Main application window
│   ├── view/
│   │   ├── AGraphView.{h,cpp}    # 2D waveform / spectrum graph widget
│   │   └── AHistogramView.{h,cpp}# Amplitude histogram widget
│   ├── eeg_data_flow/
│   │   ├── dataFlow.{h,cpp}      # Data pipeline & recording logic
│   │   └── serial/               # Serial port driver (Linux, CppLinuxSerial)
│   ├── fft/
│   │   ├── fft.{h,cpp}           # FFT / IFFT implementation (Cooley–Tukey)
│   │   └── fft_spectrum.{h,cpp}  # Spectrum magnitude computation
│   └── wavelet/
│       └── wavelet.{h,cpp}       # Wavelet transform wrapper
├── tests/
│   └── test.cpp                  # Unit tests
├── res/
│   └── data.txt                  # Sample / recorded EEG data
└── CMakeLists.txt
```

---

## Dependencies

| Library | Purpose |
|---|---|
| [AUI Framework](https://github.com/aui-framework/aui) | GUI (core + views) |
| [FFTW3](https://www.fftw.org/) | Fast Fourier Transform |
| [wavelib](https://github.com/rafat/wavelib) | Discrete Wavelet Transform |
| [OpenNN](https://github.com/Artelnics/opennn) | Neural network support |
| [GLM](https://github.com/g-truc/glm) | Vector/matrix math |

---

## Build Instructions

### Prerequisites

- CMake ≥ 3.16
- C++17-capable compiler (GCC / Clang)
- FFTW3 development package

```bash
# Ubuntu / Debian
sudo apt install cmake build-essential libfftw3-dev
```

### Configure & Build

```bash
git clone <repo-url> eeg_proj
cd eeg_proj
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
```

The AUI framework, wavelib, and OpenNN are fetched and built automatically by CMake via **aui.boot**.

### Run

```bash
./build/eeg_proj
```

---

## Hardware

The application expects an EEG device connected via a USB-to-serial adapter. The serial driver supports configurable baud rates (up to 460 800 baud), data bits, parity, and stop bits through the `CppLinuxSerial` library.

---

## License

This project was developed as a diploma thesis. All rights reserved.
