//
//  CeShi.hpp
//  PojectShaoGame
//
//  Created by shao on 2018/8/6.
//

#ifndef CeShi_hpp
#define CeShi_hpp

#include <iostream>
#include "cocos2d.h"
#include "PropertyData.hpp"
#include "Box2D/Box2D.h"

class PropertyData;
class Ceshi : public cocos2d::Sprite{
    public :
    static Ceshi *createWithProperty(PropertyData *property,b2Body *body,std::string str);
    bool init(PropertyData *property,b2Body *body,std::string str);
};

#endif /* CeShi_hpp */
