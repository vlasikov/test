#ifndef TBUTTON_H
#define TBUTTON_H

#include "window.h"
//#include "form1.h"
#include <QString>

class tButton : public Window
{
public:
    tButton(int height_, int width_, int y_, int x_, int color_, int top);
    void writeName(QString buttonName);

private:
//    WINDOW name;
    int width;
    void setTop(bool on);
};

#endif // TBUTTON_H
