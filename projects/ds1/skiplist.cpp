#include"skiplist.h"
#include<math.h>

/*
template<class T, class K>
inline int skipNode<T, K>::randomLevel()
{
	//level
	int level = 1;
	while (Math.random() < 1 && level < max_level)
		level += 1;
	return level;
}
*/

template<class T, class K>
skipList<T, K>::skipList(T largeKey,int maxPairs,float prob){
	//constructor
	cutoff=prob*RAND_MAX;//RAND_MAX-rand函数可能返回的最大值
	maxLevel=(int) ceil(logf((float)maxPairs)/logf(1/prob))-1;//ceil向上取整，给定一个比较均衡的最高层数
	levels=0;
	dSize=0;
	tailKey=largeKey;
	//pointer
	pair<T,K> tailPair;
	tailPair.first=tailKey;//tail Node
	head=new skipNode<T,K> (tailPair,maxLevel+1);//size=maxLevel+1
	tail=new skipNode<T,K> (tailPair,0);//pointer array size=0
	last=new skipNode<T,K>*[maxLevel+1];//pointer array
	//NULL
	for(int i=0;i<=maxLevel;i++) head->next[i]=tail;//point to tail
}

template<class T, class K>
int skipList<T, K>::level() const
{
	int lev = 0;
	while (rand() <= cutoff) lev++;
	return ((lev<=maxLevel)? lev:maxLevel);
}

template<class T, class K>
skipNode<T,K>* skipList<T, K>::search(const T& theKey) const
{
	skipNode<T, K>* beforeNode = head;
	for (int i = levels; i >= 0; i--)
	{
		while (beforeNode->next[i]->element.first < theKey)
			beforeNode = beforeNode->next[i];
		last[i] = beforeNode;//store the before
	}
	return beforeNode->next[0];
}

template<class T,class K>
bool skipList<T,K>::search_key(const T& k) const{
	//search,from the top layer finally to the origin link.The time complexity=height_of_index*elements_of_every_layer.
	if(k>=tailKey||dSize==0||head->next[0]==tail) return false;
	int i = 0;
	skipNode<T, K>* prev = head;
	for (i = levels; i >= 0; i--) {
		while (prev->next[i]->element.first < k) {
			prev = prev->next[i];
		}
	}
	if(prev->next[0]->element.first==k) return 1;
	return 0;
}

template<class T,class K>
void skipList<T, K>::insert_key(const pair<const T,K>& thePair) {
	//insert,if just insert but give up indexing.skipList will finally decline into single link.
	//if reconstruct index each try,time-complexity will increase into O(n)
	//so we choose a random algorithm,1/2 to build the first-layer,1/4 to build the second...
	//skipNode<T, K>* tmp = new skipNode<T, K>(k, 0);
	//tmp->level = tmp->randomLevel();
	//merge it together
	//for (int i = tmp->level - 1; i >= 0; --i) {
		//if(head->key<)//?????????????????????????????????????????????
	//}
	if (thePair.first >= tailKey)//not exists
	{
		//ostringstream s;
		//s << "Key=" << (thePair.first) << "Must be < " << tailKey;
		return;
	}
	skipNode<T, K>* theNode = search(thePair.first);//
	if (theNode->element.first == thePair.first)
	{
		//exists，change the responding second
		theNode->element.second = thePair.second;
		return;
	}
    //not exists
	int theLevel = level();//level---------------------
	if (theLevel > levels)//theLevel<=levels+1
	{
		theLevel = ++levels;
		last[theLevel] = head;
	}
	//�ڽڵ�theNode֮������½ڵ�
	skipNode<T, K>* newNode = new skipNode<T, K>(thePair, theLevel + 1);
	for (int i = 0; i <= theLevel; i++)
	{
		newNode->next[i] = last[i]->next[i];
		last[i]->next[i] = newNode;
	}

	dSize++;
	return;
}

template<class T, class K>
void skipList<T, K>::delete_key(const T& k)
{
	//delete,similar with insert
	if(k>=tailKey) return;
	skipNode<T,K>* theNode=search(k);
	if(theNode->element.first!=k)//not exists
		return;
	for(int i=0;i<levels && last[i]->next[i]==theNode;i++)
		last[i]->next[i]=theNode->next[i];//delete K
	//update
	while(levels>=0 && head->next[levels]==tail) levels--;
	delete theNode;
	dSize--;
	//cout<<"*"<<k<<endl;
}

template<class T, class K>
T skipList<T, K>::delete_min()
{
	//if(head->next[0]==tail) return;
	T MIN=head->next[0]->element.first;
	//cout<<MIN<<endl;
	delete_key(MIN);
	return MIN;
}

template<class T, class K>
void skipList<T, K>::delete_max()
{
	if(head->next[0]==tail) return;
	skipNode<T,K> *pre=head;
	for(skipNode<T,K> *cur=head->next[0];cur!=tail;cur=cur->next[0])
		pre=cur;
	T MAX=pre->element.first;
	cout<<MAX<<endl;
	delete_key(MAX);
}

template<class T,class K>
int skipList<T,K>::xorsum(){
	int sum=0;
	for(skipNode<T,K>* i=head->next[0];i!=tail;i=i->next[0]) sum^=i->element.first;
	return sum;
}