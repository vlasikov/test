#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qcustomplot/qcustomplot.h" // the header file of QCustomPlot. Don't forget to add it to your project, if you use an IDE, so it gets compiled.
#include "data.h"
#include "dft.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void newGraph();

private:
    Ui::MainWindow *ui;
    int N;
};

#endif // MAINWINDOW_H
