//
//  CustomFollow.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/22.
//
//

#include "CustomFollow.h"
USING_NS_CC;

CustomFollow::CustomFollow(){
    _type = kCustomFollowNone;
    _marginRect = Rect::ZERO;
}

CustomFollow::~CustomFollow(){
    CC_SAFE_RELEASE(_followedNode);
}

CustomFollow* CustomFollow::create(Node* followNode){
    CustomFollow *follow = new CustomFollow();
    if (follow && follow->initWithTarget(followNode, Rect::ZERO))
    {
        follow->autorelease();
        return follow;
    }
    CC_SAFE_DELETE(follow);
    return nullptr;
}

CustomFollow* CustomFollow::create(Node* followNode, CustomFollowType type){
    CustomFollow *follow = new CustomFollow();
    follow->_type = type;
    if (follow && follow->initWithTarget(followNode, Rect::ZERO))
    {
        follow->autorelease();
        return follow;
    }
    CC_SAFE_DELETE(follow);
    return nullptr;
}

CustomFollow* CustomFollow::create(Node* followNode, Rect marginRect){
    CustomFollow *follow = new CustomFollow();
    follow->_marginRect = marginRect;
    /* Rectを投げればその範囲で追従をする */
    if (follow && follow->initWithTarget(followNode,follow ->_marginRect))
    {
        follow->autorelease();
        return follow;
    }
    CC_SAFE_DELETE(follow);
    return nullptr;
}

void CustomFollow::step(float dt)
{
    CC_UNUSED_PARAM(dt);
    
    if(_boundarySet)
    {
        // whole map fits inside a single screen, no need to modify the position - unless map boundaries are increased
        if(_boundaryFullyCovered)
        {
            return;
        }
        auto winSize = Director::getInstance()->getVisibleSize();
        Vec2  newTargetPos = _halfScreenSize + Vec2(0, (winSize.height-640)/2);
        Vec2 tempPos = newTargetPos - _followedNode->getPosition();
        _target->setPosition(clampf(tempPos.x, _leftBoundary, _rightBoundary),
                             clampf(tempPos.y, _bottomBoundary, _topBoundary));
    }
    else
    {
        _target->setPosition(_halfScreenSize - _followedNode->getPosition());
    }
}