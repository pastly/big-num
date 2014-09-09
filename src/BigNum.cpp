#include "BigNum.h"

int8_t char2digit(char c) {return c-'0';}
char digit2char(int8_t i) {return i+'0';}

BigNum BigNum::operator+(BigNum that)
{
    const auto maxdigits = 1+(this->get().length() > that.get().length() ? this->get().length() : that.get().length());
    std::vector<char> arr1(maxdigits, '0');
    std::vector<char> arr2(maxdigits, '0');
    std::string ans = "";
    for (unsigned int i = 0; i < this->get().length(); i++)
        arr1[this->get().length()-1-i] = this->get()[i];
    for (unsigned int i = 0; i < that.get().length(); i++)
        arr2[that.get().length()-1-i]  = that.get()[i];
    int8_t carry = 0;
    for (unsigned int i = 0; i < arr1.size(); i++)
    {
        int8_t sum = char2digit(arr1[i]) + char2digit(arr2[i]) + carry;
        carry = 0;
        while (sum >= 10)
            {carry++; sum -= 10;}
        ans = digit2char(sum) + ans;
    }
    while (ans.length() > 1 && ans[0] == '0') ans = ans.substr(1, std::string::npos);
    return BigNum(ans);
}

BigNum::BigNum()
{
    m_value = "0";
}

BigNum::BigNum(std::string val)
{
    m_value = val;
}

BigNum::~BigNum()
{
    // dtor
}
