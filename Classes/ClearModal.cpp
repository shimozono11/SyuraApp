//
//  ClearModal.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/02.
//
//

#include "ClearModal.h"
#include "cocostudio/CocoStudio.h"
#include "GameScene.h"
//#include "ui/CocosGUI.h"

using namespace cocos2d;

bool ClearModal::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto Node = CSLoader::createNode("modal_csd_layer/ClearLayer.csb");
    Node -> setName("NODE");
    this -> addChild(Node);
    
    /* 女の子リストボタンを押した時の処理 */
    auto* girlListBotton = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("girllist_button"));
    girlListBotton->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
             CCLOG("女の子リストボタンが押されました");
            //好きな処理
        }
    });
    
    /* コミックリストボタンを押した時の処理 */
    auto* comicListBotton = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("comiclist_button"));
    comicListBotton->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
             CCLOG("コミックリストボタンが押されました");
            //好きな処理
        }
    });
    
    /* コミックリストボタンを押した時の処理 */
    auto* retryBotton = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("retry_button"));
    retryBotton->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("リトライボタンが押されました");
            // 遷移先の画面のインスタンス
            Scene *pScene = GameScene::createScene();
            // 0.5秒かけてフェードアウトしながら次の画面に遷移します
            //    引数１:フィードの時間
            //    引数２：移動先のシーン
            //    引数３：フィードの色（オプション）
            TransitionFade* transition = TransitionFade::create(0.5f, pScene);
            
            // 遷移実行  遷移時のアニメーション
            // 直前のsceneはもう使わないから捨ててしまう方法。基本はこれになります。
            Director::getInstance()->replaceScene(transition);

            //好きな処理
            this->menuCloseCallback(pSender);
        }
    });

    
    // モーダルのフレーム
    //    auto frame = Sprite::create("img/app_icon.png");
    //    frame->setPosition(Vec2(winSize.width/2, winSize.height/2));
    //    this->addChild(frame);
    //    //透明度を変更(0~255)
    //    frame->setOpacity(220);
    //
    //    // Menu1
    //    auto button01 = MenuItemImage::create("menu-image1.png",  // 通常状態の画像
    //                                          "menu-image1-hover.png",  // 押下状態の画像
    //                                          CC_CALLBACK_1(ClearModal::pushMenu01, this));
    //    // Menu2
    //    auto button02 = MenuItemImage::create("menu-image2.png",  // 通常状態の画像
    //                                          "menu-image2-hover.png",  // 押下状態の画像
    //                                          CC_CALLBACK_1(ClearModal::pushMenu01, this));
    //    // キャンセル
    //    auto closeItem00 = MenuItemImage::create("menu-image9.png",  // 通常状態の画像
    //                                             "menu-image9-hover.png",  // 押下状態の画像
    //                                             CC_CALLBACK_1(ClearModal::menuCloseCallback, this));
    //
    //    // ボタンの設置
    //    button01->setPosition(Point(winSize.width / 2,winSize.height /1.5));
    //    button02->setPosition(Point(winSize.width / 2,winSize.height /2.0));
    //    closeItem00->setPosition(Point(winSize.width / 2,winSize.height /3.5));
    //
    //    auto menu = Menu::create(button01, button02, closeItem00, NULL);
    //    menu->setPosition(Vec2::ZERO);
    //    this->addChild(menu, 1);
    
    // モーダル処理
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch *touch,Event*event)->bool{
        return true;
    };
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

// menuCloseCallback ClearModalオブジェクトの削除 sender
void ClearModal::menuCloseCallback(Ref* pSender)
{
    // ClearModalオブジェクトの削除
    this->removeFromParentAndCleanup(true);
}