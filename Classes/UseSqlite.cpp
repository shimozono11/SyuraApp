//
//  UseSqlite.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/12/14.
//
//

#include "UseSqlite.hpp"
#define DB_NAME  "Syura.db"
USING_NS_CC;

Scene* UseSqlite::createScene()
{
    auto scene = Scene::create();
    auto layer = UseSqlite::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool UseSqlite::init()
{
    if ( !Layer::init() ) return false;
    
    //DBファイルの保存先のパス
    auto filePath = FileUtils::getInstance()->getWritablePath();
    filePath.append(DB_NAME);
    CCLOG("%s", filePath.c_str());
    //OPEN
    auto status = sqlite3_open(filePath.c_str(), &useDataBase);
    
    //ステータスが0以外の場合はエラーを表示
    if (status != SQLITE_OK){
        CCLOG("opne failed : %s", errorMessage);
    }else{
        CCLOG("open sucessed");
    }
    
    //テーブル作成
    auto create_sql = "CREATE TABLE comic_table( comic_id text , flag int(1))";
    status = sqlite3_exec(useDataBase, create_sql, NULL, NULL, &errorMessage );
    if( status != SQLITE_OK ) CCLOG("create table failed : %s", errorMessage);
    
    //インサート
    for (const auto& comic_id : _comicIds)
    {
        CCLOG("insert value id : %s",comic_id.c_str());
        char insert_sql[256]={0};
        sprintf(insert_sql, "INSERT INTO comic_table(comic_id, flag) VALUES('%s', 0)",comic_id.c_str());
        status = sqlite3_exec(useDataBase, insert_sql , NULL, NULL, &errorMessage);
    }

    //Close
    sqlite3_close(useDataBase);
    
    return true;
}

