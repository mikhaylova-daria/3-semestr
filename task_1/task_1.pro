TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11
SOURCES += main.cpp

HEADERS += \
    DSU.h \
    Kruskal.h \
    graph.h \
    Prim.h

