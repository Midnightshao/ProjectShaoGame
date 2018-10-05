//
//  CeShi.cpp
//  PojectShaoGame
//
//  Created by shao on 2018/8/6.
//

#include "CeShi.hpp"

Ceshi * Ceshi::createWithProperty(PropertyData *property, b2Body *body, std::string str){
    Ceshi *ceshi = new Ceshi();
    if(ceshi && ceshi->init(property,body,str)){
        ceshi->autorelease();
    }else{
        CC_SAFE_DELETE(ceshi);
        return nullptr;
    }
    return ceshi;
};
bool Ceshi::init(PropertyData *property,b2Body *body,std::string str){
    return true;
}


