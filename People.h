//
// Created by jlhsmall on 2020/1/5.
//

#ifndef BOOKSTORE_PEOPLE_H
#define BOOKSTORE_PEOPLE_H
#include<iostream>
#include<cstring>

class People {
    friend void passwd();

    int type;
    char user_id[31], password[31], name[21];
public:
    static bool exist(const char *usid);
    const int gettype() { return type; }

    const char *getname() { return name; }

    const char *getuser_id() { return user_id; }

    const char *getpassword() { return password; }

    People(const char *usid = "", const char *pswd = "", const char *nm = "", int tp = 0) {
        memset(this,0,sizeof *this);
        strcpy(name, nm);
        strcpy(user_id, usid);
        strcpy(password, pswd);
        type=tp;
    }

    People &operator=(const People &right) {
        if (this == &right)return *this;
        type = right.type;
        strcpy(name, right.name);
        strcpy(user_id, right.user_id);
        strcpy(password, right.password);
        return *this;
    }

    void store();
    void mdfpassword(const char* pswd){
        strcpy(password,pswd);
    }
    void modify();
};
#endif //BOOKSTORE_PEOPLE_H
