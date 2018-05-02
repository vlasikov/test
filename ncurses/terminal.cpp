#include "terminal.h"

Terminal::Terminal()
{
    table = new QList< QList<QString> >;
    table->append( QList<QString>());
    table->append( QList<QString>());
    for(int i=0; i<20; i++)
    {
        (*table)[0].append("hello ncursor\n");
        (*table)[1].append("r");
    }


    initscr();                      // Переход в curses-режим
//    raw();                          //Берём управление клавиатурой на себя
    refresh();
    keypad(stdscr, true);           // Включаем режим чтения функциональных клавиш
    start_color ();
    noecho();                       // выключает отображение символов
    getmaxyx(stdscr, y, x);         // Записывает в переменные X и Y максимальных размеров терминала

//    window = newwin(0,0,0,0);
//    wborder(window, 0,0, 0,0, 0,0, 0,0);
//    //wattr_on(lower_frame_window,1,A_REVERSE);
//    //wborder(window, 0,0,0,0,0,0,0,0);
//    init_pair (2,0,1);
//    wattron(window, COLOR_PAIR(2));
//    waddstr(window, "window");
//    refresh();
////    wrefresh(window);

//    subwindow = newwin(10, 20, 7, 2);
//    wborder(subwindow, 0,0, 0,0, 0,0, 0,0);
////    whline (subwindow, ACS_HLINE, 1);
//    init_pair(10, COLOR_BLUE,    COLOR_YELLOW);
//    wattron(subwindow, COLOR_PAIR(10));
//    waddstr(subwindow, "[x] subwindow\n");
//    waddstr(subwindow, "[x] subwindow\n");
//    waddstr(subwindow, "[x] subwindow\n");
//    wrefresh(subwindow);


    init_pair(10, COLOR_BLUE,    COLOR_YELLOW);
    init_pair(11, COLOR_WHITE,    COLOR_WHITE);


    getmaxyx(stdscr, yMax, xMax);         // размер окна
    y = yMax/2;
    x = xMax/2;

    w0 = new Form1(yMax, xMax);
//    w0 = new Window(y, x, 0,  0, 11);
//    w1 = new tButton(3,30,y-3-2, x/2 - 30 - 5, 10);
//    w2 = new tButton(3,30,y-3-2, x/2 + 5, 10);

    topWindow = 0;
    topWindow_old = 0;

    wmove(stdscr, y, x);                    // курсор выставляем
    control();
}

//bool Terminal::printList()
//{
//    QList<QString>::iterator i;

//    int j=0;
//    for (i = (*table)[0].begin(); i != (*table)[0].end(); ++i)
//    {
//        QString s ;

//        s = (*table)[1].at(j);

//        if(s == "r")
//        {
//            wattron(stdscr,COLOR_PAIR(2));
//            printString(NULL, j, 0, *i);
//            wattroff(stdscr,COLOR_PAIR(2));
//        }
//        else
//        {
//            printString(NULL, j, 0, *i);
//        }
//        j++;
//    }
//    return true;
//}

//bool Terminal::printString(QString s)
//{
//    char c[s.size()+1];
//    qstrncpy(c, qPrintable(s), s.size()+1);
//    printw(c);

//    refresh();
//    wrefresh(window);
//    wborder(subwindow, 0,0, 0,0, 0,0, 0,0);
//    refresh();
//    wrefresh(subwindow);
//    //refresh();

//    return true;
//}

//bool Terminal::printString(WINDOW *window, int y, int x, QString s)
//{
//    char c[s.size()+1];
//    qstrncpy(c, qPrintable(s), s.size()+1);

//    if (window == NULL)                      // bufer
//    {
//        mvaddstr(y,x,c);
//        refresh();
//    }
//    else                                        // window
//    {
//        wborder(window, 0,0, 0,0, 0,0, 0,0);
//        wmove  (window, 0, 0);
//        waddstr(window, "subwindow\n");
//        waddstr(window, "subwindowwwwwwwwww\n");
//        wrefresh(window);
//    }
//    return true;
//}


void Terminal::selectString()
{
    QList<QString>::iterator i;
    for (i = (*table)[1].begin(); i != (*table)[1].end(); ++i)
    {
        *i="r";
        //(*table)[1][y] = "r";
    }

    if ((*table)[1].size()>y)
        (*table)[1][y] = "g";
}

void Terminal::updateTopWindow()
{
    switch (topWindow_old) {
    case 0:
//        w0->clear();
        break;
    case 1:
        w1->clear();
        break;
    case 2:
        w2->clear();
        break;
    default:
        break;
    }

    switch (topWindow) {
    case 0:
        w0->update();
        break;
    case 1:
        w1->update();
        break;
    case 2:
        w2->update();
        break;
    default:
        break;
    }
}

void Terminal::pressEnter()
{
    if (topWindow == 1)
    {
        Window w4 (5, 5, 0,  10, 10);
    }
}

void Terminal::control()
{
        int pressed = 0;
        while (pressed != 'e')
        {
            w0->control(pressed);
            bool show = true;
            pressed = wgetch(stdscr);
            switch (pressed)
            {
            case KEY_DOWN  :
                y++;
                break;
            case KEY_UP    :
                y--;
                break;
            case KEY_LEFT  :
                x--;
                break;
            case KEY_RIGHT :
                x++;
                break;

//            case KEY_F(1):
////                printList();
//                break;
            case KEY_F(3):

//                topWindow_old=topWindow;
//                if (topWindow>=2)
//                    topWindow = 0;
//                else
//                    topWindow++;
//                updateTopWindow();
                break;
            case KEY_F(2) :
                pressEnter();
                break;
            default:
                show = false;
                break;
            }
//            selectString();
//            printList();
//            if (show)
//            {
//                //wprintw(stdscr, "%d", c);
//                //wmove(stdscr, y, x);
//                if (ERR == wmove(stdscr, y, x)) {
//                    break;
//                }
//                refresh();
//            }
        }
        endwin();
}
