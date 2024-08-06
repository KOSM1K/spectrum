#ifndef filerdH
#define filerdH


#include <vector>
#include <fstream>
#include <sstream>
#include <complex>

using namespace std;

vector<pair<int16_t, int16_t>> readAs_int16(string path);
vector<complex<float>> pair_int16_to_cfloat(vector<pair<int16_t, int16_t>> v, float multCoef = 1.0);
vector<complex<double>> pair_int16_to_cdouble(vector<pair<int16_t, int16_t>> v, double multCoef = 1.0);

class MYsignal
{
private:
    ifstream inputFileStream;
    string path;
    unsigned long long length;
    unsigned int sample_size;
    vector<pair<int16_t, int16_t>> signal_buffered;

public:
    MYsignal(string filePcmPath);

    vector<pair<int16_t, int16_t>> get_range(unsigned long long left_sample, unsigned long long right_sample);
    vector<int16_t> get_range_1c(unsigned long long left_sample, unsigned long long right_sample, int channel);

    vector<pair<int16_t, int16_t>> get_batch(unsigned long long left_sample, unsigned long long batch_size);
    vector<int16_t> get_batch_1c(unsigned long long left_sample, unsigned long long batch_size, int channel);

    unsigned long long get_length();
    string get_path();

    ~MYsignal();
};

#endif
