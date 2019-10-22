//用顺序表写的计算器，只实现了带括号的多项运算

#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 50
typedef struct Stack
{
    int data[MAXSIZE];
    int top;
}Stack;

//创建栈
Stack* initStack()
{
    Stack* S =(Stack*)malloc(sizeof(Stack));
    S->top =-1;
    return S;
}

//判断栈是否已满 
bool isfull(Stack *S)
{
    if(S->top == MAXSIZE-1)
        return true;
    else
        return false;
}

//判断栈是否为空 
bool isempty(Stack *S)
{
    if(-1 == S->top)
        return true;
    else
        return false;
}

 //入栈操作，补充完整代码===============
bool push (Stack *S, int x)
{
//若满，不能入站
    if(isfull(S))
        return false;
    else{
    	//否则， 顶位置加1，素存入栈顶
        S->data[++S->top] = x;
        return true;
    }

}
//出栈操作，补充完整代码=================
int pop(Stack *S)
{
    int a;
    if(isempty(S))
        return false;
    else{
        a = S->data[S->top--];
        return a;
    }
}

//赋予运算符优先级
int priority(char op)
{
    switch(op)
    {
        case '(':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default :
            return 0;
    }
 }

 //计算值，并入栈。
void poppush(Stack *OP, Stack *NUM)
{
    char op;   //存储操作符
    int n1,n2,n=0;//分别存储操作数1，2，和结果
    // =================以下需要添加代码======================
        //1.操作符出栈
        op = pop(OP);
        //2.操作数1出栈
        n1 = pop(NUM);
        //3.操作数2出栈
        n2 = pop(NUM);
        //4.用分支结构进行四则运算
        switch(op){
        case '+':
            n = n2+n1;
        break;
        case '-':
            n = n2-n1;
            break;
        case '*':
            n = n2*n1;
            break;
        case '/':
            n = n2/n1;
            break;
        }
        //5.将计算结果入栈
        push(NUM, n);
  }

int expvalue(char *s)
{
    //1.创建操作数栈
    Stack *NUM = initStack();
    //2.创建运算符栈
    Stack *OP = initStack();
    while(*s != '\0' || OP->top != -1)//如果是数字字符
    {
        if(*s>='0' && *s<='9')
        {
            int x;
            //3.转换为整形，并存入x
            x = x * 10 + *s - '0';
            //4. x入操作数栈
            s++;

            if(*s < '0' || *s > '9'){
                push(NUM, x);
                x = 0;
            }
        }
        else{
        	//如果是运算符，且（运算符栈为空，或者顶栈运算符的优先级<当前运算符的优先级） 
            if(OP->top == -1 || (OP->data[OP->top] == '(' && *s != ')') || priority(*s) > priority(OP->data[OP->top])){
                push(OP, *s);
                s++;
                continue;
            }

			//如果顶栈运算符是"("而当前运算符为")" ,则将"("弹出 
            if(OP->data[OP->top] == '(' && *s == ')'){
                pop(OP);
                s++;
                continue;
            }

			//待入栈的运算符优先级 <= 栈顶运算符优先级
            if((*s == '\0' && OP->top != -1) || (*s == ')' && OP->data[OP->top] != '(') || priority(*s) <= priority(OP->data[OP->top])){
            	//6.计算值，并入栈
                poppush(OP, NUM);
                continue;
            }
        }
    }
    int n = NUM->data[NUM->top];
    //8.释放运算符栈
    free(OP);

    //9.释放操作符栈
    free(NUM); 
    return n;//返回结果
 }

void menu1()
{
    printf("-----------------------------\n");
    printf("      计算器的表达式求值\n");
    printf("-----------------------------\n");
    printf("                             \n");
    printf("功能：计算器表达式求值功能\n");
    printf("方法:采用双栈计算表达式\n");
    printf("-------------------------------\n");
}
 //主函数
int main()
{
    menu1();
    char exp[50];
    printf("\n请输入表达式： \n");
    gets(exp);
    printf("%s = %d\n\n",exp,expvalue(exp));
    return 0;
 }
 
