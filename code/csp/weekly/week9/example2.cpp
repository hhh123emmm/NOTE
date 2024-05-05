//文件系统
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct FileSystem{
    map<string,FileSystem> children;
    bool isDir;//目录
    ll LD,LR;
    ll SD,SR;
    ll fileSize;
    FileSystem(){
        LD=LR=1e18;
        SD=SR=fileSize=0;
        isDir=true;    
    }
}root;

vector<string> nameList;
vector<FileSystem *>nodeList;

void upd_path(){//路径更新
    nameList.clear();
    nodeList.clear();

    string path;
    cin>>path;

    string cur;
    stringstream ss(path);
    while(getline(ss,cur,'/')){
        //从ss读取到cur
        nameList.push_back(cur);
    }
    //映射
    FileSystem *f=&root;
    nodeList.push_back(f);//root

    for(int i=1;i< nameList.size();++i){//0是空
        string &cur_name=nameList[i];//当前的这个孩子
        if(!f->isDir|| f->children.count(cur_name)==0){//若f不是目录或者f的孩子当中无当前文件
            break;
        }
        f=&f->children[cur_name];
        nodeList.push_back(f);
    }
}

void charge_quota(ll inc,bool isFile=true){
    for(int i=0;i<nodeList.size();++i){
        nodeList[i]->SR+=inc;
        if(i==nameList.size()-2 && isFile){
            nodeList[i]->SD+=inc;
        }
    }
}
bool create(){
    //创建一个文件
    ll fileSize;
    cin>>fileSize;

    ll inc=fileSize;

    //判断不合法情况
    auto lastNode=nodeList.back();//最后一个节点
    if(nameList.size()==nodeList.size()){
        if(lastNode->isDir) return false;//相等最后一个是目录
        inc=fileSize-lastNode->fileSize;//文件
    }else{
        if(!lastNode->isDir) return false;//最后一个不是目录，文件
    }

    for(int i=0;i<nodeList.size();++i){
        if(nodeList[i]->SR+inc>nodeList[i]->LR) return false;
        if(i==nameList.size()-2){
            //倒数第二个
            if(nodeList[i]->SD+inc>nodeList[i]->LD) return false;
        }
    }

    for(int i= (int) nodeList.size(); i<nameList.size();++i){
        nodeList.push_back(&nodeList.back()->children[nameList[i]]);//新建namelist[i],取值，放到最后
    }

    charge_quota(inc);

    nodeList.back()->fileSize=fileSize;
    nodeList.back()->isDir=false;

    return true;
}

bool remove(){
    //
    if(nameList.size()!=nodeList.size()) return true;

    //auto lastNode:FileSystem* =nodeList.back();
    FileSystem* lastNode=nodeList.back();
    if(lastNode->isDir){
        charge_quota(-lastNode->SR,false);
    }else{
        charge_quota(-lastNode->fileSize);
    }

    nodeList[nodeList.size()-2]->children.erase(nameList.back());
    return true;
}

bool quota(){
    //设置配额
    ll LD,LR;
    cin>>LD>>LR;
    if(LD==0) LD=1e18;
    if(LR==0) LR=1e18;

    if(nameList.size()!=nodeList.size()) return false;

    FileSystem * lastNode=nodeList.back();

    if(!lastNode->isDir){//不是一个目录
        return false;
    }

    if(lastNode->SD>LD|| lastNode->SR>LR){
        return false;
    }

    lastNode->LD=LD;
    lastNode->LR=LR;
    return true;
}

int main(){
    int n;
    cin>>n;
    while(n--){
        string op;
        cin>>op;

        upd_path();

        bool is_success=false;
        if(op=="C"){
            is_success=create();
        }else if(op=="R"){
            is_success=remove();
        }else{
            is_success=quota();
        }
        if(is_success) cout<<"Y\n";
        else cout<<"N\n";
    }
    return 0;
}