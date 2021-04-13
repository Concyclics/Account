//
//  Money.hpp
//  Account
//
//  Created by 陈涵 on 2020/6/14.
//

#ifndef Money_hpp
#define Money_hpp

#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <cmath>
using namespace std;
class Money
{
    friend bool signedCmp(const Money,const Money);
    friend bool unsignedCmp(const Money,const Money);
    
    public:
    
        Money(double=0);
    
        Money operator+(const Money) const;
        Money operator-(const Money) const;
        bool operator<(const Money) const;
        bool operator<=(const Money) const;
        bool operator>(const Money) const;
        bool operator>=(const Money) const;
        bool operator==(const Money) const;
        bool operator!=(const Money) const;
        
        void printStandard() const;
        void printUniversal() const;
    
        bool setYuan(int);
        bool setCent(int);
        void setSign(bool);
        bool set(double);
    
        int getYuan() const;
        int getCent() const;
        bool getSign() const;
        int Signed() const;
    
        double SignedMoney() const;
        double UnsignedMoney() const;
    
        static const int Max=100000000;
        
    private:
    
        int yuan;
        short cent;
        bool sign;
        
    
};
#endif /* Money_hpp */
