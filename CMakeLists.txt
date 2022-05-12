# Standard routine
cmake_minimum_required(VERSION 3.16)
project(eeg_proj)

# Use AUI.Boot
file(
        DOWNLOAD
        https://raw.githubusercontent.com/aui-framework/aui/master/aui.boot.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/aui.boot.cmake)
include(${CMAKE_CURRENT_BINARY_DIR}/aui.boot.cmake)

# import AUI
auib_import(AUI https://github.com/aui-framework/aui
        COMPONENTS core views)


aui_executable(eeg_proj)

# Link required libs
aui_link(eeg_proj PRIVATE aui::core aui::views -lfftw3 -lm)