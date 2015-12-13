//
//  UseSqlite.cpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/12/14.
//
//

#include "UseSqlite.hpp"
#define dbName "syura.db"

USING_NS_CC;

//データベースを開く
int SaveSQL::sqliteOpen(sqlite3 **db){
    
    auto filePath = FileUtils::getInstance()->getWritablePath();
    filePath += dbName;
    
    return sqlite3_open(filePath.c_str(),db);
    
}


//データベースのテーブルの作成
void SaveSQL::sqliteCreateTable(){
    
    //データベースを作成
    sqlite3 *db = NULL;
    if(sqliteOpen(&db) == SQLITE_OK){
        
        // key とvalueの２つ値がある テーブル(test1)を作成
        const char *sql_createtable = "CREATE TABLE comic_table(comic_id TEXT,flag bool)";
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
