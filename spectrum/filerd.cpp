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

vector<complex<double>> pair_to_cdouble(vector<pair<int16_t, int16_t>> v, double multCoef){
    vector<complex<double>> res(v.size());
    for (unsigned long long i = 0; i < v.size(); i++){
        res[i] = complex<double>(multCoef * (double)v[i].first, multCoef * (double)v[i].second);
    }
    return res;
}

vector<complex<double>> pair_to_cdouble(vector<pair<int, int>> v, double multCoef) {
    vector<complex<double>> res(v.size());
    for (unsigned long long i = 0; i < v.size(); i++) {
        res[i] = complex<double>(multCoef * (double)v[i].first, multCoef * (double)v[i].second);
    }
    return res;
}

vector<complex<double>> pair_to_cdouble(vector<pair<float, float>> v, double multCoef) {
    vector<complex<double>> res(v.size());
    for (unsigned long long i = 0; i < v.size(); i++) {
        res[i] = complex<double>(multCoef * (double)v[i].first, multCoef * (double)v[i].second);
    }
    return res;
}

vector<complex<double>> pair_to_cdouble(vector<pair<double, double>> v, double multCoef) {
    vector<complex<double>> res(v.size());
    for (unsigned long long i = 0; i < v.size(); i++) {
        res[i] = complex<double>(multCoef * (double)v[i].first, multCoef * (double)v[i].second);
    }
    return res;
}



MYsignal::MYsignal(string filePcmPath, string as_type){
    if (as_type == "int16") { asInt16 = true; sample_size = (unsigned int) sizeof(pair<int16_t, int16_t>); }
    else if (as_type == "int") { asInt = true; sample_size = (unsigned int) sizeof(pair<int, int>); }
    else if (as_type == "float") { asFloat = true;  sample_size = (unsigned int) sizeof(pair<float, float>); }
    else if (as_type == "double") { asDouble = true;  sample_size = (unsigned int) sizeof(pair<double, double>); }
    else { throw invalid_argument ("Argument \"asType\" must be one of:\n\"int16\", \"int\", \"float\", \"double\""); }

    path = filePcmPath;
    inputFileStream = ifstream(path, ios::binary | ios::in);
    if (!inputFileStream.is_open()) {throw invalid_argument ("Path seems to be incorrect. Be sure to use absolute path"); }
    else {
        inputFileStream.seekg(0, ios::end);

        if (asInt16) length = (unsigned long long)inputFileStream.tellg() / (unsigned long long)sample_size;
        else if (asInt) length = (unsigned long long)inputFileStream.tellg() / (unsigned long long)sample_size;
        else if (asFloat) length = (unsigned long long)inputFileStream.tellg() / (unsigned long long)sample_size;
        else length = (unsigned long long)inputFileStream.tellg() / (unsigned long long)sample_size;

        inputFileStream.seekg(0, ios::beg);
    }

}

vector<complex<double>> MYsignal::get_range(unsigned long long left_sample, unsigned long long right_sample) {
    if (!(left_sample < length)) {
        throw invalid_argument ((string)"\"left_sample\" (" + to_string(left_sample) + (string)") must be less than length (" +
                               to_string(length) + (string)")");
    }


    if (!(right_sample > left_sample)) {
        throw invalid_argument ((string)"\"right_sample\" (" + to_string(right_sample) +
                               (string)") must be greater than \"left_sample\" (" + to_string(left_sample) + (string)")");
    }

    unsigned long long constr_right_sample = min(length, right_sample);

    inputFileStream.seekg(sample_size * left_sample, ios::beg);

    if (asInt16) {
        vector<pair<int16_t, int16_t>> range(constr_right_sample - left_sample);
        inputFileStream.read(reinterpret_cast<char*>(range.data()), (constr_right_sample - left_sample) * sample_size);
        return pair_to_cdouble(range, 1);
    }
    else if (asInt) {
        vector<pair<int, int>> range(constr_right_sample - left_sample);
        inputFileStream.read(reinterpret_cast<char*>(range.data()), (constr_right_sample - left_sample) * sample_size);
        return pair_to_cdouble(range, 1);
    }
    else if (asFloat) {
        vector<pair<float, float>> range(constr_right_sample - left_sample);
        inputFileStream.read(reinterpret_cast<char*>(range.data()), (constr_right_sample - left_sample) * sample_size);
        return pair_to_cdouble(range, 1);
    }
    else {
        vector<pair<double, double>> range(constr_right_sample - left_sample);
        inputFileStream.read(reinterpret_cast<char*>(range.data()), (constr_right_sample - left_sample) * sample_size);
        return pair_to_cdouble(range, 1);
    }
}

vector<double> MYsignal::get_range_1c(unsigned long long left_sample, unsigned long long right_sample, int channel) {
    if ((channel == 0) || (channel == 1)) {
        vector<complex<double>> range2c = this->get_range(left_sample, right_sample);
        vector<double> range1c(range2c.size());
        for (unsigned long long i = 0; i < range1c.size(); i++) {
            if (channel == 0) range1c[i] = range2c[i].real();
            else range1c[i] = range2c[i].imag();
        }
        return range1c;
    }
    else {
        throw invalid_argument("\"channel\" must be 0 or 1 (got " + to_string(channel) + ")");
    }
}

vector<complex<double>> MYsignal::get_batch(unsigned long long left_sample, unsigned long long batch_size) {
    return this->get_range(left_sample, left_sample + batch_size);
}



vector<double> MYsignal::get_batch_1c(unsigned long long left_sample, unsigned long long batch_size, int channel) {
    if ((channel == 0) || (channel == 1)) {
        vector<complex<double>> batch2c = this->get_batch(left_sample, batch_size);
        vector<double> batch1c(batch2c.size());
        for (unsigned long long i = 0; i < batch1c.size(); i++) {
            if (channel == 0) batch1c[i] = batch2c[i].real();
            else batch1c[i] = batch2c[i].imag();
        }
        return batch1c;
    }
    else {
        throw invalid_argument("\"channel\" must be 0 or 1 (got " + to_string(channel) + ")");
    }
}


unsigned long long MYsignal::get_length(){
    return this->length;
}

string MYsignal::get_path() {
    return path;
}

MYsignal::~MYsignal() {
    inputFileStream.close();
}
