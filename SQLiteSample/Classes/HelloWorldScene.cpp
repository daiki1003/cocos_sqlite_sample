#include "HelloWorldScene.h"

USING_NS_CC;
using namespace std;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if (!Layer::init()) return false;
    
    // path for saving db
    string dbName = "test.db";
    auto filePath = FileUtils::getInstance()->getWritablePath() + dbName;
    
    auto status = sqlite3_open(filePath.c_str(), &db);
    if(status != SQLITE_OK)
    {
        CCLOG("error for opening db.");
    }
    else
    {
        CCLOG("open successed!");
    }
    
    // create table
    auto create_table = "create table user (id integer, age integer)";
    status = sqlite3_exec(db, create_table, nullptr, nullptr, &errorMessage);
    if(status != SQLITE_OK) CCLOG("create: %s", errorMessage);

    // insert row
    auto insert = "insert into user(id, age) values (1, 15)";
    status = sqlite3_exec(db, insert, nullptr, nullptr, &errorMessage);
    if(status != SQLITE_OK) CCLOG("insert: %s", errorMessage);

    sqlite3_close(db);

    return true;
}
