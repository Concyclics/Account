//
//  Date.cpp
//  Account
//
//  Created by 陈涵 on 2020/5/7.
//

#include "Date.hpp"
const short Date::mh[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
bool sameDay(const Date a,const Date b)
{
    return (a.getYear()==b.getYear()&&a.getMonth()==b.getMonth()&&a.getDay()==b.getDay());
}

bool sameMonth(const Date a,const Date b)
{
    return (a.getYear()==b.getYear()&&a.getMonth()==b.getMonth());
}

bool sameYear(const Date a,const Date b)
{
    return a.getYear()==b.getYear();
}

bool Date::operator<(const Date d) const
{
    if( year < d.getYear() )return 1;
    else if( year > d.getYear() )return 0;
    
    if( month < d.getMonth() )return 1;
    else if( month > d.getMonth() )return 0;
    
    if( day < d.getDay() )return 1;
    else if( day > d.getDay() )return 0;
    
    if( hour < d.getHour() )return 1;
    else if( hour > d.getHour() )return 0;
    
    if( minute < d.getMinute() )return 1;
    else if( minute > d.getMinute() )return 0;
    
    if( second < d.getSecond() )return 1;
    else if( second > d.getSecond() )return 0;
    
    return 0;
}

bool Date::operator<=(const Date d) const
{
    if( year < d.getYear() )return 1;
    else if( year > d.getYear() )return 0;
    
    if( month < d.getMonth() )return 1;
    else if( month > d.getMonth() )return 0;
    
    if( day < d.getDay() )return 1;
    else if( day > d.getDay() )return 0;
    
    if( hour < d.getHour() )return 1;
    else if( hour > d.getHour() )return 0;
    
    if( minute < d.getMinute() )return 1;
    else if( minute > d.getMinute() )return 0;
    
    if( second < d.getSecond() )return 1;
    else if( second > d.getSecond() )return 0;
    
    return 1;
}

bool Date::operator>(const Date d) const
{
    if( year > d.getYear() )return 1;
    else if( year < d.getYear() )return 0;
    
    if( month > d.getMonth() )return 1;
    else if( month < d.getMonth() )return 0;
    
    if( day > d.getDay() )return 1;
    else if( day < d.getDay() )return 0;
    
    if( hour > d.getHour() )return 1;
    else if( hour < d.getHour() )return 0;
    
    if( minute > d.getMinute() )return 1;
    else if( minute < d.getMinute() )return 0;
    
    if( second > d.getSecond() )return 1;
    else if( second < d.getSecond() )return 0;
    
    return 0;
}

bool Date::operator>=(const Date d) const
{
    if( year > d.getYear() )return 1;
    else if( year < d.getYear() )return 0;
    
    if( month > d.getMonth() )return 1;
    else if( month < d.getMonth() )return 0;
    
    if( day > d.getDay() )return 1;
    else if( day < d.getDay() )return 0;
    
    if( hour > d.getHour() )return 1;
    else if( hour < d.getHour() )return 0;
    
    if( minute > d.getMinute() )return 1;
    else if( minute < d.getMinute() )return 0;
    
    if( second > d.getSecond() )return 1;
    else if( second < d.getSecond() )return 0;
    
    return 1;

}

bool Date::operator==(const Date d) const
{
    if( year != d.getYear() )return 0;
    if( month != d.getMonth() )return 0;
    if( day != d.getDay() )return 0;
    if( hour != d.getHour() )return 0;
    if( minute != d.getMinute() )return 0;
    if( second != d.getSecond() )return 0;
    return 1;
}

bool Date::operator!=(const Date d) const
{
    if( year != d.getYear() )return 1;
    if( month != d.getMonth() )return 1;
    if( day != d.getDay() )return 1;
    if( hour != d.getHour() )return 1;
    if( minute != d.getMinute() )return 1;
    if( second != d.getSecond() )return 1;
    return 0;
}

bool Date::check(int m,int d,int y)
{
    //cout<<m<<d<<y<<endl;
    if(m>12||m<0)return 1;
    if(((y%4==0&&y%100!=0)||y%400==0)&&(m==2))
    {
        if(d>29||d<1)return 1;
    }
    else if(mh[m]<d||d<1)return 1;
    return 0;
}

bool Date::set(int m,int d,int y,int h,int mi,int s)
{
    return setDate(m,d,y)|setTime(h,mi,s);
}

bool Date::setDate(int m,int d,int y)
{
    if(check(m,d,y))return 1;
    month=m;
    day=d;
    year=y;
    return 0;
}

bool Date::setTime(int h,int m,int s)
{
    return setHour(h)|setMinute(m)|setSecond(s);
}

bool Date::setHour(int h)
{
    if (h>=0&&h<24)
        hour=h;
    else
        return 1;
    return 0;
}

bool Date::setMinute(int m)
{
    if ( m >= 0 && m <60)
        minute=m;
    else
        return 1;
    return 0;
}

bool Date::setSecond(int s)
{
    if (s>=0&&s<60)
        second=s;
    else
        return 1;
    return 0;
}

int Date::getHour() const
{
    return hour;
}

int Date::getMinute() const
{
    return minute;
}

int Date::getSecond() const
{
    return second;
}

int Date::getDay() const
{
    return day;
}

int Date::getMonth() const
{
    return month;
}

int Date::getYear() const
{
    return year;
}

void Date::printUniversal() const
{
    cout<<month<<'/'<<day<<'/'<<year<<endl;
    cout<<setfill('0')<<setw(2)<<getHour()<<":"<<setw(2)<<getMinute()<<":"<<setw(2)<<getSecond();
}

void Date::printStandard() const
{
    cout<<month<<'/'<<day<<'/'<<year<<endl;
    cout<<((getHour()<=12)?getHour():getHour()%12)<<":"<<setfill('0' )<<setw(2)<<getMinute()<<":"<<setw(2)<<getSecond()<<(hour<= 12?" AM":" PM");
}
void Date::printDate() const
{
    cout<<year<<"年"<<month<<"月"<<day<<"日";
}

Date::Date( int m, int d, int y ,int h,int min,int s)
{
    if(!check(m,d,y))
    {
        setDate(m,d,y);
    }
    else cout<<"Wrong Input Date.\n";
    if(setTime(h,min,s)) cout<<"Wrong Input Date.\n";
}
