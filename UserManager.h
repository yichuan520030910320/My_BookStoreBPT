#ifndef CODE_USERMANAGER_H
#define CODE_USERMANAGER_H
using namespace std;
#include "bplustree.hpp"
//#include "blockchain.h"
#define USER_DATA "user.data"
#define COMMAND_DATA "command.data"
#define TOTAL_FINANCE_DATA "finance.data"
#define EVERT_FINANCE_DATA "detail_finance.data"
#define BOOK_DATA "book.data"
#define BASIC_DATA "basic.data"//存储一些可能用到的基础数据
#define ISBN_SEARCH "isbnsearch.data"
#define USER_SEARCH "usersearch.data"
#define AUTHOR_SEARCH "authorsearch.data"
#define BOOK_NAME_SEARCH "book_namesearch.data"
#define KEYWORD_SEARCH "keywordsearch.data"
#define ISBNBPT "isbnbpt.data"
#define USERBPT "userbpt.data"
#define AUTHORBPT "authorbpt.data"
#define BOOKNAMEBPT "booknamebpt.data"
#define KETWORDBPT "ketwordbpt.data"
#define CLI_FINANCE_DETAILED "FINANCE_DETAILED_GUI.data"
#define CLI_EMPLOYEE_DETAILED "CLI_EMPLOYEE_DETAILED.data"
#define CLI_OPERATIN_SYSTEM "CLI_OPERATIN_SYSTEM.data"
#define SEARCH_CLI_FINANCE_DETAILED "SEARCH_CLI_FINANCE_DETAILED.data"
#define SEARCH_CLI_EMPLOYEE_DETAILED "SEARCH_CLI_EMPLOYEE_DETAILED.data"
#define SEARCH_CLI_OPERATIN_SYSTEM "SEARCH_CLI_OPERATIN_SYSTEM.data"
#pragma once
class user{
public:
    char id[40],password[40],name[40];
    int priviledge;
    int currentbookISBN=-1;//change the meanining to offset
    user();
    user &operator=(const user &right){
        if (this==&right) return *this;
        priviledge=right.priviledge,currentbookISBN=right.currentbookISBN;
        strcpy(id,right.id);
        strcpy(password,right.password);
        strcpy(name,right.name);
        return *this;
    }
};
class usermanager{
public:
    string filename;
    fstream f1,f2,f3,f4,f5,f6;
    int usernum;
    vector<user> user_stack;
    sjtu::BPtree<mystring,int> the_blockchai_of_usermanager;
    void logout(){
        if (usernum==1){cout<<"Invalid"<<endl;
            return;}
usernum--;
user_stack.pop_back();
       // cout<<usernum<<"   in logput"<<endl;
        //cout<<user_stack[usernum-1].id<<"(((((in logout"<<endl;
        //cout<<user_stack[usernum-1].priviledge<<"^^^^^^^ in logput"<<endl;//random
    }
    void adduser(string id,string pass,string name,int privilege){
        //cout<<"in adduser"<<endl;
        char nmd[120]={0};
        nmd[119]='\0';
        strcpy(nmd,id.c_str());
        mystring cccc(nmd);
        vector<sjtu::BPtree<mystring, int >::value_type> temp (the_blockchai_of_usermanager.find(cccc));
        if (!temp.empty()){cout<<"Invalid"<<endl;
            return;}
        if (user_stack[usernum-1].priviledge<=privilege) {
            //cout<<"defeat in the check"<<endl;
            //cout<<user_stack[usernum-1].priviledge<<endl;
            cout << "Invalid" << endl;
            return;
        }
        user tempuser;
        strcpy(tempuser.password,pass.c_str());
        strcpy(tempuser.name,name.c_str());
        strcpy(tempuser.id,id.c_str());
        tempuser.priviledge=privilege;
        int temppos;
        f1.close();
        f1.open(USER_DATA,ios::in|ios::out|ios::binary);
        f1.seekg(0,ios::end);
        temppos=f1.tellg();
        f1.write(reinterpret_cast<char*>(&tempuser),sizeof (user));
        //element tempueradd_to_search;
        char buf[120]={0};
        buf[119]='\0';
        strcpy(buf,id.c_str());
        mystring bban(buf);
        sjtu::BPtree<mystring, int>::value_type insert1(bban, temppos);
        the_blockchai_of_usermanager.insert(insert1);
        //the_blockchai_of_usermanager.add(element(temppos,id));
        //the_blockchai_of_usermanager.debug();
        //cout<<"_____________________in user add"<<endl;
        f1.close();
    }
    void su(string id,string password){
        if (password=="@q@"){
           // cout<<"8888888"<<endl;
            char nmd[120]={0};
            nmd[119]='\0';
            strcpy(nmd,id.c_str());
            mystring fwww(nmd);
            vector<sjtu::BPtree<mystring, int >::value_type> tempresult(the_blockchai_of_usermanager.find(fwww));
            if (tempresult.empty()){cout<<"Invalid"<<endl;
                return;}
            f1.close();
            f1.open(USER_DATA,ios_base::binary|ios::in | ios::out);
            if (!f1){
                f1.open(USER_DATA,ios::out|ios::binary);
            }
            f1.seekg(tempresult[0].second);
            user tempuser;
            f1.read(reinterpret_cast<char*>(&tempuser),sizeof (tempuser));
            if (tempuser.priviledge>user_stack[usernum-1].priviledge){
                cout<<"Invalid"<<endl;
                f1.close();
                return;} else{
                usernum++;
                user_stack.push_back(tempuser);
                f1.close();
            }

            return;
        }
       //cout<<"su debug"<<endl;
       f1.close();
        if (!f1.is_open()){
            f1.open(USER_DATA, ios::binary | ios::out | ios::in);

            char nmd[120]={0};
            nmd[119]='\0';
            strcpy(nmd,id.c_str());
mystring lunch(nmd);
            vector<sjtu::BPtree<mystring, int >::value_type> tempresult(the_blockchai_of_usermanager.find(lunch));

            if (!tempresult.empty())//先判断这个id是否存在在
            {//cout<<password<<" password"<<endl;
                int tempoffset = tempresult[0].second;
               //cout<<tempoffset<<"  tempoffset"<<endl;
                //cout<<f1.fail()<<"   989898"<<endl;
                f1.seekg(tempoffset + 40);
                char passtemp[40];
                f1.read(reinterpret_cast<char *>(&passtemp), 40);//cout<<"passtemp   :"<<passtemp<<"  in su"<<endl;
                char tempname[40];
                f1.read(reinterpret_cast<char *>(&tempname), 40);
                int tempprivilege;
                f1.read(reinterpret_cast<char*>(&tempprivilege),4);
                //cout<<tempprivilege<<"****"<<endl;

              //cout<<passtemp<<" "<<tempname<<"in su"<<endl;
                if (strcmp(passtemp, password.c_str()) == 0) {

                     {
                        usernum++;
                        user adduser;
                        strcpy(adduser.password, password.c_str());
                        strcpy(adduser.id, id.c_str());
                        strcpy(adduser.name, tempname);
                        adduser.priviledge=tempprivilege;
                       // cout<<adduser.password<<"***** in su fuction "<<endl;
                        user_stack.push_back(adduser);
                    }
                } else { cout << "Invalid" << endl;}
            }
            f1.close();
        } else f1.close();
        //cout<<usernum<<"   in su"<<endl;
        //cout<<user_stack[usernum-1].id<<"(((((in su"<<endl;
        //cout<<user_stack[usernum-1].priviledge<<"^^^^^^^ in su"<<endl;//random
        //cout<<f1.is_open()<<" check f1.isopen"<<endl;
    }
    void registeruser(string user_id,string pass,string username){
//adduser(user_id,pass,username,1);
        user tempuser;
        strcpy(tempuser.password,pass.c_str());
        strcpy(tempuser.name,username.c_str());
        strcpy(tempuser.id,user_id.c_str());
        tempuser.priviledge=1;
        int temppos;
        f1.close();
        f1.open(USER_DATA,ios::in|ios::out|ios::binary);
        f1.seekg(0,ios::end);
        temppos=f1.tellg();
        f1.write(reinterpret_cast<char*>(&tempuser),sizeof (user));
        char nmd[120]={0};
        nmd[119]='\0';
        strcpy(nmd,user_id.c_str());
        mystring ccnm(nmd);
        sjtu::BPtree<mystring, int>::value_type a(ccnm, temppos);

        the_blockchai_of_usermanager.insert(a);
        //the_blockchai_of_usermanager.debug();
        //cout<<"_____________________in user add"<<endl;
        f1.close();
    }
    void deleteid(string id){
        if (user_stack[usernum-1].priviledge!=7) {cout<<"Invalid"<<endl;
            return;}
        if (!((!id.empty())&&check_the_format_of_string(id))){
            //cout<<id.empty()<<" "<<check_the_format_of_string(id)<<endl;
          //  cout<<"*********in delete id"<<endl;
            cout<<"Invalid"<<endl;
            return;
        }
f1.close();
f1.open(USER_SEARCH,ios::binary|ios::in|ios::out);
        char nmd[120]={0};
        nmd[119]='\0';
        strcpy(nmd,id.c_str());
        mystring cnmlgb(nmd);
        //vector<sjtu::BPtree<mystring, int >::value_type> tempresult(the_blockchai_of_usermanager.find(nmd));
        vector<sjtu::BPtree<mystring, int >::value_type> tempresult(the_blockchai_of_usermanager.find(cnmlgb));
        if (tempresult.empty()){f1.close();
        cout<<"Invalid"<<endl;
            return;}
        else{f2.close();
            f2.open(USER_DATA,ios_base::binary|ios::in | ios::out);
            if (!f2){
                f2.open(USER_DATA,ios::out|ios::binary);
            }
            f2.seekg(tempresult[0].second);
            user tempuserr;
            f2.read(reinterpret_cast<char*>(&tempuserr),sizeof (user));
            f2.close();
            for (int i = 0; i <usernum ; ++i) {
                if (user_stack[i].id==id){cout<<"Invalid"<<endl;
                    return;}
            }
            char buf1[120]={0};
            buf1[119]='\0';
            strcpy(buf1,id.c_str());
            mystring er(buf1);
            sjtu::BPtree<mystring, int>::value_type temele(er, tempresult[0].second);
            //element tempele;
//            strcpy(tempele.key,id.c_str());
//            tempele.offset=tempresult[0];
            the_blockchai_of_usermanager.erase(temele);
            f1.close();
        }
    }
    void replace_the_password(string id,string oldpassword,string newpassword){//区别是否是root用户
        if (oldpassword=="@"){
           // cout<<"root in replace password"<<endl;
            if (!(check_the_format_of_string(newpassword))){
                cout<<"Invalid"<<endl;
              //  cout<<"  out here in check format"<<endl;
                return;}
            if (user_stack[usernum-1].priviledge!=7){
                cout<<"Invalid"<<endl;
                return;}
            char nmd[120]={0};
            nmd[119]='\0';
            strcpy(nmd,id.c_str());
            mystring nmsl(nmd);
            vector<sjtu::BPtree<mystring, int >::value_type> temp(the_blockchai_of_usermanager.find(nmsl));

            if (temp.empty()){
                cout<<"Invalid"<<endl;
                return;}
            f1.close();
            //f1.open(USER_DATA,ios::out|ios::in|ios::binary);
            f1.open(USER_DATA,ios_base::binary|ios::in | ios::out);
            if (!f1){
                f1.open(USER_DATA,ios::out|ios::binary);
            }

            f1.seekg(temp[0].second);
           // cout<<temp[0]<<"location in replace pass"<<endl;
            user tempuser;
            f1.read(reinterpret_cast<char*>(&tempuser),sizeof (user));
            char passtemp[40];
            strcpy(passtemp,newpassword.c_str());
            strcpy(tempuser.password,passtemp);
            f1.seekg(temp[0].second);
           // cout<<tempuser.password<<"  replace password now pass"<<endl;
            f1.write(reinterpret_cast<char*>(&tempuser),sizeof (user));
            f1.close();
        } else{
          //  cout<<"not root replace pass"<<endl;
            if (!(check_the_format_of_string(newpassword))){
                //cout<<"in pass change1"<<endl;
                cout<<"Invalid"<<endl;
                return;}
            char nmd[120]={0};
            nmd[119]='\0';
            strcpy(nmd,id.c_str());
            mystring nn(nmd);
            vector<sjtu::BPtree<mystring, int >::value_type> temp(the_blockchai_of_usermanager.find(nn));
            if (temp.empty()){
                cout<<"Invalid"<<endl;
                //cout<<"in pass change2"<<endl;
                return;}
            f1.close();
            f1.open(USER_DATA,ios::out|ios::in|ios::binary);
            f1.seekg(temp[0].second);
            int num=temp[0].second;
            char olpass_in_the_userdata[40];
            user tempuser;
            f1.read(reinterpret_cast<char*>(&tempuser),sizeof (user));
          // cout<<f1.fail()<<"  &&&&"<<tempuser.password<<endl;
            strcpy(olpass_in_the_userdata,tempuser.password);
           // cout<<olpass_in_the_userdata<<"    "<<oldpassword<<"   not root replce pass"<<endl;
            if (strcmp(olpass_in_the_userdata,oldpassword.c_str())==0){

f1.seekg(num);

                strcpy(tempuser.password,newpassword.c_str());
               // cout<<tempuser.password<<"*******"<<"  in not root replace pass"<<endl;
                f1.write(reinterpret_cast<char*>(&tempuser),sizeof (user));
f1.close();
            } else{
                //cout<<"  not root replacepass,dont previous pass right"<<endl;
                cout<<"Invalid"<<endl;
                f1.close();
                return;
            }
        }

    }
    usermanager();
    bool check_the_format_of_string(string index){
        if (index.length()>30) { return false; }
        for (int i = 0; i <index.length() ; ++i) {
            if (!(index[i]=='_'||(index[i]>='0'&&index[i]<='9')||(index[i]>='a'&&index[i]<='z')||(index[i]>='A'&&index[i]<='Z'))){
                //cout<<index[i]<<"      kkkkk in string check"<<endl;
                return false;
            }
        }
        return true;

    }

};
#endif