/*
 * > File Name: book.h
 * > Author: Jack Kang
 * > Mail: kangyijie@xiyoulinux.org
 * > Created Time: 2017年06月09日 星期五 08时10分07秒
 */

#ifndef _BOOK_H
#define _BOOK_H
const int BOOK_TYPE_OS = 100;
const int BOOK_TYPE_LANG = 101;
const int BOOK_TYPE_NET = 102;
const int BOOK_TYPE_MATH = 103;
const int BOOK_TYPE_DB = 104;
const int BOOK_TYPE_SUMMARIZE = 105; // 之前学长留下的总结
const int BOOK_TYPE_ALGOR = 106;
const int BOOK_TYPE_HARD = 107;
const int BOOK_TYPE_OTHER = 108;

class Book{
    public:

    private:
    std::string _name;
    int _type;
    std::string _original_owner;
    std::string _now_owner;
    std::string _location;
    bool _state;
};
#endif
