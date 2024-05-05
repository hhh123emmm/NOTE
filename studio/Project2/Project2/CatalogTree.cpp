#include"CatalogTree.h"
#include <malloc.h>
#include<iostream>
using namespace std;

catalogTree::catalogTree() {
    //����
    ptr tRoot = (TreeNode*)malloc(sizeof(TreeNode));
    tRoot->FirstChild = NULL;
    memset(tRoot->filename, 0, sizeof(tRoot->filename));
    tRoot->filename[0] = '/';
    tRoot->ifFile = false;
    tRoot->parent = NULL;
    tRoot->brother = NULL;
    tRoot->size = 0;
    root = tRoot;
    nowPtr = root;//��ǰ·��Ϊ��Ŀ¼   
}

void catalogTree::print(nowPosition D, int Depth, FILE* file)//���ļ���ӡĿ¼�ṹ
{
    ptr tmp;
    if (D != NULL) {
        for (int i = 0; i < Depth; i++) fprintf(file, "\t");//ͨ���Ʊ����ʾĿ¼�ṹ
        if (D->ifFile == true) fprintf(file, "%s	.f\n", D->filename);
        else {//Ŀ¼
            fprintf(file, "%s	.d\n", D->filename);
            for (tmp = D->FirstChild; tmp != NULL; tmp = tmp->brother) print(tmp, Depth + 1, file);//�ݹ��ӡ
        }
    }
}

void catalogTree::saveCatalog(char* filename) {
    FILE* file = fopen(filename, "w");//���ļ���д��
    if (file == NULL) {
        printf("	�ļ���ʧ��\n");
        return;
    }
    print(this->root, 0, file);//��Ŀ¼�ṹ�����ļ�
    fclose(file);
}

void inputCata(catalogTree* T, nowPosition D, char* preDir, int preDepth, FILE* file) {
    //���ļ���������
    char buf[120];
    char type[3];
    char subBuf[100];
    memset(buf, 0, sizeof(buf));
    memset(type, 0, sizeof(type));
    memset(subBuf, 0, sizeof subBuf);
    int i;
    int tmpNum = 0;
    fgets(buf, sizeof buf, file);//һ��һ����������
    if (strlen(buf) == 0) return;//�ļ�β������
    strncpy(type, buf + strlen(buf) - 3, 2);//��ȡ�����ļ����ļ�����Ŀ¼
    for (i = 0; buf[i] == '\t'; i++) {//���������ж���һ���ļ�
        tmpNum++;
    }
    char* c = new char;
    if (i == 0) inputCata(T, D, c, 0, file);//���û�����������ǵ�һ�и�·��
    else {
        //���Ǹ�·��
        strncpy(subBuf, buf + tmpNum, strlen(buf) - 4 - tmpNum);
        if (tmpNum > preDepth) {
            T->cdPath(preDir);
        }
        else if (tmpNum < preDepth) {//�������С����һ�У�ÿСһ�У���ǰָ����һ��cdfather
            for (int j = tmpNum; j < preDepth; j++) T->cdFather();
        }//Ĭ���������һ���ļ�����ͬһ���
        if (strcmp(type, ".d") == 0) {//�����Ŀ¼
            T->mkdir(subBuf, T->nowPtr);
        }
        else {//�ļ�
            T->mkfile(subBuf, T->nowPtr);
        }
        inputCata(T, T->nowPtr, subBuf, tmpNum, file);//��һ�У��ݹ�����
    }
}

void catalogTree::loadCatalog(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("    �ļ���ʧ�ܣ������ļ����Ƿ���ȷ\n");
        return;
    }
    char a[2] = "/";
    //inputCata(this,nowPtr,"/",0,file);
    inputCata(this, nowPtr, a, 0, file);
    fclose(file);//�ر�
    //cdPath("/");//???
    cdPath(a);
}

//�ݹ�������ǰλ�õ�·��
void findPath(catalogTree* a, nowPosition x) {
    if (x == a->root) {
        printf("/");
        return;
    }
    else {
        findPath(a, x->parent);
        printf("%s/\n", x->filename);
    }
}

void catalogTree::cd() {
    //�����ǰ��ľ���·��
    ptr x = nowPtr;
    findPath(this, x);
}

void catalogTree::cdPath(char* str) {
    //��ת��ָ��·��
    ptr tmp;
    if (str[0] == '/') {
        //��һ���ַ���֤���Ǿ���·��
        ptr t = root;
        const char* d = "/";
        char* p;
        p = strtok(str, d);//�ָ��ַ���
        bool flag;//�ж�·���Ƿ����
        while (p) {
            flag = false;
            for (tmp = t->FirstChild; tmp != NULL; tmp = tmp->brother) {
                if (strcmp(tmp->filename, p) == 0 && tmp->ifFile == false) {
                    t = tmp;
                    flag = true;
                    break;
                }
            }
            if (flag == false) {
                //�û�����·������
                printf("    û�и�����\n");
                return;
            }
            p = strtok(NULL, d);//?
        }
        nowPtr = t;
    }
    else {
        //���·��
        const char* d = "/";
        char* p;
        ptr t = nowPtr;
        p = strtok(str, d);
        bool flag;//
        while (p) {
            flag = false;
            for (tmp = t->FirstChild; tmp != NULL; tmp = tmp->brother) {
                if (strcmp(tmp->filename, p) == 0 && tmp->ifFile == false) {
                    t = tmp;
                    flag = true;
                    break;
                }
            }
            if (flag == false) {
                //�û�����·������
                printf("    û�и�����\n");
                return;
            }
            p = strtok(NULL, d);//?
        }
        nowPtr = t;
    }
}

void catalogTree::cdFather() {
    if (nowPtr == root) {
        printf("�ѵ���·����\n");
        return;
    }
    nowPtr = nowPtr->parent;
}

void catalogTree::ListDir() {
    //�г���ǰĿ¼�������ļ�
    nowPosition t = nowPtr;
    ptr tmp;
    for (tmp = t->FirstChild; tmp != NULL; tmp = tmp->brother) {
        if (tmp->ifFile) printf("    %s.f\n", tmp->filename);
        else printf("   %s.d\n", tmp->filename);
    }
}

//���´��뻹û��

void deletePtr(catalogTree* a, ptr t) {//ɾ��ĳ���ļ���Ŀ¼��ɾ��ָ��t��Ӧ�Ľڵ㼰�����к���
    ptr tmp;
    if (t->ifFile) {//���Ҫɾ�������ļ�
        tmp = t->parent->FirstChild;
        if (tmp == t) {//���ɾ�����ļ��Ǹ��׵ĵ�һ�����ӣ������׵Ķ���ָ��ָ����ļ����ֵܣ�Ȼ���ͷ�
            t->parent->FirstChild = tmp->brother;
            free(t);
            return;
        }

        //����ɾ�����ļ����Ǹ��׵ĵ�һ�����ӣ�ִ�������һ��ɾ���������ҵ��ýڵ��λ�ã��øýڵ��ǰ�����ֵ�ָ��ָ��ɾ��������һ���ֵܣ�Ȼ���ͷ�
        for (tmp = t->parent->FirstChild; tmp != NULL; tmp = tmp->brother) {
            if (t == tmp->brother) {
                tmp->brother = t->brother;
                free(t);
                return;
            }
        }
    }
    else {//���Ҫɾ������Ŀ¼
        if (t->FirstChild == NULL) {//�����Ŀ¼��û�к��ӣ��ļ���Ŀ¼������ֱ��ɾ��
            if (t == a->root) return;//��Ҫɾ�����Ǹ��ڵ㣬��ִ��ɾ����ֱ�ӷ���

            if (t->parent->FirstChild == t) {//�����Ŀ¼λ�ڸ��׽ڵ�ĵ�һ�����ӣ��򽫸��׵Ķ���ָ����Ϊ�գ�Ȼ���ͷ�
                t->parent->FirstChild = t->brother;
            }
            else
            {
                for (tmp = t->parent->FirstChild; tmp != NULL; tmp = tmp->brother) {//������ǵ�һ�����ӣ����ҵ��ýڵ��ǰ������ǰ�����ֵ�ָ��ָ��ýڵ���ֵܣ�Ȼ���ͷŸýڵ�
                    if (tmp->brother == t) {
                        tmp->brother = t->brother;
                        break;
                    }
                }
            }
            free(t);
        }
        else {//�����Ŀ¼���к��ӣ��ļ���Ŀ¼�����������һ�㣬���ж��亢�����ɾ����������ɾ��������ˣ����еݹ�ɾ��
            while (t->FirstChild != NULL) {//��û�ݹ鵽Ŀ¼������ײ�
                for (tmp = t->FirstChild; tmp != NULL; tmp = tmp->brother) {//�����²�����
                    if (tmp->brother == NULL) {
                        deletePtr(a, tmp);//�ݹ�ɾ����ɾ��tmp�ڵ㼰��n�����ӽڵ�
                        break;
                    }

                }
            }
            deletePtr(a, t);//���ɾ�����Լ����ڽ��亢�����Ӷ�ɾ����
        }
    }
}

void catalogTree::Delete(char* str) {//ɾ��

    //ɾ������
    nowPosition t;
    bool flag = false;
    for (t = nowPtr->FirstChild; t != NULL; t = t->brother) {
        if (strcmp(t->filename, str) == 0) {
            flag = true;
            break;
        }
    }
    if (flag == false) {
        printf("    û�и�Ŀ¼���ļ�\n");
        return;
    }
    deletePtr(this, t);

}

void catalogTree::mkdir(char* name, nowPosition t) {//�����ļ���

    ptr tmp;
    for (tmp = t->FirstChild; tmp != NULL; tmp = tmp->brother) {
        if (strcmp(tmp->filename, name) == 0) {//&&tmp->isFile == false
            cout << "   ���ܲ�����ͬ���ֵ�Ŀ¼���ļ�,����ʧ��" << '\n';
            return;
        }
    }

    tmp = (ptr)malloc(sizeof(struct TreeNode));//�������ڵ�
    tmp->parent = t;
    tmp->FirstChild = NULL;
    tmp->ifFile = false;//false��ʾ�ýڵ�ΪĿ¼
    tmp->size = 0;
    strcpy(tmp->filename, name);
    tmp->brother = t->FirstChild;
    t->FirstChild = tmp;

}

void catalogTree::mkfile(char* name, nowPosition t) {//�����ļ�
    ptr tmp;

    for (tmp = t->FirstChild; tmp != NULL; tmp = tmp->brother) {
        if (strcmp(tmp->filename, name) == 0) {//&& tmp->isFile == true
            cout << "   ���ܲ�����ͬ���ֵ��ļ�,����ʧ��" << '\n';
            return;
        }
    }

    tmp = (ptr)malloc(sizeof(struct TreeNode));//���������
    tmp->parent = t;
    tmp->FirstChild = NULL;
    tmp->ifFile = true;
    tmp->size = 1;
    strcpy(tmp->filename, name);
    tmp->brother = t->FirstChild;
    t->FirstChild = tmp;
    for (tmp = t; t != NULL; t = t->parent) {
        t->size++;
    }
}