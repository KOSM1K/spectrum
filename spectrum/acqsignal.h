#ifndef ACQSIGNAL_H
#define ACQSIGNAL_H
#include <string>
#include <vector>



class acqSignal
{
public:
    acqSignal(std::string path);
    ~acqSignal();
    int32_t getLength() { return length; }
    int16_t getSample(int32_t index) { return arr[index]; }
    std::vector<int16_t> getRange(int32_t begin, int32_t end, int32_t step = 1);
    int16_t getMaximum(int32_t begin, int32_t end, int32_t step);
    int16_t getMinimum(int32_t begin, int32_t end, int32_t step);
    int16_t getMinMax(int16_t &rMin, int16_t &rMax, int32_t begin, int32_t periodLength, int32_t step);

    

private:
    int16_t* arr;
    int32_t length;
};

#endif // ACQSIGNAL_H
