//
//  RayCastCallback1.hpp
//  PojectShaoGame
//
//  Created by shao on 2018/8/30.
//

#ifndef RayCastCallback1_hpp
#define RayCastCallback1_hpp
#include <stdio.h>
//#include "iostream"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
class RaysCastCallback1 :public b2RayCastCallback{
public:
    b2Fixture *fixture;
    b2Vec2 point;
    b2Vec2 normal;
    float32 fraction;
    RaysCastCallback1();
    virtual float32 ReportFixture(    b2Fixture* fixture, const b2Vec2& point,
                                  const b2Vec2& normal, float32 fraction);
};

#endif /* RayCastCallback1_hpp */
