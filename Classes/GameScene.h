//
//  GameScene.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//

#ifndef __SyuraProject__GameScene__
#define __SyuraProject__GameScene__

#include <stdio.h>
#include "VirtualPad.h"
class GameScene : public cocos2d::Layer
{
private:
    GameScene();
    virtual ~GameScene();

public:
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    /* タッチイベントリスナー */
    void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);

    
    CREATE_FUNC(GameScene);
};




#endif /* defined(__SyuraProject__GameScene__) */
