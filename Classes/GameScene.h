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
#include "Stage.h"

class GameScene : public cocos2d::Layer
{
private:
    GameScene();
    virtual ~GameScene();

public:
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    void update(float dt)override;
    void onGameover();
    void onClear();
    /* VirtualPad実装 */
    VirtualPad* virPad;
    
    Size winSize;
    
    /* タッチイベントリスナー */
    void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    
    /* 剛体の接触イベントリスナー */
    bool onContactBegin(PhysicsContact& contact);
    bool onContactPresolve(PhysicsContact& contact);
    void onContactSeparate(PhysicsContact& contact);
//    void onContactPostSolve(PhysicsContact& contact);衝突後

    
    /* ステージの作成 */
    CC_SYNTHESIZE_RETAIN(Stage *, _stage, Stage);
    /* VirutalPadの生成 */
    CC_SYNTHESIZE_RETAIN(VirtualPad *, _virPad, VirtualPad);
        
    CREATE_FUNC(GameScene);
    
};




#endif /* defined(__SyuraProject__GameScene__) */
