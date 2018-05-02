#include "master.h"

// fazenda/OSPO/SPSF/usc/trunk/usc_mon_newt/
// http://www.pd.infn.it/~saccarol/tutorial.html
// https://en.wikipedia.org/wiki/Newt_%28programming_library%29



Master::Master(QObject *parent) :
    QObject(parent)
{
    dataInit(&UdpData);
    settings = new Settings;

    newtInit();
    newtCls();
    newtGetScreenSize(&UdpData.terminal.maxColsScreen, &UdpData.terminal.maxRowsScreen);


//    const struct newtColors newtDefaultColorPalette = {
//        "white", "blue", 			/* root fg, bg */
//        "black", "lightgray",			/* border fg, bg */
//        "black", "lightgray",			/* window fg, bg */
//        "white", "black",			/* shadow fg, bg */
//        "red", "lightgray",			/* title fg, bg */
//        "lightgray", "red",			/* button fg, bg */
//        "red", "lightgray",			/* active button fg, bg */
//        "lightgray", "blue",			/* checkbox fg, bg */
//        "lightgray", "red",			/* active checkbox fg, bg */
//        "lightgray", "blue",			/* entry box fg, bg */
//        "blue", "lightgray",			/* label fg, bg */
//        "black", "lightgray",			/* listbox fg, bg */
//        "lightgray", "blue",			/* active listbox fg, bg */
//        "black", "lightgray",			/* textbox fg, bg */
//        "lightgray", "red",			/* active textbox fg, bg */
//        "white", "blue",			/* help line */
//        "lightgray", "blue",			/* root text */
//        "blue",					/* scale full */
//        "red",					/* scale empty */
//        "blue", "lightgray",			/* disabled entry fg, bg */
//        "black", "lightgray",			/* compact button fg, bg */
//        "lightgray", "red",			/* active & sel listbox */
//        "black", "brown"			/* selected listbox */
//    };

    const struct newtColors newtDefaultColorPalette = {
        "white", "blue", 			/* root fg, bg */
        "black", "lightgray",			/* border fg, bg */
        "black", "lightgray",			/* window fg, bg */
        "white", "black",			/* shadow fg, bg */
        "red",   "lightgray",			/* title fg, bg */
        "black", "lightgray",			/* button fg, bg */
        "red",   "lightgray",			/* active button fg, bg */
        "black", "lightgray",			/* checkbox fg, bg */
        "lightgray", "red",			/* active checkbox fg, bg */
        "black", "lightgray",			/* entry box fg, bg */
        "blue", "lightgray",			/* label fg, bg */
        "black", "lightgray",			/* listbox fg, bg */
        "lightgray", "blue",			/* active listbox fg, bg */
        "black", "lightgray",			/* textbox fg, bg */
        "lightgray", "red",			/* active textbox fg, bg */
        "white", "blue",			/* help line */
        "lightgray", "blue",			/* root text */
        "blue",					/* scale full */
        "red",					/* scale empty */
        "blue", "lightgray",			/* disabled entry fg, bg */
        "black", "lightgray",			/* compact button fg, bg */
        "lightgray", "red",			/* active & sel listbox */
        "black", "brown"			/* selected listbox */
    };

    newtSetColors(newtDefaultColorPalette);

    f1 = new Form1;
    connect(f1, SIGNAL(sg_message(QString)), this, SLOT(sl_control(QString)));
    f1->control();
}

void Master::sl_control(QString s)
{
    if (QObject::sender() == f1)
    {
        if (s == "form1_l1_1")
        {
            mf3 = new MasterForm3;              // выбрали режим предварительной настройки
            delete mf3;
        }
        if (s == "form1_l1_2")                  // выбрали экран редактирования MAC адресов
        {
            mf2 = new MasterForm2;
            delete mf2;
        }
        if (s == "form1_l1_3")
        {
            formError = new FormError;
            delete formError;
        }
        if (s == "form1_l1_4")                  // выбрали настройки канала
        {
            mf4 = new MasterForm4;
            delete mf4;
        }
    }
}

void Master::initUDP()
{
}



void Master::calcWinSize()
{
    if ( UdpData.terminal.maxColsScreen > UdpData.terminal.minColsWin)
    {
        UdpData.terminal.maxColsWin = UdpData.terminal.maxColsScreen-6;
    }
    else
    {
        UdpData.terminal.maxColsWin = UdpData.terminal.minColsWin;
    }

    if ( UdpData.terminal.maxRowsScreen > UdpData.terminal.minRowsWin)
    {
        UdpData.terminal.maxColsWin = UdpData.terminal.maxRowsScreen-6;
    }
    else
    {
        UdpData.terminal.maxColsWin = UdpData.terminal.minRowsWin;
    }
}

void Master::error(QString er)
{

}
