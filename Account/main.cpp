//
//  main.cpp
//  Account
//
//  Created by 陈涵 on 2020/6/15.
//
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iomanip>
#include <ios>
#include <fstream>
#include "Date.hpp"
#include "Money.hpp"
#include "List.cpp"
#include "Item.hpp"
using namespace std;

string helpMain="输入 V 进行查看\n输入 I 写入新项目\n输入 S 保存当前项目\n输入 U 取消未保存的操作\n输入 F 按关键字进行查找\n输入 H 查看帮助信息\n输入 E 返回上一级或退出\n( H 和 E 在所有目录下均可使用，输入大小写字母均可操作)\n";
string helpYN="输入 Y 或 y 确认，输入 N 或 n 取消。\n";
string helpExit="输入 E 或 e 可退出当前操作。\n";
//help tips
fstream* dat;
fstream data("account.dat",ios::in|ios::out|ios::binary);
List<Item> items;

Item I;
int cnt=0,total=0;
string s;
bool changed=0,sorted=0,E=0;

bool Visual();//show the account
void visualBook(bool);//show the account by visual file

bool Insert();//insert new item
bool InsertTime();//insert new time
bool InsertMoney();//insert new money
bool InsertTips();//insert new tips
bool Input();

bool Find();//find
bool FindT(list_node<Item>* num[]);//Find by time order
bool FindM(list_node<Item>* num[]);//find by money order

void Save();//save if the account changed
void reload();//load from

char YN();//input [Y/N]
char YNH();//input [Y/N] with help

bool timeCmp(const Item,const Item);
bool moneyCmp(const Item,const Item);
int main()
{
    cout<<"记账本已启动，输入 H 获得帮助信息，输入 E 回到上一级或退出！\n";
    dat=&data;
    
    while(!data)
    {
        cout<<"未找到数据库，是否重新创建？[Y/N]\n";
        char ch=YN();
        if(ch=='y')
        {
            fopen("account.dat","wb");
            dat =new fstream("account.dat",ios::in|ios::out|ios::binary);
            cnt=0;
            dat->seekp(0);
            dat->write(reinterpret_cast<char*>(&cnt),sizeof(int));
            cout<<"数据库已创建！\n";
            break;
        }
        else if(ch=='n')
        {
            cout<<"程序结束！\n";
            return 0;
        }
        else if(ch=='e')
        {
            cout<<"程序退出！\n";
            return 0;
        }
        else if(ch=='h')
        {
            cout<<"将创建一个二进制数据库，用以储存账本数据\n";
        }
        else
        {
            cout<<"输入错误，请重试!\n";
        }
    }
    dat->seekp(0);
    dat->read(reinterpret_cast<char*> (&cnt),sizeof(int));
    if(cnt==0)
    {
        cout<<"当前数据库为空！请开始您的操作！\n";
    }
    else
    {
        cout<<"当前已有 "<<cnt<<"项账目，正在载入中...\n";
        for(int i=0;i<cnt;i++)
        {
            dat->seekp(sizeof(int)+i*sizeof(Item));
            dat->read(reinterpret_cast<char*>(&I),sizeof(Item));
            items.pushBack(I);
            //I.print();
        }
        cout<<"载入完成！请开始您的操作！\n";
    }
    
    while(true)
    {
        cout<<helpMain;
        cout<<">>";
        getline(cin,s);
        if(s=="I"||s=="i")
        {
            while(Insert());
        }
        else if(s=="S"||s=="s")
        {
            Save();
            cout<<"所有更改已保存！\n";
        }
        else if(s=="V"||s=="v")
        {
            Visual();
        }
        else if(s=="U"||s=="u")
        {
            reload();
            cout<<"更改已取消！\n";
            changed=0;
        }
        else if(s=="F"||s=="f")
        {
            while(Find());
        }
        else if(s=="H"||s=="h")
        {
            cout<<helpMain;
        }
        else if(s=="E"||s=="e")
        {
            if(changed)
            {
                cout<<"您还未保存，是否进行保存？[Y/N]\n";
                char yn=YNH();
                if(yn=='n')
                {
                    cout<<"程序结束！\n";
                    (*dat).close();
                    return 0;
                }
                else if(yn=='y')
                {
                    Save();
                    cout<<"已保存！\n程序结束！\n";
                    (*dat).close();
                    return 0;
                }
                else continue;
            }
            else
            {
                cout<<"程序结束！\n";
                (*dat).close();
                return 0;
            }
        }
        else
        {
            cout<<"输入错误，请重试!\n";
        }
    }
}

bool Visual()
{
    if(items.empty())
    {
        cout<<"当前数据库为空！\n";
        return 0;
    }
    cout<<"当前已有 "<<items.size()<<"项账目\n";
    cout<<"记录时间从 ";
    ((items.begin()->data).time).printDate();
    cout<<"到 ";
    ((items.end()->pre->data).time).printDate();
    cout<<'\n';
    Money m[3];
    for(list_node<Item>* i=items.begin();i!=items.end();i=i->next)
    {
        (i->data).print();
        if((i->data).money.getSign())
        {
            m[1]=m[1]-(i->data).money;
        }
        else
        {
            m[0]=m[0]+(i->data).money;
        }
    }
    m[2]=m[0]-m[1];
    cout<<"总计毛收入 ";
    m[0].printUniversal();
    cout<<"  总计毛支出 ";
    m[1].printUniversal();
    cout<<"  总计净";
    m[2].printStandard();
    cout<<'\n';
    while(1)
    {
        cout<<"是否生成按时间顺序排序的可视化文本文件？[Y/N]\n";
        char yn=YN();
        if(yn=='n')
        {
            break;
        }
        else if(yn=='y')
        {
            visualBook(0);
            cout<<"按时间顺序排序的可视化文件已生成\n";
            break;
        }
        else if(yn=='h')
        {
            cout<<"程序会创建一个包括当前所有账目的可视化txt文本\n";
        }
        else return 0;
    }
    while(1)
    {
        cout<<"是否要按出入金额大小排序显示？[Y/N]\n";
        char yn=YN();
        if(yn=='n')
        {
            break;
        }
        else if(yn=='h')
        {
            cout<<"将会按金额收入从高到低排序！\n";
            continue;
        }
        else if(yn=='y')
        {
            items.listSort(items.begin(),items.end(),moneyCmp);
            sorted=1;
            Money m[3];
            for(list_node<Item>* i=items.begin();i!=items.end();i=i->next)
            {
                (i->data).print();
                if((i->data).money.getSign())
                {
                    m[1]=m[1]-(i->data).money;
                }
                else
                {
                    m[0]=m[0]+(i->data).money;
                }
            }
            m[2]=m[0]-m[1];
            cout<<"总计毛收入 ";
            m[0].printUniversal();
            cout<<"  总计毛支出 ";
            m[1].printUniversal();
            cout<<"  总计净";
            m[2].printStandard();
            cout<<'\n';
            while(1)
            {
                cout<<"是否生成按金额大小排序的可视化文本文件？[Y/N]\n";
                char yn=YN();
                if(yn=='n')
                {
                    break;
                }
                else if(yn=='y')
                {
                    visualBook(1);
                    cout<<"按金额大小排序的可视化文件已生成\n";
                    break;
                }
                else if(yn=='h')
                {
                    cout<<"程序会创建一个包括当前所有账目的可视化txt文本\n";
                }
                else
                {
                    items.listSort(items.begin(),items.end(),timeCmp);
                    sorted=0;
                    return 0;
                }
            }
            items.listSort(items.begin(),items.end(),timeCmp);
            sorted=0;
            break;
        }
        else return 0;
    }
    return 0;
}
void Save()
{
    if(!changed)return;
    if(sorted)items.listSort(items.begin(),items.end(),timeCmp);
    cnt=items.size();
    dat->seekp(0);
    dat->write(reinterpret_cast<char*>(&cnt),sizeof(int));
    int t=0;
    for(list_node<Item>* i=items.begin();i!=items.end();i=i->next)
    {
        I=i->data;
        dat->seekp(sizeof(int)+t*(sizeof(Item)));
        dat->write(reinterpret_cast<char*>(&I),sizeof(Item));
        t++;
    }
    dat->seekp(sizeof(int)+t*(sizeof(Item)));
    dat->write(reinterpret_cast<char*>(&I),sizeof(Item));
    changed=0;
    return;
}
bool Input()
{
    bool flag=1;
    while(flag)
    {
        E=0;
        while(InsertTime())
        {
            E=0;
        }
        if(E)return 0;
        while(1)
        {    
            cout<<"请确认您的输入[Y/N] :";
            (I.time).printDate();
            cout<<'\n';
            char ch=YN();
            if(ch=='e')return 0;
            if(ch=='y')
            {
                flag=0;
                break;
            }
            if(ch=='h')cout<<helpYN<<helpExit;
            if(ch=='n')
            {
                cout<<"请重新输入！\n";
                flag=1;
                break;
            }
        }
    }
    flag=1;
    while(flag)
    {
        E=0;
        while(InsertMoney())
        {
            E=0;
        }
        if(E)return 0;
        while(1)
        {    
            cout<<"请确认您的输入[Y/N] :";
            (I.money).printStandard();
            cout<<'\n';
            char ch=YN();
            if(ch=='e')return 0;
            if(ch=='y')
            {
                flag=0;
                break;
            }
            if(ch=='h')cout<<helpYN<<helpExit;
            if(ch=='n')
            {
                cout<<"请重新输入！\n";
                flag=1;
                break;
            }
        }
    }
    flag=1;
    while(flag)
    {
        E=0;
        while(InsertTips())
        {
            E=0;
        }
        if(E)return 0;
        while(1)
        {    
            cout<<"请确认您的输入[Y/N] :";
            I.showTip();
            cout<<'\n';
            char ch=YN();
            if(ch=='e')return 0;
            if(ch=='y')
            {
                flag=0;
                break;
            }
            if(ch=='h')cout<<helpYN<<helpExit;
            if(ch=='n')
            {
                cout<<"请重新输入！\n";
                flag=1;
                break;
            }
        }
    }
    return 1;
}
bool Insert()
{
    if(!Input())return 0;
    I.print();
    items.pushCmp(I,timeCmp);
    changed=1;
    while(1)
    {
        cout<<"账目已写入！\n是否继续写入新账目[Y/N]\n";
        char ch=YN();
        if(ch=='e')return 0;
        if(ch=='y')return 1;
        if(ch=='h')cout<<helpYN<<helpExit;
        if(ch=='n')return 0;
    }
    return 0;
    
}
bool InsertTime()
{
    cout<<"请输入时间，按照 年/月/日 的格式输入。\n>>";
    getline(cin,s);
    if(s=="E"||s=="e")
    {
        E=1;
        return 0;
    }
    if(s=="H"||s=="h")
    {
        cout<<"按年份，月份，日期的顺序输入时间，中间用“/”间隔开。\n";
        return 1;
    }
    int num[3]={0,0,0},i,t=0;
    for(i=0;i<s.size();i++)
    {
        if(s[i]>='0'&&s[i]<='9')
        {
            num[t]=num[t]*10+s[i]-'0';
        }
        else if(s[i]=='/')
        {
            t++;
        }
        else
        {
            cout<<"输入格式错误！\n";
            return 1;
        }
    }
    if(t!=2)
    {
        cout<<"输入格式错误！\n";
        return 1;
    }
    if((I.time).setDate(num[1],num[2],num[0]))
    {
        cout<<"输入数据不合法！\n";
        return 1;
    }
    return 0;
}
bool InsertMoney()
{
    cout<<"请输入金额，入账请用正数，出账请用负数。\n>>";
    getline(cin,s);
    if(s=="E"||s=="e")
    {
        E=1;
        return 0;
    }
    if(s=="H"||s=="h")
    {
        cout<<"输入出入账的金额，最多可保留小数点后两位，出账用负数表示。数据应控制在"<<(I.money).Max<<"元以内！\n";
        return 1;
    }
    double m=0;
    bool sign=0;
    int i=0;
    if(s[0]=='-')
    {
        i++;
        sign=1;
    }
    if(s[0]=='+')
    {
        i++;
    }
    for(;i<s.size();i++)
    {
        if(s[i]<='9'&&s[i]>='0')
        {
            m=m*10+s[i]-'0';
        }
        else if(s[i]=='.')
        {
            break;
        }
        else
        {
            cout<<"输入格式错误！\n";
            return 1;
        }
    }
    i++;
    if(i<s.size())
    {
        if(s[i]>='0'&&s[i]<='9')
        {
            m+=(s[i]-'0')*0.1;
            i++;
        }
        else
        {
            cout<<"输入格式错误！\n";
            return 1;
        }
    }
    if(i<s.size())
    {
        if(s[i]>='0'&&s[i]<='9')
        {
            m+=(s[i]-'0')*0.01;
            i++;
        }
        else
        {
            cout<<"输入格式错误！\n";
            return 1;
        }
    }
    if(i<s.size())
    {
        if(s[i]>='0'&&s[i]<='9')
        {
            cout<<"小数点后仅保留两位！\n";
        }
        else
        {
            cout<<"输入格式错误！\n";
        }
        return 1;
    }
    if(sign)m=-m;
    if((I.money).set(m))
    {
        cout<<"输入数据不合法！\n";
        return 1;
    }
    return 0;
}
bool InsertTips()
{
    cout<<"请输入账目备注，请控制在100字节以内。\n>>";
    getline(cin,s);
    if(s=="E"||s=="e")
    {
        E=1;
        return 0;
    }
    if(s=="H"||s=="h")
    {
        cout<<"输入账目的备注，例如支出金额用途，收入金额来源等。\n";
        return 1;
    }
    if(s.size()>100)
    {
        cout<<"长度超出限制！\n";
        return 1;
    }
    I.setTip(s);
    return 0;
}
bool Find()
{
    if(items.empty())
    {
        cout<<"当前数据库为空！\n";
        return 0;
    }
    list_node<Item>* num[items.size()];
    total=0;
    cout<<"按时间顺序查找请输入T，按出入金额大小请输入M。\n>>";
    getline(cin,s);
    if(s=="E"||s=="e")
    {
        return 0;
    }
    else if(s=="H"||s=="h")
    {
        cout<<"如果您要按照时间顺序查找请输入T，按照出入金额大小请输入M。\n";
        return 1;
    }
    else if(s=="T"||s=="t")
    {
        while(FindT(num));
    }
    else if(s=="M"||s=="m")
    {
        while(FindM(num));
    }
    else
    {
        cout<<"输入格式错误！\n";
        return 1;
    }
    if(total)cout<<"总共有 "<<total<<"项账目。\n";
    else
    {
        cout<<"无记录！\n";
        return 0;
    }
    bool del[total];
    for(int i=0;i<total;i++)
    {
        del[i]=0;
        cout<<"NO."<<i+1;
        cout<<'\n';
        (num[i]->data).print();
    }
    
    while(1)
    {
        cout<<"修改请输入 X ，删除请输入 D ，求和请输入 C，重新显示列表输入 L。\n>>";
        getline(cin,s);
        if(s=="E"||s=="e")
        {
                return 0;
        }
        else if(s=="H"||s=="h")
        {
            cout<<"您可以输入 X 来修改项目或输入 D 删除某项目，输入 C 进行求和，如果您想重新查看列表，请输入 L。\n";
            continue;
        }
        else if(s=="C"||s=="c")
        {
            Money m[3];
            for(int i=0;i<total;i++)
            {
                if(del[i])continue;
                if((num[i]->data).money.getSign())
                {
                    m[1]=m[1]-(num[i]->data).money;
                }
                else
                {
                    m[0]=m[0]+(num[i]->data).money;
                }
            }
            m[2]=m[0]-m[1];
            cout<<"总计毛收入 ";
            m[0].printUniversal();
            cout<<"  总计毛支出 ";
            m[1].printUniversal();
            cout<<"  总计净";
            m[2].printStandard();
            cout<<'\n';
        }
        else if(s=="X"||s=="x")
        {
            while(1)
            {
                cout<<"请输入要修改的编号。\n>>";
                getline(cin,s);
                if(s=="E"||s=="e")
                {
                    break;
                }
                else if(s=="H"||s=="h")
                {
                    cout<<"请输入要修改的账目的编号。\n>>";
                    continue;
                }
                int no=0;
                for(int i=0;i<s.size();i++)
                {
                    if(s[i]>='0'&&s[i]<='9')
                    {
                        no=no*10+s[i]-'0';
                    }
                    else
                    {
                        cout<<"输入格式错误！\n";
                        continue;
                    }
                }
                if(no<1||no>total)
                {
                    cout<<"请输入 1-"<<total<<" 之间的数字！\n";
                    continue;
                }
                if(del[no-1])
                {
                    cout<<"项目不存在！\n";
                    continue;
                }
                else
                {
                    cout<<"请重新输入账目！\n";
                    if(!Input()) break;
                    while(1)
                    {    
                        cout<<"您确认要用以下新账目替换旧账目吗？[Y/N]\n新: \n";
                        I.print();
                        cout<<"旧: \n";
                        (num[no-1]->data).print();
                        char yn=YN();
                        if(yn=='n')
                        {
                            cout<<"已取消！\n";
                            break;
                        }
                        else if(yn=='y')
                        {
                            del[no-1]=1;
                            items.del(num[no-1]);
                            items.pushCmp(I,timeCmp);
                            changed=1;
                            cout<<"账目已更改！\n";
                            break;
                        }
                        else if(yn=='h')
                        {
                            cout<<"新账目将替代旧账目储存在账本中!\n";
                        }
                        else break;
                    }
                }
            }
        }
        else if(s=="D"||s=="d")
        {
            
            while(1)
            {
                cout<<"请输入要删除的编号！如果要全部删除请输入 A 。\n>>";
                getline(cin,s);
                if(s=="E"||s=="e")
                {
                        break;
                }
                else if(s=="H"||s=="h")
                {
                    cout<<"请输入要删除的编号！例如 123。如果要全部删除请输入字母 A 。\n>>";
                    continue;
                }
                else if(s=="A"||s=="a")
                {
                    cout<<"您确认要删除一下项目吗？[Y/N]\n";
                    for(int i=0;i<total;i++)
                    {
                        if(del[i])continue;
                        cout<<"NO."<<i+1;
                        cout<<'\n';
                        (num[i]->data).print();
                    }
                    char yn=YNH();
                    if(yn=='n')
                    {
                        cout<<"已取消！\n";
                        continue;
                    }
                    else if(yn=='y')
                    {
                        for(int i=0;i<total;i++)
                        {
                            if(del[i])continue;
                            del[i]=1;
                            items.del(num[i]);
                        }
                        cout<<"项目都已删除！\n";
                        changed=1;
                        break;
                    }
                    else break;
                }
                else
                {
                    int no=0;
                    for(int i=0;i<s.size();i++)
                    {
                        if(s[i]>='0'&&s[i]<='9')
                        {
                            no=no*10+s[i]-'0';
                        }
                        else
                        {
                            cout<<"输入格式错误！\n";
                            continue;
                        }
                    }
                    if(no<1||no>total)
                    {
                        cout<<"请输入 1-"<<total<<" 之间的数字！\n";
                        continue;
                    }
                    if(!del[no-1])
                    {
                        cout<<"您确认要删除一下项目吗？[Y/N]\n";
                        cout<<"NO."<<no;
                        cout<<'\n';
                        (num[no-1]->data).print();
                        char yn=YNH();
                        if(yn=='n')
                        {
                            cout<<"已取消！\n";
                            continue;
                        }
                        else if(yn=='y')
                        {
                            items.del(num[no-1]);
                            del[no-1]=1;
                            cout<<"项目已删除！\n";
                            changed=1;
                            break;
                        }
                        else break;
                    }
                    else
                    {
                        cout<<"项目不存在！\n";
                        continue;
                    }
                }
            }
            
        }
        else if(s=="L"||s=="l")
        {
            for(int i=0;i<total;i++)
            {
                cout<<"NO."<<i+1;
                if(del[i])cout<<"   已删除，未保存！";
                cout<<'\n';
                (num[i]->data).print();
            }
        }
        else
        {
            cout<<"输入错误！请重试！\n";
            continue;
        }

    }
    
}
bool FindT(list_node<Item>* num[])
{
    cout<<"请依次输入闭区间左、右端点。\n";
    bool flag=1;
    while(flag)
    {
        do
        {
            E=0;
            cout<<"请先输入左端点！\n";
        }
        while(InsertTime());
        if(E)return 0;
        while(1)
        {    
            cout<<"请确认您的输入[Y/N] :";
            (I.time).printDate();
            cout<<'\n';
            char ch=YN();
            if(ch=='e')return 0;
            if(ch=='y')
            {
                flag=0;
                break;
            }
            if(ch=='h')cout<<helpYN<<helpExit;
            if(ch=='n')
            {
                cout<<"请重新输入！\n";
                flag=1;
                break;
            }
        }
    }
    Date D1=I.time;
    flag=1;
    while(flag)
    {
        do
        {
            E=0;
            cout<<"请再输入右端点！\n";
        }
        while(InsertTime());
        if(E)return 0;
        while(1)
        {    
            cout<<"请确认您的输入[Y/N] :";
            (I.time).printDate();
            cout<<'\n';
            char ch=YN();
            if(ch=='e')return 0;
            if(ch=='y')
            {
                flag=0;
                break;
            }
            if(ch=='h')cout<<helpYN<<helpExit;
            if(ch=='n')
            {
                cout<<"请重新输入！\n";
                flag=1;
                break;
            }
        }
    }
    Date D2=I.time;
    if(D2<D1)
    {
        cout<<"右区间要大于或等于左区间！\n";
        return 1;
    }
    total=0;
    for(list_node<Item>* i=items.begin();i!=items.end();i=i->next)
    {
        if((i->data).time<=D2&&(i->data).time>=D1)
        {
            num[total++]=i;
        }
        else if((i->data).time>D2)break;
    }
    return 0;
}
bool FindM(list_node<Item>* num[])
{
    cout<<"请依次输入闭区间左、右端点。\n";
    bool flag=1;
    while(flag)
    {
        do
        {
            E=0;
            cout<<"请先输入左端点！\n";
        }
        while(InsertMoney());
        if(E)return 0;
        while(1)
        {    
            cout<<"请确认您的输入[Y/N] :";
            (I.money).printStandard();
            cout<<'\n';
            char ch=YN();
            if(ch=='e')return 0;
            if(ch=='y')
            {
                flag=0;
                break;
            }
            if(ch=='h')cout<<helpYN<<helpExit;
            if(ch=='n')
            {
                cout<<"请重新输入！\n";
                flag=1;
                break;
            }
        }
    }
    Money M1=I.money;
    flag=1;
    while(flag)
    {
        do
        {
            E=0;
            cout<<"请再输入右端点！\n";
        }
        while(InsertMoney());
        if(E)return 0;
        while(1)
        {    
            cout<<"请确认您的输入[Y/N] :";
            (I.money).printStandard();
            cout<<'\n';
            char ch=YN();
            if(ch=='e')return 0;
            if(ch=='y')
            {
                flag=0;
                break;
            }
            if(ch=='h')cout<<helpYN<<helpExit;
            if(ch=='n')
            {
                cout<<"请重新输入！\n";
                flag=1;
                break;
            }
        }
    }
    Money M2=I.money;
    if(M2<M1)
    {
        cout<<"右区间要大于或等于左区间！\n";
        return 1;
    }
    total=0;
    for(list_node<Item>* i=items.begin();i!=items.end();i=i->next)
    {
        if((i->data).money<=M2&&(i->data).money>=M1)
        {
            num[total++]=i;
        }
    }
    return 0;

}
char YN()
{
    string input;
    while(1)
    {
        cout<<">>";
        getline(cin,input);
        if(input=="E"||input=="e")return 'e';
        if(input=="Y"||input=="y")return 'y';
        if(input=="N"||input=="n")return 'n';
        if(input=="H"||input=="h")return 'h';
        cout<<"输入错误！请重新输入！\n";
    }
}
char YNH()
{
    string input;
    while(1)
    {
        cout<<">>";
        getline(cin,input);
        if(input=="E"||input=="e")return 'e';
        if(input=="Y"||input=="y")return 'y';
        if(input=="N"||input=="n")return 'n';
        if(input=="H"||input=="h")cout<<helpYN<<helpExit;
        cout<<"输入错误！请重新输入！\n";
    }
}
void reload()
{
    int total;
    while(!items.empty())
    {
        items.del(items.begin());
    }
    dat->seekp(0);
    dat->read(reinterpret_cast<char*> (&total),sizeof(int));
    cnt=total;
    for(int i=0;i<cnt;i++)
    {
        dat->seekp(sizeof(int)+i*sizeof(Item));
        dat->read(reinterpret_cast<char*>(&I),sizeof(Item));
        items.pushBack(I);
    }
}
bool timeCmp(const Item a,const Item b)
{
    return a.time<b.time;
}
bool moneyCmp(const Item a,const Item b)
{
    return a.money>b.money;
}
void visualBook(bool MT)
{
    fstream* book;
    if(MT)
    {
        fopen("Account_MoneyOrder.txt","w");
        book=new fstream("Account_MoneyOrder.txt",ios::out);
    }
    else
    {
        fopen("Account_TimeOrder.txt","w");
        book=new fstream("Account_TimeOrder.txt",ios::out);
    }
   *book<<"当前有 "<<cnt<<"项账目\n";
    Money m[3];
    for(list_node<Item>* i=items.begin();i!=items.end();i=i->next)
    {
        *book<<"您于 ";
        *book<<((i->data).time).getYear()<<"年";
        *book<<((i->data).time).getMonth()<<"月";
        *book<<((i->data).time).getDay()<<"日";
        *book<<' ';
        if(((i->data).money).getSign())*book<<"支出 ";
        else *book<<"收入 ";
        *book<<((i->data).money).getYuan()<<'.'<<setfill('0')<<setw(2)<<((i->data).money).getCent()<<"元";
        *book<<"\n备注: ";
        *book<<(i->data).getTip();
        *book<<'\n';
        if((i->data).money.getSign())
        {
            m[1]=m[1]-(i->data).money;
        }
        else
        {
            m[0]=m[0]+(i->data).money;
        }
    }
    m[2]=m[0]-m[1];
    *book<<"总计毛收入 ";
    *book<<"¥"<<m[0].getYuan()<<'.'<<setfill('0')<<setw(2)<<m[0].getCent();
    *book<<"  总计毛支出 ";
    *book<<"¥"<<m[1].getYuan()<<'.'<<setfill('0')<<setw(2)<<m[1].getCent();
    *book<<"  总计净";
    if(m[2].getSign())*book<<"支出";
    else *book<<"收入";
    *book<<"¥"<<m[2].getYuan()<<'.'<<setfill('0')<<setw(2)<<m[2].getCent();
    *book<<'\n';
    (*book).close();
}
