//
//  RaysCastCallback.hpp
//  PojectShaoGame
//
//  Created by shao on 2018/5/18.
//

#ifndef RaysCastCallback_hpp
#define RaysCastCallback_hpp

#include <stdio.h>
//#include "iostream"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
class RaysCastCallback :public b2RayCastCallback{
public:
    b2Fixture *fixture;
    b2Vec2 point;
    b2Vec2 normal;
    float32 fraction;
    RaysCastCallback();
    virtual float32 ReportFixture(    b2Fixture* fixture, const b2Vec2& point,
                                  const b2Vec2& normal, float32 fraction);
};

#endif /* RaysCastCallback_hpp */
