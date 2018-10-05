//
//  Bullet.cpp
//  PojectShaoGame
//
//  Created by shao on 2018/5/9.
//

#include "Bullet.hpp"
Bullet *Bullet::createWithProperty(b2World *world,b2Vec2 vec,b2Vec2 vec0
                                   ,std::string name,int tag,float gravty,GameLayer *context
                                   ,b2Vec2 daxiao){
    Bullet *bullet = new Bullet();
    if(bullet && bullet->init(world,vec,vec0,name,tag,gravty,context,daxiao)){
        bullet->autorelease();
    }else{
        CC_SAFE_DELETE(bullet);
        return nullptr;
    }
    return bullet;
};
bool Bullet::init(b2World *world,b2Vec2 vec,b2Vec2 vec0
                  ,std::string name,int tag,float gravty,GameLayer *context
                  ,b2Vec2 daxiao){
    this->world=world;
    sprite =Sprite::create(name);
//    g=DrawNode::create();
//    g->setCameraMask((unsigned short) CameraFlag::USER1);
//    this->addChild(g);
    sprite->setTag(tag);
    sprite->setCameraMask((unsigned short) CameraFlag::USER1);
    this->addChild(sprite);
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet=true;
    
    gameLayer = context;
    body1 = this->world->CreateBody(&bodyDef);
    body1->SetTransform(vec0,0.0f);
    
    body1->SetBullet(true);
    body1->SetUserData(sprite);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(daxiao.x,daxiao.y);

    b2FixtureDef fixtureDef;
    if(tag==21){
        this->scheduleOnce(schedule_selector(Bullet::Move),2.0f);
        fixtureDef.filter.groupIndex=-1;
    }
    else if (tag==20){
//        this->scheduleOnce(schedule_selector(Bullet::Move),2.0f);
        this->schedule(schedule_selector(Bullet::Move1));
    }
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.3f;
    body1->CreateFixture(&fixtureDef);
    body1->SetGravityScale(gravty);
    //-------------------------------------------------------------
    CCLOG("x=%f.........y=%f.................xxxxxxxzzzzzzzzzyyyhhhhhheeeeexxxxxxxxxxxx",vec.x,vec.y);
    body1->SetLinearVelocity(vec);
//    this->schedule(schedule_selector(Bullet::update));

    return true;
};
void Bullet::Move(float dt){
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != nullptr) {
            Sprite* sprite = (Sprite*)b->GetUserData();
            if(sprite!=nullptr){
                sprite->setPosition( Vec2( b->GetPosition().x *PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
                sprite->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
                
                if(sprite->getTag()==21){
                    for(int i=0;i<25;i++){
                        RaysCastCallback callback;
                        auto a=i*20.0;
                        double x=cos(a* b2_pi/180);
                        double y=sin(a* b2_pi/180);
                        Vec2 v(x,y);
                        world->RayCast(&callback,b2Vec2(b->GetPosition().x,b->GetPosition().y)
                                       ,b2Vec2(b->GetPosition().x+v.x*5
                                               , b->GetPosition().y+v.y*5));
                        Vec2 pos(b->GetPosition().x*PTM_RATIO,b->GetPosition().y*PTM_RATIO);
//                        g->drawLine(pos,Vec2(callback.point.x * PT_RATIO
//                                             ,callback.point.y *PTM_RATIO),Color4F(24,1, 2, 89));
                        if(callback.fixture!=nullptr){
                            b2Body *b2= callback.fixture->GetBody();
                            auto sprite1=(Sprite *)b2->GetUserData();
                            if(sprite1!=nullptr){
                                if(sprite1->getTag()==39){
                                    gameLayer->FighterCollidingWithEnemy(b2);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    this->world->DestroyBody(body1);
    this->removeChild(sprite);
    gameLayer->removeChild(this);
}
void Bullet::update(float dt){

}
void Bullet::Move1(float dt){
    
    b2Vec2 vec = body1->GetLinearVelocity();
//    if((vec.x>-5&&vec.x<5) ){
////        gameLayer->contactListener->body1=nullptr;
//        this->world->DestroyBody(body1);
//        this->removeChild(sprite);
//        gameLayer->removeChild(this);
//    }else{}

    
    if(gameLayer->contactListener->body1!=nullptr){
        gameLayer->contactListener->body1=nullptr;
        this->world->DestroyBody(body1);
        this->removeChild(sprite);
        gameLayer->removeChild(this);
    }else if(vec.x>-5&&vec.x<5){
                this->world->DestroyBody(body1);
                this->removeChild(sprite);
                gameLayer->removeChild(this);
    }
}










