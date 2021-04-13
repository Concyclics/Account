//
//  Item.cpp
//  Account
//
//  Created by 陈涵 on 2020/6/11.
//

#include "Item.hpp"

void Item::print()
{
    cout<<"您于 ";
    time.printDate();
    cout<<' ';
    money.printStandard();
    cout<<"\n备注: ";
    showTip();
    cout<<'\n';
}
Item::Item()
{
    tip[0]='\0';
}
void Item::showTip()
{
    cout<<tip;
}

string Item::getTip() const
{
    string s=tip;
    return s;
}

bool Item::setTip(const string s)
{
    if(s.size()>100)
    {
        cout<<"Detail should be in 100Bytes.";
        return 1;
    }
    else
    {
        for(int i=0;i<s.size();i++)
        {
            tip[i]=s[i];
        }
        tip[s.size()]='\0';
        for(unsigned long i=s.size()+1;i<=100;i++)
        {
            tip[i]=0;
        }
        return 0;
    }
}
