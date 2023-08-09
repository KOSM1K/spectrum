// CAUTION
//
// FFT SIZE MUST BE ONLY POWER OF 2

#include <iostream>

#include <fstream>
#include <sstream>

using namespace std;

int read_file()
{
    ifstream f1("MagAng.pcm", fstream::binary);
    if (f1.is_open()) {
        f1.seekg(0, ios::end);
        int32_t n = f1.tellg();
        f1.seekg(0, ios::beg);

        int16_t* arr = new int16_t(n);

        f1.read((char*)arr, n);

        int length = n / 2;

        for (int16_t i = 0; i < n; i++) {
            cout << arr[i] << endl;
        }

        f1.close();
    }
    return 0;
}
