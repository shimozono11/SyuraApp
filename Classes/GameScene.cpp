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
    auto winSize = Director::getInstance()->getVisibleSize();
    
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

    /**/
    /**/
    
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
        //物理エンジンで更新
        _stage->getPlayer()->getPhysicsBody()->setVelocity(padMovement);

    }
    CCLOG("%d\n",_virPad->getSpeed());
    
}
