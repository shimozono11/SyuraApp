//
//  TopScroll.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/24.
//
//

#include "TopScroll.h"
#include "TopScroll.h"
// ScrollView インクルード
#include "extensions/cocos-ext.h"

USING_NS_CC;     // cocos2d
USING_NS_CC_EXT; // cocos2d::extension

// _/_/_/ コンストラクタ プロパティー _/_/_/
TopScroll::TopScroll()
{
    
}

// MainScene デストラクタで解放 メモリーリークを防ぐ
TopScroll::~TopScroll()
{
    
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

bool TopScroll::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // 画面サイズ取得
    auto size = Director::getInstance()->getVisibleSize();
    
    // 画面サイズでスクロールビューを作る
    auto *pScrollView = ScrollView::create(size);
    
    // スクロールビュー自体の大きさを変更したい場合
    // pScrollView->setViewSize(Size(500, 500));
    
    // バウンスを許可するか（以下は非許可）
    // pScrollView->setBounceable(false);
    
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
    auto *pSprite = Sprite::create("comic/kokona_win_risa.png");
    
    pScrollView->setContainer(pSprite);
    pScrollView->setContentSize(pSprite->getContentSize());
    
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
