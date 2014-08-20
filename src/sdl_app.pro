TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
            board.cpp \
            game.cpp \
            gem.cpp \
            main.cpp \
            object.cpp \
            texturemanager.cpp \
            utilities.cpp \
            world.cpp \
    state.cpp


HEADERS += \
            board.h \
            game.h \
            gem.h \
            object.h \
            texturemanager.h \
            utilities.h \
            world.h \
    state.h

INCLUDEPATH += ../../include

DEFINES += SDL_MAIN_HANDLED

LIBS += -L../../lib -lSDL2 -lSDL2_image #-lSDL2_ttf -lSDL2_mixer

unix {
    LIBS += `sdl2-config --libs`
}
win32 {
    LIBS += -lmingw32 -mwindows
}

QMAKE_CXXFLAGS += -std=gnu++11
