#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "qcustomplot_lib/qcustomplot.h"
#include "gpsdatahandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  
  void setupDemo();
  void setupPlot(QCustomPlot *customPlot);

  
private:

  Ui::MainWindow *ui;
  gpsdatahandler *gpsHandler;

};

#endif // MAINWINDOW_H
