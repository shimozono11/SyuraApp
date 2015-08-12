//
//  GameScene.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/07/19.
//
//

#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TopModal.h"
#include "LoseModal.h"
#include "ClearModal.h"



USING_NS_CC;
using namespace cocostudio::timeline;
/*  */
int ADD_ENEMY_RATE = 60;
int MAX_SYURAENEMY = 3;

/* 制限時間 */
const float TIME_LIMIT_SECOND = 30;

/* コンストラクタ:プレイヤーを初期化 */
GameScene::GameScene()
: _second(TIME_LIMIT_SECOND)
, _state(GameState::READY)
, _stage(nullptr)
, _virPad(nullptr)
, _secondLabel(NULL)

{
    
}

GameScene::~GameScene()
{
    //    CC_SAFE_RELEASE_NULL(_stage);なぜかここがエラーになる
    CC_SAFE_RELEASE_NULL(_virPad);
    CC_SAFE_RELEASE_NULL(_secondLabel);
}


Scene* GameScene::createScene()
{
    /* 物理エンジンを有効にしたシーンを作成 */
    auto scene = Scene::createWithPhysics();
    /* 物理空間を取り出す */
    auto world = scene->getPhysicsWorld();
    
    // 重力を設定する
    world->setGravity(Vec2(0, 0));
    
    /* デバッグビルドのとき */
#if COCOS2D_DEBUG > 0
    /* 物理空間にデバッグ用の表示を追加する */
    world -> setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif
    
    auto layer = GameScene::create();
    scene->addChild(layer);
    
    
    
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    /* 画面サイズの取得 */
    winSize = Director::getInstance()->getVisibleSize();
    
    /* ステージの読み込み */
    auto stage = Stage::create();
    this -> addChild(stage);
    this -> setStage(stage);
    
    /* バーチャルパッドの実装 */
    auto virPad = VirtualPad::create();
    this->addChild(virPad);
    this->setVirtualPad(virPad);
    
    /* トップ画面の表示 */
    //////////////////////////////////////
    // レイヤーを追加
    auto layer = TopModal::create();
    layer->setName("TOPMODAL");
    this->addChild(layer);
    
    
    /* マルチタップリスナーの設置 */
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->setEnabled(true);
    listener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    /* 物体が接触したことを検知するEventListener */
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->setEnabled(true);
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    contactListener->onContactPreSolve = CC_CALLBACK_1(GameScene::onContactPresolve, this);
    contactListener->onContactSeperate = CC_CALLBACK_1(GameScene::onContactSeparate, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    /* タイマーラベルの追加 */
    int second = static_cast<int>(_second);
    auto secondLabel = Label::createWithSystemFont(StringUtils::toString(second), "MarkerFelt", 16);
    this->setSecondLabel(secondLabel);
    
    secondLabel->enableShadow(Color4B::BLACK,Size(0.5,0.5) , 3);
    secondLabel->enableOutline(Color4B::BLACK,1.5);
    secondLabel->setPosition(Vec2(winSize.width /2.0 , winSize.height -40));
    this->addChild(secondLabel);
    
    /* タイマーヘッダーの追加 */
    auto secondLabelHeader = Label::createWithSystemFont("TIME","MarkerFelt", 16);
    secondLabelHeader->enableShadow(Color4B::BLACK,Size(0.5,0.5) , 3);
    secondLabelHeader->enableOutline(Color4B::BLACK,1.5);
    secondLabelHeader->setPosition(Vec2(winSize.width /2.0 , winSize.height -20));
    this->addChild(secondLabelHeader);
    
    
    //    auto rootNode = CSLoader::createNode("GameScene.csb");
    //    addChild(rootNode);
    
    /* update関数（毎フレーム呼び出す関数）の設置 */
    this->scheduleUpdate();
    // スケジュールの実行(秒単位)
    this->schedule(schedule_selector(GameScene::gameLogic), 1.0f);
    //
    time=0;
    isPauseFlag = false;
    
    return true;
}

void GameScene::onEnterTransitionDidFinish()
{
    // シーン遷移が完了したとき
    Layer::onEnterTransitionDidFinish();
    
    // 「READY」演出を行う
    this->addReadyLabel();
}

/**
 *タッチ開始
 *@param touches
 *@param event
 */
void GameScene::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *unused_event){
    
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();
        /* Padの画像範囲 */
        auto padBackRect = _virPad->getPadBack()->getBoundingBox();
        
        /* VirtualPadは、最初は画像の中をタッチしないと反応しない*/
        if(padBackRect.containsPoint(location)){
            /* 準備状態の場合、ゲーム開始フラッグを立てる */
            if(_state == GameState::READY){
                _state = GameState::PLAYING;
                this->onPlaying();
            }
            _virPad->startPad((int)touch->getLocation().x,(int)touch->getLocation().y,touch->getID());
            _virPad->update((int)touch->getLocation().x,(int)touch->getLocation().y,touch->getID());
        }
        
        
        
        iterator++;
    }
    return;
}

/**
 *タッチ移動
 *@param touches
 *@param event
 */
void GameScene::onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event *unused_event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();
        
        /*バーチャルパッド移動中*/
        
        _virPad->update((int)touch->getLocation().x,(int)touch->getLocation().y,touch->getID());
        
        iterator++;
    }
    return;
}

/**
 *タッチ終了
 *@param touches
 *@param event
 */
void GameScene::onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event *unused_event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();
        
        /* バーチャルパッドを離す */
        _virPad->endPad(touch->getID());
        
        iterator++;
    }
    return;
}

/**
 * 剛体の接触開始
 *@param contact 接触のインスタンス？
 *
 */
bool GameScene::onContactBegin(PhysicsContact& contact){
    
    /* 衝突した物体２つを取り出す */
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();
    
    /* 衝突した物体２つのカテゴリを取り出す */
    auto categoryA = bodyA -> getCategoryBitmask();
    auto categoryB = bodyB -> getCategoryBitmask();
    
    /* 衝突した剛体が双方ともMob敵の場合 */
    if(categoryA & static_cast<int>(Stage::TileType::MOB_ENEMY)  && categoryB & static_cast<int>(Stage::TileType::MOB_ENEMY)){
        //        CCLOG("Mob敵とMob敵がぶつかりました");
        return true;
    }
    
    /* MOB敵が衝突したとき、片方が敵でない場合 */
    if(categoryA & static_cast<int>(Stage::TileType::MOB_ENEMY)){
        
        /* 修羅場に接触した場合 */
        if(categoryB & static_cast<int>(Stage::TileType::SYURABA_EREA)){
            
            /* 修羅場エリアリストに挿入 */
            auto syuraba = _stage->getSyuraarea();
            syuraba.pushBack(bodyA->getNode());
            _stage->setSyuraarea(syuraba);
            
            //            CCLOG("%zd", _stage->getSyuraarea().size());
            //            _stage->getSyuraarea().insert(_stage->getSyuraarea().size(), bodyB->getNode());
            CCLOG("敵「修羅場なう」");
            return true;
        }
        /* 壁に接触した場合 */
        if(categoryB & static_cast<int>(Stage::TileType::WALL)){
            //            CCLOG("敵「壁なう」");
            return true;
        }
        /* 神５に接触した場合 */
        if(categoryB & static_cast<int>(Stage::TileType::SYURA_ENEMY)){
            //            CCLOG("敵「神5なう」");
            return true;
        }
        
        
    }else if(categoryB & static_cast<int>(Stage::TileType::MOB_ENEMY)){
        /*修羅場に接触した場合*/
        if(categoryA & static_cast<int>(Stage::TileType::SYURABA_EREA)){
            /* 修羅場リストにオブジェクトを追加 */
            /* 修羅場エリアリストに挿入 */
            auto syuraba = _stage->getSyuraarea();
            syuraba.pushBack(bodyB->getNode());
            _stage->setSyuraarea(syuraba);
            //            CCLOG("%zd", _stage->getSyuraarea().size());
            CCLOG("敵「修羅場なう」");
            return true;
        }
        /* 壁に接触した場合 */
        if(categoryA & static_cast<int>(Stage::TileType::WALL)){
            //            CCLOG("敵「壁なう」");
            return true;
        }
        /* 神５に接触した場合 */
        if(categoryA & static_cast<int>(Stage::TileType::SYURA_ENEMY)){
            //            CCLOG("敵「神5なう」");
            return true;
        }
        
    }
    
    /* 衝突した剛体が双方とも修羅キャラの場合 */
    if(categoryA & static_cast<int>(Stage::TileType::SYURA_ENEMY)  && categoryB & static_cast<int>(Stage::TileType::SYURA_ENEMY)){
        //        CCLOG("修羅キャラと修羅キャラががぶつかりました");
        return true;
    }
    
    /* 修羅キャラが衝突したとき、片方が修羅キャラでない場合 */
    if(categoryA & static_cast<int>(Stage::TileType::SYURA_ENEMY)){
        
        /* 修羅場に接触した場合 */
        if(categoryB & static_cast<int>(Stage::TileType::SYURABA_EREA)){
            
            /* 修羅場エリアリストに挿入 */
            auto syuraba = _stage->getSyuraarea();
            syuraba.pushBack(bodyA->getNode());
            _stage->setSyuraarea(syuraba);
            CCLOG("神５「修羅場なう」");
            return true;
        }
        /* 壁に接触した場合 */
        if(categoryB & static_cast<int>(Stage::TileType::WALL)){
            CCLOG("神5「壁なう」");
            return true;
        }
        /* Mob敵に接触した場合 */
        if(categoryB & static_cast<int>(Stage::TileType::MOB_ENEMY)){
            CCLOG("神５「モブ敵とぶつかりました」");
            return true;
        }
        
        
    }else if(categoryB & static_cast<int>(Stage::TileType::SYURA_ENEMY)){
        /*修羅場に接触した場合*/
        if(categoryA & static_cast<int>(Stage::TileType::SYURABA_EREA)){
            /* 修羅場リストにオブジェクトを追加 */
            /* 修羅場エリアリストに挿入 */
            auto syuraba = _stage->getSyuraarea();
            syuraba.pushBack(bodyB->getNode());
            _stage->setSyuraarea(syuraba);
            //            CCLOG("%zd", _stage->getSyuraarea().size());
            CCLOG("神5「修羅場なう」");
            return true;
        }
        /* 壁に接触した場合 */
        if(categoryA & static_cast<int>(Stage::TileType::WALL)){
            CCLOG("神5「壁なう」");
            return true;
        }
        /* 神５に接触した場合 */
        if(categoryA & static_cast<int>(Stage::TileType::SYURA_ENEMY)){
            CCLOG("敵「神5なう」");
            return true;
        }
        
    }
    
    
    
    
    /* 以下プレイヤーが衝突したときの処理 */
    auto otherShape = contact.getShapeA()->getBody() == _stage->getPlayer()->getPhysicsBody() ? contact.getShapeB() : contact.getShapeA();
    auto body = otherShape->getBody();
    
    auto category = body->getCategoryBitmask();
    //    auto layer = dynamic_cast<TMXLayer *>(body->getNode()->getParent());
    
    if (category & static_cast<int>(Stage::TileType::MOB_ENEMY)) {
        // ゲームオーバー
        GameScene::onLose();
    } else if (category & (int)Stage::TileType::WALL) {
        //        CCLOG("プレイやー「壁なう」");
    } else if (category & static_cast<int>(Stage::TileType::SYURABA_EREA)) {
        //        CCLOG("プレイヤー「修羅場なう」");
    }
    return true;
}

/**
 * 剛体の接触中
 *@param contact 接触クラス？
 *
 */
bool GameScene::onContactPresolve(PhysicsContact& contact){
    
    
    return true;
}

/**
 * 剛体の接触後 ：修羅場に存在する敵の管理を行う
 *@param contact 接触クラス？
 *
 */
void GameScene::onContactSeparate(PhysicsContact& contact){
    /* 修羅場エリアに入っている敵だったら、修羅場エリアのベクターから削除 TODO*/
    
    /* 接触し終わった物体２つを取り出す */
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();
    
    /* 接触し終わった物体２つのカテゴリを取り出す */
    auto categoryA = bodyA -> getCategoryBitmask();
    auto categoryB = bodyB -> getCategoryBitmask();
    
    /* 接触し終わった剛体が双方とも敵の場合 */
    if(categoryA & static_cast<int>(Stage::TileType::MOB_ENEMY)  && categoryB & static_cast<int>(Stage::TileType::MOB_ENEMY)){
        return ;
    }
    auto syuraba = _stage->getSyuraarea();
    /* 剛体が離れた時、片方がMOB敵でない場合 */
    if(categoryA & static_cast<int>(Stage::TileType::MOB_ENEMY)){
        
        /* 修羅場から接触し終わった時 */
        if(categoryB & static_cast<int>(Stage::TileType::SYURABA_EREA)){
            /* 修羅場エリアリストの中から削除 */
            syuraba.eraseObject(bodyA->getNode());
            _stage->setSyuraarea(syuraba);
            
            return ;
        }
        /* 壁に接触した場合 */
        if(categoryB & static_cast<int>(Stage::TileType::WALL)){
            //            CCLOG("敵「壁なう」");
            return ;
        }
    }
    else if(categoryB & static_cast<int>(Stage::TileType::MOB_ENEMY)){
        /*修羅場から接触し終わった時*/
        if(categoryA & static_cast<int>(Stage::TileType::SYURABA_EREA)){
            /* 修羅場エリアリストの中から削除 */
            syuraba.eraseObject(bodyA->getNode());
            _stage->setSyuraarea(syuraba);
            return ;
        }
    }
    
    /* 接触し終わった剛体が双方とも修羅キャラの場合 */
    if(categoryA & static_cast<int>(Stage::TileType::SYURA_ENEMY)  && categoryB & static_cast<int>(Stage::TileType::SYURA_ENEMY)){
        //        CCLOG("修羅キャラと修羅キャラ離れました");
        return ;
    }

    /* 剛体が離れた時、片方が修羅キャラではない */
    if(categoryA & static_cast<int>(Stage::TileType::SYURA_ENEMY)){
        if(categoryB & static_cast<int>(Stage::TileType::SYURABA_EREA)){
            
            /* 修羅場エリアヴェクターから削除 */
            syuraba.eraseObject(bodyA->getNode());
            _stage->setSyuraarea(syuraba);
            
            return ;
        }
        if(categoryB & static_cast<int>(Stage::TileType::WALL)){
            return ;
        }
        if(categoryB & static_cast<int>(Stage::TileType::MOB_ENEMY)){
            return ;
        }
    
    }else if(categoryB & static_cast<int>(Stage::TileType::SYURA_ENEMY)){

        if(categoryA & static_cast<int>(Stage::TileType::SYURABA_EREA)){
            
            /* 修羅場エリアヴェクターから削除 */
            syuraba.eraseObject(bodyB->getNode());
            _stage->setSyuraarea(syuraba);
            
            return ;
        }
        if(categoryA & static_cast<int>(Stage::TileType::WALL)){
            return ;
        }
        if(categoryA & static_cast<int>(Stage::TileType::MOB_ENEMY)){
            return ;
        }
    }
    return;
}

/**ゲーム中の準備状態の処理
 *
 *
 */
void GameScene::onReady(){
    CCLOG("GameOnReady");
}



/** ゲームオーバー処理
 *
 *
 */
void GameScene::onLose(){
    CCLOG("GameOver!!!");
    
    // レイヤーを追加
    auto layer = LoseModal::create();
    layer->setName("LoseModal");
    this->addChild(layer);
    /* 動きを止める処理 */
    this->swichPauseFlag();
    
}
/** ゲームクリア処理
 *
 *
 */
void GameScene::onClear(){
    CCLOG("gameClear!!");
    // レイヤーを追加
    auto layer = ClearModal::create();
    layer->setName("ClearModal");
    this->addChild(layer);
    /* 動きを止める処理 */
    this->swichPauseFlag();
    
}

/**ゲーム中へ移行する時、１度だけ呼ぶ処理
 * タイトルからパッド触ったときと
 *　Pauseから戻ってきた時
 */
void GameScene::onPlaying(){
    /* TopModal画面を消す */
    TopModal * topModal = this->getChildByName<TopModal *>("TOPMODAL");
    topModal->menuCloseCallback(this);
    //    TopModal::menuCloseCallback(cocos2d::Ref *pSender);
    this->swichPauseFlag();
    CCLOG("GameOnPlaying");
    
    
}
/** ゲーム開始時の処理
 *
 *
 */
void GameScene::addReadyLabel()
{
    //時間を止める！
    swichPauseFlag();
    //    cocos2d::Director::getInstance()->pause();
}



void GameScene::update(float dt){
    /* プレイヤーにスピードをセット */
    _stage->getPlayer()->setSpeed(_virPad->getSpeed());
    /* バーチャルパッドの操作 */
    if( _virPad->isTouch()){
        
        /*　バーチャルパッドの移動量でプレイヤーを操作 */
        /*　現在の位置を取得　*/
        Vec2 nowPosition = _stage->getPlayer()->getPosition();
        /* パッドから読み込んだ移動量を取得 */
        Vec2 padMovement = Vec2(_virPad->getCosX()*_virPad->getSpeed(), _virPad->getSinY()*_virPad->getSpeed());
        /* プレイヤーwo新しい位置に設定 */
        Vec2 newPosition = nowPosition + padMovement;
        /* プレイヤーの位置を更新 */
        //座標で更新
        _stage->getPlayer()->setPosition(newPosition);
        //物理エンジンでキャラの位置を移動(本当は物理エンジンで実現するのが好ましいが現在は簡単のため座標で移動)
        //        _stage->getPlayer()->getPhysicsBody()->setVelocity(padMovement);
        
        /*プレイヤーが画面外に飛び出さないように設定*/
        auto position = _stage->getPlayer()->getPosition().getClampPoint(Vec2(0,0), _stage->getTiledMap()->getContentSize());
        _stage->getPlayer()->setPosition(position);
        //    CCLOG("%d\n",_virPad->getSpeed());
    }
    
    /* プレイ中になったら時間を減らし出し、また、修羅場の判定をとる */
    if(_state == GameState::PLAYING){
        /* 修羅場エリアに入った時の処理 */
        if( _stage->getSyuraarea().size() >= 2){
            CCLOG("修羅場発生！！！");
            auto syuraba = _stage->getSyuraarea();
            //        /* ステージから全て削除 TODO ベクターをループで回す*/
            //        for(auto itr = 0 ; itr != syuraba.size() ; itr++){
            //            auto a = dynamic_cast<Enemy*>( syuraba.front());
            //            a->removeFromParent();
            //            syuraba.eraseObject(a);
            //        }
            auto itr = syuraba.begin();
            while (itr != syuraba.end())
            {
                (*itr)->removeFromParent();
                itr = syuraba.erase(itr);
            }
            /* ベクターの中からも全てのオブジェクトを削除 */
            syuraba.clear();
            _stage->setSyuraarea(syuraba);
        }
        
        /* 残り時間を減らす */
        _second -= dt;
        /* 表示の更新 */
        int second = static_cast<int>(_second);
        _secondLabel->setString(StringUtils::toString(second));
        
        int random = rand() % ADD_ENEMY_RATE;
        if( random == 0){
            _stage->addEnemyOnStage();
        }
        //        /* 平均して10秒ごとに修羅キャラを追加 */
        //        random = rand() % 600;
        //        if( random  == 0){
        //             _stage->addSyuraEnemyOnStage();
        //        }
        //
        _stage->moveEnemys();
        /* 時間が0になったら */
        if(_second < 0 ){
            _state = GameState::CLEAR;
            this->onClear();
        }
    }
    
}
/**１秒間に一回呼び出される関数
 *
 *
 */
void GameScene::gameLogic(float dt){
    /* 6秒に一回実行 */
    if(int(TIME_LIMIT_SECOND - _second) % 7 == 6){
        _stage->addSyuraEnemyOnStage();
    }
}

/** ゲームのポーズスイッチを切り替える
 * 剛体やステージ場の敵、パッド操作等を諸々止める処理をまとめただけ
 *
 */
void GameScene::swichPauseFlag()
{
    /* フラグを反転させる */
    isPauseFlag = !isPauseFlag;
    
    if(isPauseFlag){
        /* GameSceneのupdateを切る */
        this->unscheduleUpdate();
        /* パッド */
        /* プレイヤーのスピードを0にする */
        _stage->getPlayer()->setSpeed(0);
        /* プレイヤーの物理演算を切る */
        _stage->getPlayer()->getPhysicsBody()->setEnable(false);
        
        /* 敵の物理演算を切る */
        for (const auto& enemy : _stage->getEnemys())
        {
            auto enemyTag = enemy-> getTag();
            
            /* Mobキャラの場合 */
            if(enemyTag == (int)Stage::TileType::MOB_ENEMY){
                auto mobenemy = (MobEnemy*) enemy;
                mobenemy->getPhysicsBody()->setEnable(false);
            }
            /* 修羅キャラの場合 */
            if(enemyTag == (int)Stage::TileType::SYURA_ENEMY){
                auto syuraenemy = (SyuraEnemy*) enemy;
                syuraenemy->getPhysicsBody()->setEnable(false);
            }
        }
    }else{
        /* 止まっていた処理を動かす */
        this->scheduleUpdate();
        _stage->scheduleUpdate();
        _stage->getPlayer()->getPhysicsBody()->setEnable(true);
        
        /* 敵の物理演算を入れる */
        for (const auto& enemy : _stage->getEnemys())
        {
            auto enemyTag = enemy-> getTag();
            /* Mobキャラの場合 */
            if(enemyTag == (int)Stage::TileType::MOB_ENEMY){
                auto mobenemy = (MobEnemy*) enemy;
                mobenemy->getPhysicsBody()->setEnable(true);
            }
            /* 修羅キャラの場合 */
            if(enemyTag == (int)Stage::TileType::SYURA_ENEMY){
                auto syuraenemy = (SyuraEnemy*) enemy;
                syuraenemy->getPhysicsBody()->setEnable(true);
            }
        }
    }
}