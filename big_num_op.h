#ifndef BIG_NUM_BIG_NUM_OP_H
#define BIG_NUM_BIG_NUM_OP_H

#include <cstdio>
#include <stdlib.h>
#include <cstring>
#include <cmath>
#include <conio.h>
#include <time.h>
#include <algorithm>
using namespace std;

//定义结点
typedef int ListData;
typedef struct dnode{
    ListData data;
    struct dnode *prior,*next;
}DblNode;
typedef DblNode *DblList;

//algorithm
void InitList(DblList &first);
void DestroyList(DblList &first);
void ClearList(DblList &first);
int ListLength(DblList first);
void TravelList(DblList first);
void PrtList(DblList first);
void InputInteger(DblList &first,DblList &second);
void newdnodeInset(DblList &p3,DblList &newdnode,DblList &result);
void judgeAdd(int temp,int &k,DblList &newdnode);
void addition(DblList &first,DblList &second,DblList &result);
int cmpInteger(DblList first,DblList second);
void subDnode(int len,DblList &first,DblList &second,DblList &result,int &i);
void judgeSub(int temp,int &k,DblList &newdnode);
void subtraction(DblList &first,DblList &second,DblList &result);
void judgeMultiply(int temp,int &k,DblList &newdnode);
void InitSpecial(DblList &first);
void mulDnode(DblList &result,DblList &assist,int t);
void multiplication(DblList &first,DblList &second,DblList &result);

//view.h
void prtWelcomeUI();  //欢迎界面
void prtMainUI();  //用户交互主界面
void prtInputFormatUI(int op);  //输出当前执行的运算

#endif //BIG_NUM_BIG_NUM_OP_H
