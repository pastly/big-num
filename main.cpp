#include <iostream>
#include <fstream>
#include <assert.h>
#include "include/BigNum.h"

int main()
{
    std::ifstream file("tests.txt");
    if (file.is_open())
    {
        std::string a, b, c;
        bool expected;

        /// test ==
        while (file >> a >> b >> c)
        {
            if (a == "----end-of-equals-tests---") break;

            BigNum::BigNum num1(a);
            BigNum::BigNum num2(b);
            if (c == "true") expected = true;
            else             expected = false;
            assert ((num1 == num2) == expected);
        }
        //std::cout << "---------------------------------------\n";
        std::cout << "== okay!\n";
        //std::cout << "---------------------------------------\n";

        /// test <
        while (file >> a >> b >> c)
        {
            if (a == "----end-of-less-than-tests---") break;

            BigNum::BigNum num1(a);
            BigNum::BigNum num2(b);
            if (c == "true") expected = true;
            else             expected = false;
            assert ((num1 < num2) == expected);
        }
        std::cout << "<  okay!\n";

        /// test !=
        while (file >> a >> b >> c)
        {
            if (a == "----end-of-not-equal-tests---") break;

            BigNum::BigNum num1(a);
            BigNum::BigNum num2(b);
            if (c == "true") expected = true;
            else             expected = false;
            assert ((num1 != num2) == expected);
        }
        std::cout << "!= okay!\n";

        /// test >
        while (file >> a >> b >> c)
        {
            if (a == "----end-of-greater-than-tests---") break;

            BigNum::BigNum num1(a);
            BigNum::BigNum num2(b);
            if (c == "true") expected = true;
            else             expected = false;
            assert ((num1 > num2) == expected);
        }
        std::cout << ">  okay!\n";

        /// test <=
        while (file >> a >> b >> c)
        {
            if (a == "----end-of-less-than-or-equal-tests---") break;

            BigNum::BigNum num1(a);
            BigNum::BigNum num2(b);
            if (c == "true") expected = true;
            else             expected = false;
            assert ((num1 <= num2) == expected);
        }
        std::cout << "<= okay!\n";

        /// test >=
        while (file >> a >> b >> c)
        {
            if (a == "----end-of-greater-than-or-equal-tests---") break;

            BigNum::BigNum num1(a);
            BigNum::BigNum num2(b);
            if (c == "true") expected = true;
            else             expected = false;
            assert ((num1 >= num2) == expected);
        }
        std::cout << ">= okay!\n";
    }
    return 0;
}
