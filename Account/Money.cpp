//
//  Money.cpp
//  Account
//
//  Created by 陈涵 on 2020/6/14.
//

#include "Money.hpp"
Money::Money(double n)
{
    if(set(n))cout<<"Wrong input Money.\n";
}

bool Money::set(double n)
{
    if(setYuan(abs(n))||setCent(int(abs(n)*100)%100))
        return 1;
    else
        setSign(n<0);
    return 0;
}

bool Money::setYuan(int n)
{
    if(n>=0&&n<=Max)yuan=n;
    else return 1;
    return 0;
}

bool Money::setCent(int n)
{
    if(n>=0&&n<100)cent=n;
    else return 1;
    return 0;
}

void Money::setSign(bool f)
{
    sign=f;
}

int Money::getYuan() const
{
    return yuan;
}

int Money::getCent() const
{
    return cent;
}

bool Money::getSign() const
{
    return sign;
}

int Money::Signed() const
{
    if(sign)return -1;
    else return 1;
}

double Money::SignedMoney() const
{
    if(sign)return -(yuan+cent*0.01);
    else return (yuan+cent*0.01);
}

double Money::UnsignedMoney() const
{
    return (yuan+cent*0.01);
}

void Money::printStandard() const
{
    if(getSign())cout<<"支出 ";
    else cout<<"收入 ";
    cout<<getYuan()<<'.'<<setfill('0')<<setw(2)<<getCent()<<"元";
}

void Money::printUniversal() const
{
    //if(getSign())cout<<'-';
    cout<<"¥"<<getYuan()<<'.'<<setfill('0')<<setw(2)<<getCent();
}

bool signedCmp(const Money a,const Money b)
{
    return a.SignedMoney()<b.SignedMoney();
}

bool unsignedCmp(const Money a,const Money b)
{
    return a.UnsignedMoney()<b.UnsignedMoney();
}

Money Money::operator+(const Money m) const
{
    return Money(SignedMoney()+m.SignedMoney());
}

Money Money::operator-(const Money m) const
{
    return Money(SignedMoney()-m.SignedMoney());
}

bool Money::operator<(const Money m) const
{
    return SignedMoney()<m.SignedMoney();
}

bool Money::operator<=(const Money m) const
{
    return SignedMoney()<=m.SignedMoney();
}

bool Money::operator>(const Money m) const
{
    return SignedMoney()>m.SignedMoney();
}

bool Money::operator>=(const Money m) const
{
    return SignedMoney()>=m.SignedMoney();
}

bool Money::operator==(const Money m) const
{
    return SignedMoney()==m.SignedMoney();
}

bool Money::operator!=(const Money m) const
{
    return SignedMoney()!=m.SignedMoney();
}
