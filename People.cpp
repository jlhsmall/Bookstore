//
// Created by jlhsmall on 2020/1/5.
//
#include<fstream>
#include "People.h"
void People::store(){
    std::ofstream fout("People.txt",std::ofstream::app);
    fout.write(reinterpret_cast<char*>(this),sizeof(People));
    fout.close();
}
void People::modify(){
    People x;
    std::fstream fio("People.txt");
    do{
        fio.read(reinterpret_cast<char*>(&x),sizeof(People));
        if(!strcmp(x.getuser_id(),user_id)){
            fio.seekp((long)fio.tellg()-(long)sizeof(People));
            fio.write(reinterpret_cast<char*>(this),sizeof(People));
            return;
        }
    }while(1);
}
bool People::exist(const char *usid){
    People x;
    std::ifstream fin("People.txt");
    do{
        fin.read(reinterpret_cast<char*>(&x),sizeof(People));
        if(fin.eof())break;
        if(!strcmp(x.getuser_id(),usid))break;
    }while(1);
    bool ret=!fin.eof();
    fin.close();
    return ret;
}