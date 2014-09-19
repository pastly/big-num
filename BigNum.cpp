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
    BigNum BigNum::operator+(const BigNum& that) const
    {
        // if values do not have same sign, subtract them
        if (this->is_positive() != that.is_positive())
            return *this - BigNum(that.getAbsValueCharVector(), !that.is_negative());
        // make sure first is abs bigger than second
        else if (abs(that) > abs(*this))
            return that + *this;
        // add them
        else
        {
            const auto maxDigits = 1+this->getNumDigits(); // num digits of biggest number + 1 in case of carry
            std::vector<char> arr1(maxDigits, '0'); // biggest num, also stores answer
            std::vector<char> arr2(maxDigits, '0'); // second num
            for (std::vector<char>::size_type i = 0; i < this->getNumDigits(); i++) // fill in arr1 with this backwards to align digits
                arr1[this->getNumDigits()-1-i] = this->getDigit(i);
            for (std::vector<char>::size_type i = 0; i < that.getNumDigits(); i++) // fill in ar2 with that backwards to align digits
                arr2[that.getNumDigits()-1-i] = that.getDigit(i);
            // do math digits by digits
            char carry = '0';
            int8_t sum = 0;
            for (std::vector<char>::size_type i = 0; i < arr1.size(); i++)
            {
                sum = char2digit(arr1[i]) + char2digit(arr2[i]) + char2digit(carry);
                carry = '0';
                while (sum >= 10)
                    {carry++; sum -= 10;}
                arr1[i] = digit2char(sum);
            }
            flip(&arr1); // flip to be MSD --> LSD like normal
            return BigNum(arr1, this->is_negative());
        }

    }

    BigNum BigNum::operator-(const BigNum& that) const
    {

        // if the numbers have different signs, add them
        if (this->is_positive() != that.is_positive())
            return *this + BigNum(that.getAbsValueCharVector(), !that.is_negative());
        // determine final sign based on sizes and signs of this/that
        const bool negative =    ( abs(*this) > abs(that) ? this->is_negative()  : !this->is_negative() );
        // biggest + 1 so can be sure biggest number has a zero in front
        const auto maxDigits = 1+( abs(*this) > abs(that) ? this->getNumDigits() :  that.getNumDigits() );
        std::vector<char> arr1(maxDigits, '0');
        std::vector<char> arr2(maxDigits, '0');
        // fill arrays, making sure biggest is in arr1
        // fill such that leading zeros are to left, ones position is far right
        if (abs(*this) > abs(that))
        {
            for (std::vector<char>::size_type i = 0; i < this->getNumDigits(); i++)
                arr1[arr1.size()+i-this->getNumDigits()] = this->getDigit(i);
            for (std::vector<char>::size_type i = 0; i < that.getNumDigits(); i++)
                arr2[arr2.size()+i-that.getNumDigits()] = that.getDigit(i);
        }
        else if (abs(*this) < abs(that))
        {
            for (std::vector<char>::size_type i = 0; i < that.getNumDigits(); i++)
                arr1[arr1.size()+i-that.getNumDigits()] = that.getDigit(i);
            for (std::vector<char>::size_type i = 0; i < this->getNumDigits(); i++)
                arr2[arr2.size()+i-this->getNumDigits()] = this->getDigit(i);
        }
        // super special case. Save time and just return zero
        else return BigNum(std::vector<char>({'0'}));

        char tensChar = '0';
        int8_t diff = 0;
        // go through arrs, taking two digits from arr1 and subtracting one char from arr2 from them
        for (std::vector<char>::size_type i = 1; i < arr1.size(); i++)
        {
            diff = char2digit(arr1[i-1])*10 + char2digit(arr1[i]) - char2digit(arr2[i]);
            tensChar = '0';
            // if arr2's char ended up being bigger than arr1's two chars
            // go back and find some value to bring down to where we are working
            if (diff < 0)
            {
                auto j = i-1;
                // j should never < 0 because arr1 is bigger than arr2
                while (arr1[j] == '0')
                {
                    arr1[j] = '9';
                    j--;
                }
                arr1[j]--;
                diff += 10;
                tensChar = arr1[i-1];
            }
            // if diff isn't a single digit
            while (diff >= 10)
            {
                diff -= 10;
                tensChar++;
            }
            // set final values in arr1
            arr1[i-1] = tensChar;
            arr1[i] = digit2char(diff);
        }
        // use arr1 (abs value of answer) and negative (sign of answer) to make new BigNum
        return BigNum(arr1, negative);
    }

    std::string BigNum::toString() const
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
            for (std::vector<char>::size_type i = 0; i < a.size(); i++)
            {
                if      (char2digit(a[i]) > char2digit(b[i])) return true;
                else if (char2digit(a[i]) < char2digit(b[i])) return false;
            }
        }
        else // this->is_negative()
        {
            std::vector<char> a = this->getAbsValueCharVector();
            std::vector<char> b = that.getAbsValueCharVector();
            for (std::vector<char>::size_type i = 0; i < a.size(); i++)
            {
                if      (char2digit(a[i]) < char2digit(b[i])) return true;
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
        for (std::vector<char>::size_type i = 0; i < val.length(); i++)
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
