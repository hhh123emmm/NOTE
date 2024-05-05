#pragma once
#include <cstdio>
using namespace std;

struct TreeNode {
    //���ڵ�
    TreeNode* parent;//��ָ��
    TreeNode* FirstChild;//��һ������
    TreeNode* brother;//�ֵ�
    bool ifFile;//�ļ�/Ŀ¼
    char filename[100];//�ַ����洢���ڵ��Ӧ���ļ���Ŀ¼
    int depth;//��ǰ�ڵ�����
    int size;//��ǰ�ڵ����ļ�
};
typedef TreeNode* nowPosition;//��ǰλ��
typedef TreeNode* Tree;//���ڵ������ʾ������
typedef TreeNode* ptr;//ָ�����ڵ��ָ��

class catalogTree;//Ŀ¼��
void findPath(catalogTree* a, nowPosition x);//����λ��Ѱ��·��
void deletePtr(catalogTree* a, ptr t);//����λ��ɾ��

class catalogTree {
public:
    TreeNode* root;//��
    ptr nowPtr;//ָ��ǰ����λ��

    catalogTree();//���캯��
    ~catalogTree() {
        deletePtr(this, root);//ɾ����������
    }

    void mkdir(char* name, nowPosition t);//��t����Ŀ¼
    void mkfile(char* nae, nowPosition t);//��t�����ļ�
    void ListDir();//�г���ǰĿ¼�µ��ļ�
    void Delete(char* str);//ɾ��ĳ�ļ���Ŀ¼
    void cd();//��ӡ��ǰĿ¼·��
    void cdPath(char* str);//��ת��ָ��·��
    void cdFather();//��ת����·��
    void saveCatalog(char* filename);//Ŀ¼�ṹ�������ļ�
    void loadCatalog(char* filenane);//��Ŀ¼�ṹ���ļ�����
    void print(nowPosition D, int Depth, FILE* file);//���ļ���ӡ��Ŀ¼�ṹ
    void size(char* dirName);//��ӡ��ǰĿ¼�µ��ļ�����
};