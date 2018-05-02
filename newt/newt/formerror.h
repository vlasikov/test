#ifndef FORMERROR_H
#define FORMERROR_H

#include <newt.h>
#include <QObject>

class FormError : public QObject
{
    Q_OBJECT
public:
    explicit FormError(QObject *parent = 0);

private:
    newtComponent form, l1;
    int maxColsScreen, maxRowsScreen, maxColsWin, maxRowsWin;
    int counter, counter2;

    void control();

signals:

public slots:

};

#endif // FORMERROR_H
