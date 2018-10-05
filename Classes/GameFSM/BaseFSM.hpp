//
//  BaseFSM.hpp
//  PojectShaoGame
//
//  Created by shao on 2018/5/4.
//

#ifndef BaseFSM_hpp
#define BaseFSM_hpp

#include <iostream>
#include "cocos2d.h"
#include "BaseRole.hpp"
#include "BaseFSM.hpp"
#include "GameLayer.hpp"
#include "MapLayer.hpp"
#include "AnimationStateData.hpp"
#include "Bullet.hpp"
#include "cocostudio/CocoStudio.h"
#include "bones.hpp"
//-----------------------------------------引入的是下边两个c++翻译机
#include <spine/extension.h>
#include <algorithm>
extern "C"{
#include <spine/SkeletonData.h>
#include <spine/AnimationState.h>
//#include <spine/AnimationState.c>
}

USING_NS_CC;
#define PTM_L 0.03125
using namespace spine;
class BaseRole;
class GameLayer;
class MapLayer;
class Bullet;
class  BaseFSM :public Layer{
public:
    Bullet *bullet;
    BaseRole *role;
    BaseFSM *baseFSM;
    PhysicsBody *body;
    MapLayer *map;
    b2World *world;
    GameLayer *context;
    DrawNode *g;


    static BaseFSM *createFSM1(BaseRole *baseRole);
    bool init(BaseRole *baseRole);
    bool ajump=false;
    void initJump(bool ajump);
    void initMap(MapLayer *map);
    void initWorld(b2World *world);
    void startListener(spTrackEntry *entry);
    void initContext(GameLayer *context);
    void initBullet(b2Body *body,b2Vec2 b2vec,b2Vec2 b2vec1);
    void initBomb(b2Body *body,b2Vec2 b2vec,b2Vec2 b2vec1);
public:
    void swtichMoveState(int dir);
    void swtichMoveState1(int dir);
    void changeToFire();
    void changeToFire1();
    void changeToDefault();
    void changeToDefault1();
    void changeToAttack(std::string  gun);
    void changeToShin();
    void changeToSkin1();
    void changeToLeft();
    void changeToLeftFire();
    void changeToRight();
    void changeToRightFire();
    void changeToJump();
    void changeToJump1();
    void changeToDead();
    void changeToUp();
    void changeToDown();
    void changeToRecovery();
    void changeToDestroy(b2Body *body);
};

#endif /* BaseFSM_hpp */
