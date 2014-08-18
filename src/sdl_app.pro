TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += boardanimationstate.cpp \
            board.cpp \
            boardidlestate.cpp \
            boardstate.cpp \
            game.cpp \
            gem.cpp \
            main.cpp \
            object.cpp \
            texturemanager.cpp \
            utilities.cpp \
            world.cpp \


HEADERS += boardanimationstate.h \
            board.h \
            boardidlestate.h \
            boardstate.h \
            game.h \
            gem.h \
            object.h \
            texturemanager.h \
            utilities.h \
            world.h \


LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer `sdl2-config --libs`

QMAKE_CXXFLAGS += -std=gnu++11
