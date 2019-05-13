#include <iostream>

#define MAX 100

using namespace std;
typedef struct node TreeNode;

struct node{

/*
 * 结构体和共用体的区别在于：结构体的各个成员会占用不同的内存，互相之间没有影响；而共用体的所有成员占用同一
 * 内存，修改一个成员会影响其余所有成员。
 * 结构体占用的内存大于等于所有成员占用的内存的总和（成员之间可能会存在缝隙），共用体占用的内存等于最长的成
 * 占用的内存。共用体使用了内存覆盖技术，同一时刻只能保存一个成员的值，如果对新的成员赋值，就会把原来成员的
 * 覆盖掉。
*/
    union{
        char _operator; //运算符
        char data; //数据
    };

    TreeNode *leftchild;
    TreeNode *rightchild;
};

//树栈
typedef struct Tree_Stack{
    TreeNode *buf[MAX];
    int n;//指针的位置
}TreeStack;

//创建空栈
TreeStack *create_empty_stack()
{
    TreeStack *pstack;
    pstack = (TreeStack*)malloc(sizeof(TreeStack));
    pstack->n = -1;

    return pstack;
}

//入栈
void push_stack(TreeStack *p, TreeNode *node)
{
    p->n++;
    p->buf[p->n] = node;
}

//出栈
TreeNode *pop_stack(TreeStack *p)
{
    TreeNode *tem_node;
//    tem_node = (TreeNode*)malloc(sizeof (TreeNode));
    tem_node = p->buf[p->n];

    p->n--;
    return tem_node;
}

//判断树栈是否为空
bool is_empty(TreeStack *p)
{
    if(p->n == -1)
        return 0;
    else
        return 1;
}

//创建后缀表达式树
TreeNode *create_tree(char *str, TreeStack *p)
{
    int i = 0;
    TreeNode *current;
    TreeNode *right, *left;
    while(str[i]){
        if(str[i] >= 'a' && str[i] <= 'z'){
            //ASCII中, 0~9 的编码是 0x30~0x39, 所以当c在‘0'~'9'的范围中时，
            //c - '0' 就相当于计算c的实际数值
            current = (TreeNode*)malloc(sizeof(TreeNode));
            current->data = str[i];
            current->leftchild = nullptr;
            current->rightchild = nullptr;
            push_stack(p, current);
        }
        else{
            current = (TreeNode*)malloc(sizeof(TreeNode));
            current->_operator = str[i];
            right = pop_stack(p);
            left = pop_stack(p);
            current->leftchild = left;
            current->rightchild = right;
            push_stack(p, current);
        }
        i++;
    }
    return p->buf[p->n];
}

//打印节点
void print(TreeNode *p)
{
    //如果该节点左右孩子都为空则是叶子节点,打印字母.否则打印运算符
    if(p->leftchild == NULL && p->rightchild == NULL)
        printf("%c", p->data);
    else
        printf("%c", p->_operator);
}

//访问节点
int visit_node(TreeNode *p)
{
    print(p);
    return 0;
}

//先序遍历
void PreOrder(TreeNode *p)
{
    if(p != nullptr){
        visit_node(p);
        PreOrder(p->leftchild);
        PreOrder(p->rightchild);
    }
}

//中序遍历
void InOrder(TreeNode *p)
{
    if(p != nullptr){
        InOrder(p->leftchild);
        visit_node(p);
        InOrder(p->rightchild);
    }
}

//后序遍历
void PostOrder(TreeNode *p)
{
    if(p != nullptr){
        PostOrder(p->leftchild);
        PostOrder(p->rightchild);
        visit_node(p);
    }
}

int main()
{
    char buf[MAX];
    TreeStack *stack;
    TreeNode *node;

    //ab+cde+**
    scanf("%s", buf);
    stack = create_empty_stack();
    node = create_tree(buf, stack);

    printf("先序遍历:\n");
    PreOrder(node);
    printf("\n");

    printf("中序遍历:\n");
    InOrder(node);
    printf("\n");

    printf("后序遍历:\n");
    PostOrder(node);
    printf("\n");

    return 0;
}
