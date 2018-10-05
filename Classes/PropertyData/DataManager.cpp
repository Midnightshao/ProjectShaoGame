//
//  DataManager.cpp
//  PojectShaoGame
//
//  Created by shao on 2018/8/2.
//

#include "DataManager.hpp"
static DataManager * dataManager = nullptr;

DataManager *DataManager::getInstance(){
    
    if(dataManager == nullptr){
        dataManager = new DataManager();
    }
    return  dataManager;
};

void DataManager::initWithJsonFile(const char * filename){
    tollgateData = FileUtils::getInstance()->getStringFromFile(filename);
    log("打印json数据 %s",tollgateData.c_str());
}
std::vector<std::string> DataManager::getLevelDataArrayByIndex(int index){
    Document doc;
    doc.Parse<kParseDefaultFlags>(tollgateData.c_str());
    _levelDataArray.clear();
    rapidjson::Value &array =doc[""];
};

