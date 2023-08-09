// CAUTION
//
// FFT SIZE MUST BE ONLY POWER OF 2

#pragma once

#include <iostream>



#include <fstream>
#include <sstream>
#include <vector>

#include "C:/Desktop/progs/c++/dsp/DSP_func.h"
#include "C:/Desktop/progs/c++/filerd/filerd.h"

//#include <cmath>


void display_cfloat_arr(int size, cfloat *arr) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i].real() << " : " << arr[i].imag() << "\n";
    }
    
}


void complexToMagAng(int size, cfloat* inbuf, cfloat* outbuf) {
    for (int i = 0; i < size; i++) {
        outbuf[i] = cfloat(10.0, 0) * cfloat(abs(inbuf[i]), arg(inbuf[i]));
    }
}


int main()
{
    const int size_input = 2048;
    const int fft_size = 32;


    float step1 = M_PI * 0.5;
    float step2 = M_PI * -0.125;

    cfloat sigbuf[size_input];
    cfloat result[fft_size];
    cfloat spectr_order_result[fft_size];
    cfloat magAng[fft_size];



    for (int i = 0; i < size_input; i++) {
        sigbuf[i] = cfloat(cosf(0.75*M_PI + ((float) i * step1)) + cosf((float)i * step2), sinf(0.75 * M_PI + (float)i * step1) + sinf((float)i * step2));
        //std::cout << sigbuf[i].real() << std::endl;
    }

    for (int i = 0; i < fft_size; i++) {
        result[i] = (cfloat)sigbuf[i];
        //std::cout << result[i].real() << std::endl;
    }
    /*std::cout << "\nresult\n";
    display_cfloat_arr(32, result);
    std::cout << "\n";*/

    
    fft_basis(fft_size);
    

    fft_proc(result, fft_size, false);

    fft_result_spectrum_reorder(result, spectr_order_result, fft_size);
    complexToMagAng(32, spectr_order_result, magAng);

    /*  
    display_cfloat_arr(32, sigbuf);
    std::cout << std::endl;
    display_cfloat_arr(32, result);
    std::cout << std::endl;
    display_cfloat_arr(32, magAng);
    */

    std::ofstream fout1 ; //object created **fout**
    fout1.open("fftres.pcm");
    fout1.write((char*)result, 32*sizeof(cfloat));
    fout1.close();

    std::ofstream fout2; //object created **fout**
    fout2.open("fftres_reod.pcm");
    fout2.write((char*)spectr_order_result, 32 * sizeof(cfloat));
    fout2.close();

    std::ofstream fout3; //object created **fout**
    fout3.open("MagAng.pcm");
    fout3.write((char*)magAng, 32 * sizeof(cfloat));
    fout3.close();

    MYsignal smth("C:/Desktop/progs/c++/Spectrum_test/File.pcm", "int16");

    int j = 100;

    auto v = smth.get_range(10, 10+j);
    for (int i = 0; i < j; i++) {
        std::cout << v[i].real() << " : " << v[i].imag() << "\n";
    }
    std::cout << sizeof(v);
}