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

USING_NS_CC;

using namespace cocostudio::timeline;

/* コンストラクタ:プレイヤーを初期化 */
GameScene::GameScene()
:_stage(nullptr)
,_virPad(nullptr)

{
    
}

GameScene::~GameScene()
{
    CC_SAFE_RELEASE_NULL(_stage);
    CC_SAFE_RELEASE_NULL(_virPad);
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
    
    
    /* マルチタップリスナーの設置 */
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->setEnabled(true);
    listener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    /* update関数（毎フレーム呼び出す関数）の設置 */
    this->scheduleUpdate();
    
    /* 物体が接触したことを検知するEventListener */
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->setEnabled(true);
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    contactListener->onContactPreSolve = CC_CALLBACK_1(GameScene::onContactPresolve, this);
    contactListener->onContactSeperate = CC_CALLBACK_1(GameScene::onContactSeparate, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    /* 物体が衝突したことを検知するEventListener */
    
    
    /*
     auto rootNode = CSLoader::createNode("GameScene.csb");
     addChild(rootNode);
     */
    
    
    return true;
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
        
        /* VirtualPadの操作開始 */
        _virPad->startPad((int)touch->getLocation().x,(int)touch->getLocation().y,touch->getID());
        _virPad->update((int)touch->getLocation().x,(int)touch->getLocation().y,touch->getID());
        
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
    
    /* 衝突した剛体が双方とも敵の場合 */
    if(categoryA & static_cast<int>(Stage::TileType::MOB_ENEMY)  && categoryB & static_cast<int>(Stage::TileType::MOB_ENEMY)){
        //        CCLOG("なにすんのよあんた！！！");
        return true;
    }
    
    /* 敵が衝突したとき、片方が敵でない場合 */
    if(categoryA & static_cast<int>(Stage::TileType::MOB_ENEMY)){
        
        /* 修羅場に接触した場合 */
        if(categoryB & static_cast<int>(Stage::TileType::SYURABA_EREA)){
//            _stage->getEnemys().begin()
            _stage->getSyuraarea().pushBack(bodyB->getNode());
            bodyA->getNode()->removeFromParent();
            CCLOG("敵「修羅場なう」");
            return true;
        }
        /* 壁に接触した場合 */
        if(categoryB & static_cast<int>(Stage::TileType::WALL)){
//            CCLOG("敵「壁なう」");
            return true;
        }
        
        
    }else if(categoryB & static_cast<int>(Stage::TileType::MOB_ENEMY)){
        /*修羅場に接触した場合*/
        if(categoryA & static_cast<int>(Stage::TileType::SYURABA_EREA)){
            /*ここで修羅場にいる敵をどうやって格納するか考え中・・・*/
//            this->removeChild(dynamic_cast<Node*>(bodyB));
            _stage->getSyuraarea().pushBack(bodyB->getNode());
            bodyB->getNode()->removeFromParent();
            CCLOG("敵「修羅場なう」");
            return true;
        }
        /* 壁に接触した場合 */
        if(categoryA & static_cast<int>(Stage::TileType::WALL)){
//            CCLOG("敵「壁なう」");
            return true;
        }
        
    }
    
    /* 以下プレイヤーが衝突したときの処理 */
    auto otherShape = contact.getShapeA()->getBody() == _stage->getPlayer()->getPhysicsBody() ? contact.getShapeB() : contact.getShapeA();
    auto body = otherShape->getBody();
    
    auto category = body->getCategoryBitmask();
    auto layer = dynamic_cast<TMXLayer *>(body->getNode()->getParent());
    
    if (category & static_cast<int>(Stage::TileType::MOB_ENEMY)) {
        // ゲームオーバー
        GameScene::onGameover();
    } else if (category & (int)Stage::TileType::WALL) {
        CCLOG("プレイやー「壁なう」");
    } else if (category & static_cast<int>(Stage::TileType::SYURABA_EREA)) {
        CCLOG("プレイヤー「修羅場なう」");
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
 * 剛体の接触後
 *@param contact 接触クラス？
 *
 */
void GameScene::onContactSeparate(PhysicsContact& contact){
    return;
}


/** ゲームオーバー処理
 *
 *
 */
void GameScene::onGameover(){
    CCLOG("GameOver!!!");
}
/** ゲームクリア処理
 *
 *
 */
void GameScene::onClear(){
    
}

void GameScene::update(float dt){
    /* バーチャルパッドに触れている間 */
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
        //        _stage->getPlayer()->setPosition(newPosition);
        //物理エンジンでキャラの位置を移動
        _stage->getPlayer()->getPhysicsBody()->setVelocity(padMovement);
        
        /*プレイヤーが画面外に飛び出さないように設定*/
        auto position = _stage->getPlayer()->getPosition().getClampPoint(Vec2(0,0), _stage->getTiledMap()->getContentSize());
        _stage->getPlayer()->setPosition(position);
        //    CCLOG("%d\n",_virPad->getSpeed());
    }
    
    /* 敵とプレイヤーの当たり判定 */
    /* 修羅場エリアに入った時の処理 */
    /* 敵の削除 */
    
}
