//
//  BaseFSM.cpp
//  PojectShaoGame
//
//  Created by shao on 2018/5/4.
//

#include "BaseFSM.hpp"
#include "BaseFSM.hpp"
BaseFSM *BaseFSM::createFSM1(BaseRole *baseRole){
    
    BaseFSM *baseFSM =new BaseFSM();
    if(baseFSM && baseFSM->init(baseRole)){
        baseFSM ->autorelease();
    }else{
        CC_SAFE_DELETE(baseFSM);
    }
    return baseFSM;
};
bool BaseFSM::init(BaseRole *baseRole1){
    role=baseRole1;
    role->getSkeletonAnimation()->setStartListener(CC_CALLBACK_1(BaseFSM::startListener,this));
    return true;
}
void BaseFSM::initWorld(b2World *world){
    this->world=world;
}
void BaseFSM::initMap(MapLayer *map){
    this->map=map;
}
void BaseFSM::initContext(GameLayer *context){
    this->context = context;
    g= DrawNode::create();
    context->addChild(g);
}
void BaseFSM::swtichMoveState(int dir){
    switch (dir) {
        case 0:
            this->changeToDefault();
            break;
        case 1:
            this->changeToRight();
            break;
        case 3:
            this->changeToLeft();
            break;
        case 4:
//            this->changeToAttack();
            break;
        case 5:
            this->changeToUp();
            break;
        case 6:
            this->changeToDown();
            break;
        case 7:
            this->changeToJump();
            break;
        case 8:
            this->changeToJump1();
            break;
        case 9:
            this->changeToDefault1();
            break;
        case 10:this->changeToShin();
            break;
        case 11:this->changeToSkin1();
            break;
        case 12:
            this->changeToLeftFire();
            break;
        case 13:
            this->changeToRightFire();
            break;
        default:
//            this->changeToDefault();
            break;
    }
}
void BaseFSM::initJump(bool ajump){
    this->ajump=ajump;
}
//攀爬
void BaseFSM::changeToShin(){
    b2Body *body=role->getb2Body();
    b2Vec2 b2vec = b2Vec2((body->GetPosition().x),body->GetPosition().y+0.205);
    body->SetGravityScale(0);
    body->SetTransform(b2vec,map->getRotation());
    body->SetFixedRotation(true);
    body->SetAwake(true);
};
void BaseFSM::changeToSkin1(){
    b2Body *body=role->getb2Body();
    b2Vec2 b2vec = b2Vec2((body->GetPosition().x),body->GetPosition().y-0.205);
    body->SetGravityScale(0);
    body->SetTransform(b2vec,map->getRotation());
    body->SetFixedRotation(true);
    body->SetAwake(true);
}
void BaseFSM::swtichMoveState1(int dir){
    switch (dir) {
        case 0:
            this->changeToDefault();
            break;
        case 5:
//            this->changeToJump();
            break;
        case 4:
            this->changeToAttack("gun");
            break;
        default:
            break;
    }
}
void BaseFSM::changeToFire(){
    spine::SkeletonAnimation *f = role->getSkeletonAnimation();
    role->getSkeletonAnimation()->setAnimation(0, "fire", false);
}
void BaseFSM::changeToFire1(){
//    spine::SkeletonAnimation *f = role->getSkeletonAnimation();
//    role->getSkeletonAnimation()->setAnimation(0, "run2", true);
}
//攻击方向
void BaseFSM::changeToUp(){
    if(role->state !=Role_Fire){
        role->state = Role_Fire;
    changeToFire();
    b2Body *body=role->getb2Body();
    spine::SkeletonAnimation *f = role->getSkeletonAnimation();
//    role->getSkeletonAnimation()->setAnimation(0, "fire", true);
    //true是指循环播放walk动作
    
    spBone *bone1 =f->findBone("arm1");
    if(bone1){
        log("true...................");
    }else{
        log("false...................");
    }
    bone1->rotation=bone1->rotation+1.0f;
    spSkeleton *sk = bone1->skeleton;
    spAnimationStateData *s=spAnimationStateData_create(sk->data);
    spAnimationState *_state=spAnimationState_create (s);
    
    
    spBone *bone2 =f->findBone("armL");
    bone2->rotation=bone1->rotation+5;
    spSkeleton *sk1 = bone2->skeleton;
    spAnimationStateData *s1=spAnimationStateData_create(sk1->data);
    spAnimationState *_state1=spAnimationState_create (s1);
    
//    if(bone2){
//        g->clear();
//        b2Vec2 b2vec1 = b2Vec2((body->GetPosition().x +bone2->worldX/PTM_RATIO),body->GetPosition().y+bone2->worldY/PTM_RATIO);
//    }else{
//        log("log .........................false");
//    }
    spAnimationStateData_dispose (s);
    spAnimationState_dispose(_state);
    
    spAnimationStateData_dispose (s1);
    spAnimationState_dispose(_state1);
    }
}

void BaseFSM::changeToDown(){
    if(role->state !=Role_Fire){
        role->state = Role_Fire;
        changeToFire();
        b2Body *body=role->getb2Body();
        spine::SkeletonAnimation *f = role->getSkeletonAnimation();
        spBone *bone1 =f->findBone("arm1");
        bone1->rotation=bone1->rotation-1.0f;
        spSkeleton *sk = bone1->skeleton;
        spAnimationStateData *s=spAnimationStateData_create(sk->data);
        spAnimationState *_state=spAnimationState_create (s);
        
        spBone *bone2 =f->findBone("armL");
        bone2->rotation=bone1->rotation+5;
        spSkeleton *sk1 = bone2->skeleton;
        spAnimationStateData *s1=spAnimationStateData_create(sk1->data);
        spAnimationState *_state1=spAnimationState_create (s1);
        //    if(bone2){
        //        g->clear();
        //        b2Vec2 b2vec1 = b2Vec2((body->GetPosition().x+bone2->worldX/PTM_RATIO),body->GetPosition().y+bone2->worldY/PTM_RATIO);
        //    }else{
        //        log("log .........................false");
        //    }
        spAnimationStateData_dispose (s);
        spAnimationState_dispose(_state);
        spAnimationStateData_dispose (s1);
        spAnimationState_dispose(_state1);
    }

}
void BaseFSM::changeToDefault(){
    b2Body *body=role->getb2Body();
    spine::SkeletonAnimation *f = role->getSkeletonAnimation();
    if(role->state !=ROLE_DEFAULT1){
        role->state=ROLE_DEFAULT1;
        log("态度");
//        if(ajump){
//            CCLOG("ajump   true.........");
            f->setAnimation(0,"idle",true);
//        }else{
//            CCLOG("ajump   false.......");
//        }
//        f->setAnimation(0,"idle",true);
        log("原始状态1——————————————————————————————————");
        }
//    body->SetGravityScale(1);
    body->SetAwake(true);
    }
void BaseFSM::changeToDefault1(){
    b2Body *body=role->getb2Body();
    spine::SkeletonAnimation *f = role->getSkeletonAnimation();
            log("跳跃以后发生的动画。。。。。。。。。。。。。。。。。。。。。。。。。。。。。");
            f->setAnimation(1,"idle",false);
            body->SetAwake(true);
}
void BaseFSM::changeToAttack(std::string  gun){
    b2Body *body=role->getb2Body();
    if(role->state!=Role_ATTAK1){
        role->state=Role_ATTAK1;
    }
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    
//    b2Body *body1 = world->CreateBody(&bodyDef);
//
    role->getSkeletonAnimation()->setAnimation(0, "fire", true);//true是指循环播放walk动作

    spine::SkeletonAnimation *f = role->getSkeletonAnimation();
    spBone *bone1 =f->findBone("armL");
    spBone *bone3 =f->findBone("arm1");
    float rotation=bone1->rotation;
    float radian = rotation*(2*3.1415926)/360;
    float rotation_x = 20;
    float rotation_y = 20*tan(radian);

    float vo= 20;
    float rotation1=bone3->rotation;
    float radian1 = rotation1*(2*3.1415926)/360;
    float rotation_x1 = vo*-1;
    float rotation_y1 = vo*tan(radian1);
    g->clear();
    spBone *bone2 =f->findBone("Bullet");
    spBone *bone4 =f->findBone("Bullet");
    if(bone2){
        log("log.....................%f",bone2->worldX/PTM_RATIO);
        log("log.....................%f",bone2->worldY/PTM_RATIO);
        g->clear();
    }else{
        log("log .........................false");
    }
    //子弹
    if(role->getSkeletonAnimation()->getSkeleton()->flipX==0){
        g->clear();
        b2Vec2 b2vec2 = b2Vec2((body->GetPosition().x+bone2->worldX/PTM_RATIO),body->GetPosition().y+bone2->worldY/PTM_RATIO);
        CCLOG("%f.............................xxxxxxxxxxxxxxxxxxx",bone1->rotation);
//        g->drawDot(Vec2((b2vec2.x)   *32,(b2vec2.y)  *32),5,Color4F(1, 0, 0, 1));
        if(gun =="gun"){
            
//            initBullet(body,b2vec2,b2Vec2(rotation_x,rotation_y));
            Bullet*bullet = Bullet::createWithProperty(world,b2Vec2(rotation_x,rotation_y),b2vec2,"zidan.png",20,0, context, b2Vec2(PTM_L*10,PTM_L*6));
            context->addChild(bullet);
            
        }else if(gun=="bomb"){
            Bullet*bullet = Bullet::createWithProperty(world,b2Vec2(rotation_x,rotation_y),b2vec2,"zhadan_large.png",21,3.0, context, b2Vec2(1,1));
            context->addChild(bullet);
            
        }
//        Bullets(b2vec2,b2Vec2(rotation_x,rotation_y));
    }
    else if(role->getSkeletonAnimation()->getSkeleton()->flipX==-1){
        b2Vec2 b2vec1 = b2Vec2((body->GetPosition().x+bone4->worldX/PTM_RATIO),body->GetPosition().y
                               +bone4->worldY/PTM_RATIO);
        CCLOG("%f.............................xxxxxxxxxxxxxxxxxxx",bone1->rotation);
//        g->drawDot(Vec2((b2vec1.x)   *32,(b2vec1.y)  *32),5,Color4F(1, 0, 0, 1));
        if(gun=="gun"){
//            initBullet(body,b2vec1,b2Vec2(rotation_x1,rotation_y1));
            Bullet*bullet = Bullet::createWithProperty(world,b2Vec2(rotation_x1,rotation_y1),b2vec1,"zidan.png",20,0, context, b2Vec2(PTM_L*10,PTM_L*6));
            context->addChild(bullet);
        }else if(gun == "bomb"){
        Bullet*bullet = Bullet::createWithProperty(world,b2Vec2(rotation_x1,rotation_y1),b2vec1,"zhadan_large.png",21,3.0, context, b2Vec2(1,1));
        context->addChild(bullet);
        }
    }
}

void BaseFSM::initBullet(b2Body *body,b2Vec2 b2vec,b2Vec2 b2vec1){
    Sprite *sprite =Sprite::create("zidan.png");
    sprite->setName("zidan");
    sprite->setTag(20);
    sprite->setCameraMask((unsigned short) CameraFlag::USER1);
    this->context->addChild(sprite);
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet=true;
    b2Body *body1 = world->CreateBody(&bodyDef);
    body1->SetTransform(b2vec,0.0f);
    body1->SetBullet(true);
    body1->SetUserData(sprite);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(PTM_L*10,PTM_L*6);
    
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body1->CreateFixture(&fixtureDef);
    body1->SetGravityScale(0);
//-------------------------------------------------------------
    CCLOG("x=%f.........y=%f.................xxxxxxxzzzzzzzzzyyyhhhhhheeeeexxxxxxxxxxxx",b2vec1.x,b2vec1.y);
    body1->SetLinearVelocity(b2vec1);
//    body1->SetAwake(true);
}
void BaseFSM::initBomb(b2Body *body, b2Vec2 b2vec, b2Vec2 b2vec1){
    Sprite *sprite =Sprite::create("zhadan_large.png");
    sprite->setTag(21);
    sprite->setCameraMask((unsigned short) CameraFlag::USER1);
    this->context->addChild(sprite);
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet=true;
    b2Body *body1 = world->CreateBody(&bodyDef);
    body1->SetTransform(b2vec,0.0f);
    body1->SetBullet(true);
    body1->SetUserData(sprite);
    b2PolygonShape dynamicBox;
    
    b2CircleShape circleShape;
    circleShape.m_radius=1;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body1->CreateFixture(&fixtureDef);
    body1->SetGravityScale(2.0);
    //-------------------------------------------------------------
    CCLOG("x=%f.........y=%f.................xxxxxxxzzzzzzzzzyyyhhhhhheeeeexxxxxxxxxxxx",b2vec1.x,b2vec1.y);
    body1->SetLinearVelocity(b2vec1);
}
void BaseFSM::changeToLeft(){
    if(role->state!=Role_Fire){
    b2Body *body=role->getb2Body();
            if(role->state!=Role_MOVE1 && role->state!=Role_Jump1 ){
//                CCLog("ajump============   ,%s",ajump);
                    role->state=Role_MOVE1;
                if(ajump){
                    CCLOG("往右。。。。。。。。。。。。！！！！！！！！！！！！！！！！");
                    role->getSkeletonAnimation()->setAnimation(0, "run", true);//true是指循环播放walk动作
                }
    }
    CCLOG("log.......................llll");
    b2Vec2 b2vec = b2Vec2((body->GetPosition().x)-0.205,body->GetPosition().y);
    body->SetTransform(b2vec,map->getRotation());
    body->SetFixedRotation(true);
    body->SetGravityScale(1.0f);
    Size  size=Director::getInstance()->getVisibleSize();
    if(b2vec.x*32>size.width/2){
        map->getCamera()->setPosition(b2vec.x*32,map->getCamera()->getPosition().y);
    }
    role->getSkeletonAnimation()->getSkeleton()->flipX=-1;
    //face left
    body->SetAwake(true);
    }
}
//____________
void BaseFSM::changeToLeftFire(){
    
    
    b2Body *body=role->getb2Body();
    if(role->state!=Role_MOVE1 && role->state!=Role_Jump1 ){
//                        CCLog("ajump============   ,%s",ajump);
        role->state=Role_MOVE1;
        if(ajump){
            CCLOG("往右。。。。。。。。。。。。！！！！！开枪");
            role->getSkeletonAnimation()->setAnimation(0, "run2", true);//true是指循环播放walk动作
        }
    }
    CCLOG("log.......................llll");
    b2Vec2 b2vec = b2Vec2((body->GetPosition().x)-0.205,body->GetPosition().y);
    body->SetTransform(b2vec,map->getRotation());
    body->SetFixedRotation(true);
    body->SetGravityScale(1.0f);
    Size  size=Director::getInstance()->getVisibleSize();
    if(b2vec.x*32>size.width/2){
        map->getCamera()->setPosition(b2vec.x*32,map->getCamera()->getPosition().y);
    }
    role->getSkeletonAnimation()->getSkeleton()->flipX=-1;
    //face left
    body->SetAwake(true);
}

void BaseFSM::changeToRight(){
    b2Body *body=role->getb2Body();
    if(role->state!=Role_Fire){
        if(role->state!=Role_MOVE1 && role->state!=Role_Jump1 ){
                role->state=Role_MOVE1;
            if(ajump){
                CCLOG("往右。。。。。。。。。。。。！！！！！！！！！！！！！！！！");
                role->getSkeletonAnimation()->setAnimation(0, "run", true);//true是指循环播放walk动作
            }
        }
    log("fffffffffffffffffffja");
    b2Vec2 b2vec = b2Vec2((body->GetPosition().x)+0.205,body->GetPosition().y);
    body->SetTransform(b2vec,map->getRotation());
    body->SetGravityScale(1.0f);
    body->SetFixedRotation(true);
    body->SetAwake(true);
    Size  size=Director::getInstance()->getVisibleSize();
    if(b2vec.x*32>size.width/2){
    map->getCamera()->setPosition(b2vec.x*32,map->getCamera()->getPosition().y);
    }
    //face right
    role->getSkeletonAnimation()->getSkeleton()->flipX=0;
    }
}
void BaseFSM::changeToRightFire(){
    b2Body *body=role->getb2Body();
    if(role->state!=Role_MOVE1 && role->state!=Role_Jump1 ){
        role->state=Role_MOVE1;
        if(ajump){
            CCLOG("往右。。。。。。。。。。。。！！！！！！！！！！！！！！！！");
            role->getSkeletonAnimation()->setAnimation(0, "run2", true);//true是指循环播放walk动作
        }
    }
    log("fffffffffffffffffff开火。。。。。。。。。。fire");
    b2Vec2 b2vec = b2Vec2((body->GetPosition().x)+0.205,body->GetPosition().y);
    body->SetTransform(b2vec,map->getRotation());
    body->SetGravityScale(1.0f);
    body->SetFixedRotation(true);
    body->SetAwake(true);
    Size  size=Director::getInstance()->getVisibleSize();
    if(b2vec.x*32>size.width/2){
        map->getCamera()->setPosition(b2vec.x*32,map->getCamera()->getPosition().y);
    }
    //face right
    role->getSkeletonAnimation()->getSkeleton()->flipX=0;
}
void BaseFSM::changeToJump(){
//    b2Body *body=role->getb2Body();
//    if(role->state!=Role_Jump1){
//        role->state=Role_Jump1;
//        body->SetAwake(true);
//        role->getSkeletonAnimation()->setAnimation(1,"jump", false);
//    }
}
void BaseFSM::changeToJump1(){
    b2Body *body=role->getb2Body();
    if(role->state!=Role_Jump2){
        role->state=Role_Jump2;
        log("抬起________________________1");
        role->getSkeletonAnimation()->setAnimation(1,"jump1",false);
    }
    body->SetLinearVelocity(b2Vec2(0,20));
    body->SetFixedRotation(true);
    body->SetAwake(true);
}


void BaseFSM::startListener(spTrackEntry *entry){
    spAnimation *animation=entry->animation;
}
void BaseFSM::changeToRecovery(){
}
void BaseFSM::changeToDestroy(b2Body *body){
        world->DestroyBody(body);
}




