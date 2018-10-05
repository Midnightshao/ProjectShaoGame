//
//  Bullet.hpp
//  PojectShaoGame
//
//  Created by shao on 2018/5/9.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include <iostream>
#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include  "GameLayer.hpp"
#define PTM_RATIO 32

using namespace std;
USING_NS_CC;
class GameLayer;
class Bullet :public Layer{
//        CC_SYNTHESIZE(cocos2d::Vec2,velocity, Velocity);
    public:
    static Bullet *createWithProperty(b2World *world,b2Vec2 vec,b2Vec2 vec0
                                      ,std::string name,int tag,float gravty,GameLayer *context
                                      ,b2Vec2 daxiao);
        bool init(b2World *world,b2Vec2 vec,b2Vec2 vec0
                  ,std::string name,int tag,float gravty,GameLayer *context
                  ,b2Vec2 daxiao);
        Sprite *sprite;
        b2Body *body1;
        DrawNode *g;

    void  update(float dt);
    void  Move(float dt);
    void  Move1(float dt);
    std::vector<b2Body *> b2body1;
    std::vector<Sprite *> sprite1;
    
public:
        GameLayer *gameLayer;
    public:
        b2World *world;
};

#endif /* Bullet_hpp */
