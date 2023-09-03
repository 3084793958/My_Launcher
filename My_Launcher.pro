QT += core gui widgets x11extras
QT += KWindowSystem
LIBS += -lX11 -lXtst -lKF5WindowSystem
TARGET = My_Launcher
TEMPLATE = app
INCLUDEPATH += /usr/include/KF5/KWindowSystem
INCLUDEPATH += /usr/include/xcb

HEADERS += \
    launcher_widget.h \
    mylistview.h \
    myshowtablelabel.h \
    onlydraglistview.h \
    myshowlovelabel.h \
    launcher_fullscreen.h \
    setting_control.h \
    setting_widget.h \
    keyscan.h \
    fullscreenshowtablelabel.h

SOURCES += \
    launcher_widget.cpp \
    main.cpp \
    mylistview.cpp \
    myshowtablelabel.cpp \
    onlydraglistview.cpp \
    myshowlovelabel.cpp \
    launcher_fullscreen.cpp \
    setting_control.cpp \
    setting_widget.cpp \
    keyscan.cpp \
    fullscreenshowtablelabel.cpp

RESOURCES += \
    image.qrc
