#include <iostream>
#include <fstream>
#include <assert.h>
#include "include/BigNum.h"

int main()
{
    std::ifstream file("addition-tests.txt");
    if (file.is_open())
    {
        std::string a, b, c;
        BigNum ans;
        while (file >> a >> b >> c)
        {
            assert(BigNum(a) + BigNum(b) == c);
        }
        std::cout << "Addition is good";
    }
    return 0;
}
