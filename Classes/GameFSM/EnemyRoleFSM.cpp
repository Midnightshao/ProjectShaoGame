//
//  EnemyRoleFSM.cpp
//  PojectShaoGame
//
//  Created by shao on 2018/9/5.
//

#include "EnemyRoleFSM.hpp"
bool EnemeyRoleFSM::init(){
    return true;
}
void EnemeyRoleFSM::setToBody(b2Body *body,MapLayer *map){
    this->body=body;
    this->map=map;
}
void EnemeyRoleFSM::swtichMoveState(int code){
    switch (code) {
        case 1:
            changeToLeft();
            break;
        case -1:
            changeToRight();
            break;
        default:
            break;
    }
}
void EnemeyRoleFSM::changeToLeft(){
    body->SetTransform(b2Vec2(body->GetPosition().x-0.0450,body->GetPosition().y),map->getRotation());
    body->SetAwake(true);
}
void EnemeyRoleFSM::changeToRight(){
    body->SetTransform(b2Vec2(body->GetPosition().x+0.0450,body->GetPosition().y),map->getRotation());
    body->SetAwake(true);
}
void EnemeyRoleFSM::changeToAttack(){
    
}
