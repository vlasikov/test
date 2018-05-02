#include "form2.h"

// Экран Редактирования MAC адресов

Form2 *pForm2;

int entryEmptyFilter(newtComponent entry, void * data, int ch, int cursor)
{
    QString s;
    s = newtEntryGetValue(entry);

    pForm2->sendSignal();
    return ch;
}

Form2::Form2(QObject *parent) :
    QObject(parent)
{
    pForm2 = this;
    initMAC();
    calcIP();

    newtGetScreenSize(&maxColsScreen, &maxRowsScreen);
    maxColsWin = 80;//maxColsScreen - 6;
    maxRowsWin = 25;//maxRowsScreen - 6;
    newtCenteredWindow(maxColsWin,maxRowsWin, "");
    form2 = newtForm(NULL, NULL, 0);

    l1 = newtLabel(1, 0, MPKS_RU("Редактирования MAC адресов"));
    newtFormAddComponent(form2, l1);
//-------------------------------------------------------------------------
    QString s;
    s.fill('-', maxColsWin-2);
    l2 = newtLabel(1, 1, qPrintable(s));
    newtFormAddComponent(form2, l2);

    l3 = newtLabel(1, 2, MPKS_RU("Канальный узел 1"));
    newtFormAddComponent(form2, l3);
    l22 = newtLabel(20, 2, MPKS_RU("connect"));
    newtFormAddComponent(form2, l22);
//    l26 = newtLabel(30, 2, MPKS_RU(""));
//    newtFormAddComponent(form2, l26);
    l4 = newtLabel(1, 3, "IP");
    newtFormAddComponent(form2, l4);
    l5 = newtLabel(7, 3, qPrintable(IP1));
    newtFormAddComponent(form2, l5);
    l6 = newtLabel(1, 4, "MAC");
    newtFormAddComponent(form2, l6);
    e1 = newtEntry(7, 4, qPrintable(MAC1), 17, &scaleVal, 0);
    newtEntrySetFilter(e1, entryEmptyFilter, NULL);
//    newtEntrySetColors(e1, NEWT_COLORSET_WINDOW, NEWT_COLORSET_WINDOW);
    newtFormAddComponent(form2, e1);
//-------------------------------------------------------------------------
    l7 = newtLabel(1, 5, qPrintable(s));
    newtFormAddComponent(form2, l7);

    l8 = newtLabel(1, 6, MPKS_RU("Канальный узел 2"));
    newtFormAddComponent(form2, l8);
    l23 = newtLabel(20, 6, MPKS_RU("connect"));
    newtFormAddComponent(form2, l23);
//    l27 = newtLabel(30, 6, MPKS_RU("результат сравниения"));
//    newtFormAddComponent(form2, l27);
    l9 = newtLabel(1, 7, "IP");
    newtFormAddComponent(form2, l9);
    l10 = newtLabel(7, 7, qPrintable(IP1));
    newtFormAddComponent(form2, l10);
    l11 = newtLabel(1, 8, "MAC");
    newtFormAddComponent(form2, l11);
    e2 = newtEntry(7, 8, qPrintable(MAC2), 20, &scaleVal, 0);
//    newtEntrySetColors(e1, NEWT_COLORSET_WINDOW, NEWT_COLORSET_WINDOW);
    newtFormAddComponent(form2, e2);
//-------------------------------------------------------------------------
    l12 = newtLabel(1, 9, qPrintable(s));
    newtFormAddComponent(form2, l12);

    l13 = newtLabel(1, 10, MPKS_RU("Канальный узел 3"));
    newtFormAddComponent(form2, l13);
    l24 = newtLabel(20, 10, MPKS_RU("connect"));
    newtFormAddComponent(form2, l24);
//    l28 = newtLabel(30, 10, MPKS_RU("результат сравниения"));
//    newtFormAddComponent(form2, l28);
    l14 = newtLabel(1, 11, "IP");
    newtFormAddComponent(form2, l14);
    l15 = newtLabel(7, 11, qPrintable(IP1));
    newtFormAddComponent(form2, l15);
    l16 = newtLabel(1, 12, "MAC");
    newtFormAddComponent(form2, l16);
    e3 = newtEntry(7, 12, qPrintable(MAC1), 17, &scaleVal, 0);
//    newtEntrySetColors(e1, NEWT_COLORSET_WINDOW, NEWT_COLORSET_WINDOW);
    newtFormAddComponent(form2, e3);
//-------------------------------------------------------------------------
    l17 = newtLabel(1, 13, qPrintable(s));
    newtFormAddComponent(form2, l17);

    l18 = newtLabel(1, 14, MPKS_RU("Канальный узел 4"));
    newtFormAddComponent(form2, l18);
    l25 = newtLabel(20, 14, MPKS_RU("connect"));
    newtFormAddComponent(form2, l25);
//    l29 = newtLabel(30, 14, MPKS_RU("результат сравниения"));
//    newtFormAddComponent(form2, l29);
    l19 = newtLabel(1, 15, "IP");
    newtFormAddComponent(form2, l19);
    l20 = newtLabel(7, 15, qPrintable(IP1));
    newtFormAddComponent(form2, l20);
    l21 = newtLabel(1, 16, "MAC");
    newtFormAddComponent(form2, l21);
    e4 = newtEntry(7, 16, qPrintable(MAC1), 18, &scaleVal, 0);
//    newtEntrySetColors(e1, NEWT_COLORSET_WINDOW, NEWT_COLORSET_WINDOW);
    newtEntrySetFilter(e4, entryHexFilter, NULL);
    newtFormAddComponent(form2, e4);
//    newtComponentAddCallback(e4, disableCallback, &cbis);
//-------------------------------------------------------------------------
    ch1 = newtCheckbox (1, 18, MPKS_RU("Выполнить инициализаию настроек"), ' ', " X", &cbValue);
    newtFormAddComponent(form2, ch1);

    b1 = newtButton(maxColsWin/2 - 5 - (16+4), maxRowsWin - 4, MPKS_RU(" < Сохранить >  "));
    newtFormAddComponent(form2, b1);
    b2 = newtButton(maxColsWin/2 + 5, maxRowsWin - 4,          MPKS_RU("< Выход/Отмена >"));
    newtFormAddComponent(form2, b2);

//    scroll = newtVerticalScrollbar(maxColsWin-1, 0, 10, 0, 1);
//    newtFormAddComponents(form2, scroll, NULL);


    newtFormSetCurrent(form2, b2);          // фокус на кнопку выхода

}

void Form2::control()
{
    struct newtExitStruct exit_status;
    while(true)
    {
        newtFormRun(form2,&exit_status);    // co
        if (exit_status.reason==1)
        {
            if (exit_status.u.co==b1)       // save button
            {
                emit sg_message("form2_b1_save");
            }
            if (exit_status.u.co==b2)       // cancel button
            {
                break;
            }
        }
    }

    newtFormDestroy(form2);
}


void Form2::initMAC()
{
    MAC1 = "XX:XX:XX:XX:XX:XX";
    MAC2 = "XX:XX:XX:XX:XX:XX";
    MAC3 = "XX:XX:XX:XX:XX:XX";
    MAC4 = "XX:XX:XX:XX:XX:XX";
}

void Form2::calcIP()
{
    IP1 = "XXX.XXX.XXX.XXX";
    IP2 = "XXX.XXX.XXX.XXX";
    IP3 = "XXX.XXX.XXX.XXX";
    IP4 = "XXX.XXX.XXX.XXX";
}

void Form2::sendSignal()
{
    initMAC();
    emit sg_message("empty");
}
