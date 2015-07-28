//
//  Player.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//

#ifndef __SyuraProject__Player__
#define __SyuraProject__Player__

#include <stdio.h>
#include "cocos2d.h"


class Player :public cocos2d::Sprite
{
public:
    bool init() override;
    
    void update(float dt) override;
    
//    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vec2, _acceleration, Acceleration);
    CREATE_FUNC(Player);
};


#endif /* defined(__SyuraProject__Player__) */
