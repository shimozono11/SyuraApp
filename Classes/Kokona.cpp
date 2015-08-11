//
//  Kokona.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/11.
//
//

#include "Kokona.h"
#include "SyuraEnemy.h"
#include "Stage.h"
Kokona::Kokona()
{
    
}

Kokona::~Kokona(){
    
}


bool Kokona::init()
{
    if (!Sprite::initWithFile("character/kokona_stop.png")) {
        return false;
    }
    /* 修羅キャラの剛体を設置 */
    this->SyuraEnemy::setSyuraBody();
    return true;
}

void Kokona::update(float dt)
{
    
}