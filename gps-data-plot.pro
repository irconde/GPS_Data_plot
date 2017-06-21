#
#  QCustomPlot Plot Examples
#

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = plot-examples
TEMPLATE = app

SOURCES += main.cpp\
           mainwindow.cpp \
    qcustomplot_lib/qcustomplot.cpp \
    gpsdatahandler.cpp

HEADERS  += mainwindow.h \
    qcustomplot_lib/qcustomplot.h \
    gpsdatahandler.h

FORMS    += mainwindow.ui

