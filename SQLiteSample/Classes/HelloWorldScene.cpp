#include "HelloWorldScene.h"

USING_NS_CC;
using namespace std;

HelloWorld::HelloWorld()
    : db(nullptr)
    , errorMessage()
{}

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

    // update row
    auto update = "update user set age = 20 where id = 1";
    status = sqlite3_exec(db, update, nullptr, nullptr, &errorMessage);
    if(status != SQLITE_OK) CCLOG("update: %s", errorMessage);
    
    // select row(s)
    sqlite3_stmt* statement = nullptr;
    auto select = "select * from user where id = 1";
    if(sqlite3_prepare_v2(db, select, -1, &statement, nullptr) != SQLITE_OK) CCLOG("prepare: %s", errorMessage);
    else
    {
        if (sqlite3_step(statement) == SQLITE_ROW)
        {
            for (int i = 0; i < sqlite3_column_count(statement); i++)
            {
                string name = sqlite3_column_name(statement, i);
                int columnType = sqlite3_column_type(statement, i);
                if (columnType == SQLITE_INTEGER)
                {
                    CCLOG("%s = %d", name.c_str(), sqlite3_column_int(statement, i));
                    continue;
                }
            }
        }
    }
    sqlite3_reset(statement);
    sqlite3_finalize(statement);
    
    sqlite3_close(db);

    return true;
}

HelloWorld::~HelloWorld() {}
