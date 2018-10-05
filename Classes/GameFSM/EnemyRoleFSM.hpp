//
//  EnemyRoleFSM.hpp
//  PojectShaoGame
//
//  Created by shao on 2018/9/5.
//

#ifndef EnemyRoleFSM_hpp
#define EnemyRoleFSM_hpp

#include <iostream>
#include "cocos2d.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "MapLayer.hpp"
class MapLayer;
class EnemeyRoleFSM :public cocos2d::Node{
public:
    virtual bool  init();
    CREATE_FUNC(EnemeyRoleFSM);
    
    void setToBody(b2Body *body,MapLayer *map);
    void swtichMoveState(int code);
    void changeToLeft();
    void changeToRight();
    void changeToAttack();
public:
    int i=1;
    b2Body *body;
    MapLayer *map;
};
#endif /* EnemyRoleFSM_hpp */
