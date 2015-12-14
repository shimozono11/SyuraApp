//
//  UseSqlite.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/12/14.
//
//

#include "UseSqlite.hpp"
#define dbName "syuraApp.db"

USING_NS_CC;

//データベースを開く
int UseSqlite::sqliteOpen(sqlite3 **db){
    
    auto filePath = FileUtils::getInstance()->getWritablePath();
    filePath += dbName;
    
    
    return sqlite3_open(filePath.c_str(),db);
    
}


//データベースのテーブルの作成
void UseSqlite::sqliteCreateTable(){
    
    //データベースを作成
    sqlite3 *db = NULL;
    if(sqliteOpen(&db) == SQLITE_OK){
        
        // key とvalueの２つ値がある テーブル(test1)を作成
        const char *sql_createtable = "CREATE TABLE comic_table(comic_id TEXT,flag integer)";
        sqlite3_stmt *stmt = NULL;
        if (sqlite3_prepare_v2(db, sql_createtable, -1, &stmt, NULL) == SQLITE_OK) {
            
            if (sqlite3_step(stmt) == SQLITE_DONE) {
                
                CCLOG("create table done");
            }
            
            sqlite3_reset(stmt);
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}

//初期データの挿入

//keyとvalueを設定する(初期)
void UseSqlite::sqliteSetValueForKey(const char *key,const char *value){
    
    
    std::string fullpath = FileUtils::getInstance()->getWritablePath();
    fullpath += dbName;
    sqlite3 *db = NULL;
    
    if (sqlite3_open(fullpath.c_str(), &db) == SQLITE_OK) {
        const char *sql_select = "INSERT INTO comic_table(comic_id,false)VALUES(?,0)";
        sqlite3_stmt *stmt = NULL;
        
        if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL) == SQLITE_OK) {
            
            sqlite3_bind_text(stmt, 1, key, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, value, -1, SQLITE_TRANSIENT);
            
            if (sqlite3_step(stmt) == SQLITE_DONE) {
                
                CCLOG("replace comic_id:%s values:%s",key,value);
            }
            
            sqlite3_reset(stmt);
            
        }
        
        sqlite3_finalize(stmt);

    
    }
    
    sqlite3_close(db);
    
    
}


