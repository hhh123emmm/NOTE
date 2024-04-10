#pragma once

template<class T>
class LoserTree{
private:
    int *tree;//输者树
    T *player;//参赛选手n个选手对应内部节点n-1
    int lowExt;//最底层外部节点个数
    int offset;//offset=2*s-1,s为最底层最左端的内部节点
    int numberOfPlayers;//竞赛选手数量
public:
    void play(int,int,int);
    void initialize(T *thePlayer,int theNumberOfPlayers);
    int loser() const;//返回输者的索引
    void rePlay(int thePlayer);//在参赛者thePlayer的分数变化后参赛
};