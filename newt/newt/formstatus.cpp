#include "formstatus.h"

FormStatus::FormStatus(QObject *parent) :
    QObject(parent)
{
    newtGetScreenSize(&maxColsScreen, &maxRowsScreen);
    maxColsWin = 80;// maxColsScreen - 6;
    maxRowsWin = 25;//maxRowsScreen - 6;
    //newtOpenWindow(2, 2, maxColsWin, maxRowsWin, "");
    newtCenteredWindow(maxColsWin,maxRowsWin, "");
    form = newtForm(NULL, NULL, 0);

    l1 = newtLabel(1, 0, MPKS_RU("информация") );
    newtFormAddComponent(form, l1);

    QString s;
    s.fill('-', maxColsWin-2);
    l2 = newtLabel(1, 1, qPrintable(s));
    newtFormAddComponent(form, l2);

    b2 = newtButton(maxColsWin/2 + 5, maxRowsWin - 4,          MPKS_RU("< Выход/Отмена >"));


    list1 = newtListbox(1, 2, 15, NEWT_LISTBOX_RETURNEXIT );             // NEWT_FLAG_SCROLL
    newtListboxSetWidth(list1, maxColsWin-2);
    newtListboxSetCurrent(list1, 1);
    newtFormAddComponent(form, list1);

    newtFormAddComponents(form, b2, NULL);

    newtFormAddHotKey(form, NEWT_KEY_F2);
}

void FormStatus::control()
{
    struct newtExitStruct exit_status;
    void *listNumCurrent=0;

    while(true)
    { //       newtDrawForm(form);
        newtFormRun(form,&exit_status);
        if (exit_status.reason==1)                                  // co
        {
            if (exit_status.u.co==b2)
            {  // cancel button
                break;
            }
        }
    }

    newtFormDestroy(form);
}
