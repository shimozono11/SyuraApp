//
//  Player.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//

#include "Player.h"
#include "Stage.h"

USING_NS_CC;

/// アニメーションが何フレームあるか
const int FRAME_COUNT = 4;

bool Player::init()
{
    if (!Sprite::initWithFile("map/futsuo_icon.png")) {
        return false;
    }
    
    this -> setPosition(Vec2(200, 600));
    /* 剛体の設置 */
    auto body = PhysicsBody::createCircle(this->getContentSize().width / 2.0);
    // 剛体の回転を無効にする
    body->setRotationEnable(false);
    // 全ての剛体と接触判定を行う
    this->setPhysicsBody(body);

    this->scheduleUpdate();
    
    return true;
}

void Player::update(float dt)
{
}