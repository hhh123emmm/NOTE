#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<class T,class K>
struct skipNode {
	typedef pair<const T, K> pairType;
	pairType element;
	skipNode<T,K> **next;//pointer array
	int max_level;// seems useless
	skipNode(const pairType& thePair,int size)
		:element(thePair) {next=new skipNode<T,K>* [size];//allocate space
		};
};

template<class T,class K>
class skipList {
private:
	skipNode<T, K>* head;//point to the head
	skipNode<T, K>* tail;//tail pointer
	skipNode<T, K>** last;//for insert/delete,last[i]
	float cutoff;//ensure layer num,why float
	int levels;//current max 
	int dSize;//num of pair
	int maxLevel;//admitted max
	T tailKey;//biggest forever key
	//int Level;//useless but forget to delete
public:
	skipList(T,int,float);//largeKey,maxPairs,probability
	int level() const;//insert
	skipNode<T,K>* search(const T&) const;//insert
	skipList make_skipList(){}//seems useless
	bool search_key(const T& k) const;//search
	void insert_key(const pair<const T,K>&);//insert
	void delete_key(const T& k);//delete
	T delete_min();//min
	void delete_max();//max
	int xorsum();
	bool empty(){return dSize==0;}
};