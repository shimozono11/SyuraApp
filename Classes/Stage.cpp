//
//  Stage.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//

#include "Stage.h"
USING_NS_CC;

Stage::Stage()
:_tiledMap(nullptr)
{
    
}
Stage::~Stage()
{
    CC_SAFE_RELEASE_NULL(_tiledMap);
}

bool Stage::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    /* マップファイルからノードを作成 */
    auto map = TMXTiledMap::create("map/stage1.tmx");
    this->addChild(map);
    this->setTiledMap(map);
    
    this->scheduleUpdate();
    
    return true;
}

void Stage::update(float dt)
{
    
}