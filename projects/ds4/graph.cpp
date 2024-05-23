#include"graph.h"

void graph::topsort()
{//确定一个拓扑序列 以便后续
    int cnt = 1;
    queue<int> q;//队列
    for (int i = 1; i <= n; i++) {
        if (in_deg[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();//取
        //nodes[u].toponum = cnt;//1-n
        topo[cnt] = u;//排序
        cnt++;
        for (auto e : nodes[u].edges) {//遍历该点出边
            if (--in_deg[e.des] == 0)
                q.push(e.des);//为0塞
        }
    }
}
//dfs 剪枝
void graph::backtracking(int level, int cnt)
{
    int u = topo[level];//当前点
    if (level > n) {//最底层
        if(bestRes>cnt) {//记录最好情况
            bestRes = cnt;
            for (int i = 1; i <= n; i++) {
                place_bst[i] = false;
                place_bst[i] = nodes[i].booster;
            }
        }
        return;
    }
    if(level==1) backtracking(level+1,cnt);
    else{
        int temp=INT32_MAX;
        for (int k = 1; k < level; k++) {//双重循环，拓扑序，当前点所有可能的入边
            for (auto& x : nodes[topo[k]].edges) {//k->x
                if (x.des == u)//如果存在当前点的入边
                    temp=min(temp,nodes[topo[k]].press - x.w);//当前点压力最小值
            }
        }
        if(temp<0) return;//当前情况错误
        for (int j = 0; j < 2; j++)//对于每个点都有放放大器和不放放大器两种可能
        {
            if (j == 1) {//当前点放放大器
                cnt++;
                nodes[u].press = Pmax;
                nodes[u].booster = true;
                //剪枝
                if (cnt >= bestRes) return;
                else {
                    backtracking(level + 1, cnt);
                }
            }else if (j == 0) {//不放
                nodes[u].press = temp;
                nodes[u].booster = false;
                backtracking(level + 1, cnt);
            }
        }
    }
}
//分支定界
void graph::branch_bound()
{//分支定界通过活节点扩张来生成子集树
    btnode* enode = new btnode(Pmax, 1);//活结点 1-pmax
    int level = 1;
    while (level <= n - 1)
    {//进行活结点的拓展
        int u = topo[level+1];//该层扩展的节点
        int temp_press = INT32_MAX;
        int flag = 0;
        for (int k = 1; k <= level ; k++) {
            for (auto& e : nodes[topo[k]].edges) {
                if (e.des == u) {//当前节点所有入边
                    btnode* p = enode;
                    for (int j = level; j > k; j--)//从当前情况往上找，找到当前路上这一点的压力值
                        p = p->parent;
                    temp_press = min(temp_press, p->press - e.w);//可能压力最小值
                }
            }
        }
        //必须放
        if (temp_press - nodes[u].max_to_cost < Pmin) {//会导致下一个点压力值过小
            flag = 1;
        }
        if (flag == 0) {//两种
            btnode* t = new btnode(temp_press, level + 1, enode, enode->bstnum);//不放
            pq.push(t);
            btnode* tt = new btnode(Pmax, level + 1, enode, enode->bstnum + 1);//放
            tt->have_bt = true;
            pq.push(tt);
        }
        else {//必须放
            btnode* tt = new btnode(Pmax, level + 1, enode, enode->bstnum + 1);
            tt->have_bt = true;
            pq.push(tt);
        }
        enode = pq.top(); pq.pop();//优先级队列，直到找到完全遍历的最小的
        level = enode->level;
    }
    bestRes = enode->bstnum;
    btnode* p = enode;//根据enode找这一支
    while (p) {
        place_bst[topo[p->level]] = p->have_bt;
        p = p->parent;
    }
}
