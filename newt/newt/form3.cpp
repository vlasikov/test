#include "form3.h"

void Form3::form3Callback(newtComponent co, void * data)
{

//    for (int i = 0; i < 4; i++)
//            if (newtRadioGetCurrent(rb[0]) == rb[i])
//            {
//                newtRefresh();
//            }

//    struct callbackInfo * cbi = (struct callbackInfo*)data;

//    if (*cbi->state == ' ') {

//    newtEntrySetFlags(cbi->en, NEWT_FLAG_DISABLED, NEWT_FLAGS_RESET);

//    } else {

//    newtEntrySetFlags(cbi->en, NEWT_FLAG_DISABLED, NEWT_FLAGS_SET);

//    }

//    newtRefresh();

}


Form3::Form3(QObject *parent) :
    QObject(parent)
{
    newtGetScreenSize(&maxColsScreen, &maxRowsScreen);
    maxColsWin = 80;//maxColsScreen - 6;
    maxRowsWin = 25;//maxRowsScreen - 6;
    //newtOpenWindow(1, 1, 60, 20, "");
    newtCenteredWindow(maxColsWin,maxRowsWin, "");
    form3 = newtForm(NULL, NULL, 0);

    l1 = newtLabel(1, 0, MPKS_RU("Предварительная настройка канальных узлов (КУ)"));
    newtFormAddComponent(form3, l1);
//-------------------------------------------------------------------------
    QString s;
    s.fill('-', maxColsWin-2);
    l2 = newtLabel(1, 1, qPrintable(s));
    newtFormAddComponent(form3, l2);

    l3 = newtLabel(1, 2, MPKS_RU("Настройка:"));
    newtFormAddComponent(form3, l3);
    rb[0] = newtRadiobutton(13, 2, MPKS_RU("КУ1"), 0, NULL);
    rb[1] = newtRadiobutton(23, 2, MPKS_RU("КУ2"), 0, rb[0]);
    rb[2] = newtRadiobutton(33, 2, MPKS_RU("КУ3"), 0, rb[1]);
    rb[3] = newtRadiobutton(43, 2, MPKS_RU("КУ4"), 0, rb[2]);
    for (int i = 0; i < 4; i++)
    {
        newtFormAddComponent(form3, rb[i]);
        newtComponentAddCallback(rb[i], form3Callback, &cbis);
    }

    l4 = newtLabel(1, 3, MPKS_RU("IP КУ"));
    newtFormAddComponent(form3, l4);
    e1 = newtEntry(20, 3, "xxx.xxx.xxx.xxx", 15, &scaleVal, 0);
    newtFormAddComponent(form3, e1);

    l5 = newtLabel(1, 4, MPKS_RU("Маска подсети"));
    newtFormAddComponent(form3, l5);
    e2 = newtEntry(20, 4, "xxx.xxx.xxx.xxx", 15, &scaleVal, 0);
    newtFormAddComponent(form3, e2);

    l6 = newtLabel(1, 5, MPKS_RU("IP маршрутизатора"));
    newtFormAddComponent(form3, l6);
    e3 = newtEntry(20, 5, "xxx.xxx.xxx.xxx", 15, &scaleVal, 0);
    newtFormAddComponent(form3, e3);

    l7 = newtLabel(1, 6, MPKS_RU("Порты КУ:"));
    newtFormAddComponent(form3, l7);
    e4 = newtEntry(20, 6, "xxxxx", 5, &scaleVal, 0);
    newtFormAddComponent(form3, e4);
    e5 = newtEntry(30, 6, "xxxxx", 5, &scaleVal, 0);
    newtFormAddComponent(form3, e5);
    e6 = newtEntry(40, 6, "xxxxx", 5, &scaleVal, 0);
    newtFormAddComponent(form3, e6);
    e7 = newtEntry(50, 6, "xxxxx", 5, &scaleVal, 0);
    newtFormAddComponent(form3, e7);

    l8 = newtLabel(1, 7, MPKS_RU("IP1 УУ:"));
    newtFormAddComponent(form3, l8);
    e8 = newtEntry(20, 7, "xxx.xxx.xxx.xxx", 15, &scaleVal, 0);
    newtFormAddComponent(form3, e8);

    l9 = newtLabel(1, 8, MPKS_RU("IP2 УУ:"));
    newtFormAddComponent(form3, l9);
    e9 = newtEntry(20, 8, "xxx.xxx.xxx.xxx", 15, &scaleVal, 0);
    newtFormAddComponent(form3, e9);

    l10 = newtLabel(1, 9, MPKS_RU("IP3 УУ:"));
    newtFormAddComponent(form3, l10);
    e10 = newtEntry(20, 9, "xxx.xxx.xxx.xxx", 15, &scaleVal, 0);
    newtFormAddComponent(form3, e10);

    l11 = newtLabel(1, 10, MPKS_RU("IP4 УУ:"));
    newtFormAddComponent(form3, l11);
    e11 = newtEntry(20, 10, "xxx.xxx.xxx.xxx", 15, &scaleVal, 0);
    newtFormAddComponent(form3, e11);

    l12 = newtLabel(1, 11, MPKS_RU("Порты УУ:"));
    newtFormAddComponent(form3, l12);
    e12 = newtEntry(20, 11, "xxxxx", 5, &scaleVal, 0);
    newtFormAddComponent(form3, e12);
    e13 = newtEntry(30, 11, "xxxxx", 5, &scaleVal, 0);
    newtFormAddComponent(form3, e13);
    e14 = newtEntry(40, 11, "xxxxx", 5, &scaleVal, 0);
    newtFormAddComponent(form3, e14);
    e15 = newtEntry(50, 11, "xxxxx", 5, &scaleVal, 0);
    newtFormAddComponent(form3, e15);

    l12 = newtLabel(1, 12, MPKS_RU("MAC КУ:"));
    newtFormAddComponent(form3, l12);
    e16 = newtEntry(20, 12, "xx:xx:xx:xx:xx:xx", 17, &scaleVal, 0);
    newtFormAddComponent(form3, e16);


    b1 = newtButton(maxColsWin/2 - 5 - (16+4), maxRowsWin - 4, MPKS_RU(" < Сохранить >  "));
    newtFormAddComponent(form3, b1);
    b2 = newtButton(maxColsWin/2 + 5, maxRowsWin - 4,          MPKS_RU("< Выход/Отмена >"));
    newtFormAddComponent(form3, b2);

    newtFormSetCurrent(form3, b2);          // фокус на кнопку выхода
}

void Form3::control()
{
    struct newtExitStruct exit_status;
    while(true)
    {
        newtFormRun(form3,&exit_status);
        if (exit_status.reason==1)          // co
        {
            if (exit_status.u.co==b1)       // save button
            {
                emit sg_message("form3_b1_save");
            }
            if (exit_status.u.co==b2)       // cancel button
            {
                break;
            }
        }
    }

    newtFormDestroy(form3);
}
