#include"CatalogTree.h"
#include<bits/stdc++.h>
using namespace std;

catalogTree::catalogTree(){
    //构造
    ptr tRoot=(TreeNode*)malloc(sizeof(TreeNode));
    tRoot->FirstChild=NULL;
    memset(tRoot->filename,0,sizeof(tRoot->filename));
    tRoot->filename[0]='/';
    tRoot->ifFile=false;
    tRoot->parent=NULL;
    tRoot->brother=NULL;
    tRoot->size=0;
    root=tRoot;
    nowPtr=root;//当前路径为根目录   
}

void catalogTree::print(nowPosition D,int Depth,FILE *file)//向文件打印目录结构
{
    ptr tmp;
    if(D!=NULL){
        for(int i=0;i<Depth;i++) fprintf(file,"\t");//通过制表符演示目录结构
        if(D->ifFile==true) fprintf(file,"%s    .f\n",D->filename);
        else{//目录
            fprintf(file,"%s    .d\n",D->filename);
            for(tmp=D->FirstChild;tmp!=NULL;tmp=tmp->brother) print(tmp,Depth+1,file);//递归打印
        }
    }
}

bool catalogTree::saveCatalog(char *filename){
    FILE* file=fopen(filename,"w");//向文件中写入
    if(file==NULL){
        //printf("	文件打开失败\n");
        printf("    open file failed\n");
        return false;
    }
    print(this->root,0,file);//将目录结构存入文件
    fclose(file);
    return true;
}

void inputCata(catalogTree *T,nowPosition D,char *preDir,int preDepth,FILE *file){
    //将文件内容载入
    char buf[120];//存储一行
    char type[3];//f/d
    char subBuf[100];//存储子路径
    memset(buf,0,sizeof(buf));
    memset(type,0,sizeof(type));
    memset(subBuf,0,sizeof subBuf);
    int i;
    int tmpNum=0;
    fgets(buf,sizeof buf,file);//一行一行载入数据
    if(strlen(buf)==0) return;//文件尾，结束
    strncpy(type,buf+strlen(buf)-3,2);//获取该行文件是文件还是目录.d/.f
    for(i=0;buf[i]=='\t';i++){//计算缩进判断哪一级文件
        tmpNum++;
    }
    char * c=new char;//数组存储路径信息
    if(i==0) inputCata(T,D,c,0,file);//如果没有缩进，则是第一行根路径，不需要创建
    else{//否则新建
        //不是根路径
        strncpy(subBuf,buf+tmpNum,strlen(buf)-4-tmpNum);//拷贝除去缩进和文件类型信息后的部分到subBuf数组当中，前tmpNum为缩进
        if(tmpNum>preDepth){
            T->cdPath(preDir);//跳转到前置目录
        }else if(tmpNum<preDepth){//如果缩进小于上一行，每小一行，当前指针做一次cdfather，直到到达前置目录
            for(int j=tmpNum;j<preDepth;j++) T->cdFather();
        }//默认深度与上一行文件属于同一深度
        if(strcmp(type,".d")==0){//如果是目录
            T->mkdir(subBuf,T->nowPtr);//创建目录
        }else{//文件
            T->mkfile(subBuf,T->nowPtr);//创建文件
        }
        inputCata(T,T->nowPtr,subBuf,tmpNum,file);//下一行，递归输入
    }
}

bool catalogTree::loadCatalog(char *filename){
    FILE *file=fopen(filename,"r");
    if(file==NULL){
        //printf("    文件打开失败，请检查文件名是否正确\n");
        printf("    open file failed, check if the filename correct\n");
        return false;
    }
    char a[2]="/";//根目录
    //inputCata(this,nowPtr,"/",0,file);
    inputCata(this,nowPtr,a,0,file);//T,现在的位置，之前的目录和深度，读取文件
    fclose(file);//关闭
    //cdPath("/");//bug
    cdPath(a);//a是根目录，就回到根目录
    return true;
}

//递归搜索当前位置的路径
void findPath(catalogTree *a,nowPosition x){
    if(x==a->root){
        printf("/");
        return;
    }else{
        findPath(a,x->parent);
        printf("%s/\n",x->filename);
    }
}

void catalogTree::cd(){
    //输出当前项的绝对路径
    ptr x=nowPtr;
    findPath(this,x);
}

bool catalogTree::cdPath(char *str){
    //跳转到指定路径
    ptr tmp,t;
    if(str[0]=='/'){
        //第一个字符，证明是绝对路径
        t=root;
    }else{
        //相对路径
        t=nowPtr;
    }
    const char *d="/";
    char *p;
    p=strtok(str,d);//分隔字符串,将分隔的第一个字符串返回给p
    bool flag;//判断路径是否错误
    while(p){
        flag=false;
        for(tmp=t->FirstChild;tmp!=NULL;tmp=tmp->brother){
            if(strcmp(tmp->filename,p)==0&&tmp->ifFile==false){//目录
                t=tmp;
                flag=true;
                break;
            }
        }
        if(flag==false){
            //用户输入路径错误
            //printf("    没有该命令\n");
            //printf("    no such catalog\n");
            return false;
        }
        p=strtok(NULL,d);//继续分隔字符串，返回下一个节点给p
    }
    nowPtr=t;
    return true;
}

void catalogTree::cdFather(){
    if(nowPtr==root){
        //printf("已到根路径！\n");
        printf("already the root.\n");
        return;
    }
    nowPtr=nowPtr->parent;
}

void catalogTree::ListDir(){
    //列出当前目录下所有文件
    nowPosition t=nowPtr;
    ptr tmp;
    for(tmp=t->FirstChild;tmp!=NULL;tmp=tmp->brother){
        if(tmp->ifFile) printf("    %s.f\n",tmp->filename);
        else printf("   %s.d\n",tmp->filename);
    }
}

void catalogTree::size(char *dirName){
    nowPosition t;
    bool flag=false;
    for(t=nowPtr->FirstChild;t!=NULL;t=t->brother){
        if(strcmp(t->filename,dirName)==0){
            flag=true;
            break;
        }
    }
    if((strcmp(dirName,"/")==0)) flag=true;//真
    if(flag==false){
        printf("    no such catalog or filename\n");
        return;
    }else{
        if(strcmp(dirName,"/")==0) printf("size of %s : %d\n",dirName,root->size);
        else printf("sizeof %s : %d\n",dirName,t->size);
    }
}

void deletePtr(catalogTree *a, ptr t) {//删除某个文件或目录，删除指针t对应的节点及其所有孩子
	ptr tmp;
	if (t->ifFile) {//如果要删除的是文件
		tmp = t->parent->FirstChild;
		if (tmp == t) {//如果删除的文件是父亲的第一个儿子，将父亲的儿子指针指向该文件的兄弟，然后释放
			t->parent->FirstChild = tmp->brother;
			free(t);
			return;
		}

		//否则，删除的文件不是父亲的第一个儿子，执行链表的一般删除操作，找到该节点的位置，让该节点的前驱的兄弟指针指向删除结点的下一个兄弟，然后释放
		for (tmp = t->parent->FirstChild; tmp != NULL; tmp = tmp->brother) {
			if (t == tmp->brother) {
				tmp->brother = t->brother;
				free(t);
				return;
			}
		}

        for (tmp = t; t != NULL; t = t->parent) {
		t->size--;//更新size
	    }
	}
	else {//如果要删除的是目录
		if (t->FirstChild == NULL) {//如果该目录下没有孩子（文件或目录），则直接删除
			if (t == a->root) return;//若要删除的是根节点，不执行删除，直接返回

			if (t->parent->FirstChild == t) {//如果该目录位于父亲节点的第一个儿子，则将父亲的儿子指针置为空，然后释放
				t->parent->FirstChild = t->brother;
			}
			else
			{
				for (tmp = t->parent->FirstChild; tmp != NULL; tmp = tmp->brother) {//如果不是第一个儿子，则找到该节点的前驱，将前驱的兄弟指针指向该节点的兄弟，然后释放该节点
					if (tmp->brother == t) {
						tmp->brother = t->brother;
						break;
					}
				}
			}
			free(t);
		}
		else {//如果该目录下有孩子（文件或目录），则访问下一层，再判断其孩子如何删除（并进行删除），如此，进行递归删除
			while (t->FirstChild != NULL) {//还没递归到目录树的最底层
				for (tmp = t->FirstChild; tmp != NULL; tmp = tmp->brother) {//访问下层链表，
					if (tmp->brother == NULL) {
						deletePtr(a, tmp);//递归删除，删除tmp节点及其n辈孩子节点
						break;
					}

				}
			}
			deletePtr(a, t);//最后删除它自己（在将其孩子孙子都删除后）
		}
	}
}

void catalogTree::Delete(char *str) {//删除

	//删除操作
	nowPosition t;
	bool flag = false;
	for (t = nowPtr->FirstChild; t != NULL; t = t->brother) {
		if (strcmp(t->filename, str) == 0) {
			flag = true;
			break;
		}
	}
	if (flag == false) {
		//printf("    没有该目录或文件\n");
        printf("    no such catalog or file\n");
		return;
	}
	deletePtr(this, t);

}

void catalogTree::mkdir(char *name, nowPosition t) {//创建文件夹

	ptr tmp;
	for (tmp = t->FirstChild; tmp != NULL; tmp = tmp->brother) {
		if (strcmp(tmp->filename, name) == 0) {//&&tmp->isFile == false
			//cout << "   不能产生相同名字的目录或文件,创建失败" << '\n';
            cout<<" cant produce same catalog or file, create failed\n";
			return;
		}
	}

	tmp = (ptr)malloc(sizeof(struct TreeNode));//创建树节点
	tmp->parent = t;
	tmp->FirstChild = NULL;
	tmp->ifFile = false;//false表示该节点为目录
	tmp->size = 0;
	strcpy(tmp->filename, name);
	tmp->brother = t->FirstChild;
	t->FirstChild = tmp;

}

void catalogTree::mkfile(char *name, nowPosition t) {//创建文件
	ptr tmp;

	for (tmp = t->FirstChild; tmp != NULL; tmp = tmp->brother) {
		if (strcmp(tmp->filename, name) == 0) {//&& tmp->isFile == true
			//cout << "   不能产生相同名字的文件,创建失败" << '\n';
            cout<<" cant produce same catalog or file, create failed\n";
			return;
		}
	}

	tmp = (ptr)malloc(sizeof(struct TreeNode));//创建树结点
	tmp->parent = t;
	tmp->FirstChild = NULL;
	tmp->ifFile = true;
	tmp->size = 1;
	strcpy(tmp->filename, name);
	tmp->brother = t->FirstChild;
	t->FirstChild = tmp;
	for (tmp = t; t != NULL; t = t->parent) {
		t->size++;//更新size
	}
}