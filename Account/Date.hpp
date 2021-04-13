//
//  Date.hpp
//  Account
//
//  Created by 陈涵 on 2020/5/7.
//

#ifndef Date_hpp
#define Date_hpp
#include <iostream>
#include <stdio.h>
#include <iomanip>
using namespace std;

class Date
{
    friend bool sameDay(const Date,const Date);
    friend bool sameMonth(const Date,const Date);
    friend bool sameYear(const Date,const Date);
    
    public:
    
        Date(int=1,int=1,int=2000,int=0,int=0,int=0);
        bool setTime(int,int,int);//hour,minute,second
        bool setHour(int);
        bool setMinute(int);
        bool setSecond(int);
        bool setDate(int,int,int);
        bool check(int,int,int);
        bool set(int,int,int,int,int,int);
        
        bool operator<(const Date) const;
        bool operator<=(const Date) const;
        bool operator>(const Date) const;
        bool operator>=(const Date) const;
        bool operator==(const Date) const;
        bool operator!=(const Date) const;
        
        int getHour() const;
        int getMinute() const;
        int getSecond() const;
        int getYear() const;
        int getMonth() const;
        int getDay() const;
        
        void printUniversal() const;
        void printStandard() const;
        void printDate() const;
        
        static const short mh[13];
    
    private:
        
        short hour;
        short minute;
        short second;
        short month;
        short day;
        short year;
        
        
};
#endif /* Date_hpp */
