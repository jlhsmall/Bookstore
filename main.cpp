#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include<vector>
#include<algorithm>
#include<iomanip>
#include "People.h"
#include "Book.h"
People cur("root","sjtu","root",7),pnon;
std::string cur_file;long cur_pos=-100;Book bnon;
std::vector<std::pair<double,double> >iocome;
void reset(){
    std::ofstream fout("People.txt");
    fout.close();
    for(int i=0;i<97;++i){
        std::ofstream fout2("Book"+std::to_string(i)+".txt");
        fout2.close();
    }
}
void init(){
    std::ifstream fin("People.txt");
    if(!fin){
        fin.close();
        reset();
    }
    if(!People::exist(cur.getuser_id()))cur.store();
    double x=0;
    iocome.push_back(std::make_pair(x,x));
}
bool check_usid_and_pswd(const char *ch) {
    if(strlen(ch)>30)return 0;
    for (int i = 0; i < strlen(ch); ++i)
        if ((ch[i] < '0' || ch[i] > '9') && (ch[i] < 'a' || ch[i] > 'z') && (ch[i] < 'A' || ch[i] > 'Z') &&
            ch[i] != '_')
            return 0;
    return 1;
}
bool check_num(const char *ch){
    for (int i = 0; i < strlen(ch); ++i)
        if (ch[i] < '0' || ch[i] > '9' )
            return 0;
    return 1;
}
bool check_nm(const char *ch){
    return strlen(ch)<=20;
}
bool check_isb(const char *ch){
    return check_num(ch)&&strlen(ch)<20;
}
bool check_nm_au_kw(const char *ch){
    if(ch[0]=='\0')return 1;
    if(ch[0]!='\"'||ch[strlen(ch)-1]!='\"')return 0;
    return strlen(ch)<41;
}
bool check_double(const char *ch){
    bool flg=1;
    for(int i=0;i<strlen(ch);++i){
        if(ch[i]=='.'){
            if(flg)flg=0;
            else return 0;
        }
        else if(ch[i]<'0'||ch[i]>'9')
            return 0;
    }
    return 1;
}
void su(const char* usid,const char* pswd){
    if(!check_usid_and_pswd(usid)||!check_usid_and_pswd(pswd)){
        std::cout<<"Invalid"<<std::endl;return;
    }
    People x;
    std::ifstream fin("People.txt");
    do{
        fin.read(reinterpret_cast<char*>(&x),sizeof(People));
        if(fin.eof())break;
        if(!strcmp(x.getuser_id(),usid)){
            if(x.gettype()<cur.gettype()||!strcmp(x.getpassword(),pswd)){
                cur=x;fin.close();return;
            }
            break;
        }
    }while(1);
    std::cout<<"Invalid"<<std::endl;
    fin.close();
}
void logout(){
    if(cur.gettype()<1)std::cout<<"Invalid"<<std::endl;
    else cur=pnon;
}
void useradd(const char* usid,const char* pswd,const char* s_tp,const char* nm) {
/*    if(cur.gettype()<3){
        std::cout<<"Invalid"<<std::endl;
        return;
    }*/
    if(!check_usid_and_pswd(usid)||!check_usid_and_pswd(pswd)||!check_nm(nm)||!check_num(s_tp)){
        std::cout<<"Invalid"<<std::endl;return;
    }
    int tp=atoi(s_tp);
    if (cur.gettype() <= tp || People::exist(usid)) {
        std::cout<<"Invalid"<<std::endl;
        return;
    }
    People x(usid, pswd, nm, tp);
    std::ofstream fout("People.txt", std::ofstream::app);
    fout.write(reinterpret_cast<char *>(&x), sizeof(People));
    fout.close();
}
void regster(const char* usid,const char* pswd,const char* nm) {
    if(!check_usid_and_pswd(usid)||!check_usid_and_pswd(pswd)||!check_nm(nm)){
        std::cout<<"Invalid"<<std::endl;
        return;
    }
    if(People::exist(usid)) {
        std::cout<<"Invalid"<<std::endl;
        return;
    }
    People x(usid, pswd, nm,1);
    std::ofstream fout("People.txt", std::ofstream::app);
    fout.write(reinterpret_cast<char *>(&x), sizeof(People));
    fout.close();
}
void del(const char* usid){
    if(!check_usid_and_pswd(usid)){
        std::cout<<"Invalid"<<std::endl;
        return;
    }
    if(cur.gettype()<7){
        std::cout<<"Invalid"<<std::endl;
        return;
    }
    People x;
    std::fstream fio("People.txt");
    do{
        fio.read(reinterpret_cast<char*>(&x),sizeof(People));
        if(fio.eof())break;
        if(!strcmp(x.getuser_id(),usid)){
            fio.seekp((long)fio.tellg()-(long)sizeof(People));
            fio.write(reinterpret_cast<char*>(&pnon),sizeof(People));
            return;
        }
    }while(1);
    std::cout<<"Invalid"<<std::endl;
    return;
}
void passwd(const char* usid,const char* oldpswd,const char* newpswd){
    if(!check_usid_and_pswd(usid)||!check_usid_and_pswd(oldpswd)||!check_usid_and_pswd(newpswd)){
        std::cout<<"Invalid"<<std::endl;
        return;
    }
    std::fstream fio("People.txt");
    People x;
    do{
        fio.read(reinterpret_cast<char*>(&x),sizeof(People));
        if(fio.eof())break;
        if(!strcmp(x.getuser_id(),usid))break;
    }while(1);
    if(fio.eof()){
        std::cout<<"Invalid"<<std::endl;
    }
    else {
        if (cur.gettype() == 7) {
            x.mdfpassword(newpswd);
            fio.seekp((long) fio.tellg() - (long) sizeof(People));
            fio.write(reinterpret_cast<char *>(&x), sizeof(People));
        }
        else {
            if (cur.gettype() < 1) {
                std::cout << "Invalid" << std::endl;
                return;
            }
            if (strcmp(oldpswd, x.getpassword())) {
                std::cout << "Invalid" << std::endl;
                return;
            }
            x.mdfpassword(newpswd);
            fio.seekp((long) fio.tellg() - (long) sizeof(People));
            fio.write(reinterpret_cast<char *>(&x), sizeof(People));
        }
    }
    fio.close();
}
void select(const char* isb) {
    if (!check_isb(isb) || cur.gettype() < 3) {
        std::cout << "Invalid" << std::endl;
        return;
    }
    cur_file = Book::haxi(isb);
    std::ifstream fin(cur_file);
    Book x;
    Book y(isb);
    do {
        fin.read(reinterpret_cast<char *>(&x), sizeof(Book));
        if (fin.eof())break;
        if (!strcmp(x.getisbn(), isb)) {
            cur_pos = (long) fin.tellg() - (long) sizeof(Book);
            fin.close();
            return;
        }
    } while (1);
    fin.close();
    std::ofstream fout(cur_file,std::ofstream::app);
    cur_pos = fout.tellp();
    fout.write(reinterpret_cast<char *>(&y), sizeof(Book));
    fout.close();
}
void mdf(const char* isb,const char* nm,const char* au,const char* kw,const char* s_pr) {
    if(!check_isb(isb)||!check_nm_au_kw(nm)||!check_nm_au_kw(au)||!check_nm_au_kw(kw)||!check_double(s_pr)){
        std::cout<<"Invalid"<<std::endl;
        return;
    }
    if (cur.gettype() < 3) {
        std::cout<<"Invalid"<<std::endl;
        return;
    }
    std::fstream fio(cur_file);
    fio.seekg(cur_pos);
    Book x;
    fio.read(reinterpret_cast<char *>(&x), sizeof(Book));
    if(nm[0]!='\0')x.mdfname(nm);
    if(au[0]!='\0')x.mdfauthor(au);
    if(kw[0]!='\0')x.mdfkeyword(kw);
    if(s_pr[0]!='\0')x.mdfprice(atof(s_pr));
    fio.seekp(cur_pos);
    if (isb[0]=='\0'||!strcmp(isb, x.getisbn())) {
        fio.write(reinterpret_cast<char *>(&x), sizeof(Book));
        fio.close();
        return;
    }
    fio.close();
    x.mdfisbn(isb);
    if (Book::exist(isb)) {
        std::cout<<"Invalid"<<std::endl;
        return;
    }
    fio.open(cur_file);
    fio.seekp(cur_pos);
    fio.write(reinterpret_cast<char *>(&bnon), sizeof(Book));
    fio.close();
    cur_file = Book::haxi(isb);
    std::ofstream fout(cur_file, std::ofstream::app);
    cur_pos = fout.tellp();
    fout.write(reinterpret_cast<char *>(&x), sizeof(Book));
    fout.close();
}
void import(char* s_quan,char* s_cost) {
    if (!check_num(s_quan) || !check_double(s_cost)) {
        std::cout << "Invalid" << std::endl;
        return;
    }
    if (cur.gettype() < 3) {
        std::cout << "Invalid" << std::endl;
        return;
    }
    int quan = atoi(s_quan);
    double cost = (atof(s_cost));
    Book x;
    std::fstream fio(cur_file);
    fio.seekg(cur_pos);
    fio.read(reinterpret_cast<char *>(&x), sizeof(Book));
    x.mdfquantity(quan);
    fio.seekp(cur_pos);
    fio.write(reinterpret_cast<char *>(&x), sizeof(Book));
    std::pair<double, double> old = iocome[(int) iocome.size() - 1];
    iocome.push_back(std::make_pair(old.first, old.second + cost));
}
void show_book(const char* isb,const char* nm,const char* au,const char* kw) {
    bool flgg=1;
    std::vector<Book>toshow;
    if (!check_isb(isb) || !check_nm_au_kw(nm) || !check_nm_au_kw(au) || !check_nm_au_kw(kw)) {
        std::cout << "Invalid" << std::endl;
        return;
    }
    if (cur.gettype() < 1) {
        std::cout << "Invalid" << std::endl;
        return;
    }
    Book x;
    char ch[42];memset(ch,0,sizeof ch);
    for (int i = 0; i < 97; ++i) {
        std::string file = "Book" + std::to_string(i) + ".txt";
        std::ifstream fin(file);
        do {
            fin.read(reinterpret_cast<char *>(&x), sizeof(Book));

            if (fin.eof())break;
            if (x == bnon)continue;
            if (isb[0] && strcmp(isb, x.getisbn()))continue;
            if (nm[0]) {
                strcpy(ch, x.getname());
                ch[strlen(ch) + 1] = '\0';
                ch[strlen(ch)] = '\"';
                if (strncmp(ch , nm+1, strlen(nm) - 1))continue;
            }
            if (au[0]) {
                strcpy(ch, x.getauthor());
                ch[strlen(ch) + 1] = '\0';
                ch[strlen(ch)] = '\"';
                if (strncmp(ch, au+1, strlen(au) - 1))continue;
            }
            if (kw[0]) {
                strncpy(ch, kw + 1, strlen(kw) - 2);
                ch[strlen(kw) - 2] = '\0';
                if (ch && strstr(x.getkeyword(), ch) == NULL)continue;
            }
            toshow.push_back(x);
        } while (1);
        fin.close();
    }
    std::sort(toshow.begin(), toshow.end());
    std::vector<Book>::iterator ii;
    for (ii = toshow.begin(); ii != toshow.end(); ++ii) {
        std::cout << ii->getisbn() << '\t' << ii->getname() << '\t' << ii->getauthor() << '\t' << ii->getkeyword()
                  << '\t'<< std::fixed << std::setprecision(2) << ii->getprice() << '\t' << ii->getquantity() << "本" << std::endl;
    }
}
void show_finance(const char* s_tim) {
    if (!check_num(s_tim)) {
        std::cout << "Invalid" << std::endl;
        return;
    }
    if (cur.gettype() < 7) {
        std::cout << "Invalid" << std::endl;
        return;
    }
    if (s_tim[0] == '\0') {
        std::cout << "+ " << std::fixed << std::setprecision(2) << iocome[(int) iocome.size() - 1].first << " - "
                  << iocome[(int) iocome.size() - 1].second << std::endl;
        return;
    }
    int tim = atoi(s_tim);
    if (iocome.size() <= tim + 1)
        std::cout << "+ " << std::fixed << std::setprecision(2) << iocome[(int) iocome.size() - 1].first << " - "
                  << iocome[(int) iocome.size() - 1].second << std::endl;
    else
        std::cout << "+ " << std::fixed << std::setprecision(2)<< iocome[(int) iocome.size() - 1].first - iocome[(int) iocome.size() - tim - 1].first
                  << " - "
                  << iocome[(int) iocome.size() - 1].second - iocome[(int) iocome.size() - tim - 1].second
                  << std::endl;
}
void buy(const char* isb,const char* s_quan){
    std::string file(Book::haxi(isb));
    std::fstream fio(file);
    Book x;
    do{
        fio.read(reinterpret_cast<char*>(&x),sizeof(Book));
        if(fio.eof())break;
        if(!strcmp(x.getisbn(),isb))break;
    }while(1);
    int quan=atoi(s_quan);
    if(fio.eof()||x.getquantity()<quan) {
        std::cout << "Invalid" << std::endl;
        return;
    }
    x.mdfquantity(-quan);
    fio.seekp((long)fio.tellg()-(long)sizeof(Book));
    fio.write(reinterpret_cast<char*>(&x),sizeof(Book));
    std::pair<double,double> old=iocome[(int)iocome.size()-1];
    iocome.push_back(std::make_pair(old.first+quan*x.getprice(),old.second));
}
int main() {
    //reset();
    init();int l;
    char op[300],ch[300], isb[21], nm[41], au[41], kw[41],s_pr[21];
    memset(op,0,sizeof op);
    memset(ch,0,sizeof ch);
    memset(isb,0,sizeof isb);
    memset(nm,0,sizeof nm);
    memset(au,0,sizeof au);
    memset(kw,0,sizeof kw);
    memset(s_pr,0,sizeof s_pr);
    std::vector<char*>v;
    while(std::cin>>op){
        std::cin.getline(ch,299);
        l=strlen(ch);
        v.clear();
        for(int i=0;i<l;++i){
            while(i<l&&(ch[i]==' '||ch[i]=='\t'))++i;
            if(i==l)break;
            v.push_back(ch+i);
            for(;i<l&&(ch[i]!=' '&&ch[i]!='\t');++i)
                if(ch[i]=='\"'){
                    for(++i;i<l&&ch[i]!='\"';++i);
                    if(i<l)++i;break;
                }
            ch[i]='\0';
        }
        if(!strcmp(op,"su")){
            if(v.size()==2)su(v[0],v[1]);
            else if(v.size()==1)su(v[0],"");
            else std::cout<<"Invalid"<<std::endl;
        }
        else if(!strcmp(op,"logout")){
            if(v.size())std::cout<<"Invalid"<<std::endl;
            else logout();
        }
        else if(!strcmp(op,"useradd")){
            if(v.size()!=4)std::cout<<"Invalid"<<std::endl;
            else useradd(v[0],v[1],v[2],v[3]);
        }
        else if(!strcmp(op,"register")){
            if(v.size()!=3)std::cout<<"Invalid"<<std::endl;
            else regster(v[0],v[1],v[2]);
        }
        else if(!strcmp(op,"delete")){
            if(v.size()!=1)std::cout<<"Invalid"<<std::endl;
            else del(v[0]);
        }
        else if(!strcmp(op,"passwd")){
            if(v.size()==2)passwd(v[0],"",v[1]);
            else if(v.size()==3)passwd(v[0],v[1],v[2]);
            else std::cout<<"Invalid"<<std::endl;
        }
        else if(!strcmp(op,"select")){
            if(v.size()!=1)std::cout<<"Invalid"<<std::endl;
            else select(v[0]);
        }
        else if(!strcmp(op,"modify")){
            if(cur_pos==-100||v.size()>5||!v.size()){
                std::cout<<"Invalid"<<std::endl;
                continue;
            }
            isb[0]=nm[0]=au[0]=kw[0]=s_pr[0]='\0';
            int i;
            for(i=0;i<v.size();++i){
                if(!strncmp("-ISBN=",v[i],6))
                    strcpy(isb,v[i]+6);
                else if(!strncmp("-name=",v[i],6))
                    strcpy(nm,v[i]+6);
                else if(!strncmp("-author=",v[i],8))
                    strcpy(au,v[i]+8);
                else if(!strncmp("-keyword=",v[i],9))
                    strcpy(kw,v[i]+9);
                else if(!strncmp("-price=",v[i],7))
                    strcpy(s_pr,v[i]+7);
                else break;
            }
            if(i<v.size())std::cout<<"Invalid"<<std::endl;
            else mdf(isb,nm,au,kw,s_pr);
        }
        else if(!strcmp(op,"import")){
            if(cur_pos==-100||v.size()!=2)std::cout<<"Invalid"<<std::endl;
            else import(v[0],v[1]);
        }
        else if(!strcmp(op,"show")){
            if(v.size()&&!strcmp(v[0],"finance")){
                if(v.size()>2){
                    std::cout<<"Invalid"<<std::endl;
                    continue;
                }
                if(v.size()==1)v.push_back("");
                show_finance(v[1]);
                continue;
            }
            if(v.size()>4){
                std::cout<<"Invalid"<<std::endl;
                continue;
            }
            isb[0]=nm[0]=au[0]=kw[0]='\0';
            int i;
            for(i=0;i<v.size();++i){
                if(!strncmp("-ISBN=",v[i],6))
                    strcpy(isb,v[i]+6);
                else if(!strncmp("-name=",v[i],6))
                    strcpy(nm,v[i]+6);
                else if(!strncmp("-author=",v[i],8))
                    strcpy(au,v[i]+8);
                else if(!strncmp("-keyword=",v[i],9))
                    strcpy(kw,v[i]+9);
                else break;
            }

            if(i<v.size())std::cout<<"Invalid"<<std::endl;
            else show_book(isb,nm,au,kw);
        }
        else if(!strcmp(op,"buy")){
            if(cur_pos==-100||v.size()!=2)std::cout<<"Invalid"<<std::endl;
            else buy(v[0],v[1]);
        }
        else if(!strcmp(op,"exit")){
            break;
        }
        else{
            std::cout<<"Invalid"<<std::endl;
        }
    }
    return 0;
}