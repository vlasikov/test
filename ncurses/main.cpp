#include <QCoreApplication>
//#include <ncurses.h>
#include "terminal.h"
#include "/usr/include/ncursesw/ncurses.h"

#include <QList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Terminal t;

    return a.exec();
}
