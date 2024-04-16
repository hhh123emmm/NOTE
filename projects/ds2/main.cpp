#include"LoserTree.h"
#include"LoserTree.cpp"
#include<iostream>
#include<fstream>
using namespace std;

struct merge{
    int id,key;
    bool operator<=(merge &p){
        return (id!=p.id) ?(id<p.id):(key<p.key);
    }
};

string getFilePath(int layer,int index){
    return "E:\\TEST\\DS2\\out\\Seg"+to_string(layer)+"_"+to_string(index)+".txt";
}

int visitDisk=0,cacheSize=200;//访问磁盘次数，cache大小

int toSegString(int size){
    int filenum=0;
    merge *m=new merge[size+1];
    int incache=0,outcache=0;
    for(int i=1;i<=size;i++){
        incache++;//读入缓存的量
        if(incache%cacheSize==0&&incache!=0){visitDisk++;incache=0;}
        cin>>m[i].key;
        m[i].id=1;
    }
    if(incache>0) visitDisk++;
    ofstream fout1(getFilePath(0,1),ios::app);//以追加的方式创建一个输出流seg-0-1
    int flag=1;//？
    LoserTree<merge> ltree(m,size);
    int num=0;
    incache=0;
    while(m[ltree.winner()].key!=INT_MIN){//获胜者不是INT_MIN
        if(!(cin>>num)) num=INT_MIN;
        else{
            incache++;
            if(incache%cacheSize==0&&incache!=0){visitDisk++;incache=0;}
        }
        merge winner;
        winner.id=m[ltree.winner()].id;
        winner.key=m[ltree.winner()].key;
        if(ltree.winner()>size){
            size=size+1;
            size=size-1;//////////////////////???????????????????????
        }
        merge newplay;
        newplay.key=num;
        if(num>=winner.key) newplay.id=winner.id;
        else newplay.id=(num==INT_MIN)?INT_MAX:winner.id+1;
        filenum=winner.id>filenum?winner.id:filenum;
        ltree.rePlay(ltree.winner(),newplay);
        if(winner.id>flag){
            flag=winner.id;
            fout1=ofstream(getFilePath(0,winner.id),ios::app);
        }
        fout1<<winner.key<<" ";//.............
        outcache++;
        if(outcache%cacheSize==0&&outcache!=0){visitDisk++;outcache=0;}
    }
    if(incache!=0) visitDisk++;
    if(outcache!=0) visitDisk++;
    fout1.close();
    return filenum;
}

void outSort(int filenum,int k){
    int incache=0,outcache=0;
    int layer=0;
    if (filenum == 1) {
        ofstream out("E:\\TEST\\DS2\\out\\output.txt");
        ifstream fin(getFilePath(0,1));
        int tempnumber;
        while (fin >> tempnumber) {
            out << tempnumber << ' ';
            incache++;outcache++;
            if(incache%cacheSize==0&&incache!=0) {visitDisk++;incache=0;}
            if(outcache%cacheSize==0&&outcache!=0){visitDisk++;outcache=0;}
        }
        if(incache!=0) {visitDisk++; incache=0;}
        if(outcache!=0) {visitDisk++; outcache=0;}
    }
    while (filenum > 1) {
        int index=1,outindex=1;
        layer++;
        int count = filenum;
        while (count > 0) {
            if (count == 1) {
                ifstream fin = ifstream(getFilePath(layer - 1, index));
                int temp;
                ofstream fout(getFilePath(layer, outindex), ios::app);
                while (fin >> temp) {
                    fout << temp << ' ';
                    incache++;outcache++;
                    if(incache%cacheSize==0&&incache!=0) {visitDisk++;incache=0;}
                    if(outcache%cacheSize==0&&outcache!=0){visitDisk++;outcache=0;}
                }
                if(incache!=0) {visitDisk++; incache=0;}
                if(outcache!=0) {visitDisk++; outcache=0;}
                fout.close();
                count--;
            } else {
                int segFilenum = count > k ? k : count;
                pair<int, int> element[segFilenum + 1];
                int temp=index;
                ifstream fins[segFilenum+1];
                for (int i = 1; i <= segFilenum; ++i) {
                    fins[i]=ifstream(getFilePath(layer-1,index));
                    fins[i] >> element[i].first;
                    incache++;
                    if(incache%cacheSize==0&&incache!=0) {visitDisk++;incache=0;}
                    element[i].second = index;
                    index++;
                }
                if(incache%cacheSize==0&&incache!=0) {visitDisk++;incache=0;}
                LoserTree<pair<int, int>> loserTree(element, segFilenum);
                ofstream fout(getFilePath(layer,outindex), ios::app);
                while (element[loserTree.winner()].first != INT_MAX) {
                    pair<int, int> winner = element[loserTree.winner()];
                    pair<int, int> newplay;
                    if (!(fins[winner.second-temp+1] >> newplay.first)) newplay.first = INT_MAX;
                    else {incache++;if(incache%cacheSize==0&&incache!=0) {visitDisk++;incache=0;}}
                    newplay.second = winner.second;
                    loserTree.rePlay(loserTree.winner(), newplay);
                    fout << winner.first << ' ';
                    outcache++;
                    if(outcache%cacheSize==0&&outcache!=0){visitDisk++;outcache=0;}
                }
                if(incache!=0) {visitDisk++; incache=0;}
                if(outcache!=0) {visitDisk++; outcache=0;}
                count -= segFilenum;
                outindex++;
                fout.close();
                for (int i = 1; i <= segFilenum; ++i) {
                    fins[i].close();
                }
            }
        }
        filenum= ceil((float)filenum/k);
    }
}
//void outSort

int main(){
    freopen("E:\\TEST\\DS2\\in\\data1.txt","r",stdin);//
    int n,size=1000,k=4;//输者树大小为1000，4路归并
    cin>>n;//n是数据量
    int filenum=toSegString(size);//
    outSort(filenum,k);
    cout<<visitDisk;
}