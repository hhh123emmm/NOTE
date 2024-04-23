#include"LoserTree.h"
#include"LoserTree.cpp"
#include<iostream>
#include<fstream>
using namespace std;

int visitDisk=0,cacheSize=200;//访问磁盘次数，cache大小
const int IntMax=300000000;

struct merge{//本质就是pair
    int id,key;//id是文件序号，key是关键字
    bool operator<=(merge &p){
        return (id!=p.id) ?(id<p.id):(key<p.key);//id不同，id小的为胜者，id相同，关键字小的为胜者//前size个数id默认为0//后面加的数值比当前输者树最小值要小，说明这个数需要放到新的文件里
    }
};

string getFilePath(int layer,int index){
    return "E:\\TEST\\DS2\\out\\Seg"+to_string(layer)+"_"+to_string(index)+".txt";
}

int ran(int size,int nnn){
    int filenum=0;
    merge *m=new merge[size+1];
    int incache=0,outcache=0;
    for(int i=1;i<=size;i++){//先读入输者树大小的量
        incache++;//读入缓存的量
        if(incache%cacheSize==0&&incache!=0){visitDisk++;incache=0;}
        int randnum=rand()%IntMax;nnn--;
        m[i].key=randnum;
        m[i].id=1;
    }
    if(incache>0) visitDisk++;
    ofstream fout1(getFilePath(0,1),ios::app);//以追加的方式创建一个输出流seg-0-1
    int flag=1;//标识当前打开的文件
    LoserTree<merge> ltree(m,size);//用m数组初始化一个size大小的输者树
    int num=0;
    incache=0;
    while(m[ltree.winner()].key!=INT_MIN){//获胜者不是INT_MIN，INT_MIN的id是INT_MAX,若它获胜，原值都已pop
        if(nnn<0) num=INT_MIN;
        else{
            incache++;
            if(incache%cacheSize==0&&incache!=0){visitDisk++;incache=0;}
        }
        merge winner;
        winner.id=m[ltree.winner()].id;
        winner.key=m[ltree.winner()].key;
        merge newplay;
        newplay.key=rand()%IntMax;nnn--;
        if(num>=winner.key) newplay.id=winner.id;//id不变，放在一个文件，新加入的值比原先胜者大
        else newplay.id=(num==INT_MIN)?INT_MAX:winner.id+1;//比原先胜者小，放到新的文件
        filenum=winner.id>filenum?winner.id:filenum;//更新文件数量
        ltree.rePlay(ltree.winner(),newplay);//取出赢者
        if(winner.id>flag){//打开新的文件
            flag=winner.id;
            fout1=ofstream(getFilePath(0,winner.id),ios::app);//0-s
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

int toSegString(int size){//size是输者树大小//生成初始顺串
    int filenum=0;
    merge *m=new merge[size+1];
    int incache=0,outcache=0;
    for(int i=1;i<=size;i++){//先读入输者树大小的量
        incache++;//读入缓存的量
        if(incache%cacheSize==0&&incache!=0){visitDisk++;incache=0;}
        cin>>m[i].key;
        m[i].id=1;
    }
    if(incache>0) visitDisk++;
    ofstream fout1(getFilePath(0,1),ios::app);//以追加的方式创建一个输出流seg-0-1
    int flag=1;//标识当前打开的文件
    LoserTree<merge> ltree(m,size);//用m数组初始化一个size大小的输者树
    int num=0;
    incache=0;
    while(m[ltree.winner()].key!=INT_MIN){//获胜者不是INT_MIN，INT_MIN的id是INT_MAX,若它获胜，原值都已pop
        if(!(cin>>num)) num=INT_MIN;
        else{
            incache++;
            if(incache%cacheSize==0&&incache!=0){visitDisk++;incache=0;}
        }
        merge winner;
        winner.id=m[ltree.winner()].id;
        winner.key=m[ltree.winner()].key;
        merge newplay;
        newplay.key=num;
        if(num>=winner.key) newplay.id=winner.id;//id不变，放在一个文件，新加入的值比原先胜者大
        else newplay.id=(num==INT_MIN)?INT_MAX:winner.id+1;//比原先胜者小，放到新的文件
        filenum=winner.id>filenum?winner.id:filenum;//更新文件数量
        ltree.rePlay(ltree.winner(),newplay);//取出赢者
        if(winner.id>flag){//打开新的文件
            flag=winner.id;
            fout1=ofstream(getFilePath(0,winner.id),ios::app);//0-s
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
    if (filenum == 1) {//只有一个文件，可以直接输出
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
    while (filenum > 1) {//归并
        int index=1,outindex=1;//文件索引
        layer++;//layer==1——归并层数
        int count = filenum;//当前文件数
        while (count > 0) {//当前文件未全部处理一遍
            if (count == 1) {//1个文件直接输出
                ifstream fin = ifstream(getFilePath(layer - 1, index));//layer-1--index
                int temp;
                ofstream fout(getFilePath(layer, outindex), ios::app);//1-1
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
            } else {//多个文件进行归并
                int segFilenum = count > k ? k : count;//参与比赛选手数
                pair<int, int> element[segFilenum + 1];//element数对
                int temp=index;//记录index，用于处理输入流
                ifstream fins[segFilenum+1];//每个选手实际都是一个输入流
                for (int i = 1; i <= segFilenum; ++i) {//初始化输入流
                    fins[i]=ifstream(getFilePath(layer-1,index));//index不可以改成i，可能有好几轮
                    fins[i] >> element[i].first;//first--key值
                    incache++;//缓存，处理磁盘访问次数
                    if(incache%cacheSize==0&&incache!=0) {visitDisk++;incache=0;}
                    element[i].second = index;//second
                    index++;
                }
                if(incache%cacheSize==0&&incache!=0) {visitDisk++;incache=0;}//磁盘访问次数
                LoserTree<pair<int, int>> loserTree(element, segFilenum);//segFilenum个玩家，关键字小的优先输出，关键字相同，索引小的先出
                ofstream fout(getFilePath(layer,outindex), ios::app);//1-1输出流，outindex
                while (element[loserTree.winner()].first != INT_MAX) {//没结束
                    pair<int, int> winner = element[loserTree.winner()];//赢者索引对应的文件流
                    pair<int, int> newplay;//新玩家
                    if (!(fins[winner.second-temp+1] >> newplay.first)) newplay.first = INT_MAX;//胜者输入流空了
                    else {incache++;if(incache%cacheSize==0&&incache!=0) {visitDisk++;incache=0;}}
                    newplay.second = winner.second;
                    loserTree.rePlay(loserTree.winner(), newplay);//把原本的胜者吐出去，加入新的比赛选手
                    fout << winner.first << ' ';
                    outcache++;
                    if(outcache%cacheSize==0&&outcache!=0){visitDisk++;outcache=0;}
                }
                if(incache!=0) {visitDisk++; incache=0;}//更新访问磁盘数
                if(outcache!=0) {visitDisk++; outcache=0;}
                count -= segFilenum;//文件减少
                outindex++;//下一个输出文件
                fout.close();
                for (int i = 1; i <= segFilenum; ++i) {
                    fins[i].close();
                }
            }
        }
        filenum= ceil((float)filenum/k);//全部处理一遍后，继续归并，浮点数除法除k向上取整，直到sheng，多处理一次
    }
}
//void outSort

int main(){
    freopen("E:\\TEST\\DS2\\in\\data1.txt","r",stdin);//
    int n,size=1000,k=4;//输者树大小为1000，4路归并
    cin>>n;//n是数据量
    int filenum=toSegString(size);//生成初始顺串
    //int filenum=ran(size,2000);
    outSort(filenum,k);//k路归并
    cout<<visitDisk;
}