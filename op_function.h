#include "big_num_op.h"

//初始化带头结点的双向循环链表
void InitList(DblList &first){
    first=(DblNode *)malloc(sizeof(DblNode));  //创建头结点
    if(!first){
        printf("\n内存分配失败！\n");
        exit(1);
    }
    first->data=0;  //头结点存储该长整数的总位数，初始化为0
    first->prior=first->next=first;
}

//销毁双循环链表（销毁头节点）
void DestroyList(DblList &first){
    DblList q,p=first->next;
    while (p!=first){
        q=p;
        p=p->next;
        free(q);
    }
    free(first);
}

//清空带头结点的双循环链表（保留头结点）
void ClearList(DblList &first){
    DblList q,p=first->next;
    while (p!=first){
        q=p;
        p=p->next;
        free(q);
    }
    first->data=0;
    first->prior=first->next=first;
}

//计算带头结点的双向循环链表的长度
int ListLength(DblList first){
    DblList p=first->next;
    int count=0;
    while(p!=first){
        p=p->next;
        count++;
    }
    return count;
}

//测试用函数
//遍历循环链表
void TravelList(DblList first){
    printf("\n===========================TravelList_Testing============================\n");
    DblList p=first->next;
    while (p!=first){
        //注意此处的输出格式问题
        if(p->next==first)
            printf("%4d",p->data);
        else
            printf("%4d,",p->data);

        p=p->next;
    }
    printf(";\tthe number of node: %d\n",first->data);
    getchar();
    if(getch())return;
}

//按格式输出循环链表
void PrtList(DblList first){
    printf("\n==================================================================\n");
    DblList p=first->next;
    if (p->data==0) ;   //特殊情况只存在于数字"0"
    else if(first->data<0) printf("-");
    else if (first->data>0) printf("+");
    int flag_is_first_node=0;
    while (p!=first){
        if(ListLength(first)==1 && flag_is_first_node==0){//长度为1时，直接输出即可
            printf("%d",p->data);
            flag_is_first_node++;
            p=p->next;
            continue;
        }
        else if (flag_is_first_node==0){
            printf("%d,",p->data);//节点长度超过1，需要输出一个“,”
            flag_is_first_node++;
            p=p->next;//节点指针后移
            continue;//跳过下面的循环
        }
        else if(p->data==0){//特判：为“0”时，直接输出数字“0”
            printf("0");
            break;//直接跳出循环
        }
        if(p->next==first && flag_is_first_node!=0){ //注意此处的输出格式问题
            if(p->data>=1000)printf("%4d",p->data);
            if(p->data<1000 && p->data>=100)printf("0%d",p->data);
            if(p->data<100 && p->data>=10)printf("00%d",p->data);
            if(p->data<10)printf("000%d",p->data);
        }
        else{
            if(p->data>=1000)printf("%4d,",p->data);
            if(p->data<1000 && p->data>=100)printf("0%d,",p->data);
            if(p->data<100 && p->data>=10)printf("00%d,",p->data);
            if(p->data<10)printf("000%d,",p->data);
        }

        p=p->next;
    }
    printf(";\t该长整数有: %d个节点\n",abs(first->data));
    if(getch())return;
}

// 核心代码
//存储输入的长整数
void InputInteger(DblList &first,DblList &second){
    printf("请注意您的输入格式：(添加\";\"结束输入)\n");
    char str[3][8]={"1","2"};
    DblList assist; //辅助链表
    for (int i = 0; i < 2; ++i) {
        if(i==0)assist=first;
        else assist=second;
        printf("请输入第 %s 个长整数： ",str[i]);
        DblList newdnode,p;
        int temp,flag=1;
        char ch;
        scanf("%d",&temp);
        if(temp<0){  //读取第一个结点数据，处理正负数，存储的长整数的正负与头结点data的正负一致
            assist->data--;
            flag=0;
        }
        else assist->data++;
        //创建第一个结点并插入链尾
        newdnode=(DblNode *)malloc(sizeof(DblNode));
        newdnode->data=abs(temp);  //结点数值为正，符号位存于头结点，与头结点data域的正负一致
        newdnode->prior=assist;
        assist->next=newdnode;
        newdnode->next=assist;
        assist->prior=newdnode;

        p=newdnode;  //p为链尾结点

        scanf("%c",&ch);  //判断输入是否结束
        if(ch==';')continue;
        while (scanf("%d",&temp)){  //读取第二个结点到最后一个结点
            newdnode=(DblNode *)malloc(sizeof(DblNode));  //创建新结点并插入链尾
            newdnode->data=temp;
            newdnode->prior=p;
            p->next=newdnode;
            newdnode->next=assist;
            assist->prior=newdnode;

            if(flag)assist->data++;  //更新链的长度
            else assist->data--;
            p=newdnode;  //使p指向链尾
            scanf("%c",&ch);
            if(ch==';')break;
            else if(ch==',')continue;
            else {
                printf("\nInput Error!\n");
                getchar();
                if(getch())exit(0);
                return;
            }
        }
    }
    return;
}

//头结点的下一个位置插入新结点
//p3:指向result当前运算结点(初始化为链尾结点)
void newdnodeInset(DblList &p3,DblList &newdnode,DblList &result){
    p3->prior=newdnode;
    result->next=newdnode;
    newdnode->next=p3;
    newdnode->prior=result;
    p3=newdnode;
}

//初始化链表数值为 0
void InitSpecial(DblList &first){
    DblList newdnode=(DblNode *)malloc(sizeof(DblNode));
    newdnode->data=0;
    newdnode->next=newdnode->prior=first;
    first->next=first->prior=newdnode;
    first->data=1;
}

//加法进位处理
void judgeAdd(int temp,int &k,DblList &newdnode){
    if(temp/10000==0){
        newdnode->data=temp;
        k=0;
    }
    else{
        newdnode->data=temp%10000;
        //k=temp/10000;
        k=1;
    }
}

//加法
void addition(DblList &first,DblList &second,DblList &result){
    int len1=abs(first->data),len2=abs(second->data);
    int len=max(len1,len2);
    int smb1=first->data/abs(first->data),smb2=second->data/abs(second->data);  //取符号位（判断正负）
    //p1:指向first当前运算结点(初始化为链尾结点)，p2:指向second当前运算结点(初始化为链尾结点)
    DblList newdnode,p1=first->prior,p2=second->prior,p3=result;  //p3:指向result当前运算结点(初始化为链尾结点)

    if(smb1+smb2!=0){  //两数都为正的情况 或 两数都为负的情况（负的情况可以转换为正的情况计算）
        int k=0,temp,i;  //k:记录进位  temp:储存计算的临时结果
        for (i = 0; i < len; i++) {  //从最低位开始计算（即从链尾开始向前求加）
            newdnode=(DblNode *)malloc(sizeof(DblNode));
            if(p1!=first && p2!=second){  //如果两条链均未计算到头结点
                temp=p1->data+p2->data+k;
                judgeAdd(temp,k,newdnode);
                p1=p1->prior;   //使指针指向下一个要计算的结点（指向高位）
                p2=p2->prior;   //使指针指向下一个要计算的结点（指向高位）
            }
            else if(p1!=first && p2==second){  //如果second链已算到头结点，而first未到
                temp=p1->data+k;
                judgeAdd(temp,k,newdnode);
                p1=p1->prior;  //使指针指向下一个要计算的结点（指向高位）
            }
            else if(p1==first && p2!=second){  //如果first链已算到头结点，而second未到
                temp=p2->data+k;
                judgeAdd(temp,k,newdnode);
                p2=p2->prior;   //使指针指向下一个要计算的结点（指向高位）
            }
            newdnodeInset(p3,newdnode,result);  //头结点的下一个位置插入新结点
        }
        while(k){  //处理最高位计算需要进位的情况
            newdnode=(DblNode *)malloc(sizeof(DblNode));
            i++;
            temp=k;
            judgeAdd(temp,k,newdnode);  //判断是否需要进位
            newdnodeInset(p3,newdnode,result);  //头结点的下一个位置插入新结点
        }
        //两数为正的情况
        if(smb1+smb2>0)result->data=i; //储存链表长度（数位总数）,结果的正负与该值一致
        //两数为负的情况
        if(smb1+smb2<0)result->data=-i;  //储存链表长度（数位总数）,结果的正负与该值一致
        return;
    }

    if(smb1+smb2==0){  //一正一负的情况，交由减法函数进行处理
        if(smb1>0){  //first为正
            second->data=abs(second->data);
            subtraction(first,second,result);
            second->data=-second->data;  //恢复second的符号位
        }
        else{
            first->data=abs(first->data);
            subtraction(second,first,result);
            first->data=-first->data;  //恢复first的符号位
        }
        return;
    }
}

//减法借位处理
void judgeSub(int temp,int &k,DblList &newdnode){
    if(temp>=0){  //不需要借位
        newdnode->data=temp;
        k=0;
    }
    else{  //需要借位
        newdnode->data=temp+10000;
        k=1;
    }
}

//比较长度相等的两个数，哪个较大
int cmpInteger(DblList first,DblList second){
    DblList p1=first->next,p2=second->next;
    while(p1!=first){
        if(p1->data==p2->data){
            p1=p1->next;
            p2=p2->next;
            continue;
        }
        else if(p1->data>p2->data)return 1;
        else if(p1->data<p2->data)return -1;
    }
    return 0;
}

//减法结点数值相减处理
void subDnode(int len,DblList &first,DblList &second,DblList &result,int &i){  //函数调用时，fisrt传入值比second传入大
    DblList newdnode,p1=first->prior,p2=second->prior,p3=result;  //first和second的计算均从链尾结点开始（即从最低位开始计算）
    int temp,k=0;  //k:初始借位为0
    for (i = 0; i < len; i++) {  //循环次数为两个数的最大长度
        newdnode=(DblNode *)malloc(sizeof(DblNode));
        if(p1!=first && p2!=second){  //如果两个指针均未到头结点
            temp=p1->data-p2->data-k;
            judgeSub(temp,k,newdnode);  //判断是否需要借位，并且为新结点赋值
            p1=p1->prior;  //使指针指向下一个要计算的结点（指向高位）
            p2=p2->prior;  //使指针指向下一个要计算的结点（指向高位）
        }
        else {  //如果p2已到头结点，而p1未到头结点
            temp=p1->data-k;
            judgeSub(temp,k,newdnode);
            p1=p1->prior;
        }
        //头结点的下一个位置插入新结点
        newdnodeInset(p3,newdnode,result);  //在结果链表result中插入计算得到的新结点
    }
}

//减法
void subtraction(DblList &first,DblList &second,DblList &result){
    int len1=abs(first->data),len2=abs(second->data);
    int smb1=first->data/abs(first->data),smb2=second->data/abs(second->data);  //取符号位（判断正负）
    //p3:指向result当前运算结点(初始化为链尾结点)
    DblList newdnode,p3=result;
    if(smb1+smb2>0){  //两数都为正的情况
        int i,flag;  //flag:标记结果的正负; i:标记结果的链表长度
        if(len1>len2){  //如果第一个数的长度大于第二个
            flag=1;  //相减结果为正
            subDnode(len1,first,second,result,i); //两数相减，结果存于result中
        }
        if(len1<len2){  //如果第二个数长度大于第一个
            flag=-1;  //相减结果为负
            subDnode(len2,second,first,result,i);  //两数相减，结果存于result中
        }
        if(len1==len2){  //如果两个数的长度相等，则比较哪个数更大
            if(cmpInteger(first,second)>0){  //如果first>second
                subDnode(len1,first,second,result,i); //调用时向参数first传入较大值first
                flag=1;  //相减结果为正
            }
            if(cmpInteger(first,second)<0){  //如果first<second
                subDnode(len2,second,first,result,i);  //调用时向参数first传入较大值second
                flag=-1;  //相减结果为负
            }
            if(cmpInteger(first,second)==0){  //如果两个数相等
                newdnode=(DblNode *)malloc(sizeof(DblNode));
                newdnode->data=0;  //相减结果为0；
                newdnodeInset(p3,newdnode,result);
                flag=1;  //计算结果为正
                i=1;
            }
        }
        //处理计算结果的正负及链表长度
        if(flag==1)result->data=i;
        else result->data=-i;
        return;
    }
    if(smb1+smb2<0){  //两个都为负的情况，可转换为两个为正相减的情况
        //转换为两个正数相减
        first->data=abs(first->data);
        second->data=abs(second->data);
        subtraction(second,first,result); //递归调用subtraction函数处理
        //恢复两个数符号位的正负情况
        first->data=-first->data;
        second->data=-second->data;
        return;
    }
    if(smb1+smb2==0){  //一正一负
        if(first->data>0 && second->data<0){  //first为正second为负的情况
            second->data=abs(second->data);  //转换为两个正数相加
            addition(first,second,result);  //交由加法函数进行处理
            second->data=-second->data;  //恢复原输入数据的符号位的正负情况
        }
        if(first->data<0 && second->data>0){  //second为正first为负的情况
            first->data=abs(first->data); //转换为两个正数相加
            addition(first,second,result);  //交由加法函数进行处理
            first->data=-first->data;  //恢复原输入数据的符号位的正负情况
            result->data=-result->data;  //两数相减结果为负
        }
        return;
    }
}

//乘法进位处理
void judgeMultiply(int temp,int &k,DblList &newdnode){
    if(temp/10000==0){
        newdnode->data=temp;
        k=0;
    }
    else{
        newdnode->data=temp%10000;
        k=temp/10000;
    }
}

//乘法结点相加处理
void mulDnode(DblList &result,DblList &assist,int t){
    DblList newdnode,p1=result,p2=assist->prior;
    int temp,k=0;
    while(t--)
        p1=p1->prior;  //处理起始相加位置
    while (p2!=assist){
        if(p1->prior!=result){
            temp=p1->prior->data+p2->data+k;
            judgeMultiply(temp,k,p1->prior);
            p1=p1->prior;
        }
        else{
            newdnode=(DblNode *)malloc(sizeof(DblNode));
            temp=p2->data+k;
            judgeMultiply(temp,k,newdnode);
            newdnodeInset(p1,newdnode,result);
            result->data++;
        }
        p2=p2->prior;
    }
    while(k) {  //处理最高位计算需要进位的情况
        newdnode = (DblNode *) malloc(sizeof(DblNode));
        temp = k;
        judgeMultiply(temp, k, newdnode); //判断是否需要进位
        //头结点的下一个位置插入新结点
        newdnodeInset(p1, newdnode, result);
        result->data++;
    }
}

//乘法
void multiplication(DblList &first,DblList &second,DblList &result){
    int smb1=first->data/abs(first->data),smb2=second->data/abs(second->data);  //取符号位（判断正负）

    DblList assist;  //辅助计算链表，存储临时计算结果
    InitList(assist);  //初始化辅助链表
    InitSpecial(result); //初始化result数值为0，长度为1；
    DblList newdnode,p1,p2=second->prior,p4;

    int temp,i=0,t; //temp:储存临时结果  t:处理起始相加位置
    while(p2!=second){
        t=i++;
        int k=0;
        p1=first->prior;
        p4=assist;
        while (p1!=first){
            newdnode=(DblNode *)malloc(sizeof(DblNode));
            temp=p2->data*p1->data+k;
            judgeMultiply(temp,k,newdnode);
            newdnodeInset(p4,newdnode,assist);

            assist->data++;  //每添加一个新的结点，辅助链表长度+1
            p1=p1->prior;
        }
        p2=p2->prior;
        while(k){  //处理最高位计算需要进位的情况
            newdnode=(DblNode *)malloc(sizeof(DblNode));
            temp=k;
            judgeMultiply(temp,k,newdnode); //判断是否需要进位
            //头结点的下一个位置插入新结点
            newdnodeInset(p4,newdnode,assist);
            assist->data++;
        }
        mulDnode(result,assist,t);
        ClearList(assist);
    }
    if(smb1+smb2==0)result->data=-result->data;
    else result->data=abs(result->data);
    return;
}
