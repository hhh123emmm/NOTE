#pragma once
#include<limits.h>
#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<fstream>
#include<sstream>
#include<climits>
#include<string>
#include<windows.h>
#include<time.h>
#include<sys/timeb.h>
#include<math.h>
using namespace std;
//const int INT32_MAX=0x3f3f3f3f;
ifstream fin;
ofstream fout;

struct btnode {//用于分支定界的子集树
    btnode* parent;//指向父节点
    int press;//压力
    int level;//节点层级
    bool have_bt;//是否放放大器
    int bstnum;//优先级 从根到节点x的路径上的bst个数
    btnode() {
        parent = NULL;
        press = 0; level = 0; have_bt = false;
        bstnum = 0;

    }
    btnode(int pres, int lev, btnode* par = NULL, int bstn = 0) {
        parent = par;
        press = pres; level = lev;
        bstnum = bstn;
        have_bt = false;
    }
};
class Edge {//边
public:
    int des;//终点编号
    int w;//长度
    Edge(int to, int cost) : des(to), w(cost) {}
    ~Edge() {}
};
class Node {
public:
    vector<Edge> edges;//记录所有出边的边集
    int press;//压力--    >0即可
    bool booster;//是否放置放大器
    int max_to_cost;//以该点为起点的最长边
    Node() {
        press = 0;
        booster = false;
        edges.clear();
        max_to_cost = 0;
    }
    ~Node() {}
};

struct cmp
{
    bool operator () (const btnode* p1, const btnode* p2) {
        return p1->bstnum > p2->bstnum;//分支定界用，bstnum小的优先
    }
};

class graph {
private:
    int Pmin, Pmax;
    vector<Node> nodes;//点集
    vector<int> in_deg;//各点的入度--拓扑排序用
    vector<int> topo;//拓扑序列--两种方法都用
    vector<bool> place_bst;//结果数组
    priority_queue<btnode*, vector<btnode*>, cmp> pq;//最小堆 分支定界用
public:
    int n, m;//顶点数 边
    graph() {
        //cin >> n >> m >> Pmax;
        fin >> n >> m >> Pmax;
        Pmin = 0;
        bestRes = INT_MAX;
        in_deg.resize(n + 1, 0);
        topo.resize(n + 1, 0);
        place_bst.resize(n + 1, false);
        //初始化顶点
        for (int i = 0; i <= n; i++)
            nodes.emplace_back(Node());//直接创建，省去移动和拷贝，实际使用和push_back没什么区别。创建n+1个默认对象
        //读入边
        for (int i = 1; i <= m; i++) {
            int u, v, w;
            //cin >> u >> v >> w;
            fin >> u >> v >> w;
            nodes[u].edges.emplace_back(v, w);
            //修改入度
            in_deg[v]++;
            nodes[u].max_to_cost = max(nodes[u].max_to_cost, w);//最大耗费
        }
        nodes[1].press = Pmax;
        place_bst[1] = true;//节点1相当于放大器
    }
    ~graph() {}
    int bestRes;//最优解-数目
    void topsort();//拓扑排序
    void backtracking(int level, int cnt);//回溯解决
    void branch_bound();//分支定界解决

};