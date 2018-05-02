#ifndef WINDOW_H
#define WINDOW_H

#include "/usr/include/ncursesw/ncurses.h"
//#include <ncurses.h>
#include <QString>
#include <QList>

class Window
{
public:
    Window(int height_, int width_, int y_, int x_, int color_);
    void update();
    void clear();
    bool printString(QString s, int color);
    void drawBorder();
    virtual int control(int pressed);
    virtual void setTop(bool on);       // всегда переопределять
    bool getTop(void);
    bool tabPress();

    QList <Window*> *subWindowsList;
    WINDOW *name;
    int color;
    bool top;                           //  окошко активно или нет
    bool controlTab;                    // флаг, что окно умеет работать с табом
private:
    int x, y, height, width;

    void draw();
};

#endif // WINDOW_H
