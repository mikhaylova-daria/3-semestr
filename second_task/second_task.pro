TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11
SOURCES += main.cpp

HEADERS += \
    sparse_table.h \
    FCB.h \
    LCAtoRMQ.h \
    treap.h \
    libr.h

