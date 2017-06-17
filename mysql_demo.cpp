/*************************************************************************
	> File Name: mysql_demo.cpp
	> Author: Jack Kang
	> Mail: xiyoulinux.kangyijie@gmail.com
	> Created Time: 2017年06月14日 星期三 13时10分15秒
 ************************************************************************/

#include<iostream>
#include<assert.h>
#include<mysql/mysql.h>
using namespace std;
MYSQL *db;
MYSQL_ROW row;
MYSQL_RES* result;
MYSQL_FIELD* field; 
int main(void)
{
    string sql("SELECT * FROM test");
    db = mysql_init(db);
    assert(db != NULL);
    if(!mysql_real_connect(db,"localhost","root","*****","mysql",0,NULL,0)){
        cout << "conn eorror\n" << mysql_error(db) << endl;
        return 1;
    }
    
    if(mysql_query(db,sql.c_str())){
        cout << "query eorror\n" << mysql_error(db) << endl;
        return 1;
    }
    result = mysql_store_result(db);
    assert(result!= NULL);
    int field_num = mysql_num_fields(result);
    while(1){
        row = mysql_fetch_row(result);
        if(!row)
            break;
        for(int j= 0; j < field_num; j++){
            cout << row[j] << "\t\t";

        }
        cout << endl;
    }
    mysql_free_result(result);
    
    mysql_close(db);

}
