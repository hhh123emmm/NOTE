#include "LoserTree.h"
#include<math.h>
template<class T>
LoserTree<T>::LoserTree(T *thePlayer, int theNumberOfPlayers){
    int n=theNumberOfPlayers;
    player=thePlayer;
    numberOfPlayers=n;
    tree=new int[n+1];//记录输者的输者树
    temp=new int[n+1];//记录赢者的边数组
    int s=pow(2,floor(log(n-1)/log(2)));//内部节点最底层的最左端索引
    lowExt=2*(n-s);//最底层外部节点个数
    offset=2*s-1;//最底层，-1方便使用索引
    for(int i=2;i<=lowExt;i+=2) play((i+offset)/2,i-1,i);//对最底层的外部节点进行比赛
    int t;//
    if(n%2==1){//奇数
        play(n/2,temp[n-1],lowExt+1);//temp[n-1]--lowExt-1和lowExt的winner和lowExt+1进行比较
        t=lowExt+3;//+1比过了，+2/+3来比
    }
    else t=lowExt+2;//0比过了，+2/+1来比
    for(int i=t;i<=n;i+=2) play((i-lowExt+n-1)/2,i-1,i);//处理次底层的这些节点
    tree[0]=temp[1];
}

template<class T>
void LoserTree<T>::play(int index,int l,int r){
    //数据较小的晋级
    //if(palyer[l]<player[r]) tree[index]=l;
    tree[index]=loser(l,r);
    //else tree[index]=r;
    temp[index]=winner(l,r);
    while(index%2==1&&index>1)//右节点非根节点
    {
        //tree[index/2]=(player[tree[index-1]]<=player[tree[index]])?tree[index-1]:tree[index];
        tree[index/2]=loser(temp[index-1],temp[index]);
        temp[index/2]=winner(temp[index-1],temp[index]);
        index/=2;
    }
}

template<class T>
void LoserTree<T>::rePlay(int thePlayer,T newValue){
    int n=numberOfPlayers;
    player[thePlayer]=newValue;//改变winner[1]/tree[0]的值
    int mn,lech,rich;
    if(thePlayer<=lowExt){//找到被改变节点的父节点
        mn=(offset+thePlayer)/2;//外部节点在树中类比的位置，offset是最底层外部节点在树中的索引，/2刚好为根索引
        lech=2*mn-offset;//左边
        rich=lech+1;//右孩子
    }
    else {//存在外部节点在次底层
        mn=(thePlayer-lowExt+n-1)/2;
        if(2*mn==n-1){//一个在底层，一个在次底层
            lech=temp[2*mn];//左孩子为胜者
            rich=lech+1;
        }
        else{//都在次底层
            lech=2*mn-n+1+lowExt;
            rich=lech+1;
        }
    }
    if(thePlayer==tree[0]){//始终的胜者-跟败者比较不断更新胜者
        for(;mn>=1;mn/=2){//从第下面比开始
            int oldone=tree[mn];//原败者
            tree[mn]=loser(oldone,thePlayer);
            temp[mn]=winner(oldone,thePlayer);
            thePlayer=temp[mn];//更新胜者
        }
    }
    else {//不是一直赢，重新比赛
        tree[mn]=loser(lech,rich);//输者
        temp[mn]=winner(lech,rich);//赢者
        if(mn==n-1&&n%2==1){//次底层，倒数第2个玩家，且是奇数
            mn/=2;
            tree[mn]=loser(temp[n-1],lowExt+1);//lowExt+1 最底层外部节点的个数+1,次底层外部节点
            temp[mn]=winner(temp[n-1],lowExt+1);
        }
        mn/=2;
        for(;mn>=1;mn/=2){
            tree[mn]=loser(temp[mn*2],temp[mn*2+1]);
            temp[mn]=winner(temp[mn*2],temp[mn*2+1]);
        }
    }
    tree[0]=temp[1];
}
