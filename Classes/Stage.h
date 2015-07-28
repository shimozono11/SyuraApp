//
//  Stage.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//

#ifndef __SyuraProject__Stage__
#define __SyuraProject__Stage__

#include <stdio.h>

#include "cocos2d.h"
#include "Player.h"
#include "CustomFollow.h"
#include "Enemy.h"

class Stage :public cocos2d::Layer
{
public:
    
    /// タイルの種類
    enum class TileType {
        /// 壁
        WALL = 1 << 0,
        /// プレイヤー
        PLAYER = 1 << 1,
        /// MOBの敵キャラ
        MOB_ENEMY = 1 << 2,
        /// 修羅場を起こす敵キャラ
        SYURA_ENEMY = 1 << 3,
        /// 修羅場エリア
        SYURABA_EREA = 1 << 4
    };

//    void update(float dt) override;
//    
//    CC_SYNTHESIZE_READONLY(int, _level, Level);
    cocos2d::Size winSize;

    void update(float dt)override;
    
    /* タイルマップ */
    CC_SYNTHESIZE_RETAIN(cocos2d::TMXTiledMap *, _tiledMap, TiledMap);
    /* プレイヤー */
    CC_SYNTHESIZE_RETAIN(Player *, _player, Player);
    /* 敵 */
    CC_SYNTHESIZE(cocos2d::Vector<Enemy*>,_enemys,Enemys);
    /* 修羅場エリアに入っている敵を格納する */
    CC_SYNTHESIZE(cocos2d::Vector<Enemy*>,_syuraarea, Syuraarea)
    CREATE_FUNC(Stage);
    /** ステージ番号からステージを生成します
     *  @param level ステージ番号
     *  @return ステージ
     */
//    static Stage * createWithLevel(int level);
protected:
//    bool initWithLevel(int level); gmcmnmdnkg8bc
    Stage();
    virtual ~Stage();
    bool init() override;
private:
    
    /** 指定のレイヤーの特定位置のタイルに剛体を設置する
     *  指定座標にタイルがなかった場合はnullptrを返す
     *  @param layer 対象のレイヤー
     *  @param coordinate 対象タイルのあるマップ上の座標
     *  @return タイルのスプライト、またはnullptr
     */
    cocos2d::Sprite* addPhysicsBodyTMX(cocos2d::TMXLayer *layer, cocos2d::Vec2& coordinate);
    
    //フィールドに敵を追加
    void addEnemyOnStage();
    //修羅場で管理するエリアに敵を追加
    void addEnemyOnSyuraba(Enemy *enemy);
    //敵を動かす
    void moveEnemys();
    //ステージ上から敵を削除
    bool removeEnemyOnStage(Enemy *enemy);
    //修羅場発生時に実行する関数。修羅場の敵を全て削除
    bool removeEnemyOnSyuraba();
    //修羅場が起きずに敵が離れた場合の関数
    bool leaveEnemyOnSyuraba(Enemy *enemy);
};


#endif /* defined(__SyuraProject__Stage__) */
