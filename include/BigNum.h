#ifndef BIGNUM_H
#define BIGNUM_H

#include <string>
#include <vector>

namespace BigNum
{

    class BigNum
    {
        public:
            std::string       getAsString()           const;
            std::vector<char> getAbsValueCharVector() const {return m_value;}
            bool              is_negative()           const {return m_negative;}
            bool              is_positive()           const {return !is_negative();}
            //BigNum operator+(BigNum that);
            //BigNum operator-(BigNum that);
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
