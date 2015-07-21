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
,_player(nullptr)
{
    
}
Stage::~Stage()
{
    CC_SAFE_RELEASE_NULL(_tiledMap);
    CC_SAFE_RELEASE_NULL(_player);
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
    
//    /* プレイヤーの設置 */
    auto player = Player::create();
    player ->setPosition(Vec2(200,500));
    this->addChild(player);
    this->setPlayer(player);
    
    this->scheduleUpdate();
    
    return true;
}

void Stage::update(float dt)
{
    
}