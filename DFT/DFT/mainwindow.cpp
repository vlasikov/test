#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    N = 360;

    // Рисуем график
    newGraph();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newGraph() {

    // generate some data:
    QVector<double> x(N), y(N); //
    double Y[N];
    struct Fourier F[N], fromF[N];

    for (int i=0; i<N; i++)
    {
      x[i] = i; //
      y[i] = (sin(10*x[i] *  PI/180.0) + 0.5*sin(100*x[i] *  PI/180.0))/2; //
      Y[i] = y[i];
    }
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel(MPKS_RU("Градусы. (функция y = (sin(10*x) + 0.5*sin(100*x))/2)"));
    ui->customPlot->yAxis->setLabel(MPKS_RU("Функция"));
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(0, N);
    ui->customPlot->yAxis->setRange(-1, 1);
    ui->customPlot->replot();

    //-----------------------------------------------calc DFT (прямое преобразование)
    DFP(N, Y, F);

    for (int i=0; i<N; i++)
    {
      y[i] = F[i].Amplitude;
    }

    // create graph and assign data to it:
    ui->customPlot_2->addGraph();
    ui->customPlot_2->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customPlot_2->xAxis->setLabel(MPKS_RU("Гармоники N"));
    ui->customPlot_2->yAxis->setLabel(MPKS_RU("Амплитуда (Спектр)"));
    // set axes ranges, so we see all data:
    ui->customPlot_2->xAxis->setRange(0, N);
    ui->customPlot_2->yAxis->setRange(0, 0.5);
    ui->customPlot_2->replot();

    //-----------------------------------------------calc fromDFT (обратное преобразование)
    fromDFP(N, F, fromF);

    for (int i=0; i<N; i++)
    {
      y[i] = fromF[i].Amplitude * cos(fromF[i].Phase);
    }

    // create graph and assign data to it:
    ui->customPlot_3->addGraph();
    ui->customPlot_3->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customPlot_3->xAxis->setLabel(MPKS_RU("Градусы"));
    ui->customPlot_3->yAxis->setLabel(MPKS_RU("Функция восстановленная"));
    // set axes ranges, so we see all data:
    ui->customPlot_3->xAxis->setRange(0, N);
    ui->customPlot_3->yAxis->setRange(-1, 1);
    ui->customPlot_3->replot();
}
