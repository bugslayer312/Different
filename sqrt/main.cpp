#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cfloat>

int SqrtApproach(int value)
{
    int res = 1;
    if (value > 25)
    {
        res = 6;
    }
    while (res * res <= value)
    {
        ++res;
    }
    return res - 1;
}

void IterationApproach(long long& currentResult, long long& remain)
{
    long long resHelper = currentResult * 20;
    long long substract = 0;
    int nextDigit = 1;
    for (; nextDigit <= 10; ++nextDigit)
    {
        long long curSubstract = (resHelper + nextDigit) * nextDigit;
        if (curSubstract > remain)
        {
            break;
        }
        substract = curSubstract;
    }
    remain -= substract;
    currentResult = currentResult * 10 + nextDigit - 1;
}

double Sqrt(double value, int precise = 6)
{
    double finalCoef = 0.1;
    for (int i = 0; i < precise * 2 && value < 1.0; ++i)
    {
        value *= 100.0;
        finalCoef *= 0.1;
    }
    int intPart = value;
    value -= intPart;
    int digitsGrops[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int intPartCnt = 0;
    for (int i = 0; i < 8 && intPart != 0; ++i, intPart /= 100)
    {
        digitsGrops[i] = intPart % 100;
        ++intPartCnt;
        finalCoef *= 10.0;
    }
    for (int i = 0; i < intPartCnt / 2; ++i)
    {
        digitsGrops[i] = digitsGrops[intPartCnt - 1 - i];
    }

    double mult = 0.01;
    for (int i = 0; i < 8 && value > DBL_EPSILON; ++i, mult *= 0.01)
    {
        int digit = value / mult + 0.5;
        digitsGrops[intPartCnt + i] = digit;
        value -= digit * mult;
    }

    long long result = SqrtApproach(digitsGrops[0]);
    long long remain = digitsGrops[0] - result * result;
    for (int j = 0; j < precise; ++j)
    {
        remain = remain * 100 + digitsGrops[j + 1];
        IterationApproach(result, remain);
        finalCoef *= 0.1;
    }
    
    return result * finalCoef;
}

int main()
{
    std::vector<double> sample {10.0, 132.01, 15.16, 15230.33, 0.02};
    std::cout << std::setprecision(8);
    for (auto v : sample)
    {
        std::cout << "Sqrt(" << std::defaultfloat << v << ") = " << std::fixed << Sqrt(v) << std::endl;
    }
}
