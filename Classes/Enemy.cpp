//
//  Enemy.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//

#include "Enemy.h"
#include "Stage.h"

USING_NS_CC;
/// アニメーションが何フレームあるか
const int FRAME_COUNT = 4;

bool Enemy::init()
{
    if (!Sprite::initWithFile("img/character/mobu_icon.png")) {
        return false;
    }
    

    /* アニメーションを入れるならココ */
    
    /* 剛体の設置 */
    auto body = PhysicsBody::createCircle(this->getContentSize().width / 2.0);
    // 剛体の回転を無効にする
    body->setRotationEnable(false);
    // カテゴリをMOB_ENEMYにセットする
    body->setCategoryBitmask(static_cast<int>(Stage::TileType::MOB_ENEMY));
    
    /* 接触判定をセット */
    body->setContactTestBitmask(static_cast<int>(Stage::TileType::PLAYER));
    
    
    // 全て
    body->setCollisionBitmask(INT_MAX);

    /* すbて */
    body->setCollisionBitmask(INT_MAX);
    // 全ての剛体の接触判定を行う

    body->setContactTestBitmask(INT_MAX);

    this->setPhysicsBody(body);
    this->scheduleUpdate();
    
    return true;
}

void Enemy::update(float dt)
{
   
}
