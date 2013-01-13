TARGET = AprilBrush
;DESTDIR = Release
;MOC_DIR = Release/Build
;OBJECTS_DIR = Release/Build
;RCC_DIR = Release/Build
QT += widgets \
    quick

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    canvas.cpp \
    brushengine.cpp \
    widgets/brushsettings.cpp \
    widgets/inputdevices.cpp \
    widgets/colorpicker.cpp \
    undocommands.cpp \
    widgets/layermanager.cpp

HEADERS += \
    mainwindow.h \
    canvas.h \
    brushengine.h \
    widgets/brushsettings.h \
    widgets/inputdevices.h \
    widgets/colorpicker.h \
    undocommands.h \
    widgets/layermanager.h

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    qml/main.qml

