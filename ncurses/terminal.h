#ifndef TERMINAL_H
#define TERMINAL_H

#include "window.h"
#include "tbutton.h"
#include "form1.h"
//#include <ncurses.h>
#include "/usr/include/ncursesw/ncurses.h"
#include <QList>
#include <QString>

class Terminal
{
public:
    Terminal();

    Form1 *w0;
private:
    WINDOW *window, *subwindow;
    tButton *w1, *w2;
    QList<QString> *list, *list2;
    QList< QList<QString> > *table;
    QString title;
    int x,y,xMax,yMax;
    int topWindow, topWindow_old;

    void selectString();
//    bool printList();
//    bool printString(QString s);
//    bool printString(WINDOW *window, int, int, QString s);
    void printTitle();
    void control();
    void pressTab();
    void updateTopWindow();
    void pressEnter();
    int  tabCounter;
};

#endif // TERMINAL_H
