//
//  AlllPropertyData.hpp
//  PojectShaoGame
//
//  Created by shao on 2018/9/2.
//

#ifndef AlllPropertyData_hpp
#define AlllPropertyData_hpp

#include <iostream>
#include "stdio.h"
#include "iostream"
#include "cocos2d.h"
#include "PropertyData.hpp"

USING_NS_CC;
using namespace std;
class PropertyData;
class AllPropertyData{

public:
//    static
    static void setSprite(Sprite *sprite1);
    static Sprite * getSprite();
    
    
    static void setSprite1(Sprite *sprite1);
    static Sprite * getSprite1();
    
    static void setSprite2(Sprite *sprite1);
    static Sprite * getSprite2();
    
    static void setSprite3(Sprite *sprite1);
    static Sprite * getSprite3();
    
    
    static void setSprite();
    static  int  fun(int a);
    static PropertyData * setPropertyData(int proertyData);
};
#endif /* AlllPropertyData_hpp */
