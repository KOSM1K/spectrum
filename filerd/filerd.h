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

    bool asInt16 = false,
         asInt = false,
         asFloat = false,
         asDouble = false;
    
public:
    MYsignal(string filePcmPath, string as_type);

    vector<complex<double>> get_range(unsigned long long left_sample, unsigned long long right_sample);
    vector<double> get_range_1c(unsigned long long left_sample, unsigned long long right_sample, int channel);

    vector<complex<double>> get_batch(unsigned long long left_sample, unsigned long long batch_size);
    vector<double> get_batch_1c(unsigned long long left_sample, unsigned long long batch_size, int channel);

    ~MYsignal();
    string get_path();
};

#endif
