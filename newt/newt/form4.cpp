#include "form4.h"

Form4::Form4(QObject *parent) :
    QObject(parent)
{
    newtGetScreenSize(&maxColsScreen, &maxRowsScreen);
    maxColsWin = 80;//maxColsScreen - 6;
    maxRowsWin = 25;//maxRowsScreen - 6;
    //newtOpenWindow(1, 1, 60, 20, "");
    newtCenteredWindow(maxColsWin,maxRowsWin, "");
    form4 = newtForm(NULL, NULL, 0);

    l1 = newtLabel(1, 0, MPKS_RU("Настройка канала"));
    newtFormAddComponent(form4, l1);
//-------------------------------------------------------------------------
    QString s;
    s.fill('-', maxColsWin-2);
    l2 = newtLabel(1, 1, qPrintable(s));
    newtFormAddComponent(form4, l2);

//    list1 = newtListbox(1, 2, 3, NEWT_LISTBOX_RETURNEXIT | NEWT_FLAG_SCROLL);             // NEWT_FLAG_SCROLL
//    newtListboxSetWidth(list1, maxColsWin-2);
//    newtListboxAppendEntry(list1, MPKS_RU("Режим предварительной настройки"), (void *) 1);
//    newtListboxAppendEntry(list1, MPKS_RU("Редактирования MAC адресов"), (void *) 2);
//    newtListboxAppendEntry(list1, MPKS_RU("Редактирование канального узла"), (void *) 3);
//    newtListboxAppendEntry(list1, MPKS_RU("Настройка канала"), (void *) 4);
//    newtListboxSetCurrent(list1, 0);
//    //newtListboxSetEntry(list1, 2, "qweqwe3");
//    newtFormAddComponent(form4, list1);

    l3 = newtLabel(1, 2, MPKS_RU("канал:"));
    newtFormAddComponent(form4, l3);
    e1 = newtEntry(20, 2, "xx", 2, &scaleVal, 0);
    newtFormAddComponent(form4, e1);

    l4 = newtLabel(1, 3, MPKS_RU("Файл устройства:"));
    newtFormAddComponent(form4, l4);
    e2 = newtEntry(20, 3, "file.ini", 59, &scaleVal, 0);
    newtFormAddComponent(form4, e2);


    ch[0] = newtCheckbox (1, 3, MPKS_RU("Сигнал LL"), ' ', " X", &cbValue);
    newtFormAddComponent(form4, ch[0]);

    ch[1] = newtCheckbox (1, 4, MPKS_RU("сигнал шлейф ЗАС"), ' ', " X", &cbValue);
    newtFormAddComponent(form4, ch[1]);

    ch[2] = newtCheckbox (1, 5, MPKS_RU("шлейф"), ' ', " X", &cbValue);
    newtFormAddComponent(form4, ch[2]);

    ch[3] = newtCheckbox (1, 6, MPKS_RU("HDLC"), ' ', " X", &cbValue);
    newtFormAddComponent(form4, ch[3]);

    l5 = newtLabel(1, 7, MPKS_RU("Скорость:"));
    newtFormAddComponent(form4, l5);
    list1 = newtListbox(20, 7, 1, NEWT_LISTBOX_RETURNEXIT );             // NEWT_FLAG_SCROLL
    newtListboxSetWidth(list1, 9);
    newtListboxAppendEntry(list1, MPKS_RU("   600"), (void *) 1);
    newtListboxAppendEntry(list1, MPKS_RU("1200"), (void *) 2);
    newtListboxAppendEntry(list1, MPKS_RU("2400"), (void *) 3);
    newtListboxAppendEntry(list1, MPKS_RU("4800"), (void *) 4);
    newtListboxSetCurrent(list1, 0);
    //newtListboxSetEntry(list1, 2, "qweqwe3");
    newtFormAddComponent(form4, list1);

    l6 = newtLabel(1, 8, MPKS_RU("Синхронизация:"));
    newtFormAddComponent(form4, l6);
    list2 = newtListbox(20, 8, 1, NEWT_LISTBOX_RETURNEXIT );             // NEWT_FLAG_SCROLL
    newtListboxSetWidth(list2, 24);
    newtListboxAppendEntry(list2, MPKS_RU("синхронный TxC и RxC "), (void *) 1);
    newtListboxAppendEntry(list2, MPKS_RU("синхронный TxC0 и RxC"), (void *) 2);
    newtListboxAppendEntry(list2, MPKS_RU("асинхронный"), (void *) 3);
    newtListboxSetCurrent(list2, 0);
    //newtListboxSetEntry(list1, 2, "qweqwe3");
    newtFormAddComponent(form4, list2);

    b1 = newtButton(maxColsWin/2 - 5 - (16+4), maxRowsWin - 4, MPKS_RU(" < Сохранить >  "));
    newtFormAddComponent(form4, b1);
    b2 = newtButton(maxColsWin/2 + 5, maxRowsWin - 4,          MPKS_RU("< Выход/Отмена >"));
    newtFormAddComponent(form4, b2);

    newtFormSetCurrent(form4, b2);          // фокус на кнопку выхода
}

void Form4::control()
{
    struct newtExitStruct exit_status;
    while(true)
    {
        newtFormRun(form4,&exit_status);
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

    newtFormDestroy(form4);
}
