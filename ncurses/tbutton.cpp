#include "tbutton.h"

tButton::tButton(int height_, int width_, int y_, int x_, int color_, int top) : Window( height_,  width_,  y_,  x_,  color_)
{
    width = width_;
    writeName("-------------\n");

    if (top)
    {
        setTop(true);
    }
}

void tButton::writeName(QString buttonName)
{
    QString s;
    for(int i=0; i<width; i++)
    {
        s.append(" ");
    }

    wmove  (name, 0, 0);        // курсор в 0; 0

    printString(s, 0);
    wattroff(name,COLOR_PAIR(color));
    wattron(name, COLOR_PAIR(0));
    printString(buttonName, 1);
    wattroff(name, COLOR_PAIR(0));
    wattron(name,COLOR_PAIR(color));
    printString(s, 0);

    drawBorder();

//    wborder(name, 0,0, 0,0, 0,0, 0,0);
//    wrefresh(name);
}

void tButton::setTop(bool on)
{
    top = on;
    if (on)
    {
        wmove  (name, 0, 0);        // курсор в 0; 0

        printString("s", 0);
        wattroff(name,COLOR_PAIR(color));
        wattron(name, COLOR_PAIR(11));
        printString("buttonName", 1);
        wattroff(name, COLOR_PAIR(11));
        wattron(name,COLOR_PAIR(color));
        printString("s", 0);

        drawBorder();
    }
}
