#include "bplustree.hpp"
//#include "blockchain.h"
#include "UserManager.h"
#include <sys/stat.h>
user::user() {
    priviledge=-1;
    currentbookISBN=-1;

}
inline bool exists_test3 (const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}
usermanager::usermanager():filename(USER_DATA),the_blockchai_of_usermanager(USERBPT,USER_SEARCH){

user temp;
temp.priviledge=7;
strcpy(temp.name,"hhhhlalal");
strcpy(temp.id,"root");
strcpy(temp.password,"sjtu");
user basic;
strcpy(basic.id,"what's the fffffffffffffuck");
strcpy(basic.name,"dont want to codeqwqqqqqq");
basic.priviledge=0;
user_stack.clear();
user_stack.push_back(basic);
//user_stack.push_back(temp);
usernum=1;//将用户信息写入存储文件中
//cout<<f1.is_open()<<"constructer in usermanager"<<endl;
    if (!(exists_test3(filename))){
        f1.close();
        if (!f1.is_open()) {
            //cout<<filename<<endl;

            f1.open(filename, ios_base::binary | ios::in | ios::out);
            if (!f1) {
                f1.open(filename, ios::out | ios::binary);
            }
            //f1.open(filename, ios::binary |  ios::out);
            f1.seekg(0);
            f1.write(reinterpret_cast<char *>(&temp), sizeof(user));
            char temp11[10];
            strcpy(temp11,"root");
            mystring  a1(temp11);
            sjtu::BPtree<mystring, int>::value_type a(a1, 0);
            the_blockchai_of_usermanager.insert(a);
            //the_blockchai_of_usermanager.debug();
            f1.close();//暴力打开会出锅吗？？？
        } else f1.close();
    }
}