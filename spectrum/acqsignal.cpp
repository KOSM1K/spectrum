#include "acqsignal.h"

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

acqSignal::acqSignal(string path)
{
    //building signal buf, writing signal length
    ifstream f1(path, fstream::binary);
    if (f1.is_open()){
        f1.seekg(0,  ios::end);
        int32_t n = f1.tellg();
        f1.seekg(0, ios::beg);
        arr = new int16_t[n];
        f1.read((char*)arr, n);

        length = n/2;

        f1.close();
    }
    else{
        length = 0;
        arr = nullptr;
    }
}

acqSignal::~acqSignal(){
    delete[] arr;
}

vector<int16_t> acqSignal::getRange(int32_t begin, int32_t end, int32_t step){
    vector<int16_t> pcur;
    for (int32_t i = begin; i < end; i+= step){
        pcur.push_back(arr[i]);
    }
    return pcur;
}

int16_t acqSignal::getMaximum(int32_t begin, int32_t end, int32_t step){
    int16_t locMax = arr[begin];
    for (int32_t i = begin; i < end; i+= step){
        if (locMax < arr[i]){
            locMax = arr[i];
        }
    }
    return locMax;
}

int16_t acqSignal::getMinimum(int32_t begin, int32_t end, int32_t step){
    int16_t locMin = arr[begin];
    for (int32_t i = begin; i < end; i+= step){
        if (locMin > arr[i]){
            locMin = arr[i];
        }
    }
    return locMin;
}

int16_t acqSignal::getMinMax(int16_t &rMin, int16_t &rMax, int32_t begin, int32_t periodLength, int32_t step){
    int16_t locMin = arr[begin];
    int16_t locMax = arr[begin];
    int16_t tmp_smpl;
    int32_t pt = begin;
    int16_t Mean = 0;
    for (int32_t i = 0; i < periodLength; i+= step){
        tmp_smpl = arr[pt];
        locMin = (locMin > tmp_smpl)? tmp_smpl : locMin;
        locMax = (locMax < tmp_smpl)? tmp_smpl : locMax;
        pt += step;
    }
    rMin = locMin;  rMax = locMax;
    return Mean;
}
