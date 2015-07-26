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

class Enemy :public cocos2d::Sprite
{
private:
    
public:
    
    bool init() override;
    int _speed;
    void update(float dt) override;
    //    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vec2, _acceleration, Acceleration);
    /* 敵の移動速度 */
    
    CREATE_FUNC(Enemy);
};



#endif /* defined(__SyuraProject__Enemy__) */
