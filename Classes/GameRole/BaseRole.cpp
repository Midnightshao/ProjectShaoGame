//
//  BaseRole.cpp
//  PojectGame
//
//  Created by shao on 2018/4/23.
//

#include "BaseRole.hpp"
#include <spine/BoneData.h>
#include "spine/spine-cocos2dx.h"

BaseRole *BaseRole::createWithProperty(PropertyData *property,b2Body *body,std::string str){
    BaseRole *baseRole = new BaseRole();
    if(baseRole && baseRole->init(property,body,str)){
        baseRole->autorelease();
    }else{
        CC_SAFE_DELETE(baseRole);
        return nullptr;
    }
    return baseRole;
}
bool BaseRole::init(PropertyData *property,b2Body *body,std::string str){
    int i=1;
    f=spine::SkeletonAnimation::createWithJsonFile("bodyname.json", "bodyname.atlas",0.13f);
    bool ac=f->setAttachment("arm","body1/arm");
//    g = DrawNode::create();
    
    f->setCameraMask((unsigned short) CameraFlag::USER1);
    b2PolygonShape dynamicBox;
    body->SetUserData(f);
    f->setTag(29);
    dynamicBox.SetAsBox(i, i*2.5,b2Vec2(0,2.5),this->getRotation());
    f->setName(str);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 3.0f;
    fixtureDef.friction = 2.0f;
    body->CreateFixture(&fixtureDef);
    body->SetBullet(true);
    body->SetAwake(true);
    this->setb2Body(body);
    this->addChild(f);
    this->schedule(schedule_selector(BaseRole::ChangeR));
    return true;
}
void BaseRole::ChangeR(float dt){
    
    if(AllPropertyData::getSprite()!=nullptr){
        f->setAttachment("arm","body1/armgun");
    }
}
