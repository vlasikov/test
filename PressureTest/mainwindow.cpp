#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ��������� ����
    newAct = new QAction(tr("Save"), this);
    fileMenu = this->menuBar()->addMenu(tr("File"));
    fileMenu->addAction(newAct);

    // ������ ������
    newGraph(ui->customPlot);
    ui->customPlot->replot();

    // ������� ���������� ������� ��� ��������
    table = new QList< QList<QString> >;
    initTable(table);

    // ������ �������
    this->createUI(QStringList()     << MPKS_RU("��������")
                                     << MPKS_RU("��������� ��������")
                                     << MPKS_RU("���������� ��������")
                                     << MPKS_RU("���������, �����./�������.")
                   );

    QDate dateToday = QDate::currentDate();
    ui->lineEdit_3->setText(dateToday.toString(("dd/MM/yyyy")));

    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(sl_createHtml()));
}


//extern "C"{
//     int *c = new int[10];
// }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newGraph(QCustomPlot *customPlot) {

    // generate some data:
    QVector<double> x(101.0), y(101.0); // initialize with entries 0..100
    for (int i=0; i<101; i++)
    {
      x[i] = i*3; // x goes from -1 to 1
      y[i] = 0.055555556*(atan (x[i]/10.0) * 180.0 / PI); // ��������� ����������
    }
    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel(MPKS_RU("�����, �."));
    customPlot->yAxis->setLabel(MPKS_RU("��������, ���/��^2"));
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(0, 300);
    customPlot->yAxis->setRange(0, 5.5);
    customPlot->replot();
}

int GetNod(int ch,int zn) { //����� ���
 return (ch ? GetNod(zn%ch,ch) : zn);
 }

QString ClipFraction (int ch,int zn) { //���������, ���� ���� ���>1
 int nod = GetNod(ch,zn);
 if (nod>1) { ch/=nod; zn/=nod; }
 QString result;
 if (ch==0) result.setNum(0);
 else if (ch==zn) result.setNum(1);
 else if (zn==1) result.setNum(ch);
 else result = QString("%1/%2").arg(ch).arg(zn);
 return result;
}

void MainWindow::createUI(const QStringList &headers)
{
    ui->tableWidget->setColumnCount(4); // ��������� ����� �������
    ui->tableWidget->setShowGrid(true); // �������� �����
    // ��������� ��������� ������ ������ ��������
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // ��������� ��������� ���������
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // ������������� ��������� �������
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    // ����������� ��������� ������� �� �ӣ ��������� ������������
    //ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    // �������� ������� ��� ������� 0
    //ui->tableWidget->hideColumn(0);

    for (int i=0; i<TABLE_V; i++){
        // ��������� ������
        ui->tableWidget->insertRow(i);
        for (int j=0; j<TABLE_H; j++)
            ui->tableWidget->setItem(i,j, new QTableWidgetItem( (*table)[i].at(j) ));
    }

    // �������� ������� �� �����������
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::sl_createHtml()
{
    QString s1,s2, Html="";
    s1 = ui->tableWidget->item(1, 2)->text();
    s2 = ui->tableWidget->item(2, 1)->text();
    Html +=
            QString("<div align=center>")+
                QString(MPKS_RU("����� �� ����������."))+
            QString("</div>")+
            QString("<div align=left>")+
                QString(MPKS_RU("���� N "))+ ui->lineEdit->text()+
            QString("</div>")+
            QString("<div align=left>")+
                QString(MPKS_RU("�������� "))+ ui->lineEdit_2->text()+
            QString("</div>")+

            QString("<table border=\"1\" width=\"100%\" height=\"100%\" >")+
            QString("<tr>")+
                QString(MPKS_RU("<td>�������</td>"))+
                QString(MPKS_RU("<td>��������� ��������</td>"))+
                QString(MPKS_RU("<td>���������� ��������</td>"))+
                QString(MPKS_RU("<td>��������� �����/�������</td>"))+
            QString("</tr>")+
            QString("<tr>")+
                QString("<td>") + ui->tableWidget->item(0, 0)->text() + QString("</td>")+
                QString("<td>") + ui->tableWidget->item(0, 1)->text() + QString("</td>")+
                QString("<td>") + ui->tableWidget->item(0, 2)->text() + QString("</td>")+
                QString("<td>") + ui->tableWidget->item(0, 3)->text() + QString("</td>")+
            QString("</tr>")+
            QString("<tr>")+
                QString("<td>") + ui->tableWidget->item(1, 0)->text() + QString("</td>")+
                QString("<td>") + ui->tableWidget->item(1, 1)->text() + QString("</td>")+
                QString("<td>") + ui->tableWidget->item(1, 2)->text() + QString("</td>")+
                QString("<td>") + ui->tableWidget->item(1, 3)->text() + QString("</td>")+
            QString("</tr>")+
            QString("<tr>")+
                QString("<td>") + ui->tableWidget->item(2, 0)->text() + QString("</td>")+
                QString("<td>") + ui->tableWidget->item(2, 1)->text() + QString("</td>")+
                QString("<td>") + ui->tableWidget->item(2, 2)->text() + QString("</td>")+
                QString("<td>") + ui->tableWidget->item(2, 3)->text() + QString("</td>")+
            QString("</tr>")+
            QString("<tr>")+
                QString("<td>") + ui->tableWidget->item(3, 0)->text() + QString("</td>")+
                QString("<td>") + ui->tableWidget->item(3, 1)->text() + QString("</td>")+
                QString("<td>") + ui->tableWidget->item(3, 2)->text() + QString("</td>")+
                QString("<td>") + ui->tableWidget->item(3, 3)->text() + QString("</td>")+
            QString("</tr>")+
            QString("<tr>")+
                QString("<td>") + ui->tableWidget->item(4, 0)->text() + QString("</td>")+
                QString("<td>") + ui->tableWidget->item(4, 1)->text() + QString("</td>")+
                QString("<td>") + ui->tableWidget->item(4, 2)->text() + QString("</td>")+
                QString("<td>") + ui->tableWidget->item(4, 3)->text() + QString("</td>")+
            QString("</tr>")+
            QString("</table>");

    CreatePdf::print(&Html);
}
