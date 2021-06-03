//
// Created by 18303 on 2021/5/31.
//

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include "bplustree.hpp"

#define TESTSIZE 150
using std::cout;
using std::cerr;
using std::map;
using std::pair;
using namespace std;
map<int, vector<int>> answer;
vector<int> store;


void testIntAll() {
    sjtu::BPtree<int, int> bpt("bpt", "data");

    srand(22);
    int s;

    for (int i = 0; i < TESTSIZE; i++) {

        s = rand() % 10 + 1;
        store.push_back(s);
        cout<<s<<"          insert   "<<i<<endl;
        sjtu::BPtree<int, int>::value_type a(s, i);
        bpt.insert(a);
        //cout<<bpt.f11.find()
        if (i % (TESTSIZE / 100) == 0)cout << "[count down] Inserting...\t" << i * 100 / TESTSIZE + 1 << "%" << endl;
    }
    cout << endl;

    for (int i = 0; i < TESTSIZE; i++) {
        if (i % 2 == 0) {
            answer[store[i]].push_back(i);
        }
        if (i % (TESTSIZE / 100) == 0)cout << "[count down] Pushing...\t" << i * 100 / TESTSIZE + 1 << "%" << endl;
    }
    cout << endl;
    int i;
    for (i = 0; i < TESTSIZE; i++) {
        if (i % 2 == 1) {
             cout<<i<<"       in erase:   "<<store[i]<<endl;
            sjtu::BPtree<int, int>::value_type a(store[i], i);


            if (!bpt.erase(a)) {
                cerr << "[error]erase failed when erasing\nkey: " << store[i] << "\tdata: " << i << endl;
                break;
            }
        }
        if (i % (TESTSIZE / 100) == 0)cout << "[count down] Erasing...\t" << i * 100 / TESTSIZE + 1 << "%" << endl;
    }
    cout << endl;


    int cnt = 0;
    size_t size = answer.size();


    for (i = 1; i <= 10; ++i) {
        cout << i << " " << "&&&&&&&&&&&&&&" << endl;
        vector<sjtu::BPtree<int, int>::value_type> result;

        result = bpt.find(i);
        sort(result.begin(), result.end());
        for (int j = 0; j < result.size(); ++j) {
            cout << result[j].second << " ";
        }
        cout << endl;

    }


    for (const auto &i:answer) {
        vector<sjtu::BPtree<int, int>::value_type> result;

        result = bpt.find(i.first);

        sort(result.begin(), result.end());
        if (i.second.size() != result.size()) {
            cerr << "[error]wrong size." << endl;
            cerr << "key: " << i.first << endl;
            cerr << "answer size: " << i.second.size() << endl;
            cerr << "answer:" << endl;
            for (auto j : i.second)cerr << j << " ";
            cerr << endl;
            cerr << "result size: " << result.size() << endl;
            cerr << "result:" << endl;
            for (auto j : result)cerr << j.second << " ";
            cerr << endl;
        } else {
            for (int j = 0; j < i.second.size(); j++) {
                if (i.second[j] != result[j].second) {
                    cerr << "[error]wrong answer." << endl;
                    cerr << "data: " << i.second[j] << endl;
                    cerr << "your data: " << result[j].second << endl;
                }
            }
        }
        if (size / 100 != 0 && cnt % (size / 100) == 0)
            cout << "[count down] Checking...\t" << cnt * 100 / size + 1 << "%" << endl;
        cnt++;
    }
    cout << "over\n";
    cout << endl;
}

//void testRepeatedInsert() {
//    init();
//    int a = 100;
//    BPlusTree<int, int> bpt("test");
//    for (int i = 0 ; i < TESTSIZE ; ++i) {
//        bpt.insert(a, i);
//    }
//    vector<int> tt;
//    bpt.find(a,tt);
//    if (tt.size() != TESTSIZE) cerr << "[error] size wrong!\n";
//    else {
//        sort(tt.begin(), tt.end());
//        int cnt = 0;
//        for (auto i: tt) {
//            if (i != cnt)cerr << "[error] element wrong!" << endl;
//            cnt++;
//        }
//    }
//}
void testsecond() {
    sjtu::BPtree<int, int> bpt("bpt", "data");
    for (int i = 1; i <= 10; ++i) {
        cout<<i<<"******************"<<endl;
        vector<sjtu::BPtree<int, int>::value_type> result;

        result = bpt.find(i);
        sort(result.begin(), result.end());
        for (int j = 0; j < result.size(); ++j) {
            cout << result[j].second << " ";
        }
        cout << endl;

    }
    cout << "over\n";
    cout << endl;

}

int main() {
    //testIntAll();
     testsecond();
    return 0;
}