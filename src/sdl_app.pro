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
    boardlogic.cpp


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
    notifier.h

INCLUDEPATH += ../SDL2-bin/include
INCLUDEPATH += ../SDL2_image-bin/x86_64-w64-mingw32/include

DEFINES += SDL_MAIN_HANDLED

LIBS += \
        -L../SDL2_image-bin/i686-w64-mingw32/lib \
        #-L../SDL2_image-bin/x86_64-w64-mingw32/lib \
        -L../SDL2-bin/lib/x86 \
        -lSDL2 -lSDL2_image #-lSDL2_ttf -lSDL2_mixer

unix {
    LIBS += `sdl2-config --libs`
}
win32 {
    LIBS += -lmingw32 -mwindows
}

QMAKE_CXXFLAGS += -std=gnu++11
