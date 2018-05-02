#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "createpdf.h"
#include <QMainWindow>
#include <QTimer>
#include <QDate>
#include "qcustomplot/qcustomplot.h" // the header file of QCustomPlot. Don't forget to add it to your project, if you use an IDE, so it gets compiled.

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList< QList<QString> > *table;

private:
    QMenu * fileMenu;
    QAction * newAct;
//    QCustomPlot *customPlot;
    QTimer dataTimer;

    int GetNod(int ch,int zn);
    QString ClipFraction (int ch,int zn);
    void createUI(const QStringList &headers);
    void newGraph(QCustomPlot *customPlot);
private slots:
     void sl_createHtml();
};

#endif // MAINWINDOW_H
