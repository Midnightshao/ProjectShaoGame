//
//  DataManager.hpp
//  PojectShaoGame
//
//  Created by shao on 2018/8/2.
//

#ifndef DataManager_hpp
#define DataManager_hpp

#include <iostream>
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
using namespace rapidjson;
USING_NS_CC;
class DataManager{
public:
    static DataManager *getInstance();
    void initWithJsonFile(const char *filename);
    std::vector<std::string> getLevelDataArrayByIndex(int index);
public:
    std::string tollgateData;
    std::vector<std::string> _levelDataArray;
    CC_SYNTHESIZE(int,levelIndex,LevelIndex);
};

#endif /* DataManager_hpp */
