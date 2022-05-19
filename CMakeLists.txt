# Standard routine
cmake_minimum_required(VERSION 3.16)
project(eeg_proj)


set(AUI_VERSION 3abfecb9)
# Use AUI.Boot
file(
        DOWNLOAD
        https://raw.githubusercontent.com/aui-framework/aui/${AUI_VERSION}/aui.boot.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/aui.boot.cmake)
include(${CMAKE_CURRENT_BINARY_DIR}/aui.boot.cmake)

# import AUI
auib_import(AUI https://github.com/aui-framework/aui
        VERSION ${AUI_VERSION}
        COMPONENTS core views)

auib_import(wavelib https://github.com/rafat/wavelib)

auib_import(opennn https://github.com/Artelnics/opennn/archive/refs/heads/master.zip ARCHIVE ADD_SUBDIRECTORY)


aui_executable(eeg_proj)

# Link required libs
aui_link(eeg_proj PRIVATE aui::core aui::views wavelib::wavelib -lfftw3 -lm opennn)
target_include_directories(eeg_proj PUBLIC ${opennn_DIR})
message("${opennn_ROOT}")

aui_enable_tests()
