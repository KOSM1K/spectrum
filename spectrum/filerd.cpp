//-------------------
#include "filerd.h"
//-------------------

#include <iostream>

#include <fstream>
#include <sstream>

#include <stdexcept>

#include <vector>

#include <complex>

using namespace std;

// https://stackoverflow.com/questions/40392644/how-to-read-a-binary-file-of-complex-numbers-in-c
// https://www.cyberforum.ru/cpp-beginners/thread1932558.html

vector<complex<double>> pair_to_cdouble(vector<pair<int16_t, int16_t>> v, double multCoef = 1){
    vector<complex<double>> res(v.size());
    for (unsigned long long i = 0; i < v.size(); i++){
        res[i] = complex<double>(multCoef * (double)v[i].first, multCoef * (double)v[i].second);
    }
    return res;
}

MYsignal::MYsignal(string filePcmPath){
    sample_size = (unsigned int) sizeof(pair<int16_t, int16_t>);
    path = filePcmPath;
    inputFileStream = ifstream(path, ios::binary | ios::in);

    if (!inputFileStream.is_open()) {throw invalid_argument ("Path seems to be incorrect. Be sure to use absolute path"); }
    else {
        inputFileStream.seekg(0, ios::end);

        length = (unsigned long long)inputFileStream.tellg() / (unsigned long long)sample_size;

        inputFileStream.seekg(0, ios::beg);

        signal_buffered.reserve(length);
        inputFileStream.read(reinterpret_cast<char*>(signal_buffered.data()), length * sample_size);

        inputFileStream.close();
    }

}

vector<pair<int16_t, int16_t>> MYsignal::get_range(unsigned long long left_sample, unsigned long long right_sample) {
    if (left_sample >= length) {
        throw invalid_argument ((string)"\"left_sample\" (" + to_string(left_sample) + (string)") must be less than length (" +
                               to_string(length) + (string)")");
    }


    if (right_sample <= left_sample) {
        throw invalid_argument ((string)"\"right_sample\" (" + to_string(right_sample) +
                               (string)") must be greater than \"left_sample\" (" + to_string(left_sample) + (string)")");
    }

    unsigned long long constr_right_sample = min(length, right_sample);

    // inputFileStream.seekg(sample_size * left_sample, ios::beg);
    auto subvec_start = signal_buffered.begin() + left_sample;
    auto subvec_end = signal_buffered.begin() + constr_right_sample;
    return vector<pair<int16_t, int16_t>>(subvec_start, subvec_end);
}


vector<int16_t> MYsignal::get_range_1c(unsigned long long left_sample, unsigned long long right_sample, int channel) {
    vector<pair<int16_t, int16_t>> buf = this->get_range(left_sample, right_sample);
    vector<int16_t> res;
    res.reserve(buf.size());
    if (channel == 0){
        for (auto i: buf){
            res.push_back(i.first);
        }
    }
    else{
        for (auto i: buf){
            res.push_back(i.second);
        }
    }
    return res;
}

vector<pair<int16_t, int16_t>> MYsignal::get_batch(unsigned long long left_sample, unsigned long long batch_size){
    return this->get_range(left_sample, left_sample + batch_size);
}


vector<int16_t> MYsignal::get_batch_1c(unsigned long long left_sample, unsigned long long batch_size, int channel){
    return this->get_range_1c(left_sample, left_sample + batch_size, channel);
}


unsigned long long MYsignal::get_length(){
    return length;
}

string MYsignal::get_path() {
    return path;
}

MYsignal::~MYsignal() {
    
}
