
TEMPLATE = app
TARGET = qt64
DEPENDPATH += .
INCLUDEPATH += .
QT += widgets

# Input
HEADERS += qt64.h
HEADERS += \
    qhexedit2/qhexedit.h \
    qhexedit2/qhexedit_p.h \
    qhexedit2/xbytearray.h \
    qhexedit2/commands.h 

FORMS += Qt64GUI.ui
SOURCES += main.cpp qt64.cpp  \
	qhexedit2/commands.cpp  qhexedit2/qhexedit.cpp  qhexedit2/qhexedit_p.cpp  qhexedit2/xbytearray.cpp


LIBS += ../libc64fc/libc64fc.a
LIBS += `libusb-config --libs`

QMAKE_CXXFLAGS += `libusb-config --cflags`

