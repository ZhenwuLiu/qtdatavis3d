TEMPLATE = subdirs
SUBDIRS += qmlbars \
           qmlscatter \
           qmlsurface \
           qmlcustominput \
           qmllegend \
           qmlmultigraph \
           qmloscilloscope \
           qmlsurfacelayers \
           qmlaxisformatter

!android:!ios {
    SUBDIRS += bars \
               custominput \
               customproxy \
               itemmodel \
               scatter \
               surface \
               rotations \
               draggableaxes
}

qtHaveModule(multimedia):!android:!ios: SUBDIRS += audiolevels
