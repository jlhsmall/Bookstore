//
// Created by jlhsmall on 2020/1/6.
//

#ifndef BOOKSTORE_BOOK_H
#define BOOKSTORE_BOOK_H
#include<cstring>
#include<string>
class Book {
    friend bool operator ==(const Book &x,const Book &y);
    friend bool operator <(const Book &x,const Book &y);
    char isbn[21], name[41], author[41], keyword[41];
    double price;int quantity;
public:
    static bool exist(const char *isb);
    static std::string haxi(const char *isb);
    const char *getisbn() { return isbn; }

    const char *getname() { return name; }

    const char *getauthor() { return author; }

    const char *getkeyword() { return keyword; }

    const double getprice() { return price; }

    const int getquantity() { return quantity; }

    Book(const char *isb = "", const char *nm = "", const char *au = "", const char *kw = "",
         const double pr = 0.0, const int quan = 0) : price(pr), quantity(quan) {
        strcpy(isbn, isb);
        strcpy(name, nm);
        strcpy(author, au);
        strcpy(keyword, kw);
    }
    Book &operator =(const Book &right) {
        if (this == &right)return *this;
        price = right.price;
        quantity = right.quantity;
        strcpy(isbn, right.isbn);
        strcpy(name, right.name);
        strcpy(author, right.author);
        strcpy(keyword, right.keyword);
        return *this;
    }
    //void store();
    void mdfisbn(const char* isb){
        strcpy(isbn,isb);
    }
    void mdfname(const char* nm){
        strncpy(name,nm+1,strlen(nm)-2);name[strlen(nm)-2]='\0';
    }
    void mdfauthor(const char* au){
        strncpy(author,au+1,strlen(au)-2);author[strlen(au)-2]='\0';
    }
    void mdfkeyword(const char* kw){
        strncpy(keyword,kw+1,strlen(kw)-2);keyword[strlen(kw)-2]='\0';
    }
    void mdfprice(const double pr){
        price=pr;
    }
    void mdfquantity(int quan){quantity+=quan;}
};


#endif //BOOKSTORE_BOOK_H
