#include "form1.h"

Form1::Form1(int maxY, int maxX) : Window(0,0,0,0,11)
{

    b1 = new tButton(3,30,maxY-3-2, maxX/2 - 30 - 5, 10, true);
    b2 = new tButton(3,30,maxY-3-2, maxX/2 + 5, 10, false);

    b3 = new tButton(3,30,maxY-3-20, maxX/2 - 30 - 5, 10, true);
    b4 = new tButton(3,30,maxY-3-20, maxX/2 + 5, 10, false);

    subWindowsList->append(b1);
    subWindowsList->append(b2);

    subWindowsList->append(b3);
    subWindowsList->append(b4);
}
