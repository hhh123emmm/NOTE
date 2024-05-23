#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "FibHeap.h"
#include "FibHeap.cpp"

using namespace fib_heap;
using namespace std;

#define INFI 1e9

void Dijkstra()
{
	int Vnum, Enum; // The number of vertexes and edges
	cout << "Please input the information of the DAG, firstly the number of vertex and edges" 
		<< " then the information of edges, finally the start point" << endl;
	cin >> Vnum >> Enum;

	vector<vector<pair<int, int>>> G(Vnum);//创建一个Vnum大小的vector，基本对象是Vector

	for (int i = 0; i < Enum; i++){//边初始化
		int start, end;
		int weight;
		cin >> start >> end >> weight;
		G[start].emplace_back(end, weight);
	}

	vector<FibNode*> ptr(Vnum, nullptr);//一系列斐波那契节点指针
	FibHeap fibheap;//斐波那契堆
	
	int Startid;
	cin >> Startid;//起点

	for (int i = 0; i < Vnum; i++){//遍历所有顶点
		if(i == Startid){
			ptr[i] = fibheap.insert(0);//插入0并返回
			ptr[i]->id = i;
			continue;
		}
		ptr[i] = fibheap.insert(INFI);//插入最大值
		ptr[i]->id = i;
	}

	int cnt = 0;
	vector<bool> vis(Vnum, 0);//是否访问
	vector<int> dis(Vnum, INFI);//距离函数

	while(cnt < Vnum){
		int v = fibheap.min->id;//起点
		int Dis = fibheap.extract_min();//取出最小值-0
		dis[v] = Dis;
		vis[v] = 1;
		for (auto [end, weight]: G[v]){//遍历起点相邻的边
			if(!vis[end]){//未访问过
				if(weight + Dis < ptr[end]->key){//松弛
					fibheap.decrease_key(ptr[end], weight + Dis);//减小节点值
				}
			}
		}
		cnt++;//取出V次最小值
	}
	for (int i = 0; i < Vnum; i++){//最短路径
		cout << dis[i] << " \n"[i == Vnum - 1];
	}
}

void perform(){
	//演示
	FibHeap fib;
	vector<FibNode*> ptr(120, nullptr);
	//插入节点
	cout<<"*\n";
	for(int i=1;i<=100;i++) ptr[i]=fib.insert(i);
	fib.output(fib.min);cout<<"\n";
	//删除最小节点
	cout<<"**\n";
	fib.extract_min();
	fib.output(fib.min);cout<<"\n";
	//减小或增加节点值
	cout<<"***\n";
	fib.decrease_key(ptr[100],1);
	fib.output(fib.min);cout<<"\n";
	//删除节点
	cout<<"****\n";
	fib.delete_node(ptr[50]);
	fib.output(fib.min);cout<<"\n";
	//合并两个堆
	cout<<"*****\n";
	FibHeap another;
	another.insert(-1);another.insert(-2);
	fib.merge(another);
	fib.output(fib.min);cout<<"\n";
}
int main(){
	//Dijkstra();
	perform();
	return 0;
}