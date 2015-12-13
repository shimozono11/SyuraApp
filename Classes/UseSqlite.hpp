//
//  UseSqlite.hpp
//  SyuraProject
//
//  Created by 林　真史 on 2015/12/14.
//
//

#ifndef UseSqlite_hpp
#define UseSqlite_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "sqlite3.h"

class SaveSQL : public cocos2d::Node {
    
    
public:
    virtual  bool init();
    
    static int sqliteOpen(sqlite3 **db);
    
    static void sqliteCreateTable();
    static const char* sqliteGetValueForKey(const char *key);
    static void sqliteSetValueForKey(const char *key,const char *value);
    
    static void sqliteUpdateValueForKey(const char *key,const char *value);
    
};


#endif /* UseSqlite_hpp */
