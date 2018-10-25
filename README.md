# 长整数计算器

## 使用的数据结构：双向循环链表

### 1.节点定义

```c++
//定义结点
typedef int ListData;
typedef struct dnode{
    ListData data;
    struct dnode *prior,*next;
}DblNode;
typedef DblNode *DblList;
```

### 2.数据存储

+ 长整数的正负和长度：存储于头节点的`data`域中，`data`初始化为`0`
	+ `data`域的正负代表输入长整数的正负
	+ `abs(data)`代表有几个节点存储
+ 每个节点存储`4位`整数，节点计算时，相当于是`万进制`
+ 每次输入的`4位`整数均插入到尾部

### 3.加法运算部分

#### 3.1 加法进位处理

```c++
void judgeAdd(int temp,int &k,DblList &newdnode){
    if(temp / 10000 == 0){
        newdnode->data = temp;
        k = 0;
    }
    else{
        newdnode->data = temp % 10000;
        k = 1;
    }
}
```

#### 3.2 加法运算

```c++
void addition(DblList &first,DblList &second,DblList &result){
    if 同正同负{
        if 同正{
            从尾节点开始，对应节点相加{
            	judgeAdd();
            }
            判断最高位是否需要进位
        }
        else{
            从尾节点开始，对应节点相加{
        		judgeAdd();
            }
            判断最高位是否需要进位
        }
    }
    else{
        //一正一负
        转到减法来处理
    }
}
```

### 4.减法运算部分

#### 4.1减法借位处理

```c++
void judgeSub(int temp,int &k,DblList &newdnode){
    if(temp >= 0){  //不需要借位
        newdnode->data = temp;
        k=0;
    }
    else{  //需要借位
        newdnode->data = temp + 10000;
        k = 1;
    }
}
```

#### 4.2 减法节点处理

```c++
void subDnode(int len,DblList &first,DblList &second,DblList &result,int &i)
{////函数调用时，fisrt传入值比second传入大
    从尾节点开始，对应节点相减{
        judgeSub();
    }
}
```

#### 4.3减法部分

```c++
void subtraction(DblList &first,DblList &second,DblList &result){
    if (两数皆为正数){
        if (len(fisrt) > len(second)){
            相减为正；
            subDnode(first,second);
        }
        else if(len(fisrt) < len(second)){
            相减为负数；
            subDnode(second,first);
        }
        else{ //节点数相同
            if (first > second){
            	相减为正
                subDnode(first,second);
            }
            if (first < second){
            	相减为负
                subDnode(second,first);
            }
        }
    }
    if (两数皆为负数){
    	转为两个正数相减；
        恢复符号位；
    } 
    if (一正一负){
        转为两个正数相加；
        恢复符号位；
    }
}
```

### 5.乘法运算部分

#### 5.1 乘法进位处理

```c++
void judgeMultiply(int temp,int &k,DblList &newdnode){
    if(temp / 10000 == 0){
        newdnode->data = temp;
        k = 0;
    }
    else{
        newdnode->dat a= temp % 10000;
        k = temp / 10000;//注意此处与加法不同
    }
}
```

#### 5.2 乘法节点处理

```

```



