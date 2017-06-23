#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include "gpsdatahandler.h"

#define _WIDTH  128
#define _HEIGHT 128

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{

  ui->setupUi(this);
  setGeometry(400, 250, _WIDTH, _HEIGHT);

  this->gpsHandler = new gpsdatahandler();
  this->gpsHandler->computeDistAlt();
  setupDemo();

}

void MainWindow::setupDemo()
{
  setupPlot(ui->customPlot);
  setWindowTitle("distance-altitude graph");
  statusBar()->clearMessage();
  ui->customPlot->replot();
}

void MainWindow::setupPlot(QCustomPlot *customPlot)
{
    QVector<double> *x = this->gpsHandler->getDistanceData();
    QVector<double> *y = this->gpsHandler->getAltitudeData();

    QColor plotColor(75, 75, 75, 255);
    QColor backColor(175, 175, 175, 255);

    customPlot->addGraph();
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    customPlot->graph()->setPen(QPen(plotColor.lighter(200)));
    customPlot->graph()->setBrush(QBrush(plotColor));
    customPlot->setBackground(backColor);
    customPlot->xAxis->setVisible(false);
    customPlot->graph(0)->setData(*x, *y);
    customPlot->graph(0)->rescaleAxes();

}

MainWindow::~MainWindow()
{
  delete ui;
}






























