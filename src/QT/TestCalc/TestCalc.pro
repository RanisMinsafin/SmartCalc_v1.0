QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../s21_parser.c \
    ../../s21_stack.c \
    ../../s21_smartcalc.c \
    ../../s21_credit.c \
    ../../s21_deposit.c \
    creditwindow.cpp \
    depositwindow.cpp \
    graphwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../../s21_parser.h \
    ../../s21_stack.h \
    ../../s21_smartcalc.h \
    ../../s21_credit.h \
    ../../s21_deposit.h \
    creditwindow.h \
    depositwindow.h \
    graphwindow.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    creditwindow.ui \
    depositwindow.ui \
    graphwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
