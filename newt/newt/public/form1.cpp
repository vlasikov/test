#include "form1.h"
#include <QDebug>
#include <QTextCodec>

void listCallback__(newtComponent co, void * data)
{
    newtRefresh();
}

Form1::Form1(QObject *parent) :
    QObject(parent)
{
    newtGetScreenSize(&maxColsScreen, &maxRowsScreen);
    maxColsWin = 80;// maxColsScreen - 6;
    maxRowsWin = 25;//maxRowsScreen - 6;
    newtCenteredWindow(maxColsWin,maxRowsWin, "");
    form = newtForm(NULL, NULL, 0);

    l1 = newtLabel(1, 0, MPKS_RU("Настройка МПКС") );
    newtFormAddComponent(form, l1);

    QString s;
    s.fill('-', maxColsWin-2);
    l2 = newtLabel(1, 1, qPrintable(s));
    newtFormAddComponent(form, l2);

    b2 = newtButton(maxColsWin/2 + 5, maxRowsWin - 4,          MPKS_RU("< Выход/Отмена >"));


    list1 = newtListbox(1, 2, 4, NEWT_LISTBOX_RETURNEXIT );             // NEWT_FLAG_SCROLL
    newtListboxSetWidth(list1, maxColsWin-2);
    newtListboxAppendEntry(list1, MPKS_RU("Режим предварительной настройки"), (void *) 1);
    newtListboxAppendEntry(list1, MPKS_RU("Редактирования MAC адресов"), (void *) 2);
    newtListboxAppendEntry(list1, MPKS_RU("Редактирование канального узла"), (void *) 3);
    newtListboxAppendEntry(list1, MPKS_RU("Настройка канала"), (void *) 4);
    newtListboxSetCurrent(list1, 1);
    //newtListboxSetEntry(list1, 2, "");
    newtFormAddComponent(form, list1);

    newtFormAddComponents(form, b2, NULL);

    newtFormAddHotKey(form, NEWT_KEY_F2);
//    control();
}

void Form1::control()
{
    struct newtExitStruct exit_status;
    void *listNumCurrent=0;

//    struct callbackInfo cbis;
//    newtComponentAddCallback(list1, disableCallback, &cbis);

    while(true)
    {        newtDrawForm(form);
        newtFormRun(form,&exit_status);
        if (exit_status.reason==1)                                  // co
        {
            if (exit_status.u.co==b1)
            {  // enter button
            }

            if (exit_status.u.co==b2)
            {  // cancel button
                break;
            }
            if (exit_status.u.co==list1)
            {
                if (newtFormGetCurrent(form) == list1)              // coбытие на списке
                {
                    listNumCurrent =  newtListboxGetCurrent(list1);
                    if (listNumCurrent == (void*)1)
                    {
                        emit sg_message("form1_l1_1");
                    }
                    if (listNumCurrent == (void*)2)
                    {
                        emit sg_message("form1_l1_2");
                    }
                    if (listNumCurrent == (void*)3)
                    {
                        emit sg_message("form1_l1_3");
                    }
                    if (listNumCurrent == (void*)4)
                    {
                        emit sg_message("form1_l1_4");
                    }
                }
            }
        }

        if (exit_status.reason==0)                                  // key
        {
            if (exit_status.u.key==NEWT_KEY_F12)
            {
                break;
            }
            else                 if (exit_status.u.key==NEWT_KEY_ENTER)                  // нажали enter
            {
                if (newtFormGetCurrent(form) == list1)              // coбытие на списке
                {
                    listNumCurrent =  newtListboxGetCurrent(list1);
                    if (listNumCurrent == (void*)1)
                    {
                        emit sg_message("form1_l1_1");
                    }
                    if (listNumCurrent == (void*)2)
                    {
                        emit sg_message("form1_l1_2");
                    }
                    if (listNumCurrent == (void*)3)
                    {
                        emit sg_message("form1_l1_3");
                    }
                }

            }
        }
    }

    newtFormDestroy(form);
    newtFinished();
    exit(-1);
}
