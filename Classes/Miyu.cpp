//
//  Miyu.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/08/11.
//
//

#include "Miyu.h"
#include "SyuraEnemy.h"
#include "Stage.h"
Miyu::Miyu()
{
    
}

Miyu::~Miyu(){
    
}


bool Miyu::init()
{
    if (!Sprite::initWithFile("character/miyu_stop.png")) {
        return false;
    }
    /* 修羅キャラの剛体を設置 */
    this->SyuraEnemy::setSyuraBody();

    return true;
}

void Miyu::update(float dt)
{
    
}