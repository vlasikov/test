#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mif.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QDataStream>


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
    QMenu * fileMenu;
    QToolBar *fileToolBar;
    QAction * openAct;

private slots:
    void sl_open();
    void sl_pushButton_clicked();
};

#endif // MAINWINDOW_H
