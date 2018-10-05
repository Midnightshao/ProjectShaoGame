//
//  DialogLayer.cpp
//  PojectShaoGame
//
//  Created by shao on 2018/8/28.
//

#include "DialogLayer.hpp"

 DialogLayer *DialogLayer::createDialogLayer(const char* filename,std::vector<Sprite *>  propertyVector){
     DialogLayer *dialogLayer =new DialogLayer();
     if(dialogLayer && dialogLayer->init(filename,propertyVector)){
            dialogLayer->autorelease();
        }else{
            CC_SAFE_DELETE(dialogLayer);
            return nullptr;
        }
     return dialogLayer;
};
bool DialogLayer::init(const char* filename,std::vector<Sprite *> propertyVector){
    initDialogLayer(filename,propertyVector);
    return true;
}
void DialogLayer::initDialogLayer(const char* filename,std::vector<Sprite *> propertyVector){
    if(filename == "MainScene.csb"){
        Node *rootNode = CSLoader::createNode(filename);
        rootNode->setScale(1.0);
        auto Panel_1= rootNode->getChildByName("Panel_1");
        
        auto Panel_2= rootNode->getChildByName("Panel_2");
        
        auto Panel_3= rootNode->getChildByName("Panel_3");

        auto Panel_4= rootNode->getChildByName("Panel_4");

        
        imageView = (ImageView *)Panel_1->getChildByTag(7);
        imageView1 = (ImageView *)Panel_2->getChildByTag(9);
        auto textView =  (Text *)Panel_1->getChildByTag(8);
        auto textView1 = (Text *)Panel_2->getChildByTag(10);
        auto textView2 = (Text *)rootNode->getChildByTag(12);
        auto textView3 = (Text *)rootNode->getChildByTag(11);

        Sprite *sprite = AllPropertyData::getSprite();
        if(sprite!=nullptr){
            int tags = sprite->getTag();
            PropertyData *propertyData=AllPropertyData::setPropertyData(tags);
            this->removeChild(sprite);
            imageView->loadTexture(propertyData->getImage());
            textView->setString(propertyData->getContent());
        }
        Sprite *sprite1 = AllPropertyData::getSprite1();
        if(sprite1!=nullptr){
            int tags = sprite1->getTag();
            PropertyData *propertyData=AllPropertyData::setPropertyData(tags);
            this->removeChild(sprite1);
            imageView1->loadTexture(propertyData->getImage());
            textView1->setString(propertyData->getContent());

        }
        addChild(rootNode);
    }

    
}
void DialogLayer::touchCallBack(cocos2d::Ref *sender, Widget::TouchEventType controlEvent){
    
}

