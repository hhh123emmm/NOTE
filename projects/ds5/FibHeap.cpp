#include "FibHeap.h"
#include<iostream>
namespace fib_heap {

const int FibHeap::minimumKey = 0x80000000; // the minimum int value

FibNode* FibHeap::insert(int newKey)//插入该节点到min节点之前，考虑是否更新，min节点看作双向链表表头，即插入双向链表末尾
{
	FibNode* newNode = _create_node(newKey);
	_insert_node(newNode);
	return newNode;
}
 
void FibHeap::merge(FibHeap &another)//合并到当前堆 清空另一个堆
{
	min = _merge(min, another.min);
	maxDegree += another.maxDegree;
	another.min = nullptr; // so that another 
	another.maxDegree = 0;
}
 
int FibHeap::extract_min()//取出最小值
{
	FibNode* minNode = _extract_min_node();
	int ret = minNode->key;
	delete minNode;
	return ret;
}

void FibHeap::decrease_key( FibNode* x, int newKey)//减小节点值
{
	_decrease_key(x, newKey);
}
 
void FibHeap::delete_node(FibNode* x)//删除节点
{
	decrease_key(x, minimumKey);
	extract_min();
}

FibNode* FibHeap::_create_node(int newKey)//new一个FibNode节点
{
	FibNode* newNode = new FibNode;
	newNode->key = newKey;
	newNode->left = newNode;//双向链表
	newNode->right = newNode;
	newNode->parent = nullptr;
	newNode->child = nullptr;
	newNode->degree = 0;
	newNode->mark = false;//？
	return newNode;
}

void FibHeap::_insert_node( FibNode* newNode)//插入调用merge函数
{
	min = _merge( min, newNode);
	maxDegree++;
}

void FibHeap::_remove_from_circular_list( FibNode* x)//把x两边接上，使x左右为自身
{
    if (x->right == x)//只有一个节点/空
        return;
    FibNode* leftSib = x->left;
    FibNode* rightSib = x->right;
    leftSib->right = rightSib;
    rightSib->left = leftSib;
    x->left = x->right = x;
}

FibNode* FibHeap::_merge( FibNode* a,  FibNode* b)//合并双向链表，并返回最小节点指针
{
	if(a == nullptr)
		return b;
	if(b == nullptr)	
		return a;
	if( a->key > b->key ) // swap node to ensure that a is the min one
	{
		FibNode* temp = a;
		a = b;
		b = temp;
	}
	FibNode* aRight = a->right; // 
	FibNode* bLeft	= b->left;
	a->right = b;
	b->left = a;
	aRight->left = bLeft;
	bLeft->right = aRight;
	return a;	
}

FibNode* FibHeap::_extract_min_node()//删除最小节点
{
	FibNode* mn = min;//最小值对应的斐波那契节点
    if (mn == nullptr){
        return nullptr;
    }
    _unparent_all(mn->child);//将最小节点所有孩子节点的父指针清空
    _merge(mn, mn->child);//mn->child直接串联在根表中
    if (mn == mn->right){//没有孩子||树中没有节点
        min = nullptr;
    }else{
        min = mn->right;//mn的第一个孩子
    }
    _remove_from_circular_list(mn);//移除mn
    if (min != nullptr){//
        _consolidate();
    }
    maxDegree--;
    return mn;
}

void FibHeap::_unparent_all(FibNode* x)//make all nodes' parent nullptr in a circular list
{
	if(x == nullptr)
		return;
	FibNode* y = x;
	do {
		y->parent = nullptr;
		y = y->right;
	}while(y != x);
}

void FibHeap::_consolidate()
{
    int Dn = (int)(log2(maxDegree) / log2(1.618));//最大高度
    FibNode** A = new  FibNode*[Dn + 1];//创建一个指针数组，用于存储各个度数的节点
    for(int i = 0; i < Dn + 1; i++){
        A[i] = nullptr;//初始化
    }
    vector<FibNode*> nodeList;
    auto node = min;
    do{
        nodeList.emplace_back(node);
        node = node->right;
    } while (node != min);//存入双向链表
    for (auto e: nodeList){//合并度数相同的子树
        int d = e->degree;
        _remove_from_circular_list(e);//删除连接关系
        while(A[d] != nullptr){//合并到度数相同的节点的子孩子
            auto tmp = A[d];
            if (e->key > tmp->key){
                swap(e, tmp);
            }
            _make_child(tmp, e);
            A[d++] = nullptr;
        }
        A[e->degree] = e;
        min = e;
    }
    for (int i = 0; i < Dn + 1; i++){
        if (A[i] != nullptr && A[i] != min){//把合并后的树串起来
            _merge(min, A[i]);
        }
    }
    FibNode* flag = min;
    FibNode* iter = flag;
    do{
        if (iter->key < min->key){
            min = iter;//找到并更新min
        }
        iter = iter->right;
    } while (iter != flag);
    delete []A;
}

void FibHeap::_make_child( FibNode *child,  FibNode *parent)
{
    child->parent = parent;
    parent->child = _merge(parent->child, child);//合并
    parent->degree++;
    child->mark = false;
}

void FibHeap::_decrease_key( FibNode* x, int newKey)
{
	x->key = newKey;
	FibNode* y = x->parent;//父亲值
	if ( y != nullptr && x->key < y->key )//小了
	{
		_cut(x, y);
		_cascading_cut(y);//级联剪切
	}
	if (x->key < min->key)//特别小，更新为min
		min = x;
}

void FibHeap::_cut( FibNode* x,  FibNode* y)
{
    y->child = (x == x->right ? nullptr : x->right);//更新上下级
    _remove_from_circular_list(x);//处理左右
    y->degree--;
    _merge(min, x);//x上去
    x->parent = nullptr;
    x->mark = false;
}

void FibHeap::_cascading_cut( FibNode* y)
{
	 FibNode* z = y->parent;
	if ( z != nullptr)
	{
		if( y->mark == false)
			y->mark = true;	
		else//成为新的需要被剪切的减小节点
		{
			_cut(y,z);
			_cascading_cut(z);
		}
	}
}

void FibHeap::output(FibNode* x){
	if ( x != nullptr )
	{
		FibNode* t1 = x;  
		do{
			std::cout<<t1->key<<" ";
			FibNode* t2 = t1; 
			t1 = t1->right;
			output(t2->child);
			
		} while(t1 != x); 
	}
}
void FibHeap::_clear( FibNode* x)
{
	if ( x != nullptr )
	{
		FibNode* t1 = x;  
		do{
			FibNode* t2 = t1; 
			t1 = t1->right;
			_clear(t2->child);
			delete t2;
		} while(t1 != x); 
	}
}

}