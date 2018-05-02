#include "formerror.h"

FormError::FormError(QObject *parent) :
    QObject(parent)
{
    newtGetScreenSize(&maxColsScreen, &maxRowsScreen);
    maxColsWin = 80;// maxColsScreen - 6;
    maxRowsWin = 25;//maxRowsScreen - 6;
    //newtOpenWindow(1, 1, maxColsWin, maxRowsWin, "");
    newtCenteredWindow(maxColsWin,maxRowsWin, "");
    form = newtForm(NULL, NULL, 0);

    l1 = newtLabel(1, 1, "error, press any key");
    newtFormAddComponent(form, l1);

//    newtFormSetTimer(form, 1000);
    control();
}

void FormError::control()
{
    struct newtExitStruct exit_status;
//    while(true)
    {
        newtWaitForKey();
        newtFormRun(form,&exit_status);
        if (exit_status.reason==0)                                  // key
        {
            if (exit_status.u.key==NEWT_KEY_F12)
            {
            //    break;
            }
        }
        if (exit_status.reason==1)          // co
        {
        }
        if (exit_status.reason==3)          // timer
        {
        }
    }

    newtFormDestroy(form);
}
