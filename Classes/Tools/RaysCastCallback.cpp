//
//  RaysCastCallback.cpp
//  PojectShaoGame
//
//  Created by shao on 2018/5/18.
//

#include "RaysCastCallback.hpp"

RaysCastCallback::RaysCastCallback():
fraction(0),
point(b2Vec2_zero),
normal(b2Vec2_zero),
fixture(nullptr){
    
}

float RaysCastCallback::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction)
{
   
    this->fixture=fixture;
    this->point=point;
    this->normal=normal;
    this->fraction=fraction;
    

    return fraction;
};
