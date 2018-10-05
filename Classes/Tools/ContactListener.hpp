//
//  ContactListener.hpp
//  PojectShaoGame
//
//  Created by shao on 2018/5/16.
//

#ifndef ContactListener_hpp
#define ContactListener_hpp

#include <iostream>
#include "cocos2d.h"
#include <vector>
#include "GameLayer.hpp"
#include "PropertyData.hpp"
#include "Box2D/Box2D.h"
#include "AllPropertyData.hpp"
#include "EnemyRole.hpp"
class PropertyData;
class AllPropertyData;
class EnemyRole;
USING_NS_CC;
using namespace std;

class ContactListener : public b2ContactListener{
    
    public:
        b2World *world;
    public:
        void setb2World(b2World *world);
    public:
        virtual void BeginContact(b2Contact *contact);
        virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
        virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
        virtual void EndContact(b2Contact* contact);
        bool ladder;
    //这个是子弹
        b2Body *body1 =nullptr;
    //这个是记录敌人的血槽。
        b2Body * body =nullptr;
        b2Body * getBody();
    //这个是记录自己人的血槽。
        b2Body * bodyRole =nullptr;

    public:
//        AllPropertyData *allpropertyData;
    //得到某个值
//    std::vector<Sprite *> propertyVector;
    
    
    
    //清理各种刚体与精灵
    std::vector<b2Body *> b2body;
    std::vector<Sprite *> sprite;
//    PropertyData * sp;
//    std::vector<PropertyData *> propertyVector1;
//    std::vector<PropertyData *> propertyVector2;
//    std::vector<PropertyData *> propertyVector3;
};
#endif /* ContactListener_hpp */
