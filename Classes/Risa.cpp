//
//  Risa.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/11.
//
//

#include "Risa.h"
#include "SyuraEnemy.h"
#include "Stage.h"
Risa::Risa()
{
    
}

Risa::~Risa(){
    
}


bool Risa::init()
{
    if (!Sprite::initWithFile("character/risa_stop.png")) {
        return false;
    }
    /* 修羅キャラの剛体を設置 */
    auto body = cocos2d::PhysicsBody::createCircle(this->getContentSize().width / 2.0);
    if(!this->setSyuraBody(body)){
        return false;
    }
    return true;
}

void Risa::update(float dt)
{
    
}