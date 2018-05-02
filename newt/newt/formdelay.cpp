#include "formdelay.h"
#include <QCoreApplication>

FormDelay::FormDelay(QObject *parent) :
    QObject(parent)
{
    counter = 0;
    counter2 = 0;
    newtGetScreenSize(&maxColsScreen, &maxRowsScreen);

    maxColsWin = 80;
    maxRowsWin = 25;
    newtCenteredWindow(maxColsWin,maxRowsWin, "");
    formDelay = newtForm(NULL, NULL, 0);

    l1 = newtLabel(maxColsWin/2, maxRowsWin/2, "");
    newtFormAddComponent(formDelay, l1);

    newtFormSetTimer(formDelay, 20);
}

void FormDelay::control()
{
    struct newtExitStruct exit_status;
    while(true)
    {
        newtFormRun(formDelay,&exit_status);
        if (exit_status.reason==1)          // co
        {
        }
        if (exit_status.reason==3)          // timer
        {
            QCoreApplication::processEvents();

            spinner();
            counter2 ++;
            if (counter2 >= 20)
                break;
        }
    }

    newtFormDestroy(formDelay);
}

void FormDelay::spinner()
{
    const char *spinner = "-\\|/";
    QString s;
    s = spinner[counter];
    counter++;
    if (counter >= 4)
        counter = 0;

    newtLabelSetText(l1, qPrintable(s));
}
