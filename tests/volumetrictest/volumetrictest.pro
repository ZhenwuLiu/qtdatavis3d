android|ios {
    error( "This example is not supported for android or ios." )
}

!include( ../tests.pri ) {
    error( "Couldn't find the tests.pri file!" )
}

SOURCES += main.cpp volumetrictest.cpp
HEADERS += volumetrictest.h

QT += widgets

OTHER_FILES += doc/src/* \
               doc/images/*

RESOURCES += \
    volumetrictest.qrc
