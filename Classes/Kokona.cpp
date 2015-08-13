//
//  Kokona.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/11.
//
//

#include "Kokona.h"
#include "SyuraEnemy.h"
#include "Stage.h"
USING_NS_CC;
Kokona::Kokona()
{
    
}

Kokona::~Kokona(){
    
}


bool Kokona::init()
{
    if (!Sprite::initWithFile("character/kokona_000.png")) {
        return false;
    }
    /* アニメーションを入れるならココ */
    for(int i = 1 ; i < FRAME_COUNT ; i++ ){
        sprintf(fileName, "character/kokona_00%d.png", i);
        auto rect  = this->getTextureRect();
        auto frame = SpriteFrame::create(fileName,rect);
        _frames.pushBack(frame);
    }
    this->setAnimation();

    /* 修羅キャラの剛体を設置 */
    auto body = cocos2d::PhysicsBody::createCircle(this->getContentSize().width / 2.0);
    if(!this->setSyuraBody(body)){
        return false;
    }
    return true;
}

void Kokona::setAnimation(){
    /* スピードが変わったらアニメーションを入れる */
    if(_speed != _oldSpeed){
        
        if(_speed ==0){
            this->stopAllActions();
            /* 止まっているたびに元の画像読み出しているので遅い　TODO */
            this->setTexture("character/kokona_000.png");
        }
        if(_speed > 0 ){
            auto animation = Animation::createWithSpriteFrames(_frames, 0.3f/getSpeed());
            animation->setRestoreOriginalFrame(true);
            this->runAction(RepeatForever::create(Animate::create(animation)));
        }
        
        this->setOldSpeed(_speed);
    }
}



void Kokona::update(float dt)
{
    
}