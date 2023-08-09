//---------------------------------------------------------------------------

#ifndef DSP_funcH
#define DSP_funcH



#include <stdint.h>
// #include <math.h>
#include <cmath>
#include <complex>
typedef std::complex<float> cfloat;
typedef std::complex<int16_t> cint16;

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

void GainAttSmpl(int16_t smpl_re, int16_t smpl_im, double MultVal, int16_t &res_re, int16_t &res_im, int16_t maxFixed);
int16_t Fl2FixRnd(double val, int16_t ScaleToFixed);
void cmplxDSPmult(int16_t A_re, int16_t A_im, int16_t B_re, int16_t B_im, int16_t &res_re, int16_t &res_im);
void GetNextCarrSmpl(double &Phase, double dPh, int16_t &res_re, int16_t &res_im);

//void fft_result_standard_reorder(cfloat* inbuf, cfloat* outbuf, int len, int addrbits_mask);
void fft_result_spectrum_reorder(cfloat* inbuf, cfloat* outbuf, int len);
void fft_proc(cfloat* data, int len, bool inverse = false);
void bin_reverse(cfloat* data, int length);
void fft_basis(int len);

void window_coeffs_Blackman_calc(float* coeffs, int win_width, int win_len);
void window_apply(float* coeffs, cfloat* samples, int len);

int Convert_int16_text(int16_t Val, char *convstr);

//---------------------------------------------------------------------------

#endif
