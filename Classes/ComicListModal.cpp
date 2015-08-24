//
//  ComicListModal.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/15.
//
//

#include "ComicListModal.h"
//横方向に配置されるコミックアイコンの数
const int HORIZONTAL_COUNT = 3;
//縦方向に配置されるコミックアイコンの数
const int VERTICAL_COUNT = 4 ;
// on "init" you need to initialize your instance
bool ComicListModal::init()
{
    //初期化
    if ( !CCLayer::init() ) return false;
    
    //画面サイズを取得
    auto winSize = Director::getInstance()->getWinSize();
    
    /* 背景を暗くするレイヤーの設置 */
    auto background = Sprite::create("backpaper.png");
    background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    background->setPosition(winSize / 2);
    //レイヤーの乗算処理
    BlendFunc blend;
    blend.src = GL_ZERO;
    blend.dst = GL_SRC_COLOR;
    background->setBlendFunc(blend);
    this -> addChild(background);
    
    /*メニューの背景を設置*/
    auto backpaper = Sprite::create("comiclist/backpaper_top.png");
    backpaper->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    backpaper->setPosition(winSize/2);
    this->addChild(backpaper);
    
    
    
    /*ボタンの設置*/
    //閉じるボタンの設定
    auto button = ui::Button::create();
    // タッチイベント True
    button->setTouchEnabled(true);
    // ボタンの中心位置　アーカーポンイント
    button->setAnchorPoint( Vec2::ANCHOR_TOP_RIGHT);
    // 通常状態の画像 押下状態の画像
    button->loadTextures("charadetail/charadetail_close.png","charadetail/charadetail_close_clicked.png", "");
    // ボタンの配置
    button->setPosition(winSize/2 + (backpaper->getContentSize() / 2 ));
    // ボタンのイベント
    button->addTouchEventListener([this](Ref* pSender, cocos2d::ui::Widget::TouchEventType type){
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED)         {
            // 処理
            this->removeFromParentAndCleanup(true);
        }
    });
    this->addChild(button,0);
    
    auto topScroll = TopScroll::create();
    this ->addChild(topScroll);
    
    
    
    
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
