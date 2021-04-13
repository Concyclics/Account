//
//  Item.hpp
//  Account
//
//  Created by 陈涵 on 2020/6/11.
//

#ifndef Item_hpp
#define Item_hpp
#include "Date.hpp"
#include "Money.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
class Item
{

    public:
        Item();
        Date time;
        Money money;
        void showTip();
        string getTip() const;
        bool setTip(const string);
        void print();
    private:
        char tip[101];
        
};

#endif /* Item_hpp */
