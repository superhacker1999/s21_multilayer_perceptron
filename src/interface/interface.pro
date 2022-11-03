QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../code/layer.cc \
    ../code/network.cc \
    ../code/neuron.cc \
    ../controller/controller.cc \
    ../helpers/datahandler.cc \
    ../helpers/parser.cc \
    main.cpp \
    painter.cpp \
    scene.cpp

HEADERS += \
    ../controller/controller.h \
    ../helpers/datahandler.h \
    ../helpers/parser.h \
    ../includes/layer.h \
    ../includes/network.h \
    ../includes/neuron.h \
    painter.h \
    scene.h

FORMS += \
    painter.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
 ../weights26640x100x005.txt
