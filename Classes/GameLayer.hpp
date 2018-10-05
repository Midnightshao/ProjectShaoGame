//
//  GameLayer.hpp
//  PojectGame
//
//  Created by shao on 2018/4/23.
//

#ifndef GameLayer_hpp
#define GameLayer_hpp
#include "Box2D/Box2D.h"
#include <iostream>
#include "MapLayer.hpp"
#include "cocos2d.h"
#include "BaseRole.hpp"
#include "PropertyData.hpp"
#include "BaseFSM.hpp"
#include "Tools/GLES-Render.hpp"
#include "GameRole/BaseRole.hpp"
#include "GameLayer.hpp"
#include "DialogLayer.hpp"
#include "spine/spine-cocos2dx.h"
#include "RaysCastCallback.hpp"
#include "Tools/RaysCastCallback.hpp"
#include "RayCastCallback1.hpp"
#include "AllPropertyData.hpp"
#include "EnemyRoleFSM.hpp"
#include "Tools/ContactListener.hpp"
using namespace std;
USING_NS_CC;
#define PTM_RATIO 32
class RaysCastCallback1;
class ContactListener;
class PropertyData;
class BaseFSM;
class AllPropertyData;
class DialogLayer;
class MapLayer;
class EnemeyRoleFSM;
class BaseRole;

typedef enum{
    rocker_stay =0,
    rocker_right,
    rocker_up,
    rocker_left,
    rocker_down,
}tagDirection;


class GameLayer :public cocos2d::Layer{
    public:
        CREATE_FUNC(GameLayer);
        static cocos2d::Scene *createScene();
        virtual bool init();
        void update(float dt);
        void addNewSpriteAtPosition(Vec2 p);
        void initPhysics();
//      敌人被攻击血条减少。
        void FighterCollidingWithEnemy(b2Body *body);
//      主角被敌人攻击到了。
        void FightCollidingWithRole();
    
        GLESDebugDraw *m_debugDraw;
        virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);
    
    
        tagDirection tagD;
        void onkeybroadPressed(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
        void onkeybroadReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
    
        void onkeybroadPressed1(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
        void onkeybroadReleased1(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
    
        void onJumpTo();
        virtual bool onTouchBegan(Touch *pTouch,Event *Event);
        void shexian(b2Body *b);
    public:
        ContactListener *contactListener;
        virtual void onEnter();
        bool onkeybroad = false;
        bool onkeybroad1 =false;
        bool onJump =false;
        bool onJump1=false;
        bool dialog=false;
        bool ladder;
        bool ladder1;
    
    
        int rockerDirection=0;
        int rockerDirection1=NULL;
        int z;
        int sprite_z;
        int z1;
        int sprite_z1;
        float hp;
            BaseFSM *baseFSM;
            BaseFSM *baseFSM1;
            EnemeyRoleFSM *enemyRoleFSM;

            BaseRole* role;
            b2World  *world;
            MapLayer *map;
            DrawNode *g;
            b2Body *body;
            spine::SkeletonAnimation *f;
            b2RayCastInput input;
            b2RayCastOutput output;
            Camera *camera1;
            Sprite *sprite_xin;
            Sprite *sprite_title;
    
            Sprite *sprite_title1;
            DialogLayer *dia;
            AllPropertyData *allpro;
            std::vector<Sprite *> propertyVector;
    
    public:
        void asyncUpdate(float t);
        void asyncUpdate1(float t);
        void asyncUpdate2(float t);
        void asyncUpdate3_ladder(float t);
        void findPathAsync();
        std::thread    *m_pWorkThread;
};
#include "Tools/ContactListener.hpp"

#endif /* GameLayer_hpp */
