//
//  EnemyRole.cpp
//  PojectShaoGame
//
//  Created by shao on 2018/8/4.
//

#include "EnemyRole.hpp"

EnemyRole * EnemyRole::createWithProperty(PropertyData *property, b2Body *body, std::string str)
{
    EnemyRole *enemyRole = new EnemyRole();
    if(enemyRole && enemyRole->init(property,body,str)){
        enemyRole->autorelease();
    }else{
        CC_SAFE_DELETE(enemyRole);
        return nullptr;
    }
    return enemyRole;
};
bool EnemyRole::init(PropertyData *property, b2Body *body, std::string str){
//    auto spriteA = Sprite::create("BoxA2.png");
    propertyData=property;
    this->body=body;
    this->setAnchorPoint(ccp(0.5,0.5));
    this->setTexture(property->getImage());
    this->setTag(property->getID());
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1,1);
    this->setCameraMask((unsigned short) CameraFlag::USER1);
    propertyData->setImage(property->getImage());
    propertyData->setID(property->getID());
    body->SetUserData(this);
    int tags = this->getTag();
    if( tags==39){
    sprite_title1 = Sprite::create("title.png");
    sprite_title1->setScaleX(0.8);
    sprite_title1->setScaleY(0.3);
    sprite_title1->setAnchorPoint(ccp(0.0,0.0));
    sprite_title1->setPosition(this->getPositionX()-40,this->getPositionY()+80);
    sprite_title1->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(sprite_title1,10);
    

    this->schedule(schedule_selector(EnemyRole::update));
}
    b2FixtureDef fixtureDef;
    fixtureDef.filter.groupIndex=-1;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
    return true;
};
void EnemyRole::setSchedule(){
    move =true;
}
void EnemyRole::setUnSchedule(){
    move =false;
}
void EnemyRole::update(float delta){
    if(move){
        if(i==1){
            b2Vec2 b2vec = b2Vec2((body->GetPosition().x)-0.080,body->GetPosition().y);
            body->SetTransform(b2vec,0);
            body->SetAwake(true);
        }else if(i==-1){
            b2Vec2 b2vec = b2Vec2((body->GetPosition().x)+0.080,body->GetPosition().y);
            body->SetTransform(b2vec,0);
            body->SetAwake(true);
        }
        else if(i==0){
            b2Vec2 b2vec = b2Vec2((body->GetPosition().x),body->GetPosition().y);
            body->SetTransform(b2vec,0);
            body->SetAwake(true);
        }
    }
}



