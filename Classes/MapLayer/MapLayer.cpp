//
//  MapLayer.cpp
//  PojectGame
//
//  Created by shao on 2018/4/23.
//

#include "MapLayer.hpp"
//MapLayer *MapLayer::createMapLayer(const char* filename){
//    MapLayer *mapLayer=MapLayer::create();
//    
//    if(mapLayer && mapLayer->setBackground(filename)){
//        mapLayer->autorelease();
//    }else{
//        CC_SAFE_DELETE(mapLayer);
//        return nullptr;
//    }
//    return mapLayer;
//};
bool MapLayer::setBackground(const char* filename){
    camera = Camera::create();
    camera->setCameraFlag(CameraFlag::USER1);
    this->addChild(camera);
    
    camera1 = Camera::create();
    camera1->setCameraFlag(CameraFlag::USER2);
    this->addChild(camera1);
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    tileMap = TMXTiledMap::create("shaoGameProject.tmx");
    //各种物品的属性，特殊编程，无法普遍性
    TMXObjectGroup *group = tileMap->getObjectGroup("thing");
    std::vector<Value> group1 =group->getObjects();
    for(int i=0;i<group1.size();i++){
        ValueMap spawnPoint = group1[i].asValueMap();
        std::string    name= spawnPoint["name"].asString();
        float  pro = spawnPoint["x"].asFloat();
        float  pro_y=spawnPoint["y"].asFloat();
        if(name!=""){
        auto gr = group->getObject(name);
        //object中的properteis
        std::string image = gr.at("Image").asString();
        CCLOG("方块名称vvvvvvvv %s",&image);
        int    id = gr.at("id").asInt();
        CCLOG("具体位置。%f",pro);
//        CCLOG("名称 。。。。。。。。。%s");
        //这个是实体数据
        PropertyData *property=PropertyData::create();
        property->setImage(image);
        property->setID(id);
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pro/PTM_RATIO, (pro_y/PTM_RATIO));
        b2Body *body=world->CreateBody(&bodyDef);
        EnemyRole *enemyRole = EnemyRole::createWithProperty(property,body,"str");
        gameLayer->addChild(enemyRole,9);
        }
    }
    initMap();
    addChild(tileMap);
    collidable1=tileMap->getLayer("background1");
        return true;
}
void MapLayer::initWorld(b2World *world1){
    this->world=world1;
};
void MapLayer::setContext(GameLayer *gameLayer){
    this->gameLayer=gameLayer;
    
}
void MapLayer::initMap(){
    int t=0;
    collidable2= tileMap->getLayer("Enemy");
    collidable = tileMap->getLayer("Background");
    
    for(int i=0;i<=599;i++){
        for(int j=0;j<=49;j++){
            log("方块！！！！！");
            int titleGid = collidable->getTileGIDAt(Vec2(i,j));
            int titleGid1 = collidable2->getTileGIDAt(Vec2(i,j));
//           基础方块
            if(titleGid>0){
                //这里是个titleGid
                CCLOG("i= %d, j = %d",i,j);
                CCLog("error buffer:%d" ,titleGid);
                if(titleGid == 1){
                    log("fffffAAAAAA");
                    auto sprite = Sprite::create("collidable_tiles.jpg");
                    sprite->setName("ground");
                    Vec2 vec0=collidable->getPositionAt(Vec2(i,j));
                    Vec2 vec=Vec2(vec0.x+PTM_RATIO/2, vec0.y+PTM_RATIO/2);
                    sprite->setTag(11);
                    CCLOG("vec = %d,,,,,,,vec1 = %d",vec.x,vec.y);
                    this->addChild(sprite,1);
                    CCLOG("t = %d",sprite->getTag());
                    t++;
                    b2BodyDef bodyDef;
                    bodyDef.type = b2_staticBody;
                    bodyDef.position.Set(vec.x/PTM_RATIO, (vec.y/PTM_RATIO));
                    b2Body *body=world->CreateBody(&bodyDef);
                    body->SetUserData(sprite);
                    b2PolygonShape dynamicBox;
                    dynamicBox.SetAsBox(0.5,0.5);
                    b2FixtureDef fixtureDef;
                    fixtureDef.density=0.0;
                    fixtureDef.friction=1.0;
//                    fixtureDef.isSensor = true;
                    fixtureDef.shape = &dynamicBox;
                    body->CreateFixture(&fixtureDef);
                }
                //梯子
                if(titleGid==5){
                    auto sprite = Sprite::create("ladder.png");
                    Vec2 vec0=collidable->getPositionAt(Vec2(i,j));
                    Vec2 vec=Vec2(vec0.x+PTM_RATIO/2, vec0.y+PTM_RATIO/2);
                    sprite->setTag(17);
                    CCLOG("梯子。。。。。梯子");
                    this->addChild(sprite,10);
                    b2BodyDef bodyDef;
                    bodyDef.type = b2_staticBody;
                    bodyDef.allowSleep=false;
                    bodyDef.bullet=true;
                    bodyDef.position.Set(vec.x/PTM_RATIO, (vec.y/PTM_RATIO));
                    b2Body *body=world->CreateBody(&bodyDef);
                    body->SetUserData(sprite);
                    b2PolygonShape dynamicBox;
                    dynamicBox.SetAsBox(0.5,0.5);
                    b2FixtureDef fixtureDef;
                    fixtureDef.density=0.0;
                    fixtureDef.friction=1.0;
                    fixtureDef.isSensor = true;
                    fixtureDef.shape = &dynamicBox;
                    body->CreateFixture(&fixtureDef);
                }
                //梯子与楼层之间的过渡
                if(titleGid==3){
                    auto sprite = Sprite::create("ladder1.png");
                    Vec2 vec0=collidable->getPositionAt(Vec2(i,j));
                    Vec2 vec=Vec2(vec0.x+PTM_RATIO/2, vec0.y+PTM_RATIO/2);
                    sprite->setTag(25);
                    CCLOG("梯子之间过渡");
                    this->addChild(sprite,10);
                    b2BodyDef bodyDef;
                    bodyDef.type = b2_staticBody;
                    bodyDef.allowSleep=false;
                    bodyDef.bullet=true;
                    
                    bodyDef.position.Set(vec.x/PTM_RATIO, (vec.y/PTM_RATIO));
                    b2Body *body=world->CreateBody(&bodyDef);
                    body->SetUserData(sprite);
                    b2PolygonShape dynamicBox;
                    
                    dynamicBox.SetAsBox(0.5,0.5);
                    b2FixtureDef fixtureDef;
                    fixtureDef.density=0.0;
                    fixtureDef.friction=1.0;
                    fixtureDef.isSensor = false;
                    
                    
                    fixtureDef.shape = &dynamicBox;
//                    fixtureDef.filter.categoryBits=
                    body->CreateFixture(&fixtureDef);
                }
            }
            //敌人
            if(titleGid1>0){
                //敌人
                if(titleGid1==2){
                    Vec2 vec0=collidable2->getPositionAt(Vec2(i,j));
                    Vec2 vec=Vec2(vec0.x+PTM_RATIO/2, vec0.y+PTM_RATIO/2);
                    b2BodyDef bodyDef;
                    bodyDef.type = b2_dynamicBody;
                    bodyDef.position.Set(vec.x/PTM_RATIO, (vec.y/PTM_RATIO));
                    b2Body *body=world->CreateBody(&bodyDef);
                    PropertyData *property=PropertyData::create();
                    property->setImage("BoxB2.png");
                    property->setID(39);
                    EnemyRole *enemyRole = EnemyRole::createWithProperty(property,body,"str");
//                    enemyRole->setUserData(property);
                    gameLayer->addChild(enemyRole,10);
                }
                //限制方格
                if(titleGid1==7){
                    log("fffffAAAAAA");
                    auto sprite = Sprite::create();
                    Vec2 vec0=collidable2->getPositionAt(Vec2(i,j));
                    Vec2 vec=Vec2(vec0.x+PTM_RATIO/2, vec0.y+PTM_RATIO/2);
                    sprite->setTag(8);
                    CCLOG("vec = %d,,,,,,,vec1 = %d",vec.x,vec.y);
                    this->addChild(sprite,1);
                    CCLOG("t = %d",sprite->getTag());
                    b2BodyDef bodyDef;
                    bodyDef.type = b2_staticBody;
                    bodyDef.position.Set(vec.x/PTM_RATIO, (vec.y/PTM_RATIO));
                    b2Body *body=world->CreateBody(&bodyDef);
                    body->SetUserData(sprite);
                    b2PolygonShape dynamicBox;
                    dynamicBox.SetAsBox(0.5,0.5);
                    b2FixtureDef fixtureDef;
                    fixtureDef.density=0.0;
                    fixtureDef.friction=1.0;
                    fixtureDef.isSensor = true;
                    fixtureDef.shape = &dynamicBox;
                    body->CreateFixture(&fixtureDef);
                }
            }
            //绳子梯子
            
        }
    }
}
    


