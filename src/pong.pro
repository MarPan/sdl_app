TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += *.cpp \

HEADERS += \
    *.h \ *.hpp

LIBS += -lSDL2 -lSDL2_ttf -lSDL2_mixer `sdl2-config --libs`

QMAKE_CXXFLAGS += -std=gnu++11
