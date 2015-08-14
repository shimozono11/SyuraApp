//
//  CharaDetailModal.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/14.
//
//

#ifndef __SyuraProject__CharaDetailModal__
#define __SyuraProject__CharaDetailModal__

#include <stdio.h>
#include "cocosGUI.h"
class CharaDetailModal : public cocos2d::Layer
{
    
public:
    
    virtual bool init();
    
    void menuCloseCallback(Ref* pSender);
    
    void pushMenu01(Ref *pSender);
    
    // create()を使えるようにしている。
    CREATE_FUNC(CharaDetailModal);
};

#endif /* defined(__SyuraProject__CharaDetailModal__) */
