TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp

HEADERS += \
    graph.h \
    implementation_graph.h \
    iteratorBFS.h \
    iteratorDFS.h \
    Tarjan.h

