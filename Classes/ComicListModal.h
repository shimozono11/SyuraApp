//
//  ComicListModal.h
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/14.
//
//

#ifndef __SyuraProject__ComicListModal__
#define __SyuraProject__ComicListModal__

#include <stdio.h>
#include "cocos2d.h"

class CharaDetailModal : public cocos2d::Layer
{
    
public:
    
    virtual bool init();
    
    void menuCloseCallback(Ref* pSender);
    
    void pushMenu01(Ref *pSender);
    
    // create()を使えるようにしている。
    CREATE_FUNC(CharaDetailModal);
};


#endif /* defined(__SyuraProject__ComicListModal__) */
