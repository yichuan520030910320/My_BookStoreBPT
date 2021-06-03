//
// Created by 18303 on 2021/6/3.
//

//
// Created by 18303 on 2021/5/28.
#include <iostream>

using namespace std;

#include "bplustree.hpp"
#include <vector>
#include <map>
#include <ctime>

const int MAXN = 10000;

void test1() {
    srand(time(0));
    sjtu::BPtree<int, int> bptree("bpt", "data");


    vector<sjtu::BPtree<int, int>::value_type> ans;



    for (int i = 0; i < MAXN; ++i) {
        int P = rand() % 1000 + 8;

//cout<<"       /___________________________________/ininsert"<<endl;
        sjtu::BPtree<int, int>::value_type a(i, i);
        bptree.insert(a);
        if (i % 100 == 0) cout << i << endl;

    }

    cout << "finish insert___________________________________________" << endl;
    for (int i = 1; i < MAXN; i += 2) {
        cout << "in erase fuction" << endl;
        sjtu::BPtree<int, int>::value_type a(i, i);
        cout << bptree.erase(a) << endl;
        printf("%d\n", i);
        cout << "_______________________--in erase " << endl;
   }
    for (int i = 0; i < MAXN; i += 2) {
        cout << "   test find ???" << i << "_______________________________________________________" << endl;
        ans = bptree.find(i);
        cout << ans[0].second << "&&&&&&&&&" << endl;
        cout << i << "   successfind" << endl;
    }
    cout << "****" << endl;
}

void test2()
{
    sjtu::BPtree<int, int> bptree("bpt", "data");
    map<int, int> stdmp;
    cout << "in test2__________________________________________________________test 2" << endl;
    vector<sjtu::BPtree<int, int>::value_type> ans;
    vector<int> record;
    for (int i = 0; i < MAXN; i += 2) {
        cout << "   test find ???" << i << "_______________________________________________________" << endl;
        ans = bptree.find(i);
        cout << ans[0].second << "&&&&&&&&&" << endl;
        cout << i << "   successfind" << endl;
    }
}

int main() {

    test1();
    test2();

    return 0;
}



