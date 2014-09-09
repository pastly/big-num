#include "BigNum.h"

int8_t char2digit(char c) {return c-'0';}
char digit2char(int8_t i) {return i+'0';}

void flip(std::vector<char>* val)
{
    char buf;
    for (unsigned int i = 0; i < val->size() / 2; i++)
    {
        buf = val->operator[](i);
        val->operator[](i) = val->operator[](val->size()-1-i);
        val->operator[](val->size()-1-i) = buf;
    }
}

BigNum BigNum::operator+(BigNum that)
{
    const auto maxdigits = 1+(this->get().length() > that.get().length() ? this->get().length() : that.get().length());
    std::vector<char> arr1(maxdigits, '0');
    std::vector<char> arr2(maxdigits, '0');
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
        arr1[i] = digit2char(sum);
    }
    while (arr1.size() > 1 && arr1[arr1.size()-1] == '0') arr1.pop_back();
    flip(&arr1);
    return BigNum(arr1);
}

std::string BigNum::get()
{
    std::string val;
    for (unsigned int i = 0; i < m_value.size(); i++)
        val += m_value[i];
    return val;

}

BigNum::BigNum()
{
    m_value = std::vector<char>('0');
}

BigNum::BigNum(std::string val)
{
    m_value = std::vector<char>(val.length());
    for (unsigned int i = 0; i < val.length(); i++)
        m_value[i] = val[i];
}

BigNum::BigNum(std::vector<char> val)
{
    m_value = val;
}

BigNum::~BigNum()
{
    // dtor
}
