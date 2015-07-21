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
    
    /*　地形レイヤーを取得 */
//    auto tileLayer = map->getLayer("Tile");
//    /* オブジェクトレイヤーの取得 */
//    auto objectLayer = map->getLayer("Object");
//    
    
    
    /* マップのサイズ */
//    auto mapSize = map -> getMapSize();
//    for(int i = 0 ; i < mapSize.width ; ++i){
//        for(int j = 0 ; mapSize.height ; ++j){
//            auto coordinate = Vec2(i,j);
//            
//            this->addPhysicsBody(tileLayer, coordinate);
//            this->addPhysicsBody(objectLayer, coordinate);
//        }
//    }
//    // 地形レイヤーを取得する
//    auto terrainLayer = map->getLayer("Tile");
    // オブジェクトレイヤーを取得する
    auto objectLayer = map->getLayer("Object");
    
    // マップのサイズ
    auto mapSize = map->getMapSize();
    for (int x = 0; x < mapSize.width; ++x) {
        for (int y = 0; y < mapSize.height; ++y) {
            auto coordinate = Vec2(x, y);
            
//            this->addPhysicsBody(terrainLayer, coordinate);
            this->addPhysicsBody(objectLayer, coordinate);
            
        }
    }
    
    /* プレイヤーの設置 */
    auto player = Player::create();
    this->addChild(player);
    this->setPlayer(player);
    
    this->scheduleUpdate();
    
    return true;
}

Sprite* Stage::addPhysicsBody(cocos2d::TMXLayer *layer, cocos2d::Vec2 &coordinate){
    /*タイルのスプライトを取り出す*/
    auto sprite = layer -> getTileAt(coordinate);
    if(sprite){
        /* 剛体用のマテリアル */
        auto material = PhysicsMaterial();
        /* 引っかからないように摩擦をゼロに */
        material.friction = 0;
        /* 剛体を設置 */
        auto physicsBody = PhysicsBody::createBox(sprite->getContentSize(),material);
        /* 剛体を固定する */
        physicsBody->setDynamic(false);
        /* 剛体をつけるSpriteのアンカーポイントを中心にする */
        sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        /* 剛体をSpriteに付ける */
        sprite->setPhysicsBody(physicsBody);
        
        return sprite;
    }
    return nullptr;
}

void Stage::update(float dt)
{
    
}