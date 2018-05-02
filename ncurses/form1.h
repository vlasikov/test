#ifndef FORM1_H
#define FORM1_H

#include "window.h"
#include "tbutton.h"

class Form1 : public Window
{
public:
    Form1(int maxY, int maxX);
//    virtual int control(int pressed);
private:
    Window *b1, *b2, *b3, *b4;
    int subWindows;
};

#endif // FORM1_H
