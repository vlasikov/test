#ifndef DFT_H
#define DFT_H

#include <qmath.h>
#include "data.h"

extern "C"{

struct Fourier{
    double Re;
    double Im;
    double Amplitude;
    double Phase;
    double Frecuensy;
};

void DFP(int N, double *y, Fourier *F);             // прямое преобразование DFP
void fromDFP(int N, Fourier *F, Fourier *result);   // обратное преобразование DFP

}

#endif // DFT_H
