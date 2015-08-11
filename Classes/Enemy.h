//
//  Enemy.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//

#ifndef __SyuraProject__Enemy__
#define __SyuraProject__Enemy__

#include <stdio.h>
#include "cocos2d.h"

class Enemy :public cocos2d::Sprite
{
private:
    Enemy();
    virtual ~Enemy();
public:
    
    bool init() override;
    void update(float dt) override;
    //    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vec2, _acceleration, Acceleration);
    /* 敵の移動速度 */
    CC_SYNTHESIZE(int, _speed, Speed);
    CREATE_FUNC(Enemy);
};



#endif /* defined(__SyuraProject__Enemy__) */
