//
//  EnemyRole.hpp
//  PojectShaoGame
//
//  Created by shao on 2018/8/4.
//

#ifndef EnemyRole_hpp
#define EnemyRole_hpp

#include <iostream>
#include <cocos2d.h>
#include "Box2D/Box2D.h"
#include "PropertyData.hpp"
#include "EnemyRole.hpp"
#include "../GameFSM/EnemyRoleFSM.hpp"
#include "EnemyRoleFSM.hpp"

class PropertyData;
class EnemyRoleFSM;
class EnemyRole :public cocos2d::Sprite{
class EnemyRoleFSM;
public :
    static EnemyRole *createWithProperty(PropertyData *property,b2Body *body,std::string str);
    bool init(PropertyData *property,b2Body *body,std::string str);
    Sprite *sprite_title1;
    PropertyData * getProerty();
    EnemyRoleFSM * getEnemyRoleFSM();
    b2Body *body;
    int i=1;
    bool move;
    void update(float delta);
    void setEnemyRoleFSM(EnemyRoleFSM *enemyRoleFSM1);
    void setSchedule();
    void setUnSchedule();
public:
    EnemyRoleFSM *enemyRoleFSM1 =nullptr;
    PropertyData *propertyData =nullptr;

};



#endif /* EnemyRole_hpp */
