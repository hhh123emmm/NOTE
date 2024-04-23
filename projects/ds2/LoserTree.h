#pragma once
#include<iostream>
using namespace std;
template<class T>
class LoserTree{
private:
    int *tree;//输者树
    int *temp;//记录赢者方便创造输者树
    T *player;//参赛选手n个选手对应内部节点n-1
    int lowExt;//最底层外部节点个数
    int offset;//offset=2*s-1,s为最底层最左端的内部节点
    int numberOfPlayers;//竞赛选手数量
public:
    LoserTree(T* thePlayer=NULL, int theNumberOfPlayers=0);
    ~LoserTree(){delete[] tree;delete[] temp;}
    int winner(){return tree[0];}//返回赢者
    void play(int,int,int);//比赛
    int winner(int x,int y) const{return player[x]<=player[y]?x:y;};//返回赢者的索引
    int loser(int x,int y) const{return player[x]<=player[y]?y:x;};//返回输者的索引
    void rePlay(int thePlayer,T newValue);//在参赛者thePlayer的分数变化后参赛
};