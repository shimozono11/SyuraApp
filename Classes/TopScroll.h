//
//  TopScroll.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/24.
//
//

#ifndef __SyuraProject__TopScroll__
#define __SyuraProject__TopScroll__

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class TopScroll :public Layer,
public ScrollViewDelegate // デリゲート
{
protected:
    // コンストラクタ
    TopScroll();
    // デストラクタ
    virtual ~TopScroll();
    // メソッド CREATE_FUNCとの連携
    bool init(char *filename);
    
public:
    static cocos2d::Scene* createScene();
    static TopScroll* createWithLayer(char *filename);
    void scrollViewDidScroll(ScrollView *view);
    void scrollViewDidZoom(ScrollView *view);
};

#endif /* defined(__SyuraProject__TopScroll__) */
