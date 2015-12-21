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

// 抽出結果が返るコールバック関数
int UseSqlite::callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i = 0; i < argc; i++)
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    return 0;	// success
}

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
    auto status = openDB();
    //テーブル作成
    auto create_sql = "CREATE TABLE comic_table( comic_id text , flag int(1))";
    status = sqlite3_exec(useDataBase, create_sql, NULL, NULL, &errorMessage );
    if( status != SQLITE_OK ) {
        CCLOG("create table failed : %s", errorMessage);
    }else{
        //インサート
        for (const auto& comic_id : _comicIds)
        {
            CCLOG("insert value id : %s",comic_id.c_str());
            char insert_sql[256]={0};
            sprintf(insert_sql, "INSERT INTO comic_table(comic_id, flag) VALUES('%s', 0)",comic_id.c_str());
            status = sqlite3_exec(useDataBase, insert_sql , NULL, NULL, &errorMessage);
        }
    }
    if(isOpenImage("comic_icon_haruka_win_kokona.png"))
        CCLOG("success select");

    
    //Close
    sqlite3_close(useDataBase);
    
    return true;
}
//comic_idの名前から値を取り出す。失敗した場合は-1を返す
int UseSqlite::isOpenImage(char* imageName){
    auto status = openDB();
    __String *strValue = NULL;
    int v;
    char query[256] = {0};
    if (status == SQLITE_OK) {
        //test1テーブルからkeyに合わせたvalueを取り出す
//        const char *sql_select = "SELECT * FROM comic_table where comic_id ='comic_icon_haruka_win_kokona.png' ";
        sprintf(query, "SELECT * FROM comic_table where comic_id ='%s'", imageName);
        sqlite3_stmt *stmt = NULL;
        if (sqlite3_prepare_v2(useDataBase, query, (int)strlen(query), &stmt, NULL) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, imageName, (int)strlen(imageName), SQLITE_TRANSIENT);
            int ret = sqlite3_step(stmt);
            if (ret == SQLITE_DONE || ret == SQLITE_ROW) {
                int count = sqlite3_column_count(stmt);
                const unsigned char *name = sqlite3_column_text(stmt, 0);
                v = sqlite3_column_int(stmt, 1);
            }
            sqlite3_reset(stmt);
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(useDataBase);
    
    //valueがある場合
    if (v != NULL) {
        CCLOG("コミックID は　%d",v);
        return v;
    }
    //ここに来ることはないはず
    return -1;
}


int UseSqlite::openDB(){
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
    
    return status;
}

