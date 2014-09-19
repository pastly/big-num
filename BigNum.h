#ifndef BIGNUM_H
#define BIGNUM_H

#include <string>
#include <vector>

namespace BigNum
{

    class BigNum
    {
        public:
            std::string toString() const;
            std::vector<char> getAbsValueCharVector() const {return m_value;}
            char getDigit(std::vector<char>::size_type i) const {return m_value[i];}
            std::vector<char>::size_type getNumDigits() const {return m_value.size();}
            bool is_negative() const {return m_negative;}
            bool is_positive() const {return !is_negative();}
            BigNum operator+ (const BigNum& that) const;
            BigNum operator- (const BigNum& that) const;
            bool operator==(const BigNum& that) const;
            bool operator> (const BigNum& that) const;
            bool operator< (const BigNum& that) const {return   that  > *this ;}
            bool operator!=(const BigNum& that) const {return !(*this == that);}
            bool operator<=(const BigNum& that) const {return !(*this >  that);}
            bool operator>=(const BigNum& that) const {return !(*this <  that);}
            BigNum();
            BigNum(std::string val);
            BigNum(std::vector<char> absVal, bool neg = false);
            virtual ~BigNum();
        protected:
        private:
            std::vector<char> m_value;
            bool m_negative;
    };

    BigNum abs(BigNum val);

}
#endif // BIGNUM_H
