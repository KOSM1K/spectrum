//---------------------------------------------------------------------------

#ifndef DSP_methodsH
#define DSP_methodsH
//---------------------------------------------------------------------------
#include <stdint.h>

const int BufLen = 8192;
const int BufMask_p = BufLen - 1;


class MovingAverage
{
public:
        MovingAverage();
       ~MovingAverage();
double  CalcMA(double newSample);
void    ResetMA();

private:
int       Buf_p;
double   *Buf;
int       BufUsage;
double    MA_Val;

};

//--------------------------------------------------
class FIRFilter
{
public:
        FIRFilter(int TapsNum);
       ~FIRFilter();
int16_t CalcFIR(int16_t newSample);
void    LoadCoeffs(const int16_t *Coeffs, int ResultShift);

private:
int       FIRLen;
int       ResShiftVal;
int       SamplesBuf_p;
int       CoeffsBuf_p;
int16_t  *SamplesBuf;
int16_t  *CoeffsBuf;

};
//--------------------------------------------------












#endif
