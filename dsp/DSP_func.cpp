//---------------------------------------------------------------------------


#pragma hdrstop

#include "DSP_func.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

int CorrelateVectors(int16_t *EbufI, int16_t *EbufQ, int16_t *DbufI, int16_t *DbufQ, int Len, int16_t *RbufI, int16_t *RbufQ)
{
  int i, L, N;
  for(i=0; i<Len; i++)
    {  // calculate correlation between new and delayed samples
        // RbufI[i] = EbufI[i]*DbufI[i] + EbufQ[i]*DbufQ[i];
        // RbufQ[i] = EbufI[i]*DbufQ[i] - EbufQ[i]*DbufI[i];
        cmplxDSPmult(EbufI[i], EbufQ[i], DbufI[i], DbufQ[i], RbufI[i], RbufQ[i]);
    }
  return 0;
}


void bin_reverse(cfloat* data, int length)
{
  cfloat tmp;
  int i, j, k;

    for (j = 0, i = 0; i < length - 1; i++)
    {
        if (i < j)
        {
            tmp = data[j];
            data[j] = data[i];
            data[i] = tmp;
        }
        k = length / 2;
        while (k <= j)
        {
            j -= k;
            k >>= 1;
        }
        j += k;
    }
}

 cfloat wf[65536 / 2];
 cfloat wi[65536 / 2];

void fft_basis(int len)
{
  int i;
  int w_len = len >> 1;
  float w = (M_PI) / w_len;
    for (i = 0; i < w_len; ++i)
    {
        wf[i] = cfloat(cos(w * i), -sin(w * i));   //exp(-j(Omega)t)
        wi[i] = cfloat(cos(-w * i), -sin(-w * i)); //exp(-j(-Omega)t)
    }
    bin_reverse(wf, w_len);
    bin_reverse(wi, w_len);
}


// Originally was: Order of result frequency bins: 0, -1, -2, ... -F_Nyquist, +F_Nyquist, ... 2, 1
// NOW CORRECT:                                    0, 1, 2, ... +F_Nyquist, -F_Nyquist ... -2, -1 frequency
void fft_proc(cfloat* data, int len, bool inverse)
{
    int i, j, m, N, pos;
    cfloat w, u, v;
    cfloat *pw = inverse ? wi : wf;

    for (m = 1, N = len; N >>= 1; m <<= 1)
    {
        for (i = 0, pos; i < m; ++i)
        {
            w = pw[i];
            pos = i * (N << 1);
            for (j = pos; j < pos + N; ++j)
            {
                u = (data[j]);
                v = (w * data[j + N]);
                data[j] = u + v;
                data[j + N] = u - v;
            }
        }
    }
    bin_reverse(data, len);
    if (inverse)
    {
        for (i = 0; i < len; i++)
            data[i] /= len;
    }
}

/*
// Reorder in the order: 0, 1, 2, ... +F_Nyquist, -F_Nyquist ... -2, -1 frequency
void fft_result_standard_reorder(cfloat* inbuf, cfloat* outbuf, int len, int addrbits_mask)
{
    int i, j;
   // reorder bins in standard representation: from 0...+Fn -Fn...-1 frequency
    j = 0;
    for (i=0; i<len; i++)
      { outbuf[i] = inbuf[j];
        j = (j - 1)&addrbits_mask;
      }
}
*/
// Reorder in the order: -F_Nyquist ... -2, -1, 0, 1, 2, ... +F_Nyquist frequency
void fft_result_spectrum_reorder(cfloat* inbuf, cfloat* outbuf, int len)
{
    int addrbits_mask = len-1;
    int i, j;
   // reorder bins in common representation: from -Fn...0...+Fn frequency
    j = (len/2) ;
    for (i=0; i<len; i++)
      { outbuf[i] = inbuf[j];
        j = (j + 1)&addrbits_mask;
        
      }
}

void window_coeffs_Blackman_calc(float* coeffs, int win_width, int win_len)
{
  int i, k;
  const float a0=0.35875; // ������, "������������� ���� ��� ������������� �������..." (herris.djvu)
  const float a1=0.48829; // formula (33)
  const float a2=0.14128; // table 3: 4-parts, -92dB
  const float a3=0.01168;

  float arg_p, arg;

  arg_p = (2.0*M_PI) / (float)win_width;
  for(i=0; i<win_width; i++)
    {
      arg = arg_p * (float)i;
      coeffs[i] = a0 - a1*cos(arg) + a2*cos(2.0*arg) - a3*cos(3.0*arg);
     // k = (i<len/2)? i : (len-i);
     // coeffs[i] = (float)k/(float)(len/2);
    }
  for(i=win_width; i<win_len; i++)
    {
      coeffs[i] = 0.0;
    }

  return;
}

void window_apply(float* coeffs, cfloat* samples, int len)
{
  int i;
  for(i=0; i<len; i++)
    {
      samples[i] = samples[i] * coeffs[i];
    }
  return;
}






void GainAttSmpl(int16_t smpl_re, int16_t smpl_im, double MultVal, int16_t &res_re, int16_t &res_im, int16_t maxFixed)
{
 double MultResI, MultResQ;

 // Multiply
 MultResI = (double)smpl_re * MultVal;
 // Saturate
 MultResI = (MultResI > (double)maxFixed)  ? (double)maxFixed  : MultResI;
 MultResI = (MultResI < (double)-maxFixed) ? (double)-maxFixed : MultResI;
 // Rounding
 MultResI = (MultResI < 0) ? MultResI-0.5 : MultResI+0.5;
 res_re = (int16_t)MultResI;

 // Multiply
 MultResQ = (double)smpl_im * MultVal;
 // Saturate
 MultResQ = (MultResQ > (double)maxFixed)  ? (double)maxFixed  : MultResQ;
 MultResQ = (MultResQ < (double)-maxFixed) ? (double)-maxFixed : MultResQ;
 // Rounding
 MultResQ = (MultResQ < 0) ? MultResQ-0.5 : MultResQ+0.5;
 res_im = (int16_t)MultResQ;

 return;
}


int16_t Fl2FixRnd(double val, int16_t ScaleToFixed)
{
  double result;
  int32_t resultW32;
  int16_t resultW16;
  // Scale
  result = val * ScaleToFixed;
  // Round
  result = (result <0)? result-0.5 : result+0.5;
  // Saturate
  resultW32 = (int32_t)result;
  if(resultW32 > 32767) resultW32 = 32767;
  else if (resultW32 < -32767) resultW32 = -32767;

  resultW16 = (int16_t)resultW32;
  return resultW16;
}


void cmplxDSPmult(int16_t A_re, int16_t A_im, int16_t B_re, int16_t B_im, int16_t &res_re, int16_t &res_im)
{
 int32_t re, im;
 re = A_re * B_re;
 re = re - A_im*B_im;
 res_re = re >> 15;

 im = A_im * B_re;
 im = im + A_re*B_im;
 res_im = im >> 15;

 return;
}

void GetNextCarrSmpl(double &Phase, double dPh, int16_t &res_re, int16_t &res_im)
{
 double cosPh, sinPh;

 cosPh = cos(Phase);
 sinPh = sin(Phase);
 Phase += dPh;

 res_re = Fl2FixRnd(cosPh, 32767);
 res_im = Fl2FixRnd(sinPh, 32767);

 return;
}

int Convert_int16_text(int16_t Val, char *convstr)
{
  int bit_cnt;
      for(bit_cnt=0; bit_cnt<16; bit_cnt++)
        {
          if(Val&0x00008000) convstr[bit_cnt]='1';
          else convstr[bit_cnt]='0';
          Val = Val << 1;
        }
  return bit_cnt;
}

