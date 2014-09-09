#ifndef BIGNUM_H
#define BIGNUM_H

#include <string>
#include <vector>



class BigNum
{
    public:
        std::string get();
        BigNum operator+(BigNum that);
        bool operator==(BigNum that)      {return this->get() == that.get();}
        bool operator!=(BigNum that)      {return this->get() != that.get();}
        bool operator==(std::string that) {return this->get() == that;}
        bool operator!=(std::string that) {return this->get() == that;}
        bool operator==(std::vector<char> that) {return this->m_value == that;}
        bool operator!=(std::vector<char> that) {return this->m_value != that;}
        BigNum();
        BigNum(std::string val);
        BigNum(std::vector<char> val);
        virtual ~BigNum();
    protected:
    private:
        std::vector<char> m_value;
};

#endif // BIGNUM_H
