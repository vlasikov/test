#include "window.h"

Window::Window(int height_, int width_, int y_, int x_, int color_)
{
    x=x_;
    y=y_;
    height=height_;
    width=width_;
    color=color_;

    subWindowsList = new QList<Window*>;
    top = false;    // по дефолту не активное, при объявление можно указать.
    controlTab = false;

    name = newwin(height, width, y, x);
    scrollok( stdscr, true );                       // прокрутка текста
//    whline (subwindow, ACS_HLINE, 1);
    wattron(name, COLOR_PAIR(color));
    draw();
}

void Window::draw()
{
    QString s;
    for(int i=0; i<width; i++)
    {
        s.append(" ");
    }

    wmove  (name, 0, 0);        // курсор в 0; 0
    for(int i=0; i<height; i++)
        printString(s, color);
//    wborder(name, 0,0, 0,0, 0,0, 0,0);
    wmove  (name, 0, 0);        // курсор в 0; 0
    wrefresh(name);
}

bool Window::printString(QString s, int color)
{
    char c[s.size()+1];
    qstrncpy(c, qPrintable(s), s.size()+1);

    if (name == NULL)                      // bufer
    {
        mvaddstr(y,x,c);
        refresh();
    }
    else                                        // window
    {
//        wborder(name, 0,0, 0,0, 0,0, 0,0);
//        wmove  (name, 0, 0);
        waddstr(name, c);
        wrefresh(name);
    }
    return true;
}

void Window::drawBorder()
{
    wborder(name, 0,0, 0,0, 0,0, 0,0);
    wrefresh(name);
}

void Window::update()
{
    wattron(name, COLOR_PAIR(color - 1));
    draw();
}

void Window::clear()
{
    wattron(name, COLOR_PAIR(color));
    draw();
}

void Window::setTop(bool on)
{
    top = on;
}

bool Window::getTop()
{
    return top;
}

bool Window::tabPress()
{
    if(!subWindowsList->size())
        return 0;

    int j=0;
    QList<Window*>::iterator i;
    for (i = subWindowsList->begin(); i != subWindowsList->end(); ++i)
    {
        Window *a;
        a = (Window*)*i;

        if( a->getTop() )
        {
            a->setTop(false);
            if (j!=subWindowsList->size()-1)
            {
                a=(Window*)((*subWindowsList)[j+1]);
                a->setTop(true);
            }
            else
            {
                a=(Window*)((*subWindowsList)[0]);
                a->setTop(true);
            }
            return 1;
        }
        j++;
    }
    return 1;
}

int Window::control(int pressed)
{
    switch (pressed)
    {
//    case KEY_DOWN  :
//        y++;
//        break;
//    case KEY_UP    :
//        y--;
//        break;
//    case KEY_LEFT  :
//        x--;
//        break;
//    case KEY_RIGHT :
//        x++;
//        break;
    case KEY_F(3):
        tabPress();
        break;
    case (9):               // KEY_TAB
        tabPress();
        break;
    case KEY_F(2) :
        curs_set(0);
//        pressEnter();
        break;
    case (KEY_ENTER):
        tabPress();
        break;
    default:
//        show = false;
        break;
    }
    return 0;
}
