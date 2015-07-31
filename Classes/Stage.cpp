//
//  Stage.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//

#include "Stage.h"
USING_NS_CC;

/*  */
int ADD_ENEMY_RATE = 20;

Stage::Stage()
:_tiledMap(nullptr)
,_player(nullptr)
{
    
}
Stage::~Stage()
{
    CC_SAFE_RELEASE_NULL(_tiledMap);
    CC_SAFE_RELEASE_NULL(_player);
}

bool Stage::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    /* マップファイルからノードを作成 */
    auto map = TMXTiledMap::create("img/map/stage1.tmx");
    this->addChild(map);
    this->setTiledMap(map);
    
    /*　地形レイヤーを取得 */
    //    auto terrainLayer = map->getLayer("Tile");
    // オブジェクトレイヤーを取得する
    auto objectLayer = map->getLayer("Object");
    
    // 修羅場レイヤーを取得
    auto syurabaLayer = map->getLayer("Syuraba");
    
    // マップのサイズ
    auto mapSize = map->getMapSize();
    for (int i = 0; i < mapSize.width; i++) {
        for (int j = 0; j < mapSize.height; j++) {
            auto coordinate = Vec2(i, j);
            //            this->addPhysicsBody(terrainLayer, coordinate);
            this->addPhysicsBodyTMX(objectLayer, coordinate);
            this->addPhysicsBodyTMX(syurabaLayer, coordinate);
        }
    }
    
    /* プレイヤーの設置 */
    auto player = Player::create();
    this->addChild(player);
    this->setPlayer(player);
    
    /* プレイヤーに画面を追従させる */
    winSize = Director::getInstance()->getWinSize();
    /*Rectは追従する範囲を決めている Rectは左下を原点としている*/
    
    this ->runAction(CustomFollow::create(player,Rect(0, 0, _tiledMap->getContentSize().width, _tiledMap->getContentSize().height) ));
    /* x軸だけ、y軸だけと指定をする場合　この場合だとマップの範囲が扱えない */
    //    CustomFollowType type = kCustomFollowNone;
    //    this ->runAction(CustomFollow::create(player,type));
    
    this->scheduleUpdate();
    
    return true;
}

/** tmxファイルからステージを読み込んで画像を配置
 *@param layer TMXファイルから読み込んだレイヤー
 *@param coordinate
 *@return マップから読み込んだ画像
 */
Sprite* Stage::addPhysicsBodyTMX(cocos2d::TMXLayer *layer, cocos2d::Vec2 &coordinate){
    /*タイルのスプライトを取り出す*/
    auto sprite = layer -> getTileAt(coordinate);
    if(sprite){
        /* 剛体用のマテリアル */
        auto material = PhysicsMaterial();
        /* 引っかからないように摩擦をゼロに */
        material.friction = 0;
        /* 剛体を設置 */
        auto physicsBody = PhysicsBody::createBox(sprite->getContentSize(),material);
        /* 剛体を固定する */
        physicsBody->setDynamic(false);
        /* 剛体をつけるSpriteのアンカーポイントを中心にする */
        sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        /* タイルのIDを取り出す */
        auto gid = layer->getTileGIDAt(coordinate);
        /* タイルのプロパティをmapで取り出す */
        auto properties = _tiledMap->getPropertiesForGID(gid).asValueMap();
        /* "category"というプロパティが存在しているかチェック */
        if(properties.count("category") > 0){
            /* プロパティのなっからcategoryの値をintとして取り出す */
            auto category = properties.at("category").asInt();
            /* 剛体にカテゴリーをセットする */
            physicsBody->setCategoryBitmask(category);
            /* 剛体と接触判定をとるカテゴリを指定する  ここではプレイヤーと敵*/
            physicsBody->setContactTestBitmask((int)Stage::TileType::PLAYER + (int)Stage::TileType::MOB_ENEMY);
        }
        /* 剛体をSpriteに付ける */
        sprite->setPhysicsBody(physicsBody);
        return sprite;
    }
    return nullptr;
}

/*
 *敵をマップに配置
 *@return 配置した敵のSpriteクラスを返す
 *
 */
void Stage::addEnemyOnStage(){
    auto enemy = Enemy::create();
    Vec2  nowPos = _player->getPosition();
    /* 要リファクタリングTODO */
    /* 敵を配置する場所を指定 */
    /* プレイヤーからある程度離れた位置に敵追加する */
    auto addEnemyPos0 = nowPos + Vec2(0,winSize.height/2) ;
    auto addEnemyPos1 = nowPos + Vec2(winSize.width/2,0);
    auto addEnemyPos2 = nowPos + winSize/2;
    auto addEnemyPos3 = nowPos - Vec2(0,winSize.height/2);
    auto addEnemyPos4 = nowPos - Vec2(winSize.width/2,0);
    auto addEnemyPos5 = nowPos - winSize/2;
    /* 敵の初期値を設定 */
    switch (rand()%6) {
        case 0:
            /* 敵の初期位置 */
            enemy->setPosition(addEnemyPos0);
            CCLOG("0地点");
             break;
        case 1:
            enemy->setPosition(addEnemyPos1);
            CCLOG("1地点");
             break;
        case 2:
            enemy->setPosition(addEnemyPos2);
            CCLOG("2地点");
             break;
        case 3:
            enemy->setPosition(addEnemyPos3);
            CCLOG("3地点");
             break;
        case 4:
            enemy->setPosition(addEnemyPos4);
            CCLOG("4地点");
             break;
        case 5:
            enemy->setPosition(addEnemyPos5);
            CCLOG("5地点");
             break;
        default:
            /* ここに来ることはないはず */
            CCLOG("デフォルト");
            break;
    }
    //    /* x軸のランダムな位置 */
    //    float enemyXPos = rand() % static_cast<int>(winSize.width);
    //    auto enemySize = enemy -> getContentSize();
    //
    //    /* 敵の初期位置 */
    //    enemy->setPosition(Vec2(enemyXPos,winSize.height - enemySize.height/2.0 - 40));
    /* 速度の設定 */
    enemy->setSpeed((int)rand()%6);
    
    /* ステージに敵を追加 */
    this -> addChild(enemy);
    /* _enemyベクターに敵を追加する */
    _enemys.pushBack(enemy);
    
    return ;
}

/** フィールドの敵を移動
 *
 */
void Stage::moveEnemys(){
    auto iterator = _enemys.begin();
    while (iterator != _enemys.end()) {
        Enemy* enemy = (Enemy*)(*iterator);
        
        /* 現在の敵の座標を取得 */
        Vec2 Epos = enemy->getPosition();
        /* 現在のプレイヤーの座標を取得する */
        Vec2 Ppos = _player->getPosition();
        
        /* プレイヤーとの座標の差をベクトルで取得 */
        Vec2 delta = Ppos - Epos;
        /* 角度を算出 */
        auto angle = atan2f(delta.y, delta.x);
        /* 動作量 */
        float enemyMoveX =  cosf(angle)*enemy->getSpeed();
        float enemyMoveY =  sinf(angle)*enemy->getSpeed();
        
        /* 新しい座標へセット */
        Vec2 newPosition = Vec2(enemy->getPositionX() + enemyMoveX, enemy->getPositionY() + enemyMoveY);
        
        /* マップの敵へ反映 */
        enemy->setPosition(newPosition);
        /* マップ外へ出ないように丸める */
        auto position = enemy->getPosition().getClampPoint(Vec2(0,0), this->getTiledMap()->getContentSize());
        enemy->setPosition(position);
        
        iterator++;
        
    }
    return;
    
}

/** フィールドの敵を削除
 *@param *enemy 削除する敵
 *@return bool 削除できたかどうか
 */
bool Stage::removeEnemyOnStage(Enemy *enemy){
    
    /* _enemysにenemyが含まれているかを確認しておく*/
    if(_enemys.contains(enemy)){
        /* 親ノード(GameScene)から削除 */
        enemy->removeFromParent();
        /* 配列からも削除 */
        _enemys.eraseObject(enemy);
        return  true;
    }
    return false;
}

/** 修羅場エリアに入ってきた敵を格納
 *@param *enemy 挿入する敵
 */
void Stage::addEnemyOnSyuraba(Enemy *enemy){
    _syuraarea.pushBack(enemy);
}

/** 修羅場発生時に実行すし、修羅場エリアに存在する敵を全て削除
 *  同時にステージ上に存在する敵も削除する
 *@return bool 削除できたかどうか
 */
bool Stage::removeEnemyOnSyuraba(){
    /* 修羅場エリアに存在する敵を削除する */
    for (const auto& Node : _syuraarea)
    {
        Enemy *enemy = dynamic_cast<Enemy*>(Node);
        /* ステージ上から敵を削除 */
        removeEnemyOnStage(enemy);
        /* 修羅場エリアからもenemyを削除 */
        _syuraarea.eraseObject(enemy);
    }
    return true;
}
/** 修羅場が発生せずに、敵が修羅場エリアを離れた時に実行
 *  離れた敵を修羅場エリアの管理するベクターから削除
 *@param enemy 修羅場から離れた敵
 *@return bool 削除できたかどうか
 */
bool Stage::leaveEnemyOnSyuraba(Enemy *enemy){
    /* _syurabaareaにenemyが含まれているかを確認しておく*/
    if(_syuraarea.contains(enemy)){
        /* 入れるからのみ削除 */
        _enemys.eraseObject(enemy);
        return  true;
    }
    return false;
}

void Stage::update(float dt)
{
    /* 敵の発生確率を設定 */
    int random = rand() % ADD_ENEMY_RATE;
    /* 20分の１の確率で敵を追加 */
    if(random == 0 ){
        this ->addEnemyOnStage();
    }
    /* 敵キャラの位置を更新 */
    moveEnemys();
}