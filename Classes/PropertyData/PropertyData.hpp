//
//  PropertyData.hpp
//  PojectGame
//
//  Created by shao on 2018/4/23.
//

#ifndef PropertyData_hpp
#define PropertyData_hpp

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class PropertyData : public Node{
public:
    bool init();
    CREATE_FUNC(PropertyData);
public:
    
    
    CC_SYNTHESIZE(int, ID, ID);
    CC_SYNTHESIZE(int, HP, HP);
    CC_SYNTHESIZE(std::string, Image, Image);
    CC_SYNTHESIZE(int, ATK, ATK);
    CC_SYNTHESIZE(int, Speed,Speed);
    CC_SYNTHESIZE(int, Bullet,Bullet);
    CC_SYNTHESIZE(std::string,Content, Content);
    CC_SYNTHESIZE(std::string, PlayerName, PlayerName);

};
#endif

