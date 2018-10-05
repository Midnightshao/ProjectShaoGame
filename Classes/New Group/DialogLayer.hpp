//
//  DialogLayer.hpp
//  PojectShaoGame
//
//  Created by shao on 2018/8/28.
//

#ifndef DialogLayer_hpp
#define DialogLayer_hpp

#include <iostream>
#include "GameLayer.hpp"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "PropertyData.hpp"
#include "EnemyRole.hpp"
#include "AllPropertyData.hpp"
using namespace ui;
using namespace cocostudio;
USING_NS_CC;
class GameLayer;
class PropertyData;
class AllPropertyData;
class EnemyRole;
class DialogLayer :public Layer{
public:
    static DialogLayer *createDialogLayer   (const char* filename,std::vector<Sprite *> propertyVector);
    virtual bool init(const char* filename,std::vector<Sprite *> propertyVector);
    void initDialogLayer(const char* filename,std::vector<Sprite *> propertyVector);
    bool setBackground(const char* filename);
    void initMap();
    void setContext(GameLayer *gameLayer);
    
    void touchCallBack(Ref * sender, Widget::TouchEventType controlEvent);
public:
    ImageView *imageView;
    ImageView *imageView1;
    
    Text*  *textView;

    std::vector<PropertyData *> propertyVector;
    GameLayer *gameLayer;
};

#endif
/* DialogLayer_hpp */
