#pragma once
#include "CatalogTree.h"
#include<bits/stdc++.h>
using namespace std;

void start(){
    cout<<"Microsoft Windows [版本 10.0.22621.3447]\n";
    cout<<"(c) Microsoft Corporation。保留所有权利。\n";
    cout<<"menu virtual filesystem simulation\n";
    cout<<"dir          列出当前目录下的所有目录项\n";
    cout<<"cd           查看当前路径\n";
    cout<<"cd dir       当前目录变为str所表示路径的目录\n";
    cout<<"cd ..        当前目录变为当前目录的父目录\n";
    cout<<"mkdir str    在当前目录下创建一个名为str的子目录\n";
    cout<<"mkfile str   在当前目录下创建一个名为str的文件\n";
    cout<<"delete str   删除当前目录下名为str的目录或文件\n";
    cout<<"save *.dat   保存虚拟目录到*.dat文件中\n";
    cout<<"load *.dat   载入*.dat文件中的虚拟目录\n";
    cout<<"size str     查看当前某子目录下的文件数\n";
    cout<<"quit         退出\n";
}

void operate(catalogTree T){
    char s[1000];
    char subs[1000];//?
    while(true){
        T.cd();
        cout<<"->";
        memset(s,0,sizeof(s));
        memset(subs,0,sizeof(subs));
        gets_s(s,size(s));//?
        if(strlen(s)>3){
            if(s[0]=='c'&&s[1]=='d'){
                strncpy(subs,s+3,strlen(s)-3);
                if(strcmp(subs,"..")==0){
                    T.cdFather();//cd ..
                }else{//cd str
                    T.cdPath(subs);//cd str
                }
            }else if(strlen(s)>6 && s[0]=='m'&&s[1]=='k'&&s[2]=='d'&&s[3]=='i'&&s[4]=='r'){
                strncpy(subs,s+6,strlen(s)-6);
                T.mkdir(subs,T.nowPtr);
            }else if(strlen(s)>7 && s[0]=='m'&&s[1]=='k'&&s[2]=='f'&&s[3]=='i'&&s[4]=='l'&&s[5]=='e'){
                strncpy(subs,s+7,strlen(s)-7);
                T.mkfile(subs,T.nowPtr);
            }else if(strlen(s)>7 && s[0]=='d'&&s[1]=='e'&&s[2]=='l'&&s[3]=='e'&&s[4]=='t'&&s[5]=='e'){
                strncpy(subs,s+7,strlen(s)-7);
                T.Delete(subs);
            }else if(strlen(s)==4 && strcmp(s,"quit")==0){
                return ;
            }else if(strlen(s)==4 && strcmp(s,"help")==0){
                start();
            }else if(strlen(s)>5 && s[0]=='s'&&s[1]=='a'&&s[2]=='v'&&s[3]=='e'){
                strncpy(subs,s+5,strlen(s)-5);
                char filePath[100]="F:\\";
                strcat(filePath,subs);
                T.saveCatalog(filePath);
                T.print(T.root,0,stdout);//纯显示
                printf("载入成功\n");
            }else if(strlen(s)>5 && s[0]=='l'&&s[1]=='o'&&s[2]=='a'&&s[3]=='d'){
                strncpy(subs,s+5,strlen(s)-5);
                char filePath[100]="F:\\";
                strcat(filePath,subs);
                T.loadCatalog(filePath);
                T.print(T.root,0,stdout);
                printf("载入成功\n");
            }else if(strlen(s)>5 && s[0]=='s'&&s[1]=='i'&&s[2]=='z'&&s[3]=='e'){
                strncpy(subs,s+5,strlen(s)-5);
                T.size(subs);
            }else{
                printf("    没有此命令\n");
            }
        }else{
            if(strlen(s)==3){
                if(strcmp(s,"dir")==0){
                    T.ListDir();
                }else{
                    printf("    没有此命令\n");
                }
            }else if(strlen(s)==2){
                if(strcmp(s,"cd")==0){
                    T.cd();
                    printf("\n");
                }else printf("    没有此命令\n");
            }else if(strlen(s)==1){
                if(s[0]=='p') T.print(T.root,0,stdout);
                else printf("    没有此命令\n");
            }else printf("    没有此命令\n");
        }
    }
}