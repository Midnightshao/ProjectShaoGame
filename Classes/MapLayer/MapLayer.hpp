//
//  MapLayer.hpp
//  PojectGame
//
//  Created by shao on 2018/4/23.
//

#ifndef MapLayer_hpp
#define MapLayer_hpp
#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "EnemyRole.hpp"
#include "BaseRole.hpp"
#include "GameLayer.hpp"
#define PTM_RATIO 32

using namespace std;
class GameLayer;
USING_NS_CC;
class MapLayer : public Layer{
    public :
    TMXTiledMap *tileMap;
    TMXLayer *collidable;
    TMXLayer *collidable1;
    TMXLayer *collidable2;
public:
    static MapLayer *createMapLayer(const char* filename);
    void initWorld(b2World *world1);
    
    bool setBackground(const char* filename);
    void initMap();
    void setContext(GameLayer *gameLayer);
    CREATE_FUNC(MapLayer);
    CC_SYNTHESIZE(Camera *,camera,Camera);
    CC_SYNTHESIZE(Camera *,camera1,Camera1);


    b2World *world;
    GameLayer *gameLayer;
};
#endif /* MapLayer_hpp */
