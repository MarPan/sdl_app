TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
            board.cpp \
            game.cpp \
            main.cpp \
            object.cpp \
            texturemanager.cpp \
            utilities.cpp \
            world.cpp \
    state.cpp \
    statemachine.cpp \
    gamestate.cpp \
    playtimestate.cpp \
    boardstate.cpp \
    gemstate.cpp \
    gemcontroller.cpp \
    boardlogic.cpp \
    moveinfo.cpp \
    soundmanager.cpp \
    timer.cpp \
    clock.cpp


HEADERS += \
            board.h \
            game.h \
            object.h \
            texturemanager.h \
            utilities.h \
            world.h \
    state.h \
    statemachine.h \
    gamestate.h \
    playtimestate.h \
    boardstate.h \
    multiplatformSDL.h \
    gemstate.h \
    gemcontroller.h \
    boardlogic.h \
    notifier.h \
    moveinfo.h \
    soundmanager.h \
    timer.h \
    clock.h

INCLUDEPATH += ../Libraries/SDL2-2.0.3/include
INCLUDEPATH += ../Libraries/SDL2_image-2.0.0/include
INCLUDEPATH += ../Libraries/SDL2_mixer-2.0.0/include
INCLUDEPATH += ../Libraries/SDL2_ttf-2.0.12/include

DEFINES += SDL_MAIN_HANDLED

LIBS += \
        -L../Libraries/SDL2_image-2.0.0/lib/x86 \
        -L../Libraries/SDL2-2.0.3/lib/x86 \
        -L../Libraries/SDL2_ttf-2.0.12/lib/x86 \
        -L../Libraries/SDL2_mixer-2.0.0/lib/x86 \
        -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

DESTDIR = ../Bejeweled/Debug/

unix {
    LIBS += `sdl2-config --libs`
}
win32 {
    LIBS += -lmingw32 -mwindows
}

QMAKE_CXXFLAGS += -std=gnu++11
