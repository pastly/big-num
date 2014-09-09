#ifndef BIGNUM_H
#define BIGNUM_H

#include <string>
#include <vector>



class BigNum
{
    public:
        std::string get() {return m_value;}
        BigNum operator+(BigNum that);
        BigNum();
        BigNum(std::string val);
        virtual ~BigNum();
    protected:
    private:
        std::string m_value;
};

#endif // BIGNUM_H
