//
//  ContactListener.cpp
//  PojectShaoGame
//
//  Created by shao on 2018/5/16.
//

#include "ContactListener.hpp"

void ContactListener::BeginContact(b2Contact *contact){
//    log("BeginContact   AAAAAAAAAAAAAA");
    b2Body *bodyA= contact->GetFixtureA()->GetBody();
    b2Body *bodyB= contact->GetFixtureB()->GetBody();
    
    auto spriteA = (Sprite *)bodyA->GetUserData();
    auto spriteB = (Sprite *)bodyB->GetUserData();
    
    if(spriteA==nullptr){
//        log("碰撞A为空");
    }else{
//        CCLOG("spriteA....为%d",spriteA->getTag());
    }
    if(spriteB==nullptr){
//        log("碰撞B为空");
    }else{
//        CCLOG("spriteB....为%d",spriteB->getTag());
    }
    if(spriteA!=nullptr && spriteB!=nullptr){
        
        if(spriteA->getTag()==39 ){
            if(spriteB->getTag()==20){
                log("EndContact 方块消除");
                body =bodyA;
                body1=bodyB;
            }
        }
        if(spriteA->getTag()==20 ){
            if(spriteB->getTag()==39){
                log("EndContact 方块消除");
                body =bodyB;
                body1=bodyA;
            }
        }
        //处理敌人与主角的碰撞
        if(spriteA!=nullptr && spriteB!=nullptr){
            if(spriteA->getTag()==39 ){
                if(spriteB->getTag()==29){
                    bodyRole =bodyA;
                }
            }
            if(spriteA->getTag()==29 ){
                if(spriteB->getTag()==39){
                    bodyRole =bodyB;
                }
            }
        }
        
        if(spriteA->getTag()==39 || spriteA->getName()=="ground"||spriteA->getTag()==20){
            if(spriteB->getTag()==20){
                log("EndContact 子弹消除");
//                spriteB->setColor(Color3B(210,78,71));
//                b2body.push_back(bodyB);
//                sprite.push_back(spriteB);
                body1=bodyB;

            }
        }
            if(spriteA->getTag()==20){
                if(spriteB->getTag()==39 || spriteB->getName()=="ground"||spriteB->getTag()==20){
                log("EndContact 子弹消除");
                  body1=bodyA;
            }
        }
        if(spriteA->getTag()==44){
            if(spriteB->getTag()==29){
                CCLOG("已经碰撞到了++++++++++++++++++++++++++++++++++");
                AllPropertyData::setSprite1(spriteA);
                spriteA->setVisible(false);
                b2body.push_back(bodyA);
//                sprite.push_back(spriteA);
            }
        }
        if(spriteA->getTag()==41){
            if(spriteB->getTag()==29){
                AllPropertyData::setSprite(spriteA);
                b2body.push_back(bodyA);
                spriteA->setVisible(false);
//                sprite.push_back(spriteA);
                CCLOG("已经碰撞到了++++++++++++++++++++++++++++++++++");
            }
        }
    }
};
b2Body * ContactListener::getBody(){
    return body;
}
void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){
    b2Body *bodyA= contact->GetFixtureA()->GetBody();
    b2Body *bodyB= contact->GetFixtureB()->GetBody();
    
    auto spriteA = (Sprite *)bodyA->GetUserData();
    auto spriteB = (Sprite *)bodyB->GetUserData();
    

    
}
void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse){
    b2Body *bodyA= contact->GetFixtureA()->GetBody();
    b2Body *bodyB= contact->GetFixtureB()->GetBody();
    
    auto spriteA = (Sprite *)bodyA->GetUserData();
    auto spriteB = (Sprite *)bodyB->GetUserData();
    

}
void ContactListener::EndContact(b2Contact* contact){
    
//    log("BeginContact   BBBBBBBBBBBBBBBBBB");

    
    b2Body *bodyA= contact->GetFixtureA()->GetBody();
    b2Body *bodyB= contact->GetFixtureB()->GetBody();
    
    auto spriteA = (Sprite *)bodyA->GetUserData();
    auto spriteB = (Sprite *)bodyB->GetUserData();


    
}
