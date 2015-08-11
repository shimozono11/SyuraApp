//
//  Haruka.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/11.
//
//

#include "Haruka.h"
#include "SyuraEnemy.h"
#include "Stage.h"
Haruka::Haruka()
{
    
}

Haruka::~Haruka(){
    
}


bool Haruka::init()
{
    if (!Sprite::initWithFile("character/haruka_stop.png")) {
        return false;
    }
    /* 修羅キャラの剛体を設置 */
    auto body = cocos2d::PhysicsBody::createCircle(this->getContentSize().width / 2.0);
    if(!this->setSyuraBody(body)){
        return false;
    }
    
    return true;
}

void Haruka::update(float dt)
{
    
}