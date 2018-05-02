#include "dft.h"

extern "C"{

void DFP(int N, double *y, struct Fourier *F)
{
    double Arg=0.0;

    for (int k=0; k<N; k++)
    {
        F[k].Re = 0.0;
        F[k].Im = 0.0;

        for (int n=0; n<N; n++)
        {
            Arg = (double)2.0*PI*n*k/N;       //10 * x[i] *  PI/180.0// 10 * 2PI n/N
            F[k].Re +=cos(Arg)*y[n];
            F[k].Im +=sin(Arg)*y[n];
        }

        F[k].Amplitude = (sqrt( F[k].Re * F[k].Re + F[k].Im * F[k].Im )) / N;
        F[k].Phase = atan2(F[k].Im , F[k].Re) / PI * 180.0;
        F[k].Frecuensy = ((N - 1) * (k));
        Arg = 0.0;
    }
}

void fromDFP(int N, struct Fourier *F, struct Fourier *result)
{
    double Arg=0.0;

    for (int i=0; i<N; i++)
    {
        result[i].Re = 0.0;
        result[i].Im = 0.0;
        for (int n=0; n<N; n++)
        {
            Arg = (double)2.0*PI*n*i/N;
            result[i].Re +=F[n].Re*cos(Arg) - F[n].Im*sin(Arg);
            result[i].Im +=F[n].Re*sin(Arg) + F[n].Im*cos(Arg);
        }
        result[i].Amplitude = (sqrt( result[i].Re * result[i].Re + result[i].Im * result[i].Im )) / N;
        result[i].Phase = atan2(result[i].Im , result[i].Re) / PI * 180.0;
        result[i].Frecuensy = ((N - 1) * (i));

    }
}

}
