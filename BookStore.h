//
// Created by lenovo on 2021/1/19.
//
#ifndef CODE_BOOKSTORE_H
#define CODE_BOOKSTORE_H
#pragma once
#include "bplustree.hpp"
//#include "blockchain.h"
#include "UserManager.h"
#include <iomanip>
#include <set>
#include <map>
#include <stdio.h>
#include <cstring>
//#include <windows.h>
void color(int x) ;//设置字体颜色

class reportfinance{
public:
    friend ostream &operator<<(ostream &os,const reportfinance&obj);
    char ISBN[120];
    bool input_or_output;
    int num;
    double price1;
    user tempuser;
    char time[1000];
};
ostream &operator<<(ostream &os,const reportfinance&obj);
inline char* righttime(){
    time_t now = time(0);
    return ctime(&now);
}
#define HO(x) x.open(BOOK_DATA); x<<__FUNCTION__<<__LINE__<<endl;
#define DEBUG() cout<<__FUNCTION__<<__LINE__<<ENDL;
void init() ;
class Book{
public:char ISBN[30];
    char name[60];
    char author[60];
    char keywords[60];
    double price;
    int quantity;
    Book();
};
enum bookinfo{
    ISBN,NAME,AUTHOR,KETWORDS
};
class bookstore{
public:
    int tradetimes;
    int booknum;
    double totaiinput,totoaloutput;
    usermanager cmd;
    sjtu::BPtree<mystring, int> ISBN_BOOKSTORE_blocklist,BOOKNAME_BOOKSTORE_blocklist,KEYWORD_BOOKSTORE,AUTHOR_BOOKSTORE;//the region of the four output
fstream f1,f2,f3,f4,f5,f6;
fstream fa,fb;
    bookstore();
    vector<string>splitkey(string index){
        vector<string> returnvec;
        if (index.empty()){return returnvec;}
        int len=index.length();
        string a1,a2,a3,a4,a5,a6,a7,a8;
        int i;
        for ( i = 0; i <len&&index[i]!='|' ; ++i) {a1+=index[i];}
        returnvec.push_back(a1);
        for (i++;i<len&&index[i]!='|';++i) {a2+=index[i];}
        if (!a2.empty())returnvec.push_back(a2);
        for (i++;i<len&&index[i]!='|';++i) {a3+=index[i];}
        for (i++;i<len&&index[i]!='|';++i) {a4+=index[i];}
        for (i++;i<len&&index[i]!='|';++i) {a5+=index[i];}
        for (i++;i<len&&index[i]!='|';++i) {a6+=index[i];}
        for (i++;i<len&&index[i]!='|';++i) {a7+=index[i];}
        for (i++;i<len&&index[i]!='|';++i) {a8+=index[i];}
        if (!a3.empty())returnvec.push_back(a3);
        if (!a4.empty())returnvec.push_back(a4);
        if (!a5.empty())returnvec.push_back(a5);
        if (!a6.empty())returnvec.push_back(a6);
        if (!a7.empty())returnvec.push_back(a7);
        if (!a8.empty())returnvec.push_back(a8);
        return returnvec;
    }


        void report_finance();
        void report_employee(string temp);
        void log();
        void reportme();


    void run(string temp);
    void select(string ISBN_){
        //modify the stack
       // cout<<cmd.usernum<<"   in select"<<endl;
        //cout<<cmd.user_stack[cmd.usernum-1].id<<"(((((in select"<<endl;
       // cout<<cmd.user_stack[cmd.usernum-1].priviledge<<"^^^^^^^ in select"<<endl;//random
        if (ISBN_.empty()||(cmd.user_stack[cmd.usernum-1].priviledge)<3) {
           //cout<<"^^ in selelct"<<endl;
            cout<<"Invalid"<<endl;
            return;}
        //cout<<"&&&&&&&&&"<<endl;
        //(--cmd.user_stack.end())->currentbookISBN=atoi(ISBN_.c_str());
       // cout<<(--cmd.user_stack.end())->currentbookISBN<<"&&&&&&&"<<endl;
       char cnm[120]={0};
        cnm[119]='\0';
        strcpy(cnm,ISBN_.c_str());
        mystring ffuyou;
        memset(&ffuyou,0,sizeof (ffuyou));
        strcpy(ffuyou.mychar,cnm);

        vector<sjtu::BPtree<mystring, int >::value_type>tempsearch (ISBN_BOOKSTORE_blocklist.find(ffuyou));
        //cout<<tempsearch.empty()<<"&&&&&&&&&&"<<endl;
        if (tempsearch.empty()){
           //cout<<"is empty in select"<<endl;
           f1.close();
            f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f1){
                f1.open(BOOK_DATA,ios::out|ios::binary);
            }
//            f2.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
//            if (!f2){
//                f2.open(BOOK_DATA,ios::out|ios::binary);
//            }
//            f2.seekg(0);
//            char tempnam[30];
//            f2.read(reinterpret_cast<char*>(&tempnam),30);
//            cout<<"f2.fail:  "<<f2.fail()<<endl;
//            cout<<tempnam<<"test in select in tempnam"<<endl;
            f1.seekg(0,ios::end);
            int tempoffset=f1.tellg();//must be incorrect
           //cout<<tempoffset<<"***************in name selsect"<<endl;
            Book tempbook;
            strcpy(tempbook.ISBN,ISBN_.c_str());
            f1.write(reinterpret_cast<char*>(&tempbook),sizeof (Book));
            char uu[120]={0};
            uu[119]='\0';
            strcpy(uu,ISBN_.c_str());
            mystring uuuu;
            memset(&uuuu,0,sizeof (uuuu));
            strcpy(uuuu.mychar,uu);
            sjtu::BPtree<mystring, int>::value_type tempele(uuuu,tempoffset);

            //cout<<ISBN_.c_str()<<" in select"<<endl;
           //cout<<ISBN_<<"((((((((((((((((^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^(("<<endl;
            ISBN_BOOKSTORE_blocklist.insert(tempele);//todo
           // cout<<"select fuction:"<<endl;
           // ISBN_BOOKSTORE_blocklist.debug();
           // cout<<"select fuc"<<endl;
            (--cmd.user_stack.end())->currentbookISBN=tempoffset;
            //ISBN_BOOKSTORE_blocklist.debug();
            f1.close();
        } else{
            (--cmd.user_stack.end())->currentbookISBN=tempsearch[0].second;

//            f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
//            if (!f1){
//                f1.open(BOOK_DATA,ios::out|ios::binary);
//            }
//            f1.seekg(tempoffset);
//            f1.write(reinterpret_cast<char*>(&ISBN_),40);
//            element tempelement;
//            strcpy(tempelement.key,ISBN_.c_str());
//            tempelement.offset=tempoffset;
//            ISBN_BOOKSTORE_blocklist.deleteelment(tempelement);
//            ISBN_BOOKSTORE_blocklist.addelement(tempelement);
        }
    }
    void import(int tempquantity,double allcost){
        if ((cmd.user_stack[cmd.usernum-1].priviledge)<3||cmd.user_stack[cmd.usernum-1].currentbookISBN==-1) {
            cout<<"Invalid"<<endl;
            return;}
int tempisbn=cmd.user_stack[cmd.usernum-1].currentbookISBN;
        f6.close();
        f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
        if (!f6){
            f6.open(BOOK_DATA,ios::out|ios::binary);
        }
        f6.seekg(tempisbn);
        Book tempbook;
        f6.read(reinterpret_cast<char*>(&tempbook),sizeof (Book));
        char ss[30];
        strcpy(ss,tempbook.ISBN);
        //cout<<ss<<"   import"<<endl;
        string s=ss;
        f6.close();
        //std::string s = std::to_string(tempisbn) ;
        char rtm[120]={0};
        rtm[119]='\0';
        strcpy(rtm,s.c_str());
        mystring nnm;
        memset(&nnm,0,sizeof (nnm));
        strcpy(nnm.mychar,rtm);
        vector<sjtu::BPtree<mystring, int >::value_type>tempsearch (ISBN_BOOKSTORE_blocklist.find(nnm));
        int tempoffset=tempsearch[0].second;
        f1.close();
        f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
        if (!f1){
            f1.open(BOOK_DATA,ios::out|ios::binary);
        }
        f1.seekg(tempoffset);
        Book tempbook2;
        int prenum;
        f1.read(reinterpret_cast<char*>(&tempbook),sizeof (Book));
        tempbook.quantity+=tempquantity;
        f1.seekg(tempoffset);
        f1.write(reinterpret_cast<char*>(&tempbook),sizeof (Book));
        f2.close();
        f2.open(TOTAL_FINANCE_DATA,ios_base::binary|ios::in | ios::out);
        if (!f2){
            f2.open(TOTAL_FINANCE_DATA,ios::out|ios::binary);
        }
        totoaloutput+=allcost;
        booknum+=tempquantity;
        tradetimes++;
        //写入顺序，总收入，总支出，书本数量，交易次数
        f2.seekg(0);
        f2.write(reinterpret_cast<char*>(&totaiinput),8);
        f2.write(reinterpret_cast<char*>(&totoaloutput),8);
        f2.write(reinterpret_cast<char*>(&booknum),4);
        f2.write(reinterpret_cast<char*>(&tradetimes),4);
        f2.close();
        f2.open(EVERT_FINANCE_DATA,ios_base::binary|ios::in | ios::out);
        if (!f2){
            f2.open(EVERT_FINANCE_DATA,ios::out|ios::binary);
        }
        f2.seekg(0,ios::end);
        bool output=1;//1定义为支出，0定义为收入
        f2.write(reinterpret_cast<char*>(&output),sizeof (bool));
        f2.write(reinterpret_cast<char*>(&allcost),sizeof (double ));

        fa.close();
        fa.open(CLI_FINANCE_DETAILED,ios_base::binary|ios::in | ios::out);
        if (!fa){
            fa.open(CLI_FINANCE_DETAILED,ios::out|ios::binary);
        }
        fa.seekg(0,ios::end);
        reportfinance tempreport;
        strcpy(tempreport.ISBN,ss);
        tempreport.tempuser=cmd.user_stack[cmd.usernum-1];
        tempreport.num=tempquantity;
        tempreport.input_or_output=1;
        tempreport.price1=allcost;
        strcpy(tempreport.time,righttime());
        fa.write(reinterpret_cast<char*>(&tempreport),sizeof (tempreport));
        fa.close();
        f1.close(),f2.close();
    }
    void modify(string keycharacter,string index,int offset){
      // cout<<"?????????begin in modify"<<endl;
      //cout<<"index  :"<<index<<"       in modify"<<endl;
     //cout<<cmd.user_stack[cmd.usernum-1].currentbookISBN<<"******* in modify"<<endl;
    // cout<<offset<<"**************8 in modify"<<endl;
        if (index.empty()||(cmd.user_stack[cmd.usernum-1].priviledge)<3||cmd.user_stack[cmd.usernum-1].currentbookISBN==-1) {
          // cout<<"first invalid in modify fuction"<<endl;
            cout<<"Invalid"<<endl;
            return;}
        f1.close();
        f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
        if (!f1){
            f1.open(BOOK_DATA,ios::out|ios::binary);
        }
        f1.seekg(offset);

        char isbnstring_[30];
        f1.read(reinterpret_cast<char*>(&isbnstring_),30);
        string isbnstring=isbnstring_;
      //  cout<<isbnstring<<"   isbnstring in modify fuction"<<endl;
        //cout<<f1.fail()<<"  in the modify begin f1.fail"<<endl;

        if (keycharacter=="author"){
           // cout<<isbnstring<<"  &&&&& IN AUTHOR"<<endl;
           char nnnmmd[120]={0};
           nnnmmd[119]='\0';
           strcpy(nnnmmd,isbnstring.c_str());
           mystring nmsll;
            memset(&nmsll,0,sizeof (nmsll));
            strcpy(nmsll.mychar,nnnmmd);
            vector<sjtu::BPtree<mystring, int >::value_type>tempsearch (ISBN_BOOKSTORE_blocklist.find(nmsll));
            if (tempsearch.empty()){
               // cout<<"   find result empty in modify"<<endl;
                cout<<"Invalid"<<endl;
                return;}
            int tempoffset=tempsearch[0].second;
            f6.close();
            f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f6){
                f6.open(BOOK_DATA,ios::out|ios::binary);
            }
            //cout<<f6.fail()<<" f1.fail"<<" in modify_ISBN"<<endl;
            f6.seekg(tempoffset+90);
            char pre_author[60];
            f6.read(reinterpret_cast<char*>(&pre_author),60);
            //modify
            // cout<<pre_author<<"debug in preauthor in modify-ISBN branch"<<endl;
            //cout<<index<<" index in modify-ISBN branch"<<endl;
//            vector<int>tempsearch2 (ISBN_BOOKSTORE_blocklist.findelement(index));
//            // ISBN_BOOKSTORE_blocklist.debug();
//            //cout<<tempsearch2[0]<<"debug in modify_ISBN"<<endl;
//            if (!tempsearch2.empty()){cout<<"Invalid"<<endl;
//                //cout<<"the isbn is exist yet in modify ISBN"<<endl;
//                f1.close();
//                f6.close();
//                return;}
            f6.seekg(tempoffset+90);

            //modify__
            char index_[60];
            string tempput;
            strcpy(index_,index.c_str());
            for (int i = 1; index_[i] !='"' ; ++i) {
                tempput+=index_[i];
            }
            char writein[60];
            strcpy(writein,tempput.c_str());
            //cout<<index_<<"author in modify"<<endl;
            f6.write(reinterpret_cast<char*>(&writein),60);//modify__
            //cout<<index_<<" debug in index_ in modify in ISBN"<<endl;
mystring preeeeau(pre_author),wrrrri(writein);
            memset(&preeeeau,0,sizeof (preeeeau));
            memset(&wrrrri,0,sizeof (wrrrri));
            strcpy(preeeeau.mychar,pre_author),strcpy(wrrrri.mychar,writein);
            sjtu::BPtree<mystring, int>::value_type a(preeeeau,tempoffset);

            sjtu::BPtree<mystring, int>::value_type b(wrrrri,tempoffset);


            AUTHOR_BOOKSTORE.erase(a);
            //ISBN_BOOKSTORE_blocklist.debug();
            AUTHOR_BOOKSTORE.insert(b);
            //ISBN_BOOKSTORE_blocklist.debug();
            f1.close();
            f6.close();

        }
        else if (keycharacter=="name"){
           // ISBN_BOOKSTORE_blocklist.debug();
           char jj[120]={0};
           jj[119]='\0';
           strcpy(jj,isbnstring.c_str()
                   );
           mystring cao(jj);
            memset(&cao,0,sizeof (cao));
            strcpy(cao.mychar,jj);
            vector<sjtu::BPtree<mystring, int >::value_type>tempsearch (ISBN_BOOKSTORE_blocklist.find(cao));
            if (tempsearch.empty()){
               //cout<<"   tempsearch empty!!! in modify_name"<<endl;
                cout<<"Invalid"<<endl;
                f1.close();
                return;}
            int tempoffset=tempsearch[0].second;
            f6.close();
            f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f6){
                f6.open(BOOK_DATA,ios::out|ios::binary);
            }
            //cout<<f6.fail()<<" f1.fail"<<" in modify_ISBN"<<endl;
            f6.seekg(tempoffset+30);
            char pre_author[60];
            f6.read(reinterpret_cast<char*>(&pre_author),60);
            //modify
            // cout<<pre_author<<"debug in preauthor in modify-ISBN branch"<<endl;
            //cout<<index<<" index in modify-ISBN branch"<<endl;
//            vector<int>tempsearch2 (ISBN_BOOKSTORE_blocklist.findelement(index));
//            // ISBN_BOOKSTORE_blocklist.debug();
//            //cout<<tempsearch2[0]<<"debug in modify_ISBN"<<endl;
//            if (!tempsearch2.empty()){cout<<"Invalid"<<endl;
//                //cout<<"the isbn is exist yet in modify ISBN"<<endl;
//                f1.close();
//                f6.close();
//                return;}
            f6.seekg(tempoffset+30);

            //modify__
            char index_[60];
            string tempput;
            strcpy(index_,index.c_str());
            for (int i = 1; index_[i] !='"' ; ++i) {
                tempput+=index_[i];
            }
            char writein[60];
            strcpy(writein,tempput.c_str());


            f6.write(reinterpret_cast<char*>(&writein),60);//modify__

            mystring preeeeau(pre_author),wrrrri(writein);
            memset(&preeeeau,0,sizeof (preeeeau));
            memset(&wrrrri,0,sizeof (wrrrri));
            strcpy(preeeeau.mychar,pre_author);
            strcpy(wrrrri.mychar,writein);
            //cout<<index_<<" debug in index_ in modify in ISBN"<<endl;
            BOOKNAME_BOOKSTORE_blocklist.erase(sjtu::BPtree<mystring, int>::value_type(preeeeau,tempoffset));
            //ISBN_BOOKSTORE_blocklist.debug();
             BOOKNAME_BOOKSTORE_blocklist.insert(sjtu::BPtree<mystring, int>::value_type(wrrrri,tempoffset));
            //ISBN_BOOKSTORE_blocklist.debug();
            f1.close();
            f6.close();


        }
        else if (keycharacter=="ISBN"){
            //cout<<"go into in modify_ISBN fuction"<<endl;
            char fuc[120]={0};
            fuc[119]='\0';
            strcpy(fuc,isbnstring.c_str());
            mystring tmlgb(fuc);
            memset(&tmlgb,0,sizeof (tmlgb));
            strcpy(tmlgb.mychar,fuc);
            vector<sjtu::BPtree<mystring, int >::value_type>tempsearch (ISBN_BOOKSTORE_blocklist.find(tmlgb));
            if (tempsearch.empty()){
                //cout<<"finresult is empty  in modify"<<endl;
                cout<<"Invalid"<<endl;
                f1.close();
                return;}
            int tempoffset=tempsearch[0].second;
            //cout<<tempoffset<<"  tempoffset in ISBN in modify"<<endl;

            //modify
            f6.close();
            f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f6){
                f6.open(BOOK_DATA,ios::out|ios::binary);
            }
            //cout<<f6.fail()<<" f1.fail"<<" in modify_ISBN"<<endl;
            f6.seekg(tempoffset);
            char pre_author[30];
            f6.read(reinterpret_cast<char*>(&pre_author),30);
            //modify
           // cout<<pre_author<<"debug in preauthor in modify-ISBN branch"<<endl;
            //cout<<index<<" index in modify-ISBN branch"<<endl;
            char wky[120]={0};
            wky[119]='\0';
            strcpy(wky,index.c_str());
            mystring srb(wky);
            memset(&srb,0,sizeof (srb));
            strcpy(srb.mychar,wky);
            vector<sjtu::BPtree<mystring, int >::value_type>tempsearch2 (ISBN_BOOKSTORE_blocklist.find(srb));
           // ISBN_BOOKSTORE_blocklist.debug();
            //cout<<tempsearch2[0]<<"debug in modify_ISBN"<<endl;
            if (!tempsearch2.empty()){cout<<"Invalid"<<endl;
            //cout<<"the isbn is exist yet in modify ISBN"<<endl;
            f1.close();
            f6.close();
                return;}
            f6.seekg(tempoffset);

            //modify__
            char index_[30];
            strcpy(index_,index.c_str());
            f6.write(reinterpret_cast<char*>(&index_),30);//modify__
            mystring preeeeau(pre_author),wrrrrii(index_);
            //cout<<index_<<" debug in index_ in modify in ISBN"<<endl;
            ISBN_BOOKSTORE_blocklist.erase(sjtu::BPtree<mystring, int>::value_type(preeeeau,tempoffset));
            //ISBN_BOOKSTORE_blocklist.debug();
          ISBN_BOOKSTORE_blocklist.insert(sjtu::BPtree<mystring, int>::value_type(wrrrrii,tempoffset));
            //ISBN_BOOKSTORE_blocklist.debug();
           // cout<<"in modify ISBN"<<endl;
            f1.close();
            f6.close();

        }
        else if (keycharacter=="keyword"){//注意这里不同于上面，关键词要求一个一个添加到块状链表中
char bu[120]={0};
bu[119]='\0';
strcpy(bu,isbnstring.c_str());
mystring bushi(bu);
            vector<sjtu::BPtree<mystring, int >::value_type>tempsearch (ISBN_BOOKSTORE_blocklist.find(bushi));
            if (tempsearch.empty()){
                cout<<"Invalid"<<endl;
                f1.close();
                return;}
            int tempoffset=tempsearch[0].second;
            f6.close();
            f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f6){
                f6.open(BOOK_DATA,ios::out|ios::binary);
            }
            //cout<<f6.fail()<<" f1.fail"<<" in modify_ISBN"<<endl;
            f6.seekg(tempoffset+150);
            char pre_author[60];
            f6.read(reinterpret_cast<char*>(&pre_author),60);
            //modify
            // cout<<pre_author<<"debug in preauthor in modify-ISBN branch"<<endl;
            //cout<<index<<" index in modify-ISBN branch"<<endl;
//            vector<int>tempsearch2 (ISBN_BOOKSTORE_blocklist.findelement(index));
//            // ISBN_BOOKSTORE_blocklist.debug();
//            //cout<<tempsearch2[0]<<"debug in modify_ISBN"<<endl;
//            if (!tempsearch2.empty()){cout<<"Invalid"<<endl;
//                //cout<<"the isbn is exist yet in modify ISBN"<<endl;
//                f1.close();
//                f6.close();
//                return;}
            f6.seekg(tempoffset+150);

            char index_[60];
            string tempput;
            strcpy(index_,index.c_str());
            for (int i = 1; index_[i] !='"' ; ++i) {
                tempput+=index_[i];
            }
            char writein[60];
            strcpy(writein,tempput.c_str());


            f6.write(reinterpret_cast<char*>(&writein),60);//modify__
            //cout<<index_<<" debug in index_ in modify in ISBN"<<endl;
            vector<string>tempvec(splitkey(tempput));
            string str(pre_author);
            vector<string>tempbefore(splitkey(str));
            //todo
            map<string,int> tempmap;
            set<string>s;
            for (int i = 0; i<tempvec.size() ; ++i) {
            s.insert(tempvec[i]);
            }
            if (s.size()!=tempvec.size()){
                cout<<"Invalid"<<endl;
                f1.close(),f6.close();
                return;
            }
            for (int i = 0; i <tempbefore.size() ; ++i) {
                char cccnm[120]={0};
                cccnm[119]='\0';
                strcpy(cccnm,tempbefore[i].c_str());
                mystring fffu(cccnm);
                KEYWORD_BOOKSTORE.erase(sjtu::BPtree<mystring, int>::value_type(fffu,tempoffset));
            }
            for (int i = 0; i < tempvec.size(); ++i) {
                char cccnm[120]={0};
                cccnm[119]='\0';
                strcpy(cccnm,tempvec[i].c_str());
                mystring mccm(cccnm);
                KEYWORD_BOOKSTORE.insert(sjtu::BPtree<mystring, int>::value_type(mccm,tempoffset));
            }
          // KEYWORD_BOOKSTORE.debug();
           //cout<<"  in modify keyword"<<endl;
            f1.close();
            f6.close();

        }
        else if(keycharacter=="price"){
            char nmd[120]={0};
            nmd[119]='\0';
            strcpy(nmd,isbnstring.c_str());
            mystring tmmm(nmd);
            vector<sjtu::BPtree<mystring, int >::value_type>tempsearch (ISBN_BOOKSTORE_blocklist.find(tmmm));
            if (tempsearch.empty()){
                cout<<"Invalid"<<endl;
                f1.close();
                return;}
            int tempoffset=tempsearch[0].second;
            f6.close();
            f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f6){
                f6.open(BOOK_DATA,ios::out|ios::binary);
            }
            f6.seekg(tempoffset);
           // cout<<f6.fail()<<"    f1.fail() in modify in price"<<endl;
            double d = atof((index.c_str()));
            Book tempbook;
            f6.read(reinterpret_cast<char*>(&tempbook),sizeof (Book));
            tempbook.price=d;
          //  cout<<tempbook.ISBN<<" "<<tempbook.name<<" "<<tempbook.author<<" "<<tempbook.keywords<<" "<<setiosflags(ios::fixed) << setprecision(2)<<tempbook.price<<" "<<tempbook.quantity<<"debug in modify_price"<<endl;
            f6.seekg(tempoffset);
            f6.write(reinterpret_cast<char*>(&tempbook),sizeof (Book));
            {
//            f1.seekg(tempoffset+210);
//            cout<<index<<"  modify price "<<endl;
//            double d = atof((index.c_str()));
//            cout<<d<<"    double modify price"<<endl;
//            cout<<sizeof (d)<< "size of d"<<endl;
//            cout<<sizeof (Book)<<"size of book"<<endl;
//
//            f1.write(reinterpret_cast<char*>(&d),8);
        }
            f1.close();
            f6.close();
        }}
    void show(string command){
    //分成两个部分丢给两个子函数执行吧！
    int len=command.length();
    string head,body1,body2,body3,body4;
    int i;
        for (i = 0; i <len&&command[i]!=' ' ; ++i) {
            head+=command[i];
        }
        if (i==len){
            showall();
        } else{
            int temp=i;
            for (++i; i <len&&command[i]!=' ' ; ++i) {
                body1+=command[i];
            }
            //cout<<body1<<endl;
            if (body1=="finance"){
                if (i==len){
                    showfinance(-1);
                } else{
                    for (++i; i <len&&command[i]!=' ' ; ++i) {
                        body2+=command[i];
                    }
                    if (atoi(body2.c_str())<0){cout<<"Invalid"<<endl;return;}
                    showfinance(atoi(body2.c_str()));
                }
            }
            else{
               // cout<<head<<endl;
                for (temp+=2; command[temp]!='=' ; ++temp) {body3+=command[temp];}
                for (temp++; temp<len ; ++temp) {body4+=command[temp];}
                //cout<<body3<<"    "<<body4<<endl;
                show_part_withrestrict(body3,body4);
            }
        }
    }
    void buy(string ISBN_,string quantity){
       // cout<<"in buy"<<endl;
        int tempquantity=atoi(quantity.c_str());
        char oo[120]={0};
        oo[119]='\0';
        strcpy(oo,ISBN_.c_str());
        mystring ooooo(oo);
        vector<sjtu::BPtree<mystring, int >::value_type>tempsearch (ISBN_BOOKSTORE_blocklist.find(ooooo));
        if (tempsearch.empty()){
            cout<<"Invalid"<<endl;
            return;}
        if (tempquantity==0){
            cout<<"0.00"<<endl;
            return;}
        int tempoffset=tempsearch[0].second;
       // cout<<tempoffset<<"   in buy tempoffset"<<"  ISBN:"<<ISBN_<<endl;
       f1.close();
        f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
        if (!f1){
            f1.open(BOOK_DATA,ios::out|ios::binary);
        }
        Book tempbook;
        f1.seekg(tempoffset);
        double nowprice;
        int booknum_for_storage;
        f1.read(reinterpret_cast<char*>(&tempbook),sizeof (Book ));
        if (tempbook.quantity<tempquantity){
            cout<<"Invalid"<<endl;
        f1.close();
            return;}
        tempbook.quantity-=tempquantity;
        double bookprice=tempbook.price;

       // cout<<bookprice<<"   bookprice"<<endl;
        f1.seekg(tempoffset);
        f1.write(reinterpret_cast<char*>(&tempbook),sizeof (Book));
        if (bookprice==-1){cout<<"0.00"<<endl;
            return;}
       // f1.read(reinterpret_cast<char*>(&booknum_for_storage),sizeof (int));
       // booknum_for_storage+=tempquantity;
       // f1.seekg(tempoffset+218);
        //f1.write(reinterpret_cast<char*>(&booknum_for_storage),sizeof (int));
        f2.close();
        f2.open(TOTAL_FINANCE_DATA,ios_base::binary|ios::in | ios::out);
        if (!f2){
            f2.open(TOTAL_FINANCE_DATA,ios::out|ios::binary);
        }
       totaiinput+=(tempquantity*bookprice);
        booknum-=tempquantity;
        tradetimes++;
        //写入顺序，总收入，总支出，书本数量，交易次数
        f2.seekg(0);
        f2.write(reinterpret_cast<char*>(&totaiinput),8);
        f2.write(reinterpret_cast<char*>(&totoaloutput),8);
        f2.write(reinterpret_cast<char*>(&booknum),4);
        f2.write(reinterpret_cast<char*>(&tradetimes),4);
        f2.close();
        f2.open(EVERT_FINANCE_DATA,ios_base::binary|ios::in | ios::out);
        if (!f2){
            f2.open(EVERT_FINANCE_DATA,ios::out|ios::binary);
        }
        f2.seekg(0,ios::end);
        bool output=0;//1定义为支出，0定义为收入
        double allcost=bookprice*tempquantity;
        //cout<<allcost<<"    buy "<<endl;
        f2.write(reinterpret_cast<char*>(&output),sizeof (bool));
        f2.write(reinterpret_cast<char*>(&allcost),sizeof (double ));
        fa.close();
        fa.open(CLI_FINANCE_DETAILED,ios_base::binary|ios::in | ios::out);
        if (!fa){
            fa.open(CLI_FINANCE_DETAILED,ios::out|ios::binary);
        }
        fa.seekg(0,ios::end);
        reportfinance tempreport;
        tempreport.price1=allcost;
        tempreport.input_or_output=0;
        tempreport.num=tempquantity;
        strcpy(tempreport.ISBN,tempbook.ISBN);
        strcpy(tempreport.time,righttime());
        tempreport.tempuser=cmd.user_stack[cmd.usernum-1];
        fa.write(reinterpret_cast<char*>(&tempreport),sizeof (reportfinance));
        fa.close();
        f1.close(),f2.close();
        cout<<setiosflags(ios::fixed) << setprecision(2)<<allcost<<endl;
       // cout<<" the end in buy"<<endl;
    }
    void showall(){
        //ISBN_BOOKSTORE_blocklist.debug();
        //cout<<"above is showall in bookstore.h"<<endl;
        if (cmd.user_stack[cmd.usernum-1].priviledge<1){
            cout<<"Invalid"<<endl;
            return;
        }
        vector<sjtu::BPtree<mystring, int >::value_type> shoe_vec(ISBN_BOOKSTORE_blocklist.findall());
        if (shoe_vec.empty()){cout<<endl;
            return;}
        //cout<<shoe_vec[0]<<"  "<<sh
        for (int i = 0; i <shoe_vec.size() ; ++i) {
            //cout<<shoe_vec[i]<<endl;
            f1.close();
            f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f1){
                f1.open(BOOK_DATA,ios::out|ios::binary);
            }
            f1.seekg(shoe_vec[i].second);
            Book tempbook;
            f1.read(reinterpret_cast<char*>(&tempbook),sizeof (Book));
           // cout<<tempbook.price<<"   price"<<endl;
            double output=0;
            if (tempbook.price==-1){  printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, output, tempbook.quantity);
            } else printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, tempbook.price, tempbook.quantity);
f1.close();
        }
//        cout<<"in show all"<<endl;
//        vector<int>::iterator it = shoe_vec.begin();
//
//        for(; it != shoe_vec.end(); ++it)
//        {
//            f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
//            if (!f1){
//                f1.open(BOOK_DATA,ios::out|ios::binary);
//            }
//            f1.seekg(*it);
//            char ISBN_[30];
//            char name_[60];
//            char author_[60];
//            char keywords_[60];
//            double price_;
//            int quantity_;
//            f1.read(reinterpret_cast<char*>(&ISBN_),30);
//            f1.read(reinterpret_cast<char*>(&name_),60);
//            f1.read(reinterpret_cast<char*>(&author_),60);
//            f1.read(reinterpret_cast<char*>(&keywords_),60);
//            f1.read(reinterpret_cast<char*>(&price_),8);//两位小数输出
//            f1.read(reinterpret_cast<char*>(&quantity_),4);
//            cout<<ISBN_<<" "<<name_<<" "<<author_<<" "<<keywords_<<" "<<setiosflags(ios::fixed) << setprecision(2)<<price_<<" "<<quantity_<<endl;
//            //cout<<(*it)<<" ";
//        }
//        f1.close();
    }
    void  show_part_withrestrict(string type,string keyword){
        f1.clear(),f2.clear(),f3.clear(),f4.clear(),f5.clear(),f6.clear();
        //cout<<f1.fail()<<"((("<<endl;
       // cout<<cmd.user_stack[cmd.usernum-1].priviledge<<"show with restrict"<<endl;
        if (cmd.user_stack[cmd.usernum-1].priviledge<1||keyword.empty()){
            cout<<"Invalid"<<endl;
            return;
        }
        struct pair_ISBN_offset{
            int offset;
            string ISBN;
            pair_ISBN_offset(string s,int a):ISBN(s),offset(a){}
            pair_ISBN_offset() {}
            bool operator <(const  pair_ISBN_offset &s) const {
                return (strcmp(ISBN.c_str(),s.ISBN.c_str())<0);
            }
            pair_ISBN_offset(const pair_ISBN_offset & pt)//复制构造函数的定义及实现
            {
                offset=pt.offset;
               ISBN=pt.ISBN;
            }
            pair_ISBN_offset& operator =(const pair_ISBN_offset& str)//赋值运算符
            {
                if (this==&str) return *this;
                offset=str.offset;
                ISBN=str.ISBN;
                return *this;
            }
            bool operator ==(const  pair_ISBN_offset &s) const {
                return( offset==s.offset&&strcmp(ISBN.c_str(),s.ISBN.c_str())==0);
            }
        };
        if (type=="ISBN") {
            char nmd[120]={0};
            nmd[119]='\0';
            strcpy(nmd,keyword.c_str());
            mystring nmdd(nmd);
            vector<sjtu::BPtree<mystring, int >::value_type> tempans(ISBN_BOOKSTORE_blocklist.find(nmdd));
            if (tempans.empty()){cout<<endl;
                return;}
            f1.clear(),f2.clear(),f3.clear(),f4.clear(),f5.clear(),f6.clear();
            f1.close(),f2.close(),f3.close(),f4.close(),f5.close(),f6.close();
            int tempooffset=tempans[0].second;
            f1.close();
            f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f1){
                f1.open(BOOK_DATA,ios::out|ios::binary);
            }
            f6.close();
            f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f6){
                f6.open(BOOK_DATA,ios::out|ios::binary);
            }
            f6.seekg(tempooffset);
           // cout<<tempooffset<<" debug in modify tempoffset"<<endl;

            Book tempbook;
            f6.read(reinterpret_cast<char*>(&tempbook),sizeof(Book));
           // cout<<tempbook.price<<"   book.price "<<endl;
             double output=0;
            // cout<<tempbook.price<<" in show ISBN"<<endl;
            if (tempbook.price==-1){ printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, output, tempbook.quantity);
            } else printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, tempbook.price, tempbook.quantity);

            //printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, tempbook.price, tempbook.quantity);
            f1.seekg(tempooffset);
            char ISBN_[30];
            char name_[60];
            char author_[60];
            char keywords_[60];
            double price_;
            int quantity_;
            f1.read(reinterpret_cast<char*>(&ISBN_),30);
            f1.read(reinterpret_cast<char*>(&name_),60);
            f1.read(reinterpret_cast<char*>(&author_),60);
            f1.read(reinterpret_cast<char*>(&keywords_),60);
            f1.read(reinterpret_cast<char*>(&price_),8);//两位小数输出
            f1.read(reinterpret_cast<char*>(&quantity_),4);
            //cout<<price_<<" price in show with restrict"<<endl;
            //cout<<ISBN_<<" "<<name_<<" "<<author_<<" "<<keywords_<<" "<<setiosflags(ios::fixed) << setprecision(2)<<price_<<" "<<quantity_<<endl;
        f6.close();
        }
        if (type=="author"){
            int len=keyword.length();
            string beyong_master;
            for (int i = 1; i <len-1 ; ++i) {
                beyong_master+=keyword[i];
            }
            char ll[120]={0};
            ll[119]='\0';
            strcpy(ll,beyong_master.c_str());
            mystring lljb(ll);
            vector<sjtu::BPtree<mystring, int >::value_type> tempans(AUTHOR_BOOKSTORE.find(lljb));
            if (tempans.empty()){cout<<endl;
                return;}
            f1.clear(),f2.clear(),f3.clear(),f4.clear(),f5.clear(),f6.clear();
            f1.close(),f2.close(),f3.close(),f4.close(),f5.close(),f6.close();
            f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f1){
                f1.open(BOOK_DATA,ios::out|ios::binary);
            }
            set<pair_ISBN_offset> s;
            for (vector<sjtu::BPtree<mystring, int >::value_type>::const_iterator iter = tempans.cbegin();iter !=tempans.cend(); iter++) {
                //cout << (*iter) << endl;
                f1.seekg((*iter).second);
                char ISBN_[30];
                char name_[60];
                char author_[60];
                char keywords_[60];
                double price_;
                int quantity_;
                f1.read(reinterpret_cast<char*>(&ISBN_),30);
                f1.read(reinterpret_cast<char*>(&name_),60);
                f1.read(reinterpret_cast<char*>(&author_),60);
                f1.read(reinterpret_cast<char*>(&keywords_),60);
                f1.read(reinterpret_cast<char*>(&price_),8);//两位小数输出
                f1.read(reinterpret_cast<char*>(&quantity_),4);
                string name1;
                name1 = ISBN_;
                s.insert(pair_ISBN_offset(name1,(*iter).second));
                //cout<<ISBN_<<" "<<name_<<" "<<author_<<" "<<keywords_<<" "<<setiosflags(ios::fixed) << setprecision(2)<<price_<<" "<<quantity_<<endl;
            }
            set<pair_ISBN_offset>::iterator it;
            for(it=s.begin ();it!=s.end ();it++)
            {f6.close();
                f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
                if (!f6){
                    f6.open(BOOK_DATA,ios::out|ios::binary);
                }
                f6.seekg(it->offset);
              //  cout<<it->offset<<" debug in modify tempoffset"<<endl;

                Book tempbook;
                f6.read(reinterpret_cast<char*>(&tempbook),sizeof(Book));
               // cout<<tempbook.price<<"   book.price "<<endl;
                 double output=0;
            if (tempbook.price==-1){  printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, output, tempbook.quantity);
            } else printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, tempbook.price, tempbook.quantity);

f6.close();
                f1.seekg(it->offset);
                char ISBN_[30];
                char name_[60];
                char author_[60];
                char keywords_[60];
                double price_;
                int quantity_;
                f1.read(reinterpret_cast<char*>(&ISBN_),30);
                f1.read(reinterpret_cast<char*>(&name_),60);
                f1.read(reinterpret_cast<char*>(&author_),60);
                f1.read(reinterpret_cast<char*>(&keywords_),60);
                f1.read(reinterpret_cast<char*>(&price_),8);//两位小数输出
                f1.read(reinterpret_cast<char*>(&quantity_),4);
               // cout<<ISBN_<<" "<<name_<<" "<<author_<<" "<<keywords_<<" "<<setiosflags(ios::fixed) << setprecision(2)<<price_<<" "<<quantity_<<endl;
            }
        }
        if (type=="keyword"){

           //KEYWORD_BOOKSTORE.debug();
           //cout<<" aboye is in the bookstore.h showwithrestrict keyword"<<endl;
            f1.clear(),f2.clear(),f3.clear(),f4.clear(),f5.clear(),f6.clear();
            int len=keyword.length();
            string beyong_master;
            for (int i = 1; i <len-1 ; ++i) {
                beyong_master+=keyword[i];
            }
            char fw[120]={0};
            fw[119]='\0';
            strcpy(fw,beyong_master.c_str());
            mystring fwnm(fw);
            vector<sjtu::BPtree<mystring, int >::value_type> tempans(KEYWORD_BOOKSTORE.find(fwnm));
            if (tempans.empty()){cout<<endl;
            //cout<<"RUTURN HERE"<<endl;
                return;}
            f1.clear(),f2.clear(),f3.clear(),f4.clear(),f5.clear(),f6.clear();
            f1.close(),f2.close(),f3.close(),f4.close(),f5.close(),f6.close();
           // cout<<f1.fail()<< f2.fail()<<f3.fail()<<f4.fail()<<f5.fail()<<f6.fail()<<"((("<<endl;
           f1.close();
            f1.open(BOOK_DATA,ios::binary|ios::in | ios::out);
            if (!f1){f1.open(BOOK_DATA,ios::out|ios::binary);}
           // cout<<f1.fail()<<"((("<<endl;
            set<pair_ISBN_offset> s;
            s.clear();
            int cnt=1;
            for (vector<sjtu::BPtree<mystring, int >::value_type>::const_iterator iter = tempans.cbegin();iter !=tempans.cend(); iter++) {
                //cout << (*iter) << endl;
               // cout<<f1.fail()<<"((("<<endl;
                f1.seekg((*iter).second);
                Book tempbook;
                f1.read(reinterpret_cast<char*>(&tempbook),sizeof (Book));

                char ISBN_[30];
                strcpy(ISBN_,tempbook.ISBN);

                string name1;
                name1 = ISBN_;
                s.insert(pair_ISBN_offset(name1,(*iter).second));
              //  cout<<cnt++<<"***"<<*iter<<" "<<name1<<endl;
                //cout<<s.size()<<"   size of s"<<endl;
                //cout<<ISBN_<<" "<<name_<<" "<<author_<<" "<<keywords_<<" "<<setiosflags(ios::fixed) << setprecision(2)<<price_<<" "<<quantity_<<endl;
            }
          // cout<<tempans.size()<<"   "<<s.size()<<"&&&&&&&&&&&&&&&&&"<<endl;
            set<pair_ISBN_offset>::iterator it;
            for(it=s.begin ();it!=s.end ();it++)
            {
                f6.close();
                f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
                if (!f6){
                    f6.open(BOOK_DATA,ios::out|ios::binary);
                }
                f6.seekg(it->offset);
              //  cout<<it->offset<<" debug in modify tempoffset"<<endl;

                Book tempbook;
                f6.read(reinterpret_cast<char*>(&tempbook),sizeof(Book));
               // cout<<tempbook.price<<"   book.price "<<endl;
                double output=0;
                if (tempbook.price==-1){  printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, output, tempbook.quantity);
                } else printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, tempbook.price, tempbook.quantity);

                // printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, tempbook.price, tempbook.quantity);
                f6.close();
                f1.seekg(it->offset);
                char ISBN_[30];
                char name_[60];
                char author_[60];
                char keywords_[60];
                double price_;
                int quantity_;
                f1.read(reinterpret_cast<char*>(&ISBN_),30);
                f1.read(reinterpret_cast<char*>(&name_),60);
                f1.read(reinterpret_cast<char*>(&author_),60);
                f1.read(reinterpret_cast<char*>(&keywords_),60);
                f1.read(reinterpret_cast<char*>(&price_),8);//两位小数输出
                f1.read(reinterpret_cast<char*>(&quantity_),4);
              //  cout<<ISBN_<<" "<<name_<<" "<<author_<<" "<<keywords_<<" "<<setiosflags(ios::fixed) << setprecision(2)<<price_<<" "<<quantity_<<endl;
            }
        }
        if (type=="name"){
            int len=keyword.length();
            string beyong_master;
            for (int i = 1; i <len-1 ; ++i) {
                beyong_master+=keyword[i];
            }
            char wyc[120]={0};
            wyc[119]='\0';
            strcpy(wyc,beyong_master.c_str());
            mystring wychs(wyc);
            vector<sjtu::BPtree<mystring, int >::value_type>tempans(BOOKNAME_BOOKSTORE_blocklist.find(wychs));
            if (tempans.empty()){cout<<endl;
                return;}
            f1.clear(),f2.clear(),f3.clear(),f4.clear(),f5.clear(),f6.clear();
            f1.close(),f2.close(),f3.close(),f4.close(),f5.close(),f6.close();
            f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f1){
                f1.open(BOOK_DATA,ios::out|ios::binary);
            }
            set<pair_ISBN_offset> s;
            for (vector<sjtu::BPtree<mystring, int >::value_type>::const_iterator iter = tempans.cbegin();iter !=tempans.cend(); iter++) {
                //cout << (*iter) << endl;
                f1.seekg((*iter).second);
                char ISBN_[30];
                char name_[60];
                char author_[60];
                char keywords_[60];
                double price_;
                int quantity_;
                f1.read(reinterpret_cast<char*>(&ISBN_),30);
                f1.read(reinterpret_cast<char*>(&name_),60);
                f1.read(reinterpret_cast<char*>(&author_),60);
                f1.read(reinterpret_cast<char*>(&keywords_),60);
                f1.read(reinterpret_cast<char*>(&price_),8);//两位小数输出
                f1.read(reinterpret_cast<char*>(&quantity_),4);
                string name1;
                name1 = ISBN_;
                s.insert(pair_ISBN_offset(name1,(*iter).second));
                //cout<<ISBN_<<" "<<name_<<" "<<author_<<" "<<keywords_<<" "<<setiosflags(ios::fixed) << setprecision(2)<<price_<<" "<<quantity_<<endl;
            }
            set<pair_ISBN_offset>::iterator it;
            for(it=s.begin ();it!=s.end ();it++)
            {f6.close();
                f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
                if (!f6){
                    f6.open(BOOK_DATA,ios::out|ios::binary);
                }
                f6.seekg(it->offset);
                //cout<<it->offset<<" debug in modify tempoffset"<<endl;

                Book tempbook;
                f6.read(reinterpret_cast<char*>(&tempbook),sizeof(Book));
                //cout<<tempbook.price<<"   book.price "<<endl;
                 double output=0;
            if (tempbook.price==-1){  printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, output, tempbook.quantity);
            } else printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, tempbook.price, tempbook.quantity);

                f6.close();

                f1.seekg(it->offset);
                char ISBN_[30];
                char name_[60];
                char author_[60];
                char keywords_[60];
                double price_;
                int quantity_;
                f1.read(reinterpret_cast<char*>(&ISBN_),30);
                f1.read(reinterpret_cast<char*>(&name_),60);
                f1.read(reinterpret_cast<char*>(&author_),60);
                f1.read(reinterpret_cast<char*>(&keywords_),60);
                f1.read(reinterpret_cast<char*>(&price_),8);//两位小数输出
                f1.read(reinterpret_cast<char*>(&quantity_),4);
              //  cout<<ISBN_<<" "<<name_<<" "<<author_<<" "<<keywords_<<" "<<setiosflags(ios::fixed) << setprecision(2)<<price_<<" "<<quantity_<<endl;
            }
        }
        f1.close();
    }
    void showfinance(int time){
        if (cmd.user_stack[cmd.usernum-1].priviledge<7){
            cout<<"Invalid"<<endl;
            return;
        }
        if (time==-1){
            f1.close();
            f1.open(EVERT_FINANCE_DATA,ios_base::binary|ios::in | ios::out);
            if (!f1){
                f1.open(EVERT_FINANCE_DATA,ios::out|ios::binary);
            }
            f2.close();
            f2.open(EVERT_FINANCE_DATA,ios_base::binary|ios::in | ios::out);
            if (!f2){
                f2.open(EVERT_FINANCE_DATA,ios::out|ios::binary);
            }
            f2.seekg(0,ios::end);
            int end=f2.tellg();
            f1.seekg(0);
            double alloutput=0,allinput=0;
            while (f1.tellg()!=end){
                bool tempflag;
                double tempfinance;
                f1.read(reinterpret_cast<char*>(&tempflag),sizeof (bool ));
                f1.read(reinterpret_cast<char*>(&tempfinance),sizeof (double ));
//cout<<tempflag<<"   "<<tempfinance<<" in show finance -1"<<endl;
                if (tempflag){alloutput+=tempfinance;}
                else{allinput+=tempfinance;}
                //if (tempflag){cout<<"((((((((((((("<<'-'<<setiosflags(ios::fixed) << setprecision(2)<<tempfinance;}
                //else{cout<<'+'<<setiosflags(ios::fixed) << setprecision(2)<<tempfinance;}
            }
            cout<<'+'<<" "<<setiosflags(ios::fixed) << setprecision(2)<<allinput<<" "<<'-'<<" "<<setiosflags(ios::fixed) << setprecision(2)<<alloutput;
            cout<<endl;
            f1.close(),f2.close();
        } else{
            f1.close();
            f1.open(EVERT_FINANCE_DATA,ios_base::binary|ios::in | ios::out);
            if (!f1){
                f1.open(EVERT_FINANCE_DATA,ios::out|ios::binary);
            }
            f2.close();
            f2.open(EVERT_FINANCE_DATA,ios_base::binary|ios::in | ios::out);
            if (!f2){
                f2.open(EVERT_FINANCE_DATA,ios::out|ios::binary);
            }
            double alloutput=0,allinput=0;
            f2.seekg(0,ios::end);
            int end=f2.tellg();
            if (time*(sizeof (bool )+sizeof (double ))>end){
                f1.close(),f2.close();
                cout<<"Invalid"<<endl;return;
            }
            f1.seekg(-(sizeof (bool )+sizeof (double )),ios::end);
            while (time--){
                bool tempflag;
                double tempfinance;
                f1.read(reinterpret_cast<char*>(&tempflag),sizeof (bool ));
                f1.read(reinterpret_cast<char*>(&tempfinance),sizeof (double ));
               // cout<<tempflag<<"   "<<tempfinance<<endl;
//                if (tempflag){cout<<'-'<<setiosflags(ios::fixed) << setprecision(2)<<tempfinance;}
//                else{cout<<'+'<<setiosflags(ios::fixed) << setprecision(2)<<tempfinance;}
                if (tempflag){alloutput+=tempfinance;}
                else{allinput+=tempfinance;}
               f1.seekg(-(2*sizeof (bool )+2*sizeof (double )),ios::cur);
            }
            cout<<'+'<<" "<<setiosflags(ios::fixed) << setprecision(2)<<allinput<<" "<<'-'<<" "<<setiosflags(ios::fixed) << setprecision(2)<<alloutput;
            cout<<endl;
            f1.close(),f2.close();
        }
    }
};
//
//
#endif //CODE_BOOKSTORE_H
