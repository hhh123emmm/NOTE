#include"skiplist.h"
#include"skiplist.cpp"
#include <sys/time.h>

const int IntMax = 300000000;
int m, n;
int key;
int sum;//xor

//1: search for certain key
void find(skipList<int, int>& sl) {
    bool result = sl.search_key(key);
    cout << (result == 1 ? "YES" : "NO") << endl;
}

//2:insert key and output xor
void insert(skipList<int, int>& sl) {
    sl.insert_key({ key,0 });
    sum = sl.xorsum();
    cout << sum << endl;
}

//3:delete key and output xor
void erase(skipList<int, int>& sl) {
    sl.delete_key(key);
    sum = sl.xorsum();
    cout << sum << endl;
}

//4:delete min
void deletemin(skipList<int, int>& sl) {
    int t = sl.delete_min();
    cout << t << endl;//MIN
}

//5:delete max
void deletemax(skipList<int, int>& sl) {
    sl.delete_max();
}

//operate
void operate() {
    skipList<int, int> sl(IntMax, 200, 0.5);
    cin >> m >> n;
    int temp;
    for (int i = 1; i <= n; i++) {
        cin >> temp;
        sl.insert_key({ temp,0 });
    }
    int op;
    for (int j = 1; j <= m; j++) {
        cin >> op;
        if (op == 1) {
            cin >> key;
            find(sl);
        }
        else if (op == 2) {
            cin >> key;
            insert(sl);
        }
        else if (op == 3) {
            cin >> key;
            erase(sl);
        }
        else if (op == 4) deletemin(sl);
        else if (op == 5) deletemax(sl);
        else {
            cout << "Wrong" << endl;
        }
    }
}

//check for correction
void test1() {
    const int nums = 10;
    for (int i = 0; i < nums; i++) {
        //char file1[255]="E:\\TEST\\DS1\\in\\input_"+accord+".in";
        string file1 = "E:\\TEST\\DS1\\in\\input_" + to_string(i) + ".txt";
        string file2 = "E:\\TEST\\DS1\\stdout\\my" + to_string(i) + ".out";
        freopen(file1.c_str(), "r", stdin);
        freopen(file2.c_str(), "w", stdout);
        operate();
    }
}

void improve(skipList<int, int>& sl) {
    vector<int> temp;
    while (!sl.empty()) temp.push_back(sl.delete_min());
    for (auto i = 0; i < temp.size(); i++) sl.insert_key({ temp[i],0 });
    //cout<<"*******************"<<endl;
}
//check for random
void test2() {
    string file3 = "E:\\TEST\\DS1\\test.txt";
    freopen(file3.c_str(), "w", stdout);
    skipList<int, int> sl(IntMax, 20000, 0.5);
    const int length = 100000;
    int delsize = 0;
    for (int i = 1; i <= length; i++) {
        //有序链表
        int randnum = rand() % IntMax;
        sl.insert_key({ randnum,0 });//随机产生n个数据并初始化成严格跳表
    }
    for (int i = 1; i <= 10000; i++) {
        int randop = rand() % 3;
        int randnum = rand() % IntMax;
        struct timeval TimeB, TimeE;
        gettimeofday(&TimeB, NULL);
        if (randop == 0) sl.search_key(randnum);//search
        else if (randop == 1) sl.insert_key({ randnum,0 });//insert
        else {
            sl.delete_key(randnum);//delete randop=2
            delsize++;
            if (delsize == length / 30) {
                //cout<<"*";
                improve(sl);
                delsize = 0;
            }
        }
        gettimeofday(&TimeE, NULL);
        double ttt = (TimeE.tv_sec - TimeB.tv_sec) + (TimeE.tv_usec - TimeB.tv_usec) / 1000.0;//ms
        cout << "operation-" << randop << " responding num-" << randnum << " ms-time-" << ttt << endl;
    }
}

int main() {
    //test1();
    test2();
    return 0;
}