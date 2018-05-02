#ifndef CREATEPDF_H
#define CREATEPDF_H

#include <QObject>

class CreatePdf : public QObject // класс статичный без конструктора, можно и выкинуть
{
    Q_OBJECT
public:
    static void print(QString *html);

signals:

public slots:
};

#endif // CREATEPDF_H
