#include"CatalogTree.h"
#include"CatalogTree.cpp"
#include <bits/stdc++.h>
const int t=0;
const string password="hello";

void help(){
    cout<<"Microsoft Windows [version 10.0.22621.3447]\n";
    cout<<"(c) Microsoft Corporation. save all powers。\n";
    cout<<"menu virtual filesystem simulation\n";
    cout<<"dir          list all catalogs under the current one\n";
    cout<<"cd           show current path\n";
    cout<<"cd dir       change the path as str\n";
    cout<<"cd ..        change the path as father\n";
    cout<<"mkdir str    create son catalog as str\n";
    cout<<"mkfile str   create son file as str\n";
    cout<<"delete str   delete file or catalog as str\n";
    cout<<"save *.dat   save virtual catalog to *.dat\n";
    cout<<"load *.dat   load virtual catalog in *.dat\n";
    cout<<"size str     show son catalog file num\n";
    cout<<"quit         exit\n";
    cout<<"help         help menu\n";
}

int main() {
    if(t==1){
        freopen("E:\\TEST\\DS3\\in0.txt","r",stdin);
        freopen("E:\\TEST\\DS3\\out0.txt","w",stdout);
    }
	catalogTree T;
	cout<<"Microsoft Windows [version 10.0.22621.3447]\n";
    cout<<"(c) Microsoft Corporation.save all powers.\n";
	char s[1000];
	char subs[1000];
	while (true) {
		T.cd();
		//printf("->");
		memset(s, 0, sizeof(s));
		memset(subs, 0, sizeof(subs));
		gets_s(s,sizeof s);
		if (strlen(s) > 3) {
			if (s[0] == 'c'&&s[1] == 'd') {//cd ..
				strncpy(subs, s + 3, strlen(s) - 3);
				if (strcmp(subs, "..") == 0) {
					T.cdFather();
				}
				else {//cd str
					if(T.cdPath(subs)) cout<<"Jump successfully\n";
				}
			}else if (strlen(s) > 6 && s[0] == 'm'&&s[1] == 'k'&&s[2] == 'd'&&s[3] == 'i'&&s[4] == 'r') {//mkdir str
				strncpy(subs, s + 6, strlen(s) - 6);
				T.mkdir(subs, T.nowPtr);
			}else if (strlen(s) > 7 && s[0] == 'm'&&s[1] == 'k'&&s[2] == 'f'&&s[3] == 'i'&&s[4] == 'l'&&s[5] == 'e') {//mkfile str
				strncpy(subs, s + 7, strlen(s) - 7);
				T.mkfile(subs, T.nowPtr);
			}else if (strlen(s) > 7 && s[0] == 'd'&&s[1] == 'e'&&s[2] == 'l'&&s[3] == 'e'&&s[4] == 't'&&s[5] == 'e') {//delete str
				string pw;
                cout<<"please enter the password\n";
                cin>>pw;
                if(pw!=password){
                    cout<<"wrong answer!\n";
                }else{
                strncpy(subs, s + 7, strlen(s) - 7);
				T.Delete(subs);
                }
			}else if (strlen(s) == 4 && strcmp(s, "quit") == 0) {//quit
				return 0;
			}else if (strlen(s) == 4 && strcmp(s, "help") == 0) {//help
				help();
			}else if (strlen(s) > 5 && s[0] == 's'&&s[1] == 'a'&&s[2] == 'v'&&s[3] == 'e') {//save
				strncpy(subs, s + 5, strlen(s) - 5);
				char filePath[100] = "E:\\Code\\projects\\ds3\\";
				strcat(filePath, subs);//拼接
				if(T.saveCatalog(filePath)){
				    T.print(T.root, 0, stdout);
				    //printf("保存成功\n");
                    printf("save successfully\n");
                }
			}else if (strlen(s) > 5 && s[0] == 'l'&&s[1] == 'o'&&s[2] == 'a'&&s[3] == 'd') {//load *.dat
				strncpy(subs, s + 5, strlen(s) - 5);
				char filePath[100] = "E:\\Code\\projects\\ds3\\";
				strcat(filePath, subs);
				if(T.loadCatalog(filePath)){
				    T.print(T.root, 0, stdout);
				    //printf("载入成功\n");
                    printf("load successfully\n");
                }
			}else if(strlen(s)>5 && s[0]=='s'&&s[1]=='i'&&s[2]=='z'&&s[3]=='e'){
                strncpy(subs,s+5,strlen(s)-5);
                T.size(subs);
			}else {
				//printf("    没有此命令\n");
                printf("    no such comand\n");
			}
		}else {
			if (strlen(s) == 3) {
				if (strcmp(s, "dir") == 0) {//dir
					T.ListDir();
				}
				else {
					//printf("    没有此命令\n");
                    printf("    no such comand\n");
				}
			}
			else if (strlen(s) == 2) {//cd
				if (strcmp(s, "cd") == 0) {
					T.cd();
					printf("\n");
				}
				else
					//printf("    没有此命令\n");
                    printf("    no such comand\n");
			}
			else if (strlen(s) == 1) {//p
				if (s[0] == 'p') {//打印目录结构
					T.print(T.root, 0, stdout);
				}
				else {
					//printf("    没有此命令\n");
                    printf("    no such comand\n");
				}
			}
			else {
				//printf("    没有此命令\n");
                printf("    no such comand\n");
			}
		}
	}
	return 0;
}