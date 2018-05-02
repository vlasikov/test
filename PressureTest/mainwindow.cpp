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

    // Добавляем меню
    newAct = new QAction(tr("Save"), this);
    fileMenu = this->menuBar()->addMenu(tr("File"));
    fileMenu->addAction(newAct);

    // Рисуем график
    newGraph(ui->customPlot);
    ui->customPlot->replot();

    // Создаем внутреннюю таблицу для значений
    table = new QList< QList<QString> >;
    initTable(table);

    // Рисуем таблицу
    this->createUI(QStringList()     << MPKS_RU("Параметр")
                                     << MPKS_RU("Требуемое значение")
                                     << MPKS_RU("Полученное значение")
                                     << MPKS_RU("Результат, соотв./несоотв.")
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
      y[i] = 0.055555556*(atan (x[i]/10.0) * 180.0 / PI); // вычисляем арктангенс
    }
    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel(MPKS_RU("Время, с."));
    customPlot->yAxis->setLabel(MPKS_RU("Давление, кгс/см^2"));
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(0, 300);
    customPlot->yAxis->setRange(0, 5.5);
    customPlot->replot();
}

int GetNod(int ch,int zn) { //Найти НОД
 return (ch ? GetNod(zn%ch,ch) : zn);
 }

QString ClipFraction (int ch,int zn) { //Сократить, если есть НОД>1
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
    ui->tableWidget->setColumnCount(4); // Указываем число колонок
    ui->tableWidget->setShowGrid(true); // Включаем сетку
    // Разрешаем выделение только одного элемента
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем заголовки колонок
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    // Растягиваем последнюю колонку на всё доступное пространство
    //ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    // Скрываем колонку под номером 0
    //ui->tableWidget->hideColumn(0);

    for (int i=0; i<TABLE_V; i++){
        // Вставляем строку
        ui->tableWidget->insertRow(i);
        for (int j=0; j<TABLE_H; j++)
            ui->tableWidget->setItem(i,j, new QTableWidgetItem( (*table)[i].at(j) ));
    }

    // Ресайзим колонки по содержимому
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::sl_createHtml()
{
    QString s1,s2, Html="";
    s1 = ui->tableWidget->item(1, 2)->text();
    s2 = ui->tableWidget->item(2, 1)->text();
    Html +=
            QString("<div align=center>")+
                QString(MPKS_RU("Отчет об испытаниях."))+
            QString("</div>")+
            QString("<div align=left>")+
                QString(MPKS_RU("Тест N "))+ ui->lineEdit->text()+
            QString("</div>")+
            QString("<div align=left>")+
                QString(MPKS_RU("Выполнил "))+ ui->lineEdit_2->text()+
            QString("</div>")+

            QString("<table border=\"1\" width=\"100%\" height=\"100%\" >")+
            QString("<tr>")+
                QString(MPKS_RU("<td>Условие</td>"))+
                QString(MPKS_RU("<td>Требуемое значение</td>"))+
                QString(MPKS_RU("<td>Полученное значение</td>"))+
                QString(MPKS_RU("<td>Результат соотв/несоотв</td>"))+
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
