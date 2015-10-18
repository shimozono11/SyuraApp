//
//  TopScroll.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/24.
//
//

#include "TopScroll.h"
// ScrollView インクルード
#include "extensions/cocos-ext.h"

USING_NS_CC;     // cocos2d
USING_NS_CC_EXT; // cocos2d::extension

// _/_/_/ コンストラクタ プロパティー _/_/_/
TopScroll::TopScroll()
:_closeButton(nullptr)
{
    
}

// MainScene デストラクタで解放 メモリーリークを防ぐ
TopScroll::~TopScroll()
{
    CC_SAFE_RELEASE_NULL(_closeButton);
}

// createSceneはLayerをSceneに貼り付けて返すクラスメソッドです。
// 自分自身(TopScroll)を生成し、空のSceneに貼り付けて返す簡単な処理を行っているだけです。
// これでほかのシーンからの遷移が楽に行えます。
Scene* TopScroll::createScene()
{
    
    auto scene = Scene::create();
    auto layer = TopScroll::create();
    scene->addChild(layer);
    
    return scene;
}

bool TopScroll::init(char *filename)
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // 画面サイズ取得
    winSize = Director::getInstance()->getVisibleSize();
    
    
    // 画面サイズでスクロールビューを作る
    auto *pScrollView = ScrollView::create(winSize);
    pScrollView->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    pScrollView->setPosition(0,0);
//    // スクロールビュー自体の大きさを変更したい場合
//     pScrollView->setViewSize(Size(500, 500));
    
     //バウンスを許可するか（以下は非許可）
//     pScrollView->setBounceable(false);
    
    // スクロール方向の指定
    // pScrollView->setDirection(ScrollView::Direction::VERTICAL);
    /*
     列挙型定数                 説明
     Direction::BOTH          両方向
     Direction::HORIZONTAL    横（水平）方向のみ
     Direction::VERTICAL      縦（垂直）方向のみ
     Direction::NONE          制限をなくす
     */
    
    this->addChild(pScrollView);
    
    // デリゲートを使うと、スクロールの状態を取得することができます。
    //TopScrollレイヤーをデリゲートに設定
    pScrollView->setDelegate(this);
    
    //スクロールビューに入れるスプライトを用意
    auto *pSprite = Sprite::create(filename);
    
    pScrollView->setContainer(pSprite);
    pScrollView->setContentSize(pSprite->getContentSize());
    
    /*ボタンの設置*/
    //閉じるボタンの設定
    _closeButton = ui::Button::create();
    this->makeUiButton(_closeButton);
    
    this->addChild(_closeButton);
    _buttonView = true;
    
    // モーダル処理
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [ this](Touch *touch,Event*event)->bool{
        if (_buttonView) {
            _buttonView = false;
            this->removeChild(_closeButton);
        }else{
            _buttonView = true;
            auto button = ui::Button::create();
            this->setCloseButton(makeUiButton(button));
            this->addChild(_closeButton);
        }
        log("Touch!!");
        return true;
    };
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    

    
    return true;
}

// スクロール
void TopScroll::scrollViewDidScroll(ScrollView *view)
{
    log("スクロール！");
}

// ズーム
void TopScroll::scrollViewDidZoom(ScrollView *view)
{
    log("ズーム！");
}

TopScroll * TopScroll::createWithLayer(char *filename){
    TopScroll *ret = new TopScroll();
    if(ret->init(filename))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
ui::Button* TopScroll::makeUiButton(ui::Button *button){
    
    // タッチイベント True
    button->setTouchEnabled(true);
    // ボタンの中心位置　アーカーポンイント
    button->setAnchorPoint( Vec2::ANCHOR_TOP_RIGHT);
    // 通常状態の画像 押下状態の画像
    button->loadTextures("charadetail/charadetail_close.png","charadetail/charadetail_close_clicked.png", "");
    // ボタンの配置
    button->setPosition(winSize);
    // ボタンのイベント
    button->addTouchEventListener([this](Ref* pSender, cocos2d::ui::Widget::TouchEventType type){
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED)         {
            // 処理
            this->removeFromParentAndCleanup(true);
        }
    });

    return button;
}
