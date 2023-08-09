//---------------------------------------------------------------------------


#pragma hdrstop

#include "DSP_methods.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

MovingAverage::MovingAverage()
{
  Buf = new double[BufLen];
  Buf_p = 0;
  BufUsage = 0;
  MA_Val = 0;
}

MovingAverage::~MovingAverage()
{
  delete [] Buf;
}

void MovingAverage::ResetMA()
{
  Buf_p = 0;
  BufUsage = 0;
  MA_Val = 0;
}

double MovingAverage::CalcMA(double newSample)
{
  if(BufUsage == BufLen)
       {
          MA_Val = MA_Val - Buf[Buf_p]; // Subtract oldest value
          BufUsage -= 1;
       }
       {
          MA_Val = MA_Val + newSample; // Add newest value
          Buf[Buf_p] = newSample;      // and store it instead the oldest value
          Buf_p = (Buf_p + 1) & BufMask_p;
          BufUsage += 1;
       }
  return MA_Val / BufUsage;
}


//--------------------------------------------
FIRFilter::FIRFilter(int TapsNum)
{
  FIRLen       = TapsNum;
  ResShiftVal  = 16;
  SamplesBuf   = new int16_t[FIRLen];
  CoeffsBuf    = new int16_t[FIRLen];
  SamplesBuf_p = 0;
}

FIRFilter::~FIRFilter()
{
  delete [] SamplesBuf;
  delete [] CoeffsBuf;
}

void FIRFilter::LoadCoeffs(const int16_t *Coeffs, int ResultShift)
{
  for(int i=0; i<FIRLen; i++) CoeffsBuf[i] = Coeffs[i];
  ResShiftVal  = ResultShift;
}


int16_t FIRFilter::CalcFIR(int16_t newSample)
{
  int64_t MACC;
  SamplesBuf[SamplesBuf_p] = newSample; SamplesBuf_p += 1; if(SamplesBuf_p == FIRLen) SamplesBuf_p = 0;
  MACC = 0;
  for(int i=0; i<FIRLen; i++)
    {
      MACC += SamplesBuf[SamplesBuf_p] * CoeffsBuf[i]; // Convolution from old to new samples
      SamplesBuf_p += 1; if(SamplesBuf_p == FIRLen) SamplesBuf_p = 0;
    }
  return (int16_t)(MACC >> ResShiftVal); // drop out least bits
}


