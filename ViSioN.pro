



QT += core gui widgets charts

RC_ICONS = ViSioN.ico

DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXX = g++-10 
QMAKE_LINK = g++-10

QMAKE_CXXFLAGS += -std=gnu++20 -pedantic

HEADERS += beejak.hpp drishya.hpp panel.hpp
SOURCES += src/beejak.cpp src/drishya.cpp src/main.cpp src/panel.cpp

LIBS += -lm -lpthread
