
#include <iostream>
#include "BookStore.h"
using namespace std;
extern int booknum;
bookstore commandbookstore;//缺少构造函数
int main() {

    //freopen("../myout.data","w",stdout);
   // freopen("../data/1.in","r",stdin);
    init();
    string command;
    int cnt=1;
    fstream fo;
    while (getline(cin,command)){
        //cout<<"##"<<command<<endl;
        if (command=="quit"||command=="exit") break;
        command.erase(0,command.find_first_not_of(" "));
        command.erase(command.find_last_not_of(" ") + 1);

        commandbookstore.run(command);
    }
    return 0;
}
