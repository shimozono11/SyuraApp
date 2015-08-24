//
//  ComicListModal.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/15.
//
//

#include "ComicListModal.h"
#include "cocostudio/CocoStudio.h"
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
    
    auto Node = CSLoader::createNode("modal_csd_layer/ComicList.csb");
    Node -> setName("NODE");
    this -> addChild(Node);
    
    /* No01が押された時 */
    auto* No01 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No01"));
    No01->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No01が押されました");
            //好きな処理
//            auto layer = CharaDetailModal::create();
//            layer->setName("CharaDetail");
//            this->addChild(layer);
            
        }
    });
    /* No02が押された時 */
    auto* No02 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No02"));
    No02->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No02が押されました");
            //好きな処理
            //            auto layer = CharaDetailModal::create();
            //            layer->setName("CharaDetail");
            //            this->addChild(layer);
            
        }
    });
    /* No03が押された時 */
    auto* No03 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No03"));
    No03->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No03が押されました");
            //好きな処理
            //            auto layer = CharaDetailModal::create();
            //            layer->setName("CharaDetail");
            //            this->addChild(layer);
            
        }
    });
    /* No04が押された時 */
    auto* No04 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No04"));
    No04->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No04が押されました");
            //好きな処理
            //            auto layer = CharaDetailModal::create();
            //            layer->setName("CharaDetail");
            //            this->addChild(layer);
            
        }
    });
    /* No05が押された時 */
    auto* No05 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No05"));
    No05->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No05が押されました");
            //好きな処理
            //            auto layer = CharaDetailModal::create();
            //            layer->setName("CharaDetail");
            //            this->addChild(layer);
            
        }
    });
    /* No06が押された時 */
    auto* No06 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No06"));
    No06->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No06が押されました");
            //好きな処理
            //            auto layer = CharaDetailModal::create();
            //            layer->setName("CharaDetail");
            //            this->addChild(layer);
            
        }
    });
    /* No07が押された時 */
    auto* No07 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No07"));
    No07->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No07が押されました");
            //好きな処理
            //            auto layer = CharaDetailModal::create();
            //            layer->setName("CharaDetail");
            //            this->addChild(layer);
            
        }
    });
    /* No08が押された時 */
    auto* No08 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No08"));
    No08->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No08が押されました");
            //好きな処理
            //            auto layer = CharaDetailModal::create();
            //            layer->setName("CharaDetail");
            //            this->addChild(layer);
            
        }
    });
    /* No09が押された時 */
    auto* No09 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No09"));
    No09->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No09が押されました");
            //好きな処理
            //            auto layer = CharaDetailModal::create();
            //            layer->setName("CharaDetail");
            //            this->addChild(layer);
            
        }
    });
    /* No10が押された時 */
    auto* No10 = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("No10"));
    No10->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("No10が押されました");
            //好きな処理
            //            auto layer = CharaDetailModal::create();
            //            layer->setName("CharaDetail");
            //            this->addChild(layer);
            
        }
    });

    

    
    
    
    
//    /* 漫画アイコン一覧 */
//    
//    /* はるか対ここな */
//    auto harukaWinKokona = ui::Button::create();
//    harukaWinKokona->loadTextures("comiclist/comic_icon_haruka_win_kokona.png","comiclist/comic_icon_haruka_win_kokona.png");
//    // ボタンの中心位置　アーカーポンイント
//    harukaWinKokona->setAnchorPoint( Vec2::ANCHOR_TOP_RIGHT);
//    //ボタンの配置
//    harukaWinKokona->setPosition(Vec2(500,500));
//    harukaWinKokona->addTouchEventListener([this](Ref* pSender, cocos2d::ui::Widget::TouchEventType type){
//        if (type == cocos2d::ui::Widget::TouchEventType::ENDED)         {
//            // 処理
//            this->removeFromParentAndCleanup(true);
//        }
//    });
//    this->addChild(harukaWinKokona);
//
//    
//    
//    /* はるか対りさ*/
//    auto harukaWinRisa = ui::Button::create();
//    harukaWinKokona->loadTextures("comiclist/comic_icon_haruka_win_risa.png","comiclist/comic_icon_haruka_win_risa.png");
//    // ボタンの中心位置　アーカーポンイント
//    harukaWinRisa->setAnchorPoint( Vec2::ANCHOR_TOP_RIGHT);
//    //ボタンの配置
//    harukaWinRisa->setPosition(Vec2(300,300));
//    harukaWinRisa->addTouchEventListener([this](Ref* pSender, cocos2d::ui::Widget::TouchEventType type){
//        if (type == cocos2d::ui::Widget::TouchEventType::ENDED)         {
//            // 処理
//            this->removeFromParentAndCleanup(true);
//        }
//    });
//    this->addChild(harukaWinRisa);
//    
//    
//    
//    /* ここな対りさ*/
//    auto kokonaWinRisa = ui::Button::create();
//    kokonaWinRisa->loadTextures("comiclist/comic_icon_kokona_win_risa.png","comiclist/comic_icon_kokona_win_risa.png");
//    // ボタンの中心位置　アーカーポンイント
//    kokonaWinRisa->setAnchorPoint( Vec2::ANCHOR_TOP_RIGHT);
//    //ボタンの配置
//    kokonaWinRisa->setPosition(harukaWinRisa->getPosition() + Vec2(0, 200));
//    kokonaWinRisa->addTouchEventListener([this](Ref* pSender, cocos2d::ui::Widget::TouchEventType type){
//        if (type == cocos2d::ui::Widget::TouchEventType::ENDED)         {
//            // 処理
//            this->removeFromParentAndCleanup(true);
//        }
//    });
//    this->addChild(kokonaWinRisa);


    /* 漫画見る画面 */
//    auto topScroll = TopScroll::create();
//    this ->addChild(topScroll);
    
    
    
    
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
