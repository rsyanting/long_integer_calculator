#include "big_num_op.h"
#include "op_function.h"
#include "view.h"
int main(){
    prtWelcomeUI();
    DblList first,second,result;
    char op;
    InitList(first);
    InitList(second);
    InitList(result);
    for (;;) {
        scanf("%c",&op);
        if(op=='0'){
            DestroyList(first);
            DestroyList(second);
            DestroyList(result);
            break;
        }
        if(op!='0'&&op>'3'){
            printf("\n\n输入的编号有误，请核对后再次输入！\n按任意键继续……");
            getch();
            system("cls");
            prtMainUI();
            continue;
        }
        switch (op){
            case '1':
                prtInputFormatUI(op);
                InputInteger(first,second);
                //TravelList(first); //testing 测试输入数据
                //TravelList(second);
                PrtList(first);
                PrtList(second);
                addition(first,second,result);
                printf("\n=============================运算结果=============================");
                PrtList(result);
                break;
            case '2':
                prtInputFormatUI(op);
                InputInteger(first,second);
                PrtList(first);
                PrtList(second);
                subtraction(first,second,result);
                printf("\n=============================运算结果==============================");
                PrtList(result);
                break;
            case '3':
                prtInputFormatUI(op);
                InputInteger(first,second);
                PrtList(first);
                PrtList(second);
                multiplication(first,second,result);
                printf("\n=============================运算结果===============================");
                PrtList(result);
                break;
//            default:
//                return 0;
        }
        ClearList(first);
        ClearList(second);
        ClearList(result);
        prtMainUI();
    }
    return 0;
}
