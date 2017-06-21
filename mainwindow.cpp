/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011-2016 Emanuel Eichhammer                            **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.qcustomplot.com/                          **
**             Date: 13.09.16                                             **
**          Version: 2.0.0-beta                                           **
****************************************************************************/

/************************************************************************************************************
**                                                                                                         **
**  This is the example code for QCustomPlot.                                                              **
**                                                                                                         **
**  It demonstrates basic and some advanced capabilities of the widget. The interesting code is inside     **
**  the "setup(...)Demo" functions of MainWindow.                                                          **
**                                                                                                         **
**  In order to see a demo in action, call the respective "setup(...)Demo" function inside the             **
**  MainWindow constructor. Alternatively you may call setupDemo(i) where i is the index of the demo       **
**  you want (for those, see MainWindow constructor comments). All other functions here are merely a       **
**  way to easily create screenshots of all demos for the website. I.e. a timer is set to successively     **
**  setup all the demos and make a screenshot of the window area and save it in the ./screenshots          **
**  directory.                                                                                             **
**                                                                                                         **
*************************************************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include "gpsdatahandler.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setGeometry(400, 250, 542, 390);
  
  //qDebug()<< gpsValues.size();


  setupDemo(0);

  // 0:  setupScatterPixmapDemo(ui->customPlot); ----------
  // 1:  setupLineStyleDemo(ui->customPlot);---------------
  // 2:  setupDateDemo(ui->customPlot);--------------------
  // 3: setupRealtimeDataDemo(ui->customPlot);------------
  // 4: setupItemDemo(ui->customPlot);---------------------
  // 5: setupStyledDemo(ui->customPlot);-------------------

}

void MainWindow::setupDemo(int demoIndex)
{
  switch (demoIndex)
  {
    case 0:  setupScatterPixmapDemo(ui->customPlot); break;
    case 1:  setupLineStyleDemo(ui->customPlot); break;
    case 2:  setupDateDemo(ui->customPlot); break;
    case 3: setupRealtimeDataDemo(ui->customPlot); break;
    case 4: setupItemDemo(ui->customPlot); break;
    case 5: setupStyledDemo(ui->customPlot); break;
  }
  setWindowTitle("QCustomPlot: "+demoName);
  statusBar()->clearMessage();
  currentDemoIndex = demoIndex;
  ui->customPlot->replot();
}



void MainWindow::setupScatterStyleDemo(QCustomPlot *customPlot)
{
  demoName = "Scatter Style Demo";
  customPlot->legend->setVisible(true);
  customPlot->legend->setFont(QFont("Helvetica", 9));
  customPlot->legend->setRowSpacing(-3);
  QVector<QCPScatterStyle::ScatterShape> shapes;
  shapes << QCPScatterStyle::ssCross;
  shapes << QCPScatterStyle::ssPlus;
  shapes << QCPScatterStyle::ssCircle;
  shapes << QCPScatterStyle::ssDisc;
  shapes << QCPScatterStyle::ssSquare;
  shapes << QCPScatterStyle::ssDiamond;
  shapes << QCPScatterStyle::ssStar;
  shapes << QCPScatterStyle::ssTriangle;
  shapes << QCPScatterStyle::ssTriangleInverted;
  shapes << QCPScatterStyle::ssCrossSquare;
  shapes << QCPScatterStyle::ssPlusSquare;
  shapes << QCPScatterStyle::ssCrossCircle;
  shapes << QCPScatterStyle::ssPlusCircle;
  shapes << QCPScatterStyle::ssPeace;
  shapes << QCPScatterStyle::ssCustom;

  QPen pen;
  // add graphs with different scatter styles:
  for (int i=0; i<shapes.size(); ++i)
  {
    customPlot->addGraph();
    pen.setColor(QColor(qSin(i*0.3)*100+100, qSin(i*0.6+0.7)*100+100, qSin(i*0.4+0.6)*100+100));
    // generate data:
    QVector<double> x(10), y(10);
    for (int k=0; k<10; ++k)
    {
      x[k] = k/10.0 * 4*3.14 + 0.01;
      y[k] = 7*qSin(x[k])/x[k] + (shapes.size()-i)*5;
    }
    customPlot->graph()->setData(x, y);
    customPlot->graph()->rescaleAxes(true);
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName(QCPScatterStyle::staticMetaObject.enumerator(QCPScatterStyle::staticMetaObject.indexOfEnumerator("ScatterShape")).valueToKey(shapes.at(i)));
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    // set scatter style:
    if (shapes.at(i) != QCPScatterStyle::ssCustom)
    {
      customPlot->graph()->setScatterStyle(QCPScatterStyle(shapes.at(i), 10));
    }
    else
    {
      QPainterPath customScatterPath;
      for (int i=0; i<3; ++i)
        customScatterPath.cubicTo(qCos(2*M_PI*i/3.0)*9, qSin(2*M_PI*i/3.0)*9, qCos(2*M_PI*(i+0.9)/3.0)*9, qSin(2*M_PI*(i+0.9)/3.0)*9, 0, 0);
      customPlot->graph()->setScatterStyle(QCPScatterStyle(customScatterPath, QPen(Qt::black, 0), QColor(40, 70, 255, 50), 10));
    }
  }
  // set blank axis lines:
  customPlot->rescaleAxes();
  customPlot->xAxis->setTicks(false);
  customPlot->yAxis->setTicks(false);
  customPlot->xAxis->setTickLabels(false);
  customPlot->yAxis->setTickLabels(false);
  // make top right axes clones of bottom left axes:
  customPlot->axisRect()->setupFullAxesBox();
}

void MainWindow::setupLineStyleDemo(QCustomPlot *customPlot)
{
  demoName = "Line Style Demo";
  customPlot->legend->setVisible(true);
  customPlot->legend->setFont(QFont("Helvetica", 9));
  QPen pen;
  QStringList lineNames;
  lineNames << "lsNone" << "lsLine" << "lsStepLeft" << "lsStepRight" << "lsStepCenter" << "lsImpulse";
  // add graphs with different line styles:
  for (int i=QCPGraph::lsNone; i<=QCPGraph::lsImpulse; ++i)
  {
    customPlot->addGraph();
    pen.setColor(QColor(qSin(i*1+1.2)*80+80, qSin(i*0.3+0)*80+80, qSin(i*0.3+1.5)*80+80));
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName(lineNames.at(i-QCPGraph::lsNone));
    customPlot->graph()->setLineStyle((QCPGraph::LineStyle)i);
    customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    // generate data:
    QVector<double> x(15), y(15);
    for (int j=0; j<15; ++j)
    {
      x[j] = j/15.0 * 5*3.14 + 0.01;
      y[j] = 7*qSin(x[j])/x[j] - (i-QCPGraph::lsNone)*5 + (QCPGraph::lsImpulse)*5 + 2;
    }
    customPlot->graph()->setData(x, y);
    customPlot->graph()->rescaleAxes(true);
  }
  // zoom out a bit:
  customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());
  customPlot->xAxis->scaleRange(1.1, customPlot->xAxis->range().center());
  // set blank axis lines:
  customPlot->xAxis->setTicks(false);
  customPlot->yAxis->setTicks(true);
  customPlot->xAxis->setTickLabels(false);
  customPlot->yAxis->setTickLabels(true);
  // make top right axes clones of bottom left axes:
  customPlot->axisRect()->setupFullAxesBox();
}

void MainWindow::setupScatterPixmapDemo(QCustomPlot *customPlot)
{
  demoName = "Scatter Pixmap Demo";

  // irconde
  //customPlot->axisRect()->setBackground(QPixmap("./solarpanels.jpg"));
  customPlot->addGraph();
  customPlot->graph()->setLineStyle(QCPGraph::lsLine);
  QPen pen;
  pen.setColor(QColor(255, 200, 20, 200));
  pen.setStyle(Qt::DashLine);
  pen.setWidthF(2.5);
  customPlot->graph()->setPen(pen);
  customPlot->graph()->setBrush(QBrush(QColor(255,200,20,70)));
  //irconde
  //customPlot->graph()->setScatterStyle(QCPScatterStyle(QPixmap("./sun.png")));
  // set graph name, will show up in legend next to icon:
  customPlot->graph()->setName("Data from Photovoltaic\nenergy barometer 2011");
  // set data:
  QVector<double> year, value;
  year  << 2005 << 2006 << 2007 << 2008  << 2009  << 2010 << 2011;
  value << 2.17 << 3.42 << 4.94 << 10.38 << 15.86 << 29.33 << 52.1;
  customPlot->graph()->setData(year, value);

  // set title of plot:
  customPlot->plotLayout()->insertRow(0);
  customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, "Regenerative Energies"));
  // axis configurations:
  customPlot->xAxis->setLabel("Year");
  customPlot->yAxis->setLabel("Installed Gigawatts of\nphotovoltaic in the European Union");
  customPlot->xAxis2->setVisible(true);
  customPlot->yAxis2->setVisible(true);
  customPlot->xAxis2->setTickLabels(false);
  customPlot->yAxis2->setTickLabels(false);
  customPlot->xAxis2->setTicks(false);
  customPlot->yAxis2->setTicks(false);
  customPlot->xAxis2->setSubTicks(false);
  customPlot->yAxis2->setSubTicks(false);
  customPlot->xAxis->setRange(2004.5, 2011.5);
  customPlot->yAxis->setRange(0, 52);
  // setup legend:
  customPlot->legend->setFont(QFont(font().family(), 7));
  customPlot->legend->setIconSize(50, 20);
  customPlot->legend->setVisible(true);
  customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);
}

void MainWindow::setupDateDemo(QCustomPlot *customPlot)
{
  demoName = "Date Demo";
  // set locale to english, so we get english month names:
  customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
  // seconds of current time, we'll use it as starting point in time for data:
  double now = QDateTime::currentDateTime().toTime_t();
  srand(8); // set the random seed, so we always get the same random data
  // create multiple graphs:
  for (int gi=0; gi<5; ++gi)
  {
    customPlot->addGraph();
    QColor color(20+200/4.0*gi,70*(1.6-gi/4.0), 150, 150);
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    customPlot->graph()->setPen(QPen(color.lighter(200)));
    customPlot->graph()->setBrush(QBrush(color));
    // generate random walk data:
    QVector<QCPGraphData> timeData(250);
    for (int i=0; i<250; ++i)
    {
      timeData[i].key = now + 24*3600*i;
      if (i == 0)
        timeData[i].value = (i/50.0+1)*(rand()/(double)RAND_MAX-0.5);
      else
        timeData[i].value = qFabs(timeData[i-1].value)*(1+0.02/4.0*(4-gi)) + (i/50.0+1)*(rand()/(double)RAND_MAX-0.5);
    }
    customPlot->graph()->data()->set(timeData);
  }
  // configure bottom axis to show date instead of number:
  QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
  dateTicker->setDateTimeFormat("d. MMMM\nyyyy");
  customPlot->xAxis->setTicker(dateTicker);
  // configure left axis text labels:
  QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
  textTicker->addTick(10, "a bit\nlow");
  textTicker->addTick(50, "quite\nhigh");
  customPlot->yAxis->setTicker(textTicker);
  // set a more compact font size for bottom and left axis tick labels:
  customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
  customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
  // set axis labels:
  customPlot->xAxis->setLabel("Date");
  customPlot->yAxis->setLabel("Random wobbly lines value");
  // make top and right axes visible but without ticks and labels:
  customPlot->xAxis2->setVisible(true);
  customPlot->yAxis2->setVisible(true);
  customPlot->xAxis2->setTicks(false);
  customPlot->yAxis2->setTicks(false);
  customPlot->xAxis2->setTickLabels(false);
  customPlot->yAxis2->setTickLabels(false);
  // set axis ranges to show all data:
  customPlot->xAxis->setRange(now, now+24*3600*249);
  customPlot->yAxis->setRange(0, 60);
  // show legend with slightly transparent background brush:
  customPlot->legend->setVisible(true);
  customPlot->legend->setBrush(QColor(255, 255, 255, 150));
}

void MainWindow::setupRealtimeDataDemo(QCustomPlot *customPlot)
{
  demoName = "Real Time Data Demo";
  
  // include this section to fully disable antialiasing for higher performance:
  /*
  customPlot->setNotAntialiasedElements(QCP::aeAll);
  QFont font;
  font.setStyleStrategy(QFont::NoAntialias);
  customPlot->xAxis->setTickLabelFont(font);
  customPlot->yAxis->setTickLabelFont(font);
  customPlot->legend->setFont(font);
  */
  customPlot->addGraph(); // blue line
  customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
  customPlot->addGraph(); // red line
  customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));

  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  timeTicker->setTimeFormat("%h:%m:%s");
  customPlot->xAxis->setTicker(timeTicker);
  customPlot->axisRect()->setupFullAxesBox();
  customPlot->yAxis->setRange(-1.2, 1.2);
  
  // make left and bottom axes transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
  
  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
  dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::setupItemDemo(QCustomPlot *customPlot)
{
  demoName = "Item Demo";
  
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  QCPGraph *graph = customPlot->addGraph();
  int n = 500;
  double phase = 0;
  double k = 3;
  QVector<double> x(n), y(n);
  for (int i=0; i<n; ++i)
  {
    x[i] = i/(double)(n-1)*34 - 17;
    y[i] = qExp(-x[i]*x[i]/20.0)*qSin(k*x[i]+phase);
  }
  graph->setData(x, y);
  graph->setPen(QPen(Qt::blue));
  graph->rescaleKeyAxis();
  customPlot->yAxis->setRange(-1.45, 1.65);
  customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
  
  // add the bracket at the top:
  QCPItemBracket *bracket = new QCPItemBracket(customPlot);
  bracket->left->setCoords(-8, 1.1);
  bracket->right->setCoords(8, 1.1);
  bracket->setLength(13);
  
  // add the text label at the top:
  QCPItemText *wavePacketText = new QCPItemText(customPlot);
  wavePacketText->position->setParentAnchor(bracket->center);
  wavePacketText->position->setCoords(0, -10); // move 10 pixels to the top from bracket center anchor
  wavePacketText->setPositionAlignment(Qt::AlignBottom|Qt::AlignHCenter);
  wavePacketText->setText("Wavepacket");
  wavePacketText->setFont(QFont(font().family(), 10));
  
  // add the phase tracer (red circle) which sticks to the graph data (and gets updated in bracketDataSlot by timer event):
  QCPItemTracer *phaseTracer = new QCPItemTracer(customPlot);
  itemDemoPhaseTracer = phaseTracer; // so we can access it later in the bracketDataSlot for animation
  phaseTracer->setGraph(graph);
  phaseTracer->setGraphKey((M_PI*1.5-phase)/k);
  phaseTracer->setInterpolating(true);
  phaseTracer->setStyle(QCPItemTracer::tsCircle);
  phaseTracer->setPen(QPen(Qt::red));
  phaseTracer->setBrush(Qt::red);
  phaseTracer->setSize(7);
  
  // add label for phase tracer:
  QCPItemText *phaseTracerText = new QCPItemText(customPlot);
  phaseTracerText->position->setType(QCPItemPosition::ptAxisRectRatio);
  phaseTracerText->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
  phaseTracerText->position->setCoords(1.0, 0.95); // lower right corner of axis rect
  phaseTracerText->setText("Points of fixed\nphase define\nphase velocity vp");
  phaseTracerText->setTextAlignment(Qt::AlignLeft);
  phaseTracerText->setFont(QFont(font().family(), 9));
  phaseTracerText->setPadding(QMargins(8, 0, 0, 0));
  
  // add arrow pointing at phase tracer, coming from label:
  QCPItemCurve *phaseTracerArrow = new QCPItemCurve(customPlot);
  phaseTracerArrow->start->setParentAnchor(phaseTracerText->left);
  phaseTracerArrow->startDir->setParentAnchor(phaseTracerArrow->start);
  phaseTracerArrow->startDir->setCoords(-40, 0); // direction 30 pixels to the left of parent anchor (tracerArrow->start)
  phaseTracerArrow->end->setParentAnchor(phaseTracer->position);
  phaseTracerArrow->end->setCoords(10, 10);
  phaseTracerArrow->endDir->setParentAnchor(phaseTracerArrow->end);
  phaseTracerArrow->endDir->setCoords(30, 30);
  phaseTracerArrow->setHead(QCPLineEnding::esSpikeArrow);
  phaseTracerArrow->setTail(QCPLineEnding(QCPLineEnding::esBar, (phaseTracerText->bottom->pixelPosition().y()-phaseTracerText->top->pixelPosition().y())*0.85));
  
  // add the group velocity tracer (green circle):
  QCPItemTracer *groupTracer = new QCPItemTracer(customPlot);
  groupTracer->setGraph(graph);
  groupTracer->setGraphKey(5.5);
  groupTracer->setInterpolating(true);
  groupTracer->setStyle(QCPItemTracer::tsCircle);
  groupTracer->setPen(QPen(Qt::green));
  groupTracer->setBrush(Qt::green);
  groupTracer->setSize(7);
  
  // add label for group tracer:
  QCPItemText *groupTracerText = new QCPItemText(customPlot);
  groupTracerText->position->setType(QCPItemPosition::ptAxisRectRatio);
  groupTracerText->setPositionAlignment(Qt::AlignRight|Qt::AlignTop);
  groupTracerText->position->setCoords(1.0, 0.20); // lower right corner of axis rect
  groupTracerText->setText("Fixed positions in\nwave packet define\ngroup velocity vg");
  groupTracerText->setTextAlignment(Qt::AlignLeft);
  groupTracerText->setFont(QFont(font().family(), 9));
  groupTracerText->setPadding(QMargins(8, 0, 0, 0));
  
  // add arrow pointing at group tracer, coming from label:
  QCPItemCurve *groupTracerArrow = new QCPItemCurve(customPlot);
  groupTracerArrow->start->setParentAnchor(groupTracerText->left);
  groupTracerArrow->startDir->setParentAnchor(groupTracerArrow->start);
  groupTracerArrow->startDir->setCoords(-40, 0); // direction 30 pixels to the left of parent anchor (tracerArrow->start)
  groupTracerArrow->end->setCoords(5.5, 0.4);
  groupTracerArrow->endDir->setParentAnchor(groupTracerArrow->end);
  groupTracerArrow->endDir->setCoords(0, -40);
  groupTracerArrow->setHead(QCPLineEnding::esSpikeArrow);
  groupTracerArrow->setTail(QCPLineEnding(QCPLineEnding::esBar, (groupTracerText->bottom->pixelPosition().y()-groupTracerText->top->pixelPosition().y())*0.85));
  
  // add dispersion arrow:
  QCPItemCurve *arrow = new QCPItemCurve(customPlot);
  arrow->start->setCoords(1, -1.1);
  arrow->startDir->setCoords(-1, -1.3);
  arrow->endDir->setCoords(-5, -0.3);
  arrow->end->setCoords(-10, -0.2);
  arrow->setHead(QCPLineEnding::esSpikeArrow);
  
  // add the dispersion arrow label:
  QCPItemText *dispersionText = new QCPItemText(customPlot);
  dispersionText->position->setCoords(-6, -0.9);
  dispersionText->setRotation(40);
  dispersionText->setText("Dispersion with\nvp < vg");
  dispersionText->setFont(QFont(font().family(), 10));
  
  // setup a timer that repeatedly calls MainWindow::bracketDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(bracketDataSlot()));
  dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::setupStyledDemo(QCustomPlot *customPlot)
{
  demoName = "Styled Demo";
  
  // prepare data:
  QVector<double> x1(20), y1(20);
  QVector<double> x2(100), y2(100);
  QVector<double> x3(20), y3(20);
  QVector<double> x4(20), y4(20);
  for (int i=0; i<x1.size(); ++i)
  {
    x1[i] = i/(double)(x1.size()-1)*10;
    y1[i] = qCos(x1[i]*0.8+qSin(x1[i]*0.16+1.0))*qSin(x1[i]*0.54)+1.4;
  }
  for (int i=0; i<x2.size(); ++i)
  {
    x2[i] = i/(double)(x2.size()-1)*10;
    y2[i] = qCos(x2[i]*0.85+qSin(x2[i]*0.165+1.1))*qSin(x2[i]*0.50)+1.7;
  }
  for (int i=0; i<x3.size(); ++i)
  {
    x3[i] = i/(double)(x3.size()-1)*10;
    y3[i] = 0.05+3*(0.5+qCos(x3[i]*x3[i]*0.2+2)*0.5)/(double)(x3[i]+0.7)+qrand()/(double)RAND_MAX*0.01;
  }
  for (int i=0; i<x4.size(); ++i)
  {
    x4[i] = x3[i];
    y4[i] = (0.5-y3[i])+((x4[i]-2)*(x4[i]-2)*0.02);
  }
  
  // create and configure plottables:
  QCPGraph *graph1 = customPlot->addGraph();
  graph1->setData(x1, y1);
  graph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
  graph1->setPen(QPen(QColor(120, 120, 120), 2));

  QCPGraph *graph2 = customPlot->addGraph();
  graph2->setData(x2, y2);
  graph2->setPen(Qt::NoPen);
  graph2->setBrush(QColor(200, 200, 200, 20));
  graph2->setChannelFillGraph(graph1);
  
  QCPBars *bars1 = new QCPBars(customPlot->xAxis, customPlot->yAxis);
  bars1->setWidth(9/(double)x3.size());
  bars1->setData(x3, y3);
  bars1->setPen(Qt::NoPen);
  bars1->setBrush(QColor(10, 140, 70, 160));
  
  QCPBars *bars2 = new QCPBars(customPlot->xAxis, customPlot->yAxis);
  bars2->setWidth(9/(double)x4.size());
  bars2->setData(x4, y4);
  bars2->setPen(Qt::NoPen);
  bars2->setBrush(QColor(10, 100, 50, 70));
  bars2->moveAbove(bars1);
  
  // move bars above graphs and grid below bars:
  customPlot->addLayer("abovemain", customPlot->layer("main"), QCustomPlot::limAbove);
  customPlot->addLayer("belowmain", customPlot->layer("main"), QCustomPlot::limBelow);
  graph1->setLayer("abovemain");
  customPlot->xAxis->grid()->setLayer("belowmain");
  customPlot->yAxis->grid()->setLayer("belowmain");

  // set some pens, brushes and backgrounds:
  customPlot->xAxis->setBasePen(QPen(Qt::white, 1));
  customPlot->yAxis->setBasePen(QPen(Qt::white, 1));
  customPlot->xAxis->setTickPen(QPen(Qt::white, 1));
  customPlot->yAxis->setTickPen(QPen(Qt::white, 1));
  customPlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
  customPlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
  customPlot->xAxis->setTickLabelColor(Qt::white);
  customPlot->yAxis->setTickLabelColor(Qt::white);
  customPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  customPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  customPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  customPlot->xAxis->grid()->setSubGridVisible(true);
  customPlot->yAxis->grid()->setSubGridVisible(true);
  customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
  customPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
  customPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
  customPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
  QLinearGradient plotGradient;
  plotGradient.setStart(0, 0);
  plotGradient.setFinalStop(0, 350);
  plotGradient.setColorAt(0, QColor(80, 80, 80));
  plotGradient.setColorAt(1, QColor(50, 50, 50));
  customPlot->setBackground(plotGradient);
  QLinearGradient axisRectGradient;
  axisRectGradient.setStart(0, 0);
  axisRectGradient.setFinalStop(0, 350);
  axisRectGradient.setColorAt(0, QColor(80, 80, 80));
  axisRectGradient.setColorAt(1, QColor(30, 30, 30));
  customPlot->axisRect()->setBackground(axisRectGradient);
  
  customPlot->rescaleAxes();
  customPlot->yAxis->setRange(0, 2);
}

void MainWindow::realtimeDataSlot()
{
  static QTime time(QTime::currentTime());
  // calculate two new data points:
  double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = 0;
  if (key-lastPointKey > 0.002) // at most add point every 2 ms
  {
    // add data to lines:
    ui->customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
    ui->customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
    // rescale value (vertical) axis to fit the current data:
    //ui->customPlot->graph(0)->rescaleValueAxis();
    //ui->customPlot->graph(1)->rescaleValueAxis(true);
    lastPointKey = key;
  }
  // make key axis range scroll with the data (at a constant range size of 8):
  ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
  ui->customPlot->replot();
  
  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
          .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
          , 0);
    lastFpsKey = key;
    frameCount = 0;
  }
}

void MainWindow::bracketDataSlot()
{
  double secs = QCPAxisTickerDateTime::dateTimeToKey(QDateTime::currentDateTime());
  
  // update data to make phase move:
  int n = 500;
  double phase = secs*5;
  double k = 3;
  QVector<double> x(n), y(n);
  for (int i=0; i<n; ++i)
  {
    x[i] = i/(double)(n-1)*34 - 17;
    y[i] = qExp(-x[i]*x[i]/20.0)*qSin(k*x[i]+phase);
  }
  ui->customPlot->graph()->setData(x, y);
  
  itemDemoPhaseTracer->setGraphKey((8*M_PI+fmod(M_PI*1.5-phase, 6*M_PI))/k);
  
  ui->customPlot->replot();
  
  // calculate frames per second:
  double key = secs;
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
          .arg(ui->customPlot->graph(0)->data()->size())
          , 0);
    lastFpsKey = key;
    frameCount = 0;
  }
}

MainWindow::~MainWindow()
{
  delete ui;
}






























