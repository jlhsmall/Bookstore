//
// Created by jlhsmall on 2020/1/6.
//
#include<fstream>
#include<string>
#include<cmath>
#include "Book.h"
/*void Book::store(){
    std::string file(haxi(isbn));
    std::ofstream fout(file,std::ofstream::app);
    fout.write(reinterpret_cast<char*>(this),sizeof(Book));
    fout.close();
}*/
bool operator ==(const Book &x,const Book &y){
    if(fabs(x.price-y.price)>0.000001)return 0;
    if(strcmp(x.isbn,y.isbn))return 0;
    if(strcmp(x.name,y.name))return 0;
    if(strcmp(x.author,y.author))return 0;
    if(strcmp(x.keyword,y.keyword))return 0;
    return x.quantity==y.quantity;
}
bool operator <(const Book &x,const Book &y){
    return strcmp(x.isbn,y.isbn)<0;
}
std::string Book::haxi(const char *isb){
    int ret=0;
    for(int i=0;i<strlen(isb);++i)ret=(ret*128+isb[i])%97;
    return "Book"+std::to_string(ret)+".txt";
}
bool Book::exist(const char *isb) {
    std::string file(haxi(isb));
    std::ifstream fin(file);
    Book x;
    do{
        fin.read(reinterpret_cast<char*>(&x),sizeof(Book));
        if(fin.eof())break;
        if(!strcmp(x.isbn,isb))break;
    }while(1);
    bool ret=!fin.eof();
    fin.close();
    return ret;
}