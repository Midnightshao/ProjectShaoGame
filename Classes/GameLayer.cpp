//
//  GameLayer.cpp
//  PojectGame
//
//  Created by shao on 2018/4/23.
//

#include "GameLayer.hpp"
Scene * GameLayer::createScene(){
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = GameLayer::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}
bool GameLayer::init(){
    if ( !Layer::init() )
    {
        return false;
    }
    initPhysics();
    g=DrawNode::create();
    m_debugDraw = new GLESDebugDraw(PTM_RATIO);
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    auto roleMap = FileUtils::getInstance()->getValueMapFromFile("propertyRole.plist");

    PropertyData *propertyData = PropertyData::create();
    propertyData->setID(roleMap["ID"].asInt());
    propertyData->setHP(roleMap["HP"].asInt());
    hp = propertyData->getHP() * 0.01;
    //地图
    map =MapLayer::create();
    map->initWorld(world);
    map->setContext(this);
    map->setBackground("MapBackground.tmx");
    map->setCameraMask((unsigned short) CameraFlag::USER1);

    this->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(map);
    this->addChild(g);
    //dialog
    
    //血条
    Size s = Director::getInstance()->getVisibleSize();
    z=s.width/2.1;
    sprite_z=s.width/2.25;
    z1=s.height/2.12;
    sprite_z1=s.height/2.1;
    
    sprite_xin = Sprite::create("xin.png");
    sprite_xin->setCameraMask((unsigned short)CameraFlag::USER1);
    sprite_xin->setAnchorPoint(Vec2(0.0,0.0));
    this->addChild(sprite_xin,10);
    //
    sprite_title = Sprite::create("title.png");
    sprite_title->setScaleX(2.0   *hp);
    sprite_title->setScaleY(0.5);
    sprite_title->setCameraMask((unsigned short)CameraFlag::USER1);
    sprite_title->setAnchorPoint(Vec2(0.0,0.0));
    this->addChild(sprite_title,10);

    
    m_debugDraw->SetFlags(flags);   //需要显示那些东西
    
    world->SetDebugDraw(m_debugDraw);

    //人物
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(400/PTM_RATIO, 300/PTM_RATIO);
    body = world->CreateBody(&bodyDef);

    std::string  rolef = "role";
    role = BaseRole::createWithProperty(nullptr,body,rolef);
    role->setCameraMask((unsigned short) CameraFlag::USER1);
    addChild(role);
//
//
//
    //位移
    baseFSM = BaseFSM::createFSM1(role);
    baseFSM->initMap(map);
    baseFSM->initContext(this);
    baseFSM->initWorld(world);
    baseFSM->retain();
    

    
    //键盘
    auto myKeyListener = EventListenerKeyboard::create();
    myKeyListener->onKeyPressed   =  CC_CALLBACK_2(GameLayer::onkeybroadPressed, this);
    myKeyListener->onKeyReleased  =  CC_CALLBACK_2(GameLayer::onkeybroadReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);
    
    //键盘
    auto myKeyListener1 = EventListenerKeyboard::create();
    myKeyListener1->onKeyPressed   =  CC_CALLBACK_2(GameLayer::onkeybroadPressed1, this);
    myKeyListener1->onKeyReleased  =  CC_CALLBACK_2(GameLayer::onkeybroadReleased1, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener1, this);
    


    
    //触摸
    auto touch = cocos2d::EventListenerTouchOneByOne::create();
    touch->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touch, this);
    

//
    //摄像机
    this->setCameraMask((unsigned short) CameraFlag::USER1);
    g->setCameraMask((unsigned short) CameraFlag::USER1);

//
//    Vec2 p=Vec2(300, 200);
//    addNewSpriteAtPosition(Vec2(2000, 200));

    contactListener = new ContactListener();
    world->SetContactListener(contactListener);
//    scheduleUpdate();
    this->schedule(schedule_selector(GameLayer::update));
    return true;
};
bool GameLayer::onTouchBegan(Touch *touch,Event *event){

};
void GameLayer::onEnter(){
    Layer::onEnter();
};
void GameLayer::initPhysics(){
    Size s = Director::getInstance()->getVisibleSize();
    //重力参数
    b2Vec2 gravity;
    gravity.Set(0.0f, -20.0f);
    //创建世界
    world = new b2World(gravity);
    world->SetContinuousPhysics(true);
    //body边框检测
    m_debugDraw = new GLESDebugDraw(PTM_RATIO);
    // 允许物体是否休眠
    world->SetAllowSleeping(true);
    // 开启连续物理测试
    world->SetContinuousPhysics(true);
    // 定义物体地面
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);
    //创建地面物体
    b2Body* groundBody = world->CreateBody(&groundBodyDef);

    //定义一个有边的形状
    b2EdgeShape groundBox;
// 底部
    groundBox.Set(b2Vec2(0,0), b2Vec2((599),0));
//使用夹具固定形状到物体上
    groundBody->CreateFixture(&groundBox,0);
// 顶部
    groundBox.Set(b2Vec2(0,s.height*2/PTM_RATIO), b2Vec2(599,s.height*2/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
// 左边
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(0,0));
    groundBody->CreateFixture(&groundBox,0);
//  右边
     groundBox.Set(b2Vec2(599,s.height/PTM_RATIO), b2Vec2(599,0));
     groundBody->CreateFixture(&groundBox,0);
}

void GameLayer::onJumpTo(){
    
}
void GameLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags){
//
//    GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
//
//    world->DrawDebugData();
//
//    CHECK_GL_ERROR_DEBUG();
    
//    CCLayer::draw();
    
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
    
    kmGLPushMatrix();
    
    world->DrawDebugData();
    
    kmGLPopMatrix();
    
}

void GameLayer::onkeybroadPressed(EventKeyboard::KeyCode keycode, cocos2d::Event *event){
    CCLOG("key is pressed, keycode is %d", keycode);
    switch ((int)keycode) {
//  右键D键
        case 127:
            rockerDirection=1;
            onkeybroad=true;
            onJump=true;
            break;
//  左键A键
        case 124:
            rockerDirection=3;
            onkeybroad1=true;
            onJump=true;
            break;
        case 146:
            break;
        case 142:
            break;
    }
}

void GameLayer::onkeybroadReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event){
    switch ((int)keycode) {

        case 127:
            if(!onkeybroad1){
                rockerDirection=0;
            }
            onkeybroad1=false;
            onkeybroad =false;
            break;
        case 124:
            if(!onkeybroad){
                rockerDirection=0;
            }
            onkeybroad1=false;
            onkeybroad =false;
            break;
        case 146:
            break;
        case 142:
            break;
    }
}
bool ladder1;

void GameLayer::onkeybroadPressed1(EventKeyboard::KeyCode keycode, cocos2d::Event *event  ){
        switch ((int)keycode) {
        //ESC键
        case 6:
                if(!dialog){
                    dia=DialogLayer::createDialogLayer("MainScene.csb",propertyVector);
                    dia->setCameraMask((unsigned short)CameraFlag::USER2);
                    this->addChild(dia,60);
                    dialog=true;
                }else{
                    dialog=false;
                    this->schedule(schedule_selector(GameLayer::update));
                    this->removeChild(dia,true);
                }
            break;
        case 59:
//      空格键
            log("xxxxxx空格________________________________________ 跳跃");
//            rockerDirection1=0;
//                if(onJump){
                    baseFSM->changeToJump1();
                    this->schedule(schedule_selector(GameLayer::asyncUpdate1));
//                }
            break;
        case 133:
//      J键
                if(AllPropertyData::getSprite()!=nullptr){
                PropertyData *p=AllPropertyData::setPropertyData(AllPropertyData::getSprite()->getTag());
//                    baseFSM->changeToFire();
                    baseFSM->changeToAttack(p->getPlayerName());
                }else{
                    CCLOG("点击JJJJJJJJJJJ");
                }
            break;
//      W键
            case 146:
                if(this->ladder){
                    this->schedule(schedule_selector(GameLayer::asyncUpdate2));
                    rockerDirection1=10;
                }else{
                    CCLOG("点击上上上上上上上上上上上上上上上上上上上上上");
                    this->schedule(schedule_selector(GameLayer::asyncUpdate));
                    rockerDirection1=5;
                }
            break;
//      S键
        case 142:
                if(this->ladder){
                    this->schedule(schedule_selector(GameLayer::asyncUpdate2));
                    rockerDirection1=11;
                }else{
                    CCLOG("点击下下下下下下下下下下下下下下下下下下下下下下下");
                    this->schedule(schedule_selector(GameLayer::asyncUpdate));
                    rockerDirection1=6;
                }
                if(this->ladder1){
                    this->schedule(schedule_selector(GameLayer::asyncUpdate3_ladder));
                }
            break;
//        k键
            case 134:
                if(AllPropertyData::getSprite1()!=nullptr){
                    PropertyData *p=AllPropertyData::setPropertyData(AllPropertyData::getSprite1()->getTag());
                    baseFSM->changeToAttack(p->getPlayerName());
                    
                }else{
                    CCLOG("点击KKKKKKKKKKKK");
                }
                break;
    }
}

void GameLayer::onkeybroadReleased1(EventKeyboard::KeyCode keycode, cocos2d::Event *event){
    switch ((int)keycode) {
        case 59:
            log("xxxxxx空格 抬起");
//            this->unschedule(schedule_selector(GameLayer::asyncUpdate1));
            break;
        case 133:
            log("xxxxxxxx攻击1");
            log("xxxxxxxx攻击2");
            break;
        case 146:
            rockerDirection1=0;
            this->unschedule(schedule_selector(GameLayer::asyncUpdate));
             break;
        case 142:
            rockerDirection1=0;
            this->unschedule(schedule_selector(GameLayer::asyncUpdate));
            break;
    }
}

void GameLayer::addNewSpriteAtPosition(Vec2 p)
{
//    Vec2 p=Vec2(300, 200);
    log("Add sprite %0.2f x %02.f",p.x,p.y);
    auto spriteA = Sprite::create("BoxA2.png");
    spriteA->setTag(39);
    this->addChild(spriteA);
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet=true;
    bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);
    b2Body *bodyA = world->CreateBody(&bodyDef);
    body->SetBullet(true);
    bodyA->SetUserData(spriteA);
    
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1,1);

    spriteA->setCameraMask((unsigned short) CameraFlag::USER1);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    bodyA->CreateFixture(&fixtureDef);
}
//攻击敌人血格
float j;
void GameLayer::FighterCollidingWithEnemy(b2Body *body){
    if(body!=nullptr){
//        b2Body *body =contactListener->body;
        Sprite *sprite = (Sprite *)body->GetUserData();
        int a = sprite->getTag();
        EnemyRole *enemyRole = (EnemyRole *)sprite;
        int b=enemyRole->getTag();
        Sprite *sprite1=enemyRole->sprite_title1;
        sprite1->setAnchorPoint(ccp(0.0,0.0));
        j = sprite1->getScaleX();
        j = j-0.2;
        sprite1->setScaleX(j);
        if(j==0||j<0){
//        contactListener->b2body.push_back(body);
        world->DestroyBody(body);
        this->removeChild(sprite);
//            contactListener->sprite.push_back(sprite);
        }
        log("发射发射。。。。。。。。。。。。。。！！！！ %d", b);
        log("发射发射。。。。。。。。。。。。。。！^^^^^ %f", j);
        contactListener->body=nullptr;
    }
}
//被敌人攻击，主角的血槽
void GameLayer::FightCollidingWithRole(){
    b2Body *body = contactListener->bodyRole;
    if(body!=nullptr){
        hp = hp-0.1;
        sprite_title->setScaleX(2.0   *hp);
//      主角死亡处理
        if(hp==0||hp<0){
//            contactListener->b2body.push_back(body);
//            removeChild(role);
//            contactListener->sprite.push_back(role);
        }
        log("受到攻击。。。。。。。。。。。。。。！！！！ %d");
        log("发射发射。。。。。。。。。。。。。。！^^^^^ %f");
        contactListener->bodyRole=nullptr;
    }

}
void GameLayer::update(float dt){
    FighterCollidingWithEnemy(contactListener->getBody());
    FightCollidingWithRole();
    if(this->ladder){
//        CCLOG("攀爬true1111111111111");
    }else{
//        CCLOG("攀爬false");
        this->unschedule(schedule_selector(GameLayer::asyncUpdate2));
    }
    g->clear();
    float timeStep = 0.03f;
    int32 velocityIterations = 15;
    int32 positionIterations = 20;
    baseFSM->initJump(onJump);
//    CCLOG("..........  这个是。    。。。。。。%d", rockerDirection);
    baseFSM->swtichMoveState(rockerDirection);
    sprite_xin->setPosition(Vec2(map->getCamera()->getPosition().x-z,map->getCamera()->getPosition().y+z1));
    sprite_title->setPosition(Vec2(map->getCamera()->getPosition().x-sprite_z,map->getCamera()->getPosition().y+sprite_z1));
    
    world->Step(timeStep, velocityIterations, positionIterations);
//不断的迭代更新
    
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != nullptr) {
            Sprite* sprite = (Sprite*)b->GetUserData();
            if(sprite!=nullptr){
            sprite->setPosition( Vec2( b->GetPosition().x *PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
            sprite->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
                
                if(sprite->getTag()==29){
                    RaysCastCallback1 callback;
                    float j=-0.1;
                    for(int i=0;i<3;i++){
                        world->RayCast(&callback, b2Vec2((b->GetPosition().x),(b->GetPosition().y)),b2Vec2(b->GetPosition().x+j, b->GetPosition().y-0.1));
                        Vec2 pos(b->GetPosition().x*PTM_RATIO,(b->GetPosition().y)*PTM_RATIO);
                        g->drawLine(pos,Vec2(callback.point.x * PT_RATIO
                                             ,callback.point.y *PTM_RATIO)
                                    ,Color4F(134, 54, 78, 110));
                        if(callback.fixture!=nullptr){
                            b2Body *b2= callback.fixture->GetBody();
                            auto sprite=(Sprite *)b2->GetUserData();
                            
                            if(sprite!=nullptr){
                                if(sprite->getTag()==25){
                                    ladder1=true;
                                }else{
                                    ladder1=false;
                                }
                            }
                        }
                        j=j+0.1;
                    }

                    
                }
                //检测梯子
                if(sprite->getTag()==29){
                    RaysCastCallback callback;
                    world->RayCast(&callback, b2Vec2((b->GetPosition().x),(b->GetPosition().y+5)),b2Vec2(b->GetPosition().x, b->GetPosition().y+5.1));
                    Vec2 pos(b->GetPosition().x*PTM_RATIO,(b->GetPosition().y+5)*PTM_RATIO);
                    g->drawLine(pos,Vec2(callback.point.x * PT_RATIO
                                         ,callback.point.y *PTM_RATIO)
                                ,Color4F(134, 54, 78, 110));
                    if(callback.fixture!=nullptr){
                        b2Body *b2= callback.fixture->GetBody();
                        auto sprite=(Sprite *)b2->GetUserData();
                    
                        if(sprite!=nullptr){
                            if(sprite->getTag()==25){
                                b->SetTransform(b2Vec2(b->GetPosition().x,b->GetPosition().y+5),0);
                                this->unschedule(schedule_selector(GameLayer::asyncUpdate2));
                            }
                        }
                    }
                    for(int i=0;i<20;i++){
                        auto a=i*20.0;
                        double x=cos(a* b2_pi/180);
                        double y=sin(a* b2_pi/180);
                        Vec2 v(x,y);
                        RaysCastCallback callback;
                        world->RayCast(&callback,b2Vec2(b->GetPosition().x,b->GetPosition().y)
                                       ,b2Vec2(b->GetPosition().x+v.x*3
                                               , b->GetPosition().y+v.y*3));
                        Vec2 pos(b->GetPosition().x*PTM_RATIO,b->GetPosition().y*PTM_RATIO);
                        if(callback.fixture!=nullptr){
                            b2Body *b2= callback.fixture->GetBody();
                            auto sprite=(Sprite *)b2->GetUserData();
                            if(sprite!=nullptr){
                            if(sprite->getTag()==17){
//                                g->drawLine(pos,Vec2(callback.point.x * PT_RATIO
//                                                     ,callback.point.y *PTM_RATIO)
//                                                     ,Color4F(134, 54, 78, 110));
                                this->ladder=true;
                                break;
                                }
                            }
                        }else{
//                            CCLOG("不确定------------------------------！");
                            this->ladder=false;
                        }
                    }
                }
// 敌人39 的判断。
                if(sprite->getTag()==39){
                    EnemeyRoleFSM *enemyRoleFSM = EnemeyRoleFSM::create();
                    enemyRoleFSM->init();
                    enemyRoleFSM->setToBody(b,map);
                    EnemyRole *enemyRole =(EnemyRole *)sprite;
                    if(dialog){
                        enemyRole->move=false;
                    }else{
                        enemyRole->move=true;
                        //巡逻__________________________-----------------_______________-------------------------_________----_________=========
                    RaysCastCallback1 calls;
                    world->RayCast(&calls,b2Vec2(b->GetPosition().x,b->GetPosition().y-0.25)
                                   ,b2Vec2(b->GetPosition().x-1.5
                                           , b->GetPosition().y-0.25));
                    Vec2 pos(b->GetPosition().x*PTM_RATIO,b->GetPosition().y*PTM_RATIO);
//                    g->drawLine(pos,Vec2(calls.point.x * PT_RATIO
//                         ,calls.point.y *PTM_RATIO)
//                         ,Color4F(6, 54, 78, 110));
                    if(calls.fixture!=nullptr){
                        b2Body *b2= calls.fixture->GetBody();
                        auto sprite=(Sprite *)b2->GetUserData();
                        if(sprite!=nullptr){
                            if(sprite->getTag()!=17 && sprite->getTag()!=39){
                                enemyRole->i=-1;
                            }
                        }else{
                            enemyRole->i=-1;
                        }
                    }
                    RaysCastCallback1 calls1;
                    world->RayCast(&calls1,b2Vec2(b->GetPosition().x,b->GetPosition().y-0.25)
                                   ,b2Vec2(b->GetPosition().x+1.5
                                           , b->GetPosition().y-0.25));
//                    g->drawLine(pos,Vec2(calls1.point.x * PT_RATIO
//                                         ,calls1.point.y *PTM_RATIO)
//                                ,Color4F(6, 54, 78, 110));
                        if(calls1.fixture!=nullptr){
                            b2Body *b2= calls1.fixture->GetBody();
                            auto sprite=(Sprite *)b2->GetUserData();
                            if(sprite!=nullptr){
                                if(sprite->getTag()!=17 && sprite->getTag()!=39){
                                    enemyRole->i=1;
                                }
                            }else{
                                enemyRole->i=1;
                            }
                            
                        }
                }
//                    --------------------射线检测敌人
                    for(int i=0;i<18;i++){
                        auto a=i*100.0;
                        double x=cos(a* b2_pi/180);
                        double y=sin(a* b2_pi/180);
                        Vec2 v(x,y);
                        RaysCastCallback callback;
                        world->RayCast(&callback,b2Vec2(b->GetPosition().x,b->GetPosition().y)
                            ,b2Vec2(b->GetPosition().x+v.x*30
                            , b->GetPosition().y+v.y*30));
                        Vec2 pos(b->GetPosition().x*PTM_RATIO,b->GetPosition().y*PTM_RATIO);

//                        g->drawLine(pos,Vec2(callback.point.x * PT_RATIO,callback.point.y *PTM_RATIO),Color4F(1, 1, 1, 1));
                        
                        if(callback.fixture!=nullptr){
                            b2Body *b2= callback.fixture->GetBody();
                            auto sprite=(Sprite *)b2->GetUserData();
//                            CCLOG("这个是碰撞的射线。。。。。。。。。。。%d",sprite->getTag());
                            if(sprite!=nullptr){
                                if(sprite->getTag()==29){
                                    b2Vec2 bp(b2->GetPosition().x,b2->GetPosition().y);
                                    b2Vec2 bz(b->GetPosition().x,b->GetPosition().y);
                                    if(bp.x<bz.x){
                                        enemyRole->i=1;
                                        b->SetAwake(true);
                                    }else{
                                        enemyRole->i=-1;
                                        b->SetAwake(true);
                                    }
                                }else{

                                }
                            }
                        }

                    }
                }
            }
  }
}

    if(!contactListener->b2body.empty()){
        for(int i=0;i<contactListener->b2body.size();i++){
            b2Body *b=contactListener->b2body[i];
            world->DestroyBody(b);
        }
    }
    if(!contactListener->sprite.empty()){
        for(int i=0;i<contactListener->sprite.size();i++){
            Sprite *sprite=contactListener->sprite[i];
            this->removeChild(sprite,true);
        }
    }
    contactListener->b2body.clear();
    contactListener->sprite.clear();

    vector<b2Body *> f;
    vector<Sprite *> s;
    contactListener->b2body.swap(f);
    contactListener->sprite.swap(s);

}


void GameLayer::asyncUpdate(float t){
    baseFSM->swtichMoveState(rockerDirection1);
}
void GameLayer::asyncUpdate1(float t){
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != nullptr) {
            Sprite* sprite = (Sprite*)b->GetUserData();
            if(sprite!=nullptr){
                sprite->setPosition( Vec2( b->GetPosition().x *PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
                sprite->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
                shexian(b);
            }
        }
    }
//    CCLOG("这个是。。。。ffffffffeeeeeeeeiiiiiiiiiiii");
}
void GameLayer::asyncUpdate2(float t){
    baseFSM->swtichMoveState(rockerDirection1);
}
void GameLayer::asyncUpdate3_ladder(float t){
    body->SetTransform(b2Vec2(body->GetPosition().x,body->GetPosition().y-6.5),0);
    this->unschedule(schedule_selector(GameLayer::asyncUpdate3_ladder));
}
void GameLayer::shexian(b2Body *b){
    f=(spine::SkeletonAnimation *)b->GetUserData();
    if(f!=nullptr){
        if(f->getName()=="role"){
            g->clear();
            float j=-0.4;
           for(int i=0;i<=4;i++){
            RaysCastCallback1 callback;
            b2Vec2 v1(b->GetPosition().x+j,b->GetPosition().y);
            b2Vec2 v2(b->GetPosition().x+j,b->GetPosition().y-0.2);
            world->RayCast(&callback, v1, v2);
            g->drawLine(Vec2((b->GetPosition().x+j) *PTM_RATIO,b->GetPosition().y*PTM_RATIO),Vec2((callback.point.x)* PTM_RATIO, callback.point.y*PTM_RATIO),Color4F(1,1,1,1));
                                        j=j+0.3;
            if(callback.fixture!=nullptr){
                b2Body *b2= callback.fixture->GetBody();
                auto sprite=(Sprite *)b2->GetUserData();
                if(sprite!=nullptr && sprite->getTag()!=17){
                    if(sprite!=nullptr && sprite->getTag()!=8){
                        onJump = true;
                        baseFSM->initJump(onJump);
                        CCLOG("着地状态");
                        baseFSM->changeToDefault1();
                        this->unschedule(schedule_selector(GameLayer::asyncUpdate1));
                    }
                }
//                    break;
            }else{
                onJump = false;
                baseFSM->initJump(onJump);
                CCLOG("不着地状态");
            }
                                     }
        }
    }
}



