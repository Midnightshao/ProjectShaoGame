//
//  BaseRole.hpp
//  PojectGame
//
//  Created by shao on 2018/4/23.
//

#ifndef BaseRole_hpp
#define BaseRole_hpp
#include "PropertyData.hpp"
#include <cocos2d.h>
#include "Box2D/Box2D.h"
#include "iostream"
#include "BaseFSM.hpp"
#include "bones.hpp"
#include <spine/BoneData.h>
#include "spine/spine-cocos2dx.h"
#include "spine/spine.h"



#include <spine/extension.h>
#include <algorithm>
extern "C"{
#include <spine/SkeletonData.h>
#include <spine/AnimationState.h>
    //#include <spine/AnimationState.c>
}


USING_NS_CC;
class BaseFSM;
typedef enum {
    ROLE_DEFAULT1=1,
    Role_MOVE1,
    Role_DEATH1,
    Role_Jump1,
    Role_Jump2,
    Role_ATTAK1,
    Role_Fire
}ROLE_STATE1;

class BaseRole : public Layer{
    public:
    static BaseRole *createWithProperty(PropertyData *property,b2Body *body,std::string str);
    bool init(PropertyData *property,b2Body *body,std::string str);
    ROLE_STATE1 state;
    DrawNode * g;
    void  ChangeR(float dt);
    CC_SYNTHESIZE(spine::SkeletonAnimation *,f, SkeletonAnimation);
    CC_SYNTHESIZE(Sprite *,sprite, Sprite);
    CC_SYNTHESIZE(b2Body *,b2body, b2Body);

};
#endif /* BaseRole_hpp */
