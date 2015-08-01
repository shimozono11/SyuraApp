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
    /** ゲームの状態を表す
     * READY :開始演出
     * PLAYING :ゲーム中
     * PAUSE :ポーズ中
     * SYURABA :修羅場中
     * ENDING :終了演出
     * RESULT :結果
     */
    enum class GameState
    {
        READY,
        PLAYING,
        PAUSE,
        SYURABA,
        ENDING,
        RESULT
    };
    
    void onGameover();
    void onClear();
    void addReadyLabel();
    void swichPauseFlag();


    float time;
    bool isPauseFlag;
    
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    void update(float dt)override;
    void onEnterTransitionDidFinish() override;
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
    
    
    /* 制限時間用変数　*/
    CC_SYNTHESIZE(float, _second, Second);
    /* 現在のゲーム状態 */
    CC_SYNTHESIZE(GameState, _state, State);
    /* ステージの作成 */
    CC_SYNTHESIZE_RETAIN(Stage *, _stage, Stage);
    /* VirutalPadの生成 */
    CC_SYNTHESIZE_RETAIN(VirtualPad *, _virPad, VirtualPad);
    /* 制限時間用ラベル */
    CC_SYNTHESIZE_RETAIN(cocos2d::Label*, _secondLabel, SecondLabel);
    CREATE_FUNC(GameScene);
    
};




#endif /* defined(__SyuraProject__GameScene__) */
