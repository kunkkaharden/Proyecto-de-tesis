QT += core
QT -= gui

CONFIG += c++11

TARGET = Proyecto-de-tesis
CONFIG += console
CONFIG -= app_bundle
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp

LIBS += -lgomp
TEMPLATE = app

SOURCES += main.cpp \
    source/modelo/agente.cpp \
    source/modelo/entorno.cpp \
    source/utiles/arreglofloat.cpp \
    source/utiles/matrix.cpp \
    source/auxiliar/cordenadas.cpp \
    source/auxiliar/estado.cpp \
    source/modelo/aprendizajereforzado.cpp \
    source/utiles/episodio.cpp \
    source/utiles/metricas.cpp

HEADERS += \
    source/modelo/agente.h \
    source/modelo/entorno.h \
    source/utiles/arreglofloat.h \
    source/utiles/matrix.h \
    source/auxiliar/cordenadas.h \
    source/auxiliar/estado.h \
    aprendizajereforzado.h \
    source/modelo/aprendizajereforzado.h \
    source/auxiliar/ar.h \
    source/utiles/episodio.h \
    source/utiles/metricas.h
