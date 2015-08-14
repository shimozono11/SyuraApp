
//
//  CharaDetailModal.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/14.
//
//

#include "CharaDetailModal.h"

// on "init" you need to initialize your instance
bool CharaDetailModal::init()
{
    //初期化
    if ( !CCLayer::init() ) return false;
    
    //画面サイズを取得
    auto winSize = Director::getInstance()->getWinSize();
    auto _pageView = ui::PageView::create();
    _pageView->setContentSize(Size(winSize.width,winSize.height));
    _pageView->setPosition((winSize - _pageView->getContentSize())/2);
    this->addChild(_pageView);
    
    
    //コンテンツ配置
    for (int i = 0; i < 3; i++) {
        
        auto imageView = ui::ImageView::create("charadetail/backcard.png");
        auto _layout = ui::Layout::create();
        _layout->setContentSize(_pageView->getContentSize());
        imageView->setPosition(_layout->getContentSize() / 2);
        _layout->addChild(imageView);
        _pageView->insertPage(_layout, i);
        
    }
    return true;

}