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

namespace BigNum
{

    /*BigNum BigNum::operator+(BigNum that)
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

    BigNum BigNum::operator-(BigNum that)
    {
        return BigNum("0");
    }*/

    std::string BigNum::getAsString() const
    {
        std::string val = (m_negative ? "-" : "");
        for (unsigned int i = 0; i < m_value.size(); i++)
            val += m_value[i];
        return val;

    }

    bool BigNum::operator==(const BigNum& that) const
    {
        return (this->getAbsValueCharVector() == that.getAbsValueCharVector())
            && (this->is_negative()           == that.is_negative());
    }

    bool BigNum::operator>(const BigNum& that) const
    {
        if (this->is_positive() &&  that.is_negative()) return true;
        else if (this->is_negative() && that.is_positive()) return false;
        else if (this->is_positive() && this->getAbsValueCharVector().size() > that.getAbsValueCharVector().size()) return true;
        else if (this->is_positive() && this->getAbsValueCharVector().size() < that.getAbsValueCharVector().size()) return false;
        else if (this->is_negative() && this->getAbsValueCharVector().size() < that.getAbsValueCharVector().size()) return true;
        else if (this->is_negative() && this->getAbsValueCharVector().size() > that.getAbsValueCharVector().size()) return false;
        else if (this->is_positive())
        {
            std::vector<char> a = this->getAbsValueCharVector();
            std::vector<char> b = that.getAbsValueCharVector();
            for (unsigned int i = 0; i < a.size(); i++)
            {
                if (char2digit(a[i]) > char2digit(b[i])) return true;
                else if (char2digit(a[i]) < char2digit(b[i])) return false;
            }
        }
        else // this->is_negative()
        {
            std::vector<char> a = this->getAbsValueCharVector();
            std::vector<char> b = that.getAbsValueCharVector();
            for (unsigned int i = 0; i < a.size(); i++)
            {
                if (char2digit(a[i]) < char2digit(b[i])) return true;
                else if (char2digit(a[i]) > char2digit(b[i])) return false;
            }
        }
        return false;
    }

    BigNum::BigNum()
    {
        m_negative = false;
        m_value = std::vector<char>('0');
    }

    BigNum::BigNum(std::string val)
    {
        if (val[0] == '-')
        {
            m_negative = true;
            val = val.substr(1, std::string::npos);
        }
        else m_negative = false;
        int startIndex = 0;
        while (val[startIndex] == '0')
            startIndex++;
        val = val.substr(startIndex, std::string::npos);
        if (val.length() == 0) val = "0";
        if (val == "0") m_negative = false;
        m_value = std::vector<char>(val.length());
        for (unsigned int i = 0; i < val.length(); i++)
            m_value[i] = val[i];

    }

    BigNum::BigNum(std::vector<char> absVal, bool neg)
    {
        int startIndex = 0;
        while (absVal[startIndex] == '0')
            startIndex++;
        absVal = std::vector<char>(absVal.begin()+startIndex, absVal.end());
        if (absVal.size() == 0) absVal = std::vector<char>({'0'});
        if (absVal == std::vector<char>({'0'})) m_negative = false;
        m_value = absVal;
        m_negative = neg;
    }

    BigNum::~BigNum()
    {
        // dtor
    }

    BigNum abs(BigNum val)
    {
        return BigNum(val.getAbsValueCharVector());
    }

}
