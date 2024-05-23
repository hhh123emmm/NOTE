#ifndef _FIB_HEAP_H
#define _FIB_HEAP_H

#include <cmath>
#include <vector>
using namespace std;

namespace fib_heap{

 
struct FibNode
{
	int key; // key
	FibNode* left;// pointer to left brother
	FibNode* right;// right brother
	FibNode* parent;// father
	FibNode* child;// the first child
	int degree;//the number of children
	bool mark;//if the first children has been deleted--for delete node
	int id; // the vertex id--Dijkstra算法用
};

 		
class FibHeap {
public:
	FibNode* min;//the minist node
	int maxDegree;// sum degree

	FibHeap(){  // initialize a new and empty Fib Heap
		min = nullptr;
		maxDegree = 0;
	}
	~FibHeap() {
		_clear(min);
	}

	FibNode* insert(int newKey);//Insert a node with key value new_key and return the inserted node	
	void merge(FibHeap &another); //Merge current heap with another		
	int  extract_min(); //Return the key of the minimum node
	void decrease_key( FibNode* x, int newKey);//Decrease the key of node x to newKey
	void delete_node( FibNode* x);//Delete a specified node
	void output(FibNode* x);

private:
	static const int minimumKey; 
	 FibNode* _create_node(int newKey);
	void _insert_node( FibNode* newNode);
	void _remove_from_circular_list( FibNode* x);
	 FibNode* _merge( FibNode* a,  FibNode* b);
	void _make_child( FibNode *child,  FibNode *parent);
	void _consolidate();
	void _unparent_all( FibNode* x);
	 FibNode* _extract_min_node();
	void _decrease_key( FibNode* x, int newKey);
	void _cut(FibNode* x, FibNode* y);
	void _cascading_cut(FibNode* y);
	void _clear(FibNode* x);
};


}

#endif
