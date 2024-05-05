#pragma once
#include <cstdio>
using namespace std;

struct TreeNode {
    //树节点
    TreeNode* parent;//父指针
    TreeNode* FirstChild;//第一个儿子
    TreeNode* brother;//兄弟
    bool ifFile;//文件/目录
    char filename[100];//字符串存储树节点对应的文件或目录
    int depth;//当前节点的深度
    int size;//当前节点子文件
};
typedef TreeNode* nowPosition;//当前位置
typedef TreeNode* Tree;//树节点数组表示整个树
typedef TreeNode* ptr;//指向树节点的指针

class catalogTree;//目录树
void findPath(catalogTree* a, nowPosition x);//根据位置寻找路径
void deletePtr(catalogTree* a, ptr t);//根据位置删除

class catalogTree {
public:
    TreeNode* root;//根
    ptr nowPtr;//指向当前访问位置

    catalogTree();//构造函数
    ~catalogTree() {
        deletePtr(this, root);//删除根及孩子
    }

    void mkdir(char* name, nowPosition t);//在t创建目录
    void mkfile(char* nae, nowPosition t);//在t创建文件
    void ListDir();//列出当前目录下的文件
    void Delete(char* str);//删除某文件或目录
    void cd();//打印当前目录路径
    void cdPath(char* str);//跳转到指定路径
    void cdFather();//跳转到父路径
    void saveCatalog(char* filename);//目录结构保持至文件
    void loadCatalog(char* filenane);//将目录结构从文件载入
    void print(nowPosition D, int Depth, FILE* file);//向文件打印出目录结构
    void size(char* dirName);//打印当前目录下的文件个数
};