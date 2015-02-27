#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "sqlite/sqlite3.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);
    
private:
    sqlite3 *db;
    char* errorMessage;
};

#endif // __HELLOWORLD_SCENE_H__
