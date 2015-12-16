//
//  UseSqlite.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/12/14.
//
//

#include "UseSqlite.hpp"

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
    filePath.append("Test.db");
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
    auto create_sql = "CREATE TABLE user( id integer primary key autoincrement, name nvarchar(32), age int(2) )";
    status = sqlite3_exec(useDataBase, create_sql, NULL, NULL, &errorMessage );
    if( status != SQLITE_OK ) CCLOG("create table failed : %s", errorMessage);
    
    //インサート
    auto insert_sql = "INSERT INTO user(name, age) VALUES('raharu', 29)";
    status = sqlite3_exec(useDataBase, insert_sql , NULL, NULL, &errorMessage);
    
    //Close
    sqlite3_close(useDataBase);
    
    return true;
}

