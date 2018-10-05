//
//  AlllPropertyData.cpp
//  PojectShaoGame
//
//  Created by shao on 2018/9/2.
//
#include "AllPropertyData.hpp"
static  Sprite * sprite=nullptr;
static  Sprite * sprite1=nullptr;
static  Sprite * sprite2=nullptr;
static  Sprite * sprite3=nullptr;
int AllPropertyData::fun(int a){
    a=a+1;
    return a;
}
void AllPropertyData::setSprite(Sprite *sprite1){
    sprite = sprite1;
}
Sprite * AllPropertyData::getSprite(){
    return  sprite;
}
void  AllPropertyData::setSprite1(Sprite *sprite){
    sprite1 =sprite;
};
Sprite * AllPropertyData::getSprite1(){
    return sprite1;
}

void AllPropertyDatasetSprite2(Sprite *sprite){
    sprite2 =sprite;
}
Sprite * AllPropertyData::getSprite2(){
    return sprite2;
};

void AllPropertyData::setSprite3(Sprite *sprite){
    sprite3 = sprite;
};
Sprite * AllPropertyData::getSprite3(){
    return sprite3;
};




PropertyData * AllPropertyData::setPropertyData(int proertyData){
    PropertyData *property;
    switch (proertyData) {
        case 41:
            property =PropertyData::create();
            property->setPlayerName("gun");
            property->setID(41);
            property->setImage("gun1_large.png");
            property->setContent("这是一把 手枪,"
                                 "拥有攻击能力，\n"
                                 "攻击力 10。");
            return property;

        case 44:
            property =PropertyData::create();
            property->setID(44);
            property->setPlayerName("bomb");
            property->setImage("zhadan_large.png");
            property->setContent("这是一颗炸弹拥有爆炸能力\n，爆炸范围不强，爆炸里15 \n.。。。。。。。。。。。。 \n");
            return property;
        default:
            return nullptr;
    }
}







