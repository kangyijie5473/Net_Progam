/*
 * > File Name: person.h
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年06月05日 星期一 16时47分39秒
 */

#ifndef _PERSON_H
#define _PERSON_H

const int PERSON_BOSS = 200;
const int PERSON_MANAGER = 201;
const int PERSON_USER = 202;

class User{

    public:
    bool log_in();
    bool log_out();

    bool search_book_by_name();
    bool search_book_by_type();
    bool search_book_by_state();
    bool borrow_book();
    bool return_book();
    bool change_passwd();
    
    private:
    std::string _name;
    std::string _class;
    std::string _passwd;
    int _identify;
    int _id_num;
};

class Manager: public User{

    public:
    bool add_book();
    bool delete_book();
    bool change_book_info();
};

class Boss: public User{

    public:
    bool add_manger();
    bool delete_manager();
    bool add_user();
    bool delete_user();
};
#endif

