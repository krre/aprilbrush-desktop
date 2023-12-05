TARGET = aprilbrush
QT += widgets gui-private
CONFIG += c++20

SOURCES += \
    core/Application.cpp \
    core/OpenRaster.cpp \
    engine/BrushEngine.cpp \
    engine/Layer.cpp \
    engine/undo/BrushCommand.cpp \
    engine/undo/ClearCommand.cpp \
    main.cpp \
    ui/BrushSettings.cpp \
    ui/BrushSlider.cpp \
    ui/Canvas.cpp \
    ui/CanvasTabWidget.cpp \
    ui/ColorPicker.cpp \
    ui/InputDevice.cpp \
    ui/MainWindow.cpp \
    ui/NewImage.cpp \
    ui/Preferences.cpp \
    ui/StandardDialog.cpp

HEADERS += \
    core/Application.h \
    core/CommonTypes.h \
    core/Constants.h \
    core/OpenRaster.h \
    core/Settings.h \
    engine/BrushEngine.h \
    engine/Layer.h \
    engine/undo/BrushCommand.h \
    engine/undo/ClearCommand.h \
    ui/BrushSettings.h \
    ui/BrushSlider.h \
    ui/Canvas.h \
    ui/CanvasTabWidget.h \
    ui/ColorPicker.h \
    ui/InputDevice.h \
    ui/MainWindow.h \
    ui/NewImage.h \
    ui/Preferences.h \
    ui/StandardDialog.h

RESOURCES += \
    resources.qrc

DISTFILES += \
    ../README.md \
    i18n/aprilbrush-ru.ts

TRANSLATIONS = i18n/aprilbrush-ru.ts
