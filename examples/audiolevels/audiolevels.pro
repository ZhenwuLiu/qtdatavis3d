!include( ../examples.pri ) {
    error( "Couldn't find the examples.pri file!" )
}

TARGET = audiolevels

QT += multimedia

SOURCES += main.cpp \
           audiolevels.cpp \
           audiolevelsiodevice.cpp

HEADERS += audiolevels.h \
           audiolevelsiodevice.h

INSTALLS += target

OTHER_FILES += doc/src/* \
               doc/images/*

