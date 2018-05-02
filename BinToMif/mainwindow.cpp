

#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);

    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(openAct);

    connect(openAct, SIGNAL(triggered()), this, SLOT(sl_open()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(sl_pushButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sl_open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "./", tr("Binary (*.bin)"));
    if (fileName.size())
    {
        ui->lineEdit_2->setText(fileName);
    }

    else
    {
        ui->lineEdit_2->setText(trUtf8(""));
    }

}

void MainWindow::sl_pushButton_clicked()
{
    int N = ui->comboBox->currentText().toInt();
    int Width = ui->comboBox_2->currentText().toInt();;
    int Depth = ui->lineEdit->text().toInt();
    QString fileName = ui->lineEdit_2->text();


    MIF mif;
    mif.create(N, Width, Depth, fileName);
}
