//
//  MobEnemy.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/11.
//
//


#include <stdio.h>
#include "MobEnemy.h"
#include "Stage.h"
USING_NS_CC;
/// アニメーションが何フレームあるか
const int FRAME_COUNT = 4;

MobEnemy::MobEnemy()
{
    
}

MobEnemy::~MobEnemy(){
    
}


bool MobEnemy::init()
{
    if (!Sprite::initWithFile("character/mobu_stop.png")) {
        return false;
    }

    this->setTag((int)Stage::TileType::MOB_ENEMY);
    /* アニメーションを入れるならココ */
    /* 剛体の設置 */
    auto body = PhysicsBody::createCircle(this->getContentSize().width / 2.0);
    // 剛体の回転を無効にする
    body->setRotationEnable(false);
    // カテゴリをMOB_MobEnemyにセットする
    body->setCategoryBitmask(static_cast<int>(Stage::TileType::MOB_ENEMY));
    
    /* 修羅場以外と衝突する ~はビット反転 */
    body->setCollisionBitmask(~static_cast<int>(Stage::TileType::SYURABA_EREA));
    // 全ての剛体の接触判定を行う
    body->setContactTestBitmask(INT_MAX);
    
    
    this->setPhysicsBody(body);
    this->scheduleUpdate();
    
    return true;
}

void MobEnemy::update(float dt)
{
    
}
